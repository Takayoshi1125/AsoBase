#include"KeyCheck.h"
#include"StageSelectMenuUI.h"
#include "TopMenuUI.h"

TopMenuUI::TopMenuUI(GameScene* scene):PopupUIBase(scene)
{

}

void TopMenuUI::Init(Vector2 pos)
{
	PopupUIBase::Init(pos);

	mChoices.clear();
	mChoices.push_back("�X�e�[�W�ړ�");
	mChoices.push_back("�n�C�X�R�A�\��");

	mStageSelectMenuUI = new StageSelectMenuUI(mGameScene);
	int x = pos.x + mSize.x + 20;
	int y = pos.y;
	mStageSelectMenuUI->Init({x,y});

}

void TopMenuUI::Update(void)
{
	PopupUIBase::Update();

	if (keyTrgDown[KEY_P1_A])
	{
		mStageSelectMenuUI->Open();
	}

	if (mStageSelectMenuUI->IsOpen())
	{
		mStageSelectMenuUI->Update();
	}
}

void TopMenuUI::Draw(void)
{
	PopupUIBase::Draw();
	if (mStageSelectMenuUI->IsOpen())
	{
		mStageSelectMenuUI->Draw();
	}
}
