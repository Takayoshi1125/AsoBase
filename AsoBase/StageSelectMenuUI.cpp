#include<string>
#include"PopupUIBase.h"
#include"GameScene.h"
#include "StageSelectMenuUI.h"

StageSelectMenuUI::StageSelectMenuUI(GameScene* scene):PopupUIBase(scene)
{
}

void StageSelectMenuUI::Init(Vector2 pos)
{
	PopupUIBase::Init(pos);

	int stageNo=GameScene::MAX_STAGE_NO;
	for (int i = 0; i < stageNo; i++)
	{
		mChoices.push_back("ステージ" + std::to_string(i + 1));
	}
}

void StageSelectMenuUI::Update(void)
{
	PopupUIBase::Update();
}

void StageSelectMenuUI::Draw(void)
{
	PopupUIBase::Draw();
}
