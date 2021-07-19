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
	mChoices.push_back("�X�e�[�W�ړ�");
	mChoices.push_back("�n�C�X�R�A�\��");

	mStageSelectMenuUI = new StageSelectMenuUI(mGameScene);
	int x = pos.x + mSize.x + 20;
	int y = pos.y;
	mStageSelectMenuUI->Init({x,y});

	//�n�C�X�R�A���
	mHighScoreMenuUI = new HighScoreMenuUI(mGameScene);
	mHighScoreMenuUI->Init({ x,y });
}

void TopMenuUI::Update(void)
{
	
	//�X�e�[�W�Z���N�g���j���[�\�����ɂ�
	//��󂪈ړ����Ȃ��悤��

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
