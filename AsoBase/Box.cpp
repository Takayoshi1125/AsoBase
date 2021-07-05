#include<DxLib.h>
#include"Vector2.h"
#include"GameCommon.h"
#include"GameScene.h"
#include"SceneManager.h"
#include"Stage.h"
#include "Box.h"

Box::Box(GameScene* scene)
{
	mGameScene = scene;
	mSceneManager = scene->GetSceneManager();
}

void Box::Init(Vector2 mapPos)
{
	mImage = LoadGraph("Image/Box.png",true);

	mPos.x = mapPos.x * BLOCK_SIZE;
	mPos.y = mapPos.y * BLOCK_SIZE;

	mMvSPos = { 0,0 };
	mMvEPos = { 0,0 };

	mStepMove = 0.0f;

	mDir = DIR::DOWN;

	mIsStayStorage = false;

	ChangeState(STATE::IDLE);
}

void Box::Update(void)
{
	switch (mState)
	{
	case Box::STATE::IDLE:
		break;
	case Box::STATE::MOVE:
	case Box::STATE::BACK_MOVE:
	{
		//�o�ߎ��Ԃ��擾���āA�������Ԃ��v��
		mStepMove += mSceneManager->GetDeltaTime();

		//�o�ߗ����Z�o
		float t = mStepMove / TIME_MOVE;

		//���ɉ��������W(�J�n���W�`�I�����W)
		mPos = Vector2::Lerp(mMvSPos, mMvEPos, t);
		if (t >= 1.0f)
		{
			mPos = mMvEPos;
			ChangeState(STATE::IDLE);
			return;
		}
		break;
	}
	default:
		break;
	}


}

void Box::Draw(void)
{
	int x = GAME_AREA_X + mPos.x;
	int y = GAME_AREA_Y + mPos.y;

	if (mIsStayStorage == true)
	{
		DxLib::DrawGraph(x, y, mImage, true);

		//DxLib�̐F�̏�Z
		SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
		DxLib::DrawGraph(x, y, mImage, true);
		//�u�����h���[�h���I�t
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		DxLib::DrawGraph(x,y, mImage, true);
	}

	//DrawTest();
}

void Box::DrawTest(void)
{
	int miniSize = 4;
	int size = BLOCK_SIZE * miniSize;

	int img01 = MakeScreen(size, size, false);


	//�쐬�����`���Ԃ�`��Ώۂɂ���
	SetDrawScreen(img01);
	
	int c01 = 255 / (BLOCK_SIZE * 2);
	for (int y = 0; y < BLOCK_SIZE; y++)
	{
		for (int x = 0; x < BLOCK_SIZE; x++)
		{
			int tmp = c01*(x+y);
			DrawBox(
				x * miniSize, 
				y * miniSize,
				(x * miniSize) + miniSize,
				(y * miniSize) + miniSize,
				GetColor(tmp, tmp, tmp), true
			);

		}
	}

	//�`��Ώۂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	//����ʂɃI���W�i���̕`���Ԃ�\��
	DxLib::DrawGraph(20, 20, img01, true);

	int img02 = MakeScreen(size, size, false);
	
	SetDrawScreen(img02);
	int c02 = 255 /BLOCK_SIZE;
	for (int y = 0; y < BLOCK_SIZE; y++)
	{
		for (int x = 0; x < BLOCK_SIZE; x++)
		{
			int tmp = c02 * (x);
			DrawBox(
				x * miniSize,
				y * miniSize,
				(x * miniSize) + miniSize,
				(y * miniSize) + miniSize,
				GetColor(tmp, tmp, tmp), true
			);

		}
	}

	//�`��Ώۂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	//����ʂɃI���W�i���̕`���Ԃ�\��
	DxLib::DrawGraph(200, 20, img02, true);

	//--------------

	//�������̇@�@�F�̏�Z
	int imgMix01 = MakeScreen(size, size, false);
	SetDrawScreen(imgMix01);
	DxLib::DrawGraph(0, 0, img01, true);

	//DxLib�̐F�̏�Z
	SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
	DxLib::DrawGraph(0, 0, img02, true);
	//�u�����h���[�h���I�t
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�`��Ώۂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	DxLib::DrawGraph(400, 20, imgMix01, true);
	//-----------------

	//�������̓�
	//----------------------
	int imgMix02= MakeScreen(size, size, false);
	SetDrawScreen(imgMix02);

	for (int y = 0; y < BLOCK_SIZE; y++)
	{
		for (int x = 0; x < BLOCK_SIZE; x++)
		{
			float tmp1 = c01 * (x + y);
			float tmp2 = c02 * x;

			//�F�̏�Z
			float tmp = (tmp1 / 255.0f) * (tmp2 / 255.0f) * 255.0f;

			DrawBox(
				x * miniSize,
				y * miniSize,
				(x * miniSize) + miniSize,
				(y * miniSize) + miniSize,
				GetColor(tmp, tmp, tmp), true
			);

		}
	}

	//�`��Ώۂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	DxLib::DrawGraph(600, 20, imgMix02, true);


	//�������̇B�F�̉��Z
	
	int imgMix03 = MakeScreen(size, size, false);
	SetDrawScreen(imgMix03);
	DxLib::DrawGraph(0, 0, img01, true);

	//DxLib�̐F�̏�Z
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DxLib::DrawGraph(0, 0, img02, true);
	//�u�����h���[�h���I�t
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�`��Ώۂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	DxLib::DrawGraph(400, 200, imgMix03, true);


	//�������̇C�F�̉��Z
	int imgMix04 = MakeScreen(size, size, false);
	SetDrawScreen(imgMix04);

	for (int y = 0; y < BLOCK_SIZE; y++)
	{
		for (int x = 0; x < BLOCK_SIZE; x++)
		{
			float tmp1 = c01 * (x + y);
			float tmp2 = c02 * x;

			//�F�̉��Z
			float tmp = 
				((tmp1 / 255.0f) + (tmp2 / 255.0f)) * 255.0f;
			if (tmp > 255.0f)
			{
				tmp = 255.0f;
			}

			DrawBox(
				x * miniSize,
				y * miniSize,
				(x * miniSize) + miniSize,
				(y * miniSize) + miniSize,
				GetColor(tmp, tmp, tmp), true
			);

		}
	}

	//�`��Ώۂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	DxLib::DrawGraph(600, 200, imgMix04, true);

}

