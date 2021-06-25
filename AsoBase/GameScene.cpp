#include<vector>
#include<string>
#include <DxLib.h>
#include"Fader.h"
#include "KeyCheck.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include"Stage.h"
#include"Unit.h"
#include"Box.h"
#include"Storage.h"-
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

	mFader->SetFade(Fader::FADE_STATE::FADE_IN);
	mIsFading = true;

	mStage = new Stage(this);
	mStage->Init(mStageNo);
	

	SetStage();

}

/// <summary>
/// 更新ステップ
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Update(void)
{
	//ミリ秒
	float tickCount = GetTickCount64();

	mDeltTime = (tickCount - mTickCount) / 1000.0f;
	mTickCount = tickCount;

	mFader->Update();
	if (mIsFading)
	{
		Fader::FADE_STATE fState = mFader->GetState();
		switch (fState)
		{
		case Fader::FADE_STATE::FADE_IN:
			if (mFader->IsEnd())
			{
				mFader->SetFade(Fader::FADE_STATE::NONE);
				mIsFading = false;
				//ChangeStage();
			}
			break;
		case Fader::FADE_STATE::FADE_OUT:
			if (mFader->IsEnd())
			{
				//mFader->SetFade(Fader::FADE_STATE::FADE_IN);
				ChangeStage();
			}
			break;
		default:
			break;
		}
	}
	else
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
				mFader->SetFade(Fader::FADE_STATE::FADE_OUT);
				mIsFading = true;
			}

		}
	}





	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::GAMEOVER, true);
	}

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

	mStage->Render();

	int size;

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

	return std::string();
}

void GameScene::ChangeState(void)
{
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


