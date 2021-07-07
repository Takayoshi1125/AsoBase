#include<DxLib.h>
#include<cmath>
#include"GameCommon.h"
#include"SceneManager.h"
#include "TimeLimit.h"

TimeLimit::TimeLimit(SceneManager* manager)
{
	mSceneManager = manager;
}

void TimeLimit::Start(float sec)
{
	mLimitTime = sec;
}

void TimeLimit::Update(void)
{
	mLimitTime-= mSceneManager->GetDeltaTime();
	if (mLimitTime < 0)
	{
		mLimitTime = 0;
	}
}

void TimeLimit::Draw(void)
{
	float time = mLimitTime;
	int col = GetColor(0, 0, 0);
	
	if(mLimitTime>55.0f)
	{
		col = GetColor(0, 0, 0);
	}
	else
	{
		col= GetColor(255, 0, 0);

		//ƒTƒCƒŒƒ“
		float alpha = (sin(time*5.0f)+1.0f)*0.5f;
		alpha = alpha * 130.0f;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,alpha);

		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xaa0000, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
	DrawFormatStringF(0, 0, col, "%5.2f", mLimitTime);
}

bool TimeLimit::IsTimeOver(void)
{
	int ret = false;

	if (mLimitTime <= 0)
	{
		ret = true;
	}

	return ret;
}
