#include<DxLib.h>
#include"Vector2.h"
#include"GameCommon.h"
#include"KeyCheck.h"
#include"GameScene.h"
#include"SceneManager.h"
#include"Stage.h"
#include"Box.h"
#include "Unit.h"

Unit::Unit(GameScene* scene)
{
	mGameScene = scene;
	mSceneManager = scene->GetSceneManager();
}

void Unit::Init(Vector2 mapPos)
{
	LoadDivGraph("Image/Unit.png", 12, NUM_ANIM_X, NUM_ANIM_Y, IMG_SIZE,IMG_SIZE, &mUnitimg[0][0], true);

	LoadDivGraph("Image/UnitPush.png", 12, NUM_ANIM_X, NUM_ANIM_Y, IMG_SIZE, IMG_SIZE, &mImagesPush[0][0], true);

	//�}�b�v���W���X�N���[�����W�֕ϊ�
	mPos.x = mapPos.x * BLOCK_SIZE;
	mPos.y = mapPos.y * BLOCK_SIZE;

	mMvSPos = { 0,0 };
	mMvEPos = { 0,0 };

	mStepMove = 0.0f;

	mDir = DIR::DOWN;

	mAniCnt = 0;;

	mIsPushing = false;

	ChangeState(STATE::IDLE);
}

void Unit::Update(void)
{
	mAniCnt++;

	switch (mState)
	{
	case Unit::STATE::IDLE:

		mIsPushing = false;
		 if (keyNew[KEY_P1_DOWN])
		{
		mDir = DIR::DOWN;
		//�~
		//mState = STATE::MOVE;
		ChangeState(STATE::MOVE);
		return;
		}
		else if (keyNew[KEY_P1_LEFT])
		{
			mDir = DIR::LEFT;
			//�~
			//mState = STATE::MOVE;
			ChangeState(STATE::MOVE);
			return;
		}
		else if (keyNew[KEY_P1_RIGHT])
		{
			mDir = DIR::RIGHT;
			//�~
			//mState = STATE::MOVE;
			ChangeState(STATE::MOVE);
			return;
		}
		else if (keyNew[KEY_P1_UP])
		{
			mDir = DIR::UP;
			//�~
			//mState = STATE::MOVE;
			ChangeState(STATE::MOVE);
			return;
		}

		break;

	case Unit::STATE::MOVE:
	case Unit::STATE::BACK_MOVE:
	{
		mStepMove += mSceneManager->GetDeltaTime();
		float t = mStepMove / TIME_MOVE;
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

void Unit::Draw(void)
{
	int y = 0;

	//int animId=1;

	//switch (mState)
	//{
	//case Unit::STATE::IDLE:
	//	animId = 1;
	//	break;
	//case Unit::STATE::MOVE:
	//	//mAniCnt
	//	break;
	//default:
	//	break;
	//}


	//�ړ������ɉ������摜�̕\��
	switch (mDir)
	{
	case DIR::DOWN:
		y = 0;
		break;
	case DIR::LEFT:
		y = 1;
		break;
	case DIR::RIGHT:
		y = 2;
		break;
	case DIR::UP:
		y = 3;
		break;
	case DIR::MAX:
		break;
	default:
		break;
	}
	//�ړ����ɃA�j���[�V����
	int x = 0;
	

	x = mAniCnt/15 % 4;

	if (x == 3)
	{
		x = 1;
	}

	int image = -1;
	if (mIsPushing == true)
	{
		image = mImagesPush[y][x];
	}
	else
	{
		image = mUnitimg[y][x];
	}

	DrawGraph(mPos.x + GAME_AREA_X,mPos.y + GAME_AREA_Y, image, true);
}

void Unit::Release(void)
{
	for (int y = 0; y < NUM_ANIM_Y; y++)
	{
		for (int x = 0; x < NUM_ANIM_X; x++)
		{
			DeleteGraph(mUnitimg[y][x]);
			DeleteGraph(mImagesPush[y][x]);
		}
	}
}

void Unit::BackMove(GameScene::History his)
{
	mHistory = his;
	ChangeState(STATE::BACK_MOVE);
}

bool Unit::IsEnableBack(void)
{
	return mState==STATE::IDLE;
}

void Unit::ChangeState(STATE state)
{
	//��Ԃ�ύX
	mState = state;



	//��Ԃ��Ƃ̏�������
	switch (mState)
	{
	case Unit::STATE::IDLE:
		//mIsPushing = false;
		//mAniCnt = SPEED_SLOW_ANIM;
		break;
	case Unit::STATE::MOVE:
	{
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
		default:
			break;
		}

		//
		Vector2 mapPos = { mMvEPos.x / BLOCK_SIZE, mMvEPos.y / BLOCK_SIZE };

		if (mGameScene->GetStage()->IsCollision(mapPos) == true)
		{
			mIsPushing = true;
			ChangeState(STATE::IDLE);
			return;
		}

		Box* box = mGameScene->GetCollisionBox(mMvEPos);
		if (box != nullptr)
		{
			//�ו����i�s�����Ɉړ��ł��邩�ǂ���
			if (box->IsPossiblePush(mDir) == true)
			{
				//�{�b�N�X�ɓ�������
				mIsPushing = true;
				box->Push(mDir);
				//mGameScene->PlusCntMove();
			}
			else
			{
				//�{�b�N�X�ɖ��ߖ�
				mIsPushing = true;

				//���j�b�g���ړ����Ȃ�
				ChangeState(STATE::IDLE);
			}


		}
		else
		{
			mIsPushing = false;
			//mGameScene->PlusCntMove();
		}

		//�ړ����m��
		//---------------------

		if (mIsPushing == true)
		{
			//�ו������o���Z
			mGameScene->RegistHistory(mDir, mMvSPos, box);
			mGameScene->PlusCntMove();
		}
		else
		{
			//�ו������o���~
			mGameScene->RegistHistory(mDir, mMvSPos, nullptr);
			mGameScene->PlusCntMove();
		}
		//------------------------

	}
		break;
	
	case Unit::STATE::BACK_MOVE:
	{
		//�o�ߎ��Ԃ�������
		mStepMove = 0.0f;

		//
		//mHistory;
		mDir = mHistory.dir;

		mMvSPos=mMvEPos = mPos;

		mMvEPos = mHistory.unitPos;

		mGameScene->MinusCntMove();
	}
	break;

	default:
		break;

	}
}
