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
/// ������
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
/// �X�V�X�e�b�v
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

	//�Ō�̑��엚�����擾
	//�����߂�(N�L�[)
	if (keyTrgDown[KEY_P1_A]
		&&mHistoryBack.size()>0
		&&mUnit->IsEnableBack())
	{
		History his = mHistoryBack.top();
		//���炩�̏��������Ƃ�box�Ɋ����߂�����
		//box�̊����߂���������


		if (his.box != nullptr)
		{
			//size = mBoxes.size();
			//for (int i = 0; i < size; i++)
			{
				his.box->BackMove(his);
				//mBoxes[i]->BackMove(his);
			}
		}

		//�Ō�̑��엚�������j�b�g�ɓn��
		mUnit->BackMove(his);

		//�Ō�̑��엚�����폜
		mHistoryBack.pop();
	}


	//���Ԑ���
	mTimelimit->Update();
	if(mTimelimit->IsTimeOver()==true)
	{
		mSceneManager->ChangeScene(SCENE_ID::GAMEOVER, true);
		return;
	}

	//�N���A����
	bool IsClear = true;
	size = mBoxes.size();
	for (int i = 0; i < size; i++)
	{
		//���菈��
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
			//�Q�[���I�[�o�[��ʂ֑J��
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
		//�Â�����
		if (mFader->IsEnd() == true)
		{
			//�X�e�[�W�؂�ւ�
			ChangeStage();
			//���X�ɖ��邭����
			mFader->SetFade(Fader::FADE_STATE::FADE_IN);
		}
		break;
	case Fader::FADE_STATE::FADE_IN:
		//���邭����
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
/// �`�揈��
/// </summary>
/// <param name=""></param>
void GameScene::Draw(void)
{

	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ̃N���A
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
/// ���\�[�X���
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

	//���I�z��̃T�C�Y��0��
	mBoxes.clear();

	size = mStorages.size();
	for (int i = 0; i < size; i++)
	{
		mStorages[i]->Release();
		delete mStorages[i];
	}


	//���I�z��̃T�C�Y��0��
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

	//mBoxes�����ׂČ���
	//�����Ɠ������W�̉ו������݂�����A
	//���̉ו���Ԃ�l�Ƃ��ĕԂ��悤�ɂ���

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
	//�����̍��W�ƈ�v����ו��u���������
	//������Ȃ���΁Anullptr��
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
		if (mCntMove > mBestScore)
		{
			SaveScore();
		}
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
	//�ו�
	Box* tmpBox;

	//�ו��u��
	Storage* tmpStorage;

	switch (mStageNo)
	{
	case 1:
	{
		//����L����
		mUnit = new Unit(this);
		mUnit->Init(Vector2{ 10,10 });

		//�ו�

		tmpBox = new Box(this);
		tmpBox->Init(Vector2{ 12,12 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init(Vector2{ 11,11 });
		mBoxes.push_back(tmpBox);

		//�ו��u��
		
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
		//����L����
		mUnit = new Unit(this);
		mUnit->Init(Vector2{ 10,10 });

		//�ו�
		tmpBox = new Box(this);
		tmpBox->Init(Vector2{ 12,12 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init(Vector2{ 11,11 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init(Vector2{ 17,8 });
		mBoxes.push_back(tmpBox);

		//�ו��u��
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
	//�ו�
	Box* tmpBox;

	//�ו��u��
	Storage* tmpStorage;

	//�t�@�C���p�X�擾
	std::string filePath = GetCsvPathGimmick(mStageNo);

	//�t�@�C����ǂݍ���
	std::ifstream ifs(filePath);

	//1�s���ǂݍ���
	int y = 0;
	std::string line;
	while (getline(ifs, line))
	{
		//Y�ŕ������ꂽline


		std::vector<std::string>strvec =
			Utility::Split(line, ',');


		//X�ŕ������ꂽstrvec
		int size = strvec.size();
		for (int x = 0; x < size; x++)
		{
			int chipID = stoi(strvec[x]);

			switch (chipID)
			{
			case 4:
				
				//�ו�
				tmpBox = new Box(this);
				tmpBox->Init(Vector2{ x,y });
				mBoxes.push_back(tmpBox);
				break;

			case 5:
				//�ו��u��
				tmpStorage = new Storage(this);
				tmpStorage->Init(Vector2{ x,y });
				mStorages.push_back(tmpStorage);
					break;

			case 6:
				//����L����
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
	//�t�@�C���p�X�擾
	std::string filePath = GetCsvPathScore();

	//�t�@�C����ǂݍ���
	std::ifstream ifs(filePath);

	//1�s���ǂݍ���
	std::string line;
	while (getline(ifs, line))
	{
		//Y�ŕ������ꂽline

		std::vector<std::string>strvec =
			Utility::Split(line, ',');


		int stageNo = stoi(strvec[0]);
		int bestScore = stoi(strvec[1]);
		mBestScores.emplace(stageNo, bestScore);

		//int i = stoi(strvec[0]);


	}



}

void GameScene::SaveScore(void)
{
	//�����ŌĂяo��
	//BestScore>�X�e�[�W�N���A���̃X�R�A
	if (0 < mBestScores.count(mStageNo))
	{
		mBestScores[mStageNo] = mCntMove;
	}
	else
	{
		//map�̒���key���Ȃ��ꍇ
		mBestScores.emplace(mStageNo, mCntMove);
	}

	//�t�@�C���p�X�擾
	std::string filePath = GetCsvPathScore();

	std::ofstream ofs = std::ofstream(filePath);

	std::string line;
	for (std::pair<int, int>p : mBestScores)
	{
		line = "";
		line += std::to_string(p.first);
		line += ",";
		line += std::to_string(p.second);
		ofs << line << std::endl;
	}

	ofs.close();

}

int GameScene::GetBestScore(void)
{
	int ret = 999;


	if (0 < mBestScores.count(mStageNo))
	{
		std::map<int, int>::iterator it = mBestScores.find(mStageNo);
		ret = it->second;
	}

	return ret;

	//���݂̃X�e�[�W�̃x�X�g�X�R�A
}


