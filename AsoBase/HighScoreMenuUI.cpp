#include<DxLib.h>
#include"GameScene.h"
#include"PopupUIBase.h"
#include "HighScoreMenuUI.h"

HighScoreMenuUI::HighScoreMenuUI(GameScene* scene) :PopupUIBase(scene)
{
	mGameScene = scene;
}

void HighScoreMenuUI::Init(Vector2 pos)
{
	PopupUIBase::Init(pos);

	mChoices.clear();

}

void HighScoreMenuUI::Update(void)
{
	PopupUIBase::Update();

}

void HighScoreMenuUI::Draw(void)
{
	//PopupUIBase::Draw();
	//中の四角
	DrawBox(mPos.x, mPos.y,
		mPos.x + mSize.x, mPos.y + mSize.y,
		0x000000, true);

	//外枠
	DrawBox(mPos.x, mPos.y,
		mPos.x + mSize.x, mPos.y + mSize.y,
		0xffffff, false);

	SetFontSize(16);
	int size = mChoices.size();
	for (int i = 0; i < size; i++)
	{
		DrawFormatString(
			mPos.x + MARGIN_CHOICE_X,
			mPos.y + MARGIN_CHOICE_Y + (MARGIN_CHOICE_HEIGHT * i),
			0xffffff, "%s", mChoices[i].c_str()
		);
	}

	int stageNo = GameScene::MAX_STAGE_NO;

	std::map<int, int> hiScore = mGameScene->GetBestScores();

	int n = 0;
	int s = 0;


	/*if (0 < hiScore.count(stageNo))
	{
		std::map<int, int>::iterator it = hiScore.find(1);
		s = it->second;
	}*/

	for (int i = 1; i < stageNo+1; i++)
	{
		if (0 < hiScore.count(i))
		{
			std::map<int, int>::iterator it = hiScore.find(i);
			n = it->first;
			s = it->second;
		}
		DrawFormatString(300, 100+(16*i), 0xffffff, "ステージ%d:スコア%d点",n, s);
		//mChoices.push_back("ステージ" + std::to_string(i + 1)+":"+ std::to_string(s));
	}



}
