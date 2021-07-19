#include<string>
#include"KeyCheck.h"
#include"PopupUIBase.h"
#include"GameScene.h"
#include "StageSelectMenuUI.h"

StageSelectMenuUI::StageSelectMenuUI(GameScene* scene):PopupUIBase(scene)
{
	mGameScene = scene;
}

void StageSelectMenuUI::Init(Vector2 pos)
{
	PopupUIBase::Init(pos);

	int stageNo=GameScene::MAX_STAGE_NO;
	for (int i = 0; i < stageNo; i++)
	{
		mChoices.push_back("�X�e�[�W" + std::to_string(i + 1));
	}
}

void StageSelectMenuUI::Update(void)
{
	PopupUIBase::Update();

	if (keyTrgDown[KEY_P1_A])
	{
		//�I�����ꂽ�X�e�[�W�֑J��
		mGameScene->ChangeSelectStage(mSelectNo+1);
		Close();
	}

}

void StageSelectMenuUI::Draw(void)
{
	PopupUIBase::Draw();
}