void Box::Release(void)
{
	DeleteGraph(mImage);
}

Vector2 Box::GetPos(void)
{
	return mPos;
}

void Box::Push(DIR dir)
{
	mDir = dir;

	ChangeState(STATE::MOVE);
}

bool Box::IsPossiblePush(DIR dir)
{
	mDir = dir;

	Vector2 mapPos;

	mapPos = { mPos.x / BLOCK_SIZE,mPos.y / BLOCK_SIZE };

	//Vector2 mvEPos = mPos;

	switch (mDir)
	{
	case DIR::DOWN:
		mapPos.y += 1;
		break;
	case DIR::LEFT:
		mapPos.x -= 1;
		break;
	case DIR::RIGHT:
		mapPos.x += 1;
		break;
	case DIR::UP:
		mapPos.y -= 1;
		break;
	case DIR::MAX:
		break;
	default:
		break;
	}

	if (mGameScene->GetStage()->IsCollision({mapPos}) == true)
	{
		return false;
	}

	Box* box = mGameScene->GetCollisionBox({mapPos.x*BLOCK_SIZE,mapPos.y * BLOCK_SIZE });
	if (box != nullptr)
	{
		return false;
	}

	return true;
}

bool Box::IsStayStorage(void)
{
	return mIsStayStorage;
}

void Box::BackMove(GameScene::History his)
{
	mHistory = his;
	ChangeState(STATE::BACK_MOVE);
}


void Box::ChangeState(STATE state)
{
	//��Ԃ�ύX
	mState = state;

	//��Ԃ��Ƃ̏�������
	switch (mState)
	{
	case Box::STATE::IDLE:
	{

		//�ו��u���ꔻ��
		Storage* storage = mGameScene->GetCollisionStorage(mPos);
		if (storage!=nullptr)
		{
			mIsStayStorage = true;
		}
		else
		{
			mIsStayStorage = false;
		}


		break; 
	}
	case Box::STATE::MOVE:
	{
		//���`�⊮�ɂ��ړ�
		//�o�ߎ��Ԃ�������
		mStepMove = 0.0f;
		//�ړ������W�����E���W��
		mMvSPos = mMvEPos = mPos;

		switch (mDir)
		{
		case DIR::DOWN:
			mMvEPos.y += BLOCK_SIZE;
			break;
		case DIR::LEFT:
			mMvEPos.x -= BLOCK_SIZE;
			break;
		case DIR::RIGHT:
			mMvEPos.x += BLOCK_SIZE;
			break;
		case DIR::UP:
			mMvEPos.y -= BLOCK_SIZE;
			break;
		case DIR::MAX:
			break;
		}
	}
	break;

	case Box::STATE::BACK_MOVE:
	{
		//�o�ߎ��Ԃ�������
		mStepMove = 0.0f;

		//
		//mHistory;
		mDir = mHistory.dir;

		mMvSPos = mMvEPos = mPos;

		mMvEPos = mHistory.boxPos;
	}
	break;
	}

}