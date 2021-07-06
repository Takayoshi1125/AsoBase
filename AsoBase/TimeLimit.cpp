#include<DxLib.h>
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
	int col = GetColor(0, 0, 0);
	if(mLimitTime>55.0f)
	{
		col = GetColor(0, 0, 0);
	}
	else
	{
		col= GetColor(255, 0, 0);

		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA,60);

		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

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
