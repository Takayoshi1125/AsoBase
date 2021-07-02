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

	//マップ座標をスクリーン座標へ変換
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
		//×
		//mState = STATE::MOVE;
		ChangeState(STATE::MOVE);
		return;
		}
		else if (keyNew[KEY_P1_LEFT])
		{
			mDir = DIR::LEFT;
			//×
			//mState = STATE::MOVE;
			ChangeState(STATE::MOVE);
			return;
		}
		else if (keyNew[KEY_P1_RIGHT])
		{
			mDir = DIR::RIGHT;
			//×
			//mState = STATE::MOVE;
			ChangeState(STATE::MOVE);
			return;
		}
		else if (keyNew[KEY_P1_UP])
		{
			mDir = DIR::UP;
			//×
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


	//移動方向に応じた画像の表示
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
	//移動時にアニメーション
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

void Unit::ChangeState(STATE state)
{
	//状態を変更
	mState = state;

	

	//状態ごとの初期処理
	switch (mState)
	{
	case Unit::STATE::IDLE:
		//mIsPushing = false;
		//mAniCnt = SPEED_SLOW_ANIM;
		break;
	case Unit::STATE::MOVE:
	{
		//経過時間を初期化
		mStepMove = 0.0f;
		//移動元座標を限界座標に
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
		Vector2 mapPos = {mMvEPos.x / BLOCK_SIZE, mMvEPos.y / BLOCK_SIZE };

		if (mGameScene->GetStage()->IsCollision(mapPos)==true)
		{
			mIsPushing = true;
			ChangeState(STATE::IDLE);
			return;
		}

		Box* box=mGameScene->GetCollisionBox(mMvEPos);
		if (box != nullptr)
		{
			//荷物が進行方向に移動できるかどうか
			if (box->IsPossiblePush(mDir)==true)
			{
				//ボックスに動く処理
				mIsPushing = true;
				box->Push(mDir);
			}
			else 
			{
				//ボックスに命令無
				mIsPushing = true;

				//ユニットも移動しない
				ChangeState(STATE::IDLE);
			}


		}
		else
		{
			mIsPushing = false;
		}

		//移動情報確定
		//---------------------

		if (mIsPushing == true)
		{
			//荷物押し出し〇
			mGameScene->RegistHistory(mDir, mMvSPos, box);
		}
		else
		{
			//荷物押し出し×
			mGameScene->RegistHistory(mDir, mMvSPos, nullptr);
		}
		//------------------------


		break;

	case Unit::STATE::BACK_MOVE:
		//経過時間を初期化
		mStepMove = 0.0f;

		//
		mHistory;

		mMvSPos;

		mMvEPos;

		break;
	}
	default:
		break;
	}
}
