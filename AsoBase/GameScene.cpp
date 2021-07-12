#include<vector>
#include<string>
#include<fstream>
#include<stack>
#include <DxLib.h>
#include"Fader.h"
#include "KeyCheck.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include"TimeLimit.h"
#include"Stage.h"
#include"Unit.h"
#include"Box.h"
#include"Storage.h"
#include"Utility.h"
#include "GameScene.h"

GameScene::GameScene(SceneManager* manager) : SceneBase(manager)
{
	mStageNo = 1;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Init(void)
{
	mFader = new Fader();
	mFader->Init();


	mStage = new Stage(this);
	mStage->Init(mStageNo);
	
	mTimelimit = new TimeLimit(mSceneManager);
	mTimelimit->Start(60.0f);

	mImageC = LoadGraph("Image/Congratulations.png", true);

	/*while (!mHistoryBack.empty())
		mHistoryBack.pop();*/

	//mHistoryBack = std::stack<History>();

	//SetStage();
	LoadGimicData();
	LoadScore();

	mStepClear = 0.0f;

	mCntMove = 0;

	mBestScore = 6;

}

/// <summary>
/// 更新ステップ
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Update(void)
{
	

	switch (mState)
	{
	case GameScene::STATE::GAME:
		UpdateGame();
		break;
	case GameScene::STATE::CLEAR:
		UpdateClear();
		break;
	case GameScene::STATE::CHANGE_STAGE:
		UpdateChangeStage();
		break;
	}



	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::GAMEOVER, true);
	}

}

void GameScene::UpdateGame(void)
{
	mStage->UpDate();
	mUnit->Update();

	int size;

	size = mBoxes.size();
	for (int i = 0; i < size; i++)
	{
		mBoxes[i]->Update();
	}

	size = mStorages.size();
	for (int i = 0; i < size; i++)
	{
		mStorages[i]->Update();
	}

	//最後の操作履歴を取得
	//操作を戻す(Nキー)
	if (keyTrgDown[KEY_P1_A]
		&&mHistoryBack.size()>0
		&&mUnit->IsEnableBack())
	{
		History his = mHistoryBack.top();
		//何らかの条件をもとにboxに巻き戻し処理
		//boxの巻き戻し処理実装


		if (his.box != nullptr)
		{
			//size = mBoxes.size();
			//for (int i = 0; i < size; i++)
			{
				his.box->BackMove(his);
				//mBoxes[i]->BackMove(his);
			}
		}

		//最後の操作履歴をユニットに渡す
		mUnit->BackMove(his);

		//最後の操作履歴を削除
		mHistoryBack.pop();
	}


	//時間制限
	mTimelimit->Update();
	if(mTimelimit->IsTimeOver()==true)
	{
		mSceneManager->ChangeScene(SCENE_ID::GAMEOVER, true);
		return;
	}

	//クリア判定
	bool IsClear = true;
	size = mBoxes.size();
	for (int i = 0; i < size; i++)
	{
		//判定処理
		if (mBoxes[i]->IsStayStorage() == false)
		{
			IsClear = false;
			break;
		}
	}

	if (IsClear == true)
	{
		if (mStageNo >= MAX_STAGE_NO)
		{
			//ゲームオーバー画面へ遷移
			mSceneManager->ChangeScene(SCENE_ID::GAMEOVER, true);
		}
		else
		{
			//ChangeStage();
			
			
			ChangeState(STATE::CLEAR);
			return;
		}

	}
}

void GameScene::UpdateClear(void)
{
	mStepClear += mSceneManager->GetDeltaTime();
	float t = mStepClear / TIME_CLEAR_MSG;

	if (t >= 1.0f)
	{
		ChangeState(STATE::CHANGE_STAGE);
		return;
	}

}

