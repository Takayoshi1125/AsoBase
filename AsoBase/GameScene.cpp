#include<vector>
#include<string>
#include<fstream>
#include <DxLib.h>
#include"Fader.h"
#include "KeyCheck.h"
#include "GameCommon.h"
#include "SceneManager.h"
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

	mFader->SetFade(Fader::FADE_STATE::FADE_IN);
	mIsFading = true;

	mStage = new Stage(this);
	mStage->Init(mStageNo);
	

	//SetStage();
	LoadGimicData();

}

/// <summary>
/// �X�V�X�e�b�v
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Update(void)
{
	

	//�~���b
	float tickCount = GetTickCount64();

	mDeltTime = (tickCount - mTickCount) / 1000.0f;
	mTickCount = tickCount;

	//mFader->Update();
	//if (mIsFading)
	//{
	//	Fader::FADE_STATE fState = mFader->GetState();
	//	switch (fState)
	//	{
	//	case Fader::FADE_STATE::FADE_IN:
	//		if (mFader->IsEnd())
	//		{
	//			mFader->SetFade(Fader::FADE_STATE::NONE);
	//			mIsFading = false;
	//			//ChangeStage();
	//		}
	//		break;
	//	case Fader::FADE_STATE::FADE_OUT:
	//		if (mFader->IsEnd())
	//		{
	//			//mFader->SetFade(Fader::FADE_STATE::FADE_IN);
	//			ChangeStage();
	//		}
	//		break;
	//	default:
	//		break;
	//	}
	//}
	/*else
	{
		
	}*/

	switch (mState)
	{
	case GameScene::STATE::GAME:
		UpdateGame();
		break;
	case GameScene::STATE::CLEAR:
		UpdateClear();
		break;
	case GameScene::STATE::CHANGE_STATE:
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
			ChangeStage();
			/*mFader->SetFade(Fader::FADE_STATE::FADE_OUT);
			mIsFading = true;*/
		}

	}
}

void GameScene::UpdateClear(void)
{
}

void GameScene::UpdateChangeStage(void)
{
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
	case GameScene::STATE::CHANGE_STATE:
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
}

void GameScene::DrawClear(void)
{
}

void GameScene::DrawChangeStage(void)
{
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

void GameScene::ChangeState(STATE state)
{
	mState = state;

	switch (mState)
	{
	case GameScene::STATE::GAME:
		break;
	case GameScene::STATE::CLEAR:
		
		break;
	case GameScene::STATE::CHANGE_STATE:
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


