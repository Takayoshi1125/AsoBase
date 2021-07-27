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
	int x2 = SCREEN_SIZE_X - BLOCK_SIZE;
	int width = 200;

	DrawBox(x2 - width, 10, x2, 60, 0x000000, true);

	float time = mLimitTime;
	int col = GetColor(30, 144, 255);
	
	if(mLimitTime<30.0f)
	{
		//col= GetColor(255, 0, 0);

		//DrawBox(0, 20, SCREEN_SIZE_X, 60, 0x00ffff, true);

		//SetFontSize(30);
		//DrawString(0, 20, "WARNING", 0x000000);

		//ƒTƒCƒŒƒ“
		float alpha = (sin(time*5.0f)+1.0f)*0.5f;
		alpha = alpha * 130.0f;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,alpha);

		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xaa0000, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
	SetFontSize(32);
	DrawFormatStringF(850, 20, col, "%5.2f", mLimitTime);
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