void GameScene::UpdateChangeStage(void)
{
	mFader->Update();

	auto state = mFader->GetState();

	switch (state)
	{
	case Fader::FADE_STATE::FADE_OUT:
		//暗くする
		if (mFader->IsEnd() == true)
		{
			//ステージ切り替え
			ChangeStage();
			//徐々に明るくする
			mFader->SetFade(Fader::FADE_STATE::FADE_IN);
		}
		break;
	case Fader::FADE_STATE::FADE_IN:
		//明るくする
		if (mFader->IsEnd() == true)
		{
			mFader->SetFade(Fader::FADE_STATE::NONE);
			ChangeState(STATE::GAME);
		}
		break;
	}


	/*ChangeStage();
	ChangeState(STATE::GAME);*/
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name=""></param>
void GameScene::Draw(void)
{

	SetDrawScreen(DX_SCREEN_BACK);

	// 画面のクリア
	ClearDrawScreen();

	switch (mState)
	{
	case GameScene::STATE::GAME:
		DrawGame();
		break;
	case GameScene::STATE::CLEAR:
		DrawClear();
		break;
	case GameScene::STATE::CHANGE_STAGE:
		DrawChangeStage();
		break;
	}


}

void GameScene::DrawGame(void)
{
	int size;

	mStage->Render();

	size = mStorages.size();
	for (int i = 0; i < size; i++)
	{
		mStorages[i]->Draw();
	}

	mUnit->Draw();

	size = mBoxes.size();
	for (int i = 0; i < size; i++)
	{
		mBoxes[i]->Draw();
	}

	mTimelimit->Draw();

	DrawScore();
}

void GameScene::DrawClear(void)
{
	int x = 500;
	int y = 80;

	DrawGame();
	DrawGraph((SCREEN_SIZE_X - x) / 2, (SCREEN_SIZE_Y - y) / 2, mImageC, true);
}

void GameScene::DrawChangeStage(void)
{
	DrawGame();
}

void GameScene::DrawScore(void)
{
	int x1 = 0;
	int x2 = 0;
	int y2 = 60;
	int width = 100;
	int charX;
	int charY=20;

	x1 = 300;
	x2 = x1 + width;

	DrawBox(x1, 10, x1 + width, y2, 0xffffff, true);

	charX = ((x1 + x2) / 2) - 10;
	SetFontSize(32);

	SetFontSize(20);

	DrawFormatString(300, 0, 0x000000, "%d", mBestScore);

	DrawFormatString(100, 0, 0x000000, "%d", mCntMove);
}

/// <summary>
/// リソース解放
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Release(void)
{
	mStage->Release();
	delete mStage;

	mUnit->Release();
	delete mUnit;

	delete mFader;

	int size;

	size = mBoxes.size();
	for (int i = 0; i < size; i++)
	{
		mBoxes[i]->Release();
		delete mBoxes[i];
	}

	//動的配列のサイズを0に
	mBoxes.clear();

	size = mStorages.size();
	for (int i = 0; i < size; i++)
	{
		mStorages[i]->Release();
		delete mStorages[i];
	}


	//動的配列のサイズを0に
	mStorages.clear();

	DeleteGraph(mImageC);

	while (!mHistoryBack.empty())
	{
		/*auto tmp = mHistoryBack.top;
		tmp.Relese();
		delete tmp;*/
		mHistoryBack.pop();
	}
		


}

Stage* GameScene::GetStage(void)
{
	return mStage;
}

Box* GameScene::GetCollisionBox(Vector2 pos)
{

	Box* ret = nullptr;

	//mBoxesをすべて検索
	//引数と同じ座標の荷物が存在したら、
	//その荷物を返り値として返すようにする

	int size = mBoxes.size();
	for (int i = 0; i < size; i++)
	{
		if (mBoxes[i]->GetPos().x==pos.x
			&& mBoxes[i]->GetPos().y == pos.y)
		{
			ret= mBoxes[i];
		}
	}

	return ret;

}

Storage* GameScene::GetCollisionStorage(Vector2 pos)
{
	//引数の座標と一致する荷物置き場を検索
	//見つからなければ、nullptrを
	Storage* ret = nullptr;


	int size = mStorages.size();
	for (int i = 0; i < size; i++)
	{
		if (mStorages[i]->GetPos().x == pos.x
			&& mStorages[i]->GetPos().y == pos.y)
		{
			ret = mStorages[i];
			break;
		}
	}

	return ret;
}

std::string GameScene::GetCsvPathGround(int stageNo)
{
	std::string ret = "";

	ret += FILE_PATH_CSV;
	ret += std::to_string(stageNo);
	ret += "/"; 
	ret += FILE_NAME_GROUND;

	return ret;
}

std::string GameScene::GetCsvPathGimmick(int stageNo)
{
	std::string ret = "";

	ret += FILE_PATH_CSV;
	ret += std::to_string(stageNo);
	ret += "/";
	ret +=FILE_NAME_GIMMICK;

	return ret;
}

std::string GameScene::GetCsvPathScore()
{
	std::string ret = "";

	ret += "StageData/";
	ret += FILE_NAME_SCORE;

	return ret;
}

void GameScene::RegistHistory(DIR dir, Vector2 pos, Box* box)
{
	Vector2 boxPos{ 0,0 };
	if (box != nullptr)
	{
		boxPos = box->GetPos();
	}


	History his = { dir,pos,box,boxPos };

	mHistoryBack.push(his);

}

void GameScene::PlusCntMove(void)
{
	mCntMove += 1;
}

void GameScene::MinusCntMove(void)
{
	mCntMove -= 1;
}

void GameScene::ChangeState(STATE state)
{
	mState = state;

	switch (mState)
	{
	case GameScene::STATE::GAME:
		break;
	case GameScene::STATE::CLEAR:
		mStepClear = 0.0f;
		break;
	case GameScene::STATE::CHANGE_STAGE:
		mFader->SetFade(Fader::FADE_STATE::FADE_OUT);
		break;
	}
}

void GameScene::ChangeStage(void)
{
	Release();

	mStageNo++;

	Init();
}

void GameScene::SetStage(void)
{
	//荷物
	Box* tmpBox;

	//荷物置き
	Storage* tmpStorage;

	switch (mStageNo)
	{
	case 1:
	{
		//操作キャラ
		mUnit = new Unit(this);
		mUnit->Init(Vector2{ 10,10 });

		//荷物

		tmpBox = new Box(this);
		tmpBox->Init(Vector2{ 12,12 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init(Vector2{ 11,11 });
		mBoxes.push_back(tmpBox);

		//荷物置き
		
		tmpStorage = new Storage(this);
		tmpStorage->Init(Vector2{ 11,7 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init(Vector2{ 12,9 });
		mStorages.push_back(tmpStorage);
	}
	break;

	case 2:
	{
		//操作キャラ
		mUnit = new Unit(this);
		mUnit->Init(Vector2{ 10,10 });

		//荷物
		tmpBox = new Box(this);
		tmpBox->Init(Vector2{ 12,12 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init(Vector2{ 11,11 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init(Vector2{ 17,8 });
		mBoxes.push_back(tmpBox);

		//荷物置き
		tmpStorage = new Storage(this);
		tmpStorage->Init(Vector2{ 17,10 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init(Vector2{ 11,10 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init(Vector2{ 12,8 });
		mStorages.push_back(tmpStorage);
	}
	break;
	}

	
}

void GameScene::LoadGimicData(void)
{
	//荷物
	Box* tmpBox;

	//荷物置き
	Storage* tmpStorage;

	//ファイルパス取得
	std::string filePath = GetCsvPathGimmick(mStageNo);

	//ファイルを読み込む
	std::ifstream ifs(filePath);

	//1行ずつ読み込む
	int y = 0;
	std::string line;
	while (getline(ifs, line))
	{
		//Yで分割されたline


		std::vector<std::string>strvec =
			Utility::Split(line, ',');


		//Xで分割されたstrvec
		int size = strvec.size();
		for (int x = 0; x < size; x++)
		{
			int chipID = stoi(strvec[x]);

			switch (chipID)
			{
			case 4:
				
				//荷物
				tmpBox = new Box(this);
				tmpBox->Init(Vector2{ x,y });
				mBoxes.push_back(tmpBox);
				break;

			case 5:
				//荷物置き
				tmpStorage = new Storage(this);
				tmpStorage->Init(Vector2{ x,y });
				mStorages.push_back(tmpStorage);
					break;

			case 6:
				//操作キャラ
				mUnit = new Unit(this);
				mUnit->Init(Vector2{ x,y });
				break;
			}


		}

		int i = stoi(strvec[0]);

		y++;

	}

	if (true) {}

}

void GameScene::LoadScore(void)
{
	//ファイルパス取得
	std::string filePath = GetCsvPathScore();

	//ファイルを読み込む
	std::ifstream ifs(filePath);

	//1行ずつ読み込む
	std::string line;
	while (getline(ifs, line))
	{
		//Yで分割されたline

		std::vector<std::string>strvec =
			Utility::Split(line, ',');


		int stageNo = stoi(strvec[0]);
		int bestScore = stoi(strvec[1]);
		mBestScores.emplace(stageNo, bestScore);

		//int i = stoi(strvec[0]);


	}



}

int GameScene::GetBestScore(void)
{
	//現在のステージ
	mStageNo;
	//ステージごとのベストスコア
	mBestScores;

	//現在のステージのベストスコア
	return 0;
}


