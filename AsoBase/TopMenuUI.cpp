#include"KeyCheck.h"
#include"StageSelectMenuUI.h"
#include"HighScoreMenuUI.h"
#include"PopupUIBase.h"
#include "TopMenuUI.h"

TopMenuUI::TopMenuUI(GameScene* scene):PopupUIBase(scene)
{
	mGameScene = scene;
}

void TopMenuUI::Init(Vector2 pos)
{
	PopupUIBase::Init(pos);

	mChoices.clear();
	mChoices.push_back("ステージ移動");
	mChoices.push_back("ハイスコア表示");

	mStageSelectMenuUI = new StageSelectMenuUI(mGameScene);
	int x = pos.x + mSize.x + 20;
	int y = pos.y;
	mStageSelectMenuUI->Init({x,y});

	//ハイスコア画面
	mHighScoreMenuUI = new HighScoreMenuUI(mGameScene);
	mHighScoreMenuUI->Init({ x,y });
}

void TopMenuUI::Update(void)
{
	
	//ステージセレクトメニュー表示時には
	//矢印が移動しないように

	bool isOpne = mStageSelectMenuUI->IsOpen();
	if (isOpne == false)
	{
		isOpne = mHighScoreMenuUI->IsOpen();
	}
	if (isOpne)
	{

		if (mHighScoreMenuUI->IsOpen()==true)
		{
			mHighScoreMenuUI->Update();
		}
		if (mStageSelectMenuUI->IsOpen()==true)
		{
			mStageSelectMenuUI->Update();
		}


	}
	else
	{
		PopupUIBase::Update();

		if (keyTrgDown[KEY_P1_A])
		{
			switch (mSelectNo)
			{
			case 0:
				mStageSelectMenuUI->Open();
				break;
			case 1:
				mHighScoreMenuUI->Open();
				break;
			}
		}

	}


}

void TopMenuUI::Draw(void)
{
	PopupUIBase::Draw();
	if (mStageSelectMenuUI->IsOpen())
	{
		mStageSelectMenuUI->Draw();
	}

	if (mHighScoreMenuUI->IsOpen())
	{
		mHighScoreMenuUI->Draw();
	}
}
