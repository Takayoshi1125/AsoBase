#include<vector>
#include<DxLib.h>
#include"KeyCheck.h"
#include "PopupUIBase.h"

PopupUIBase::PopupUIBase(GameScene* scene)
{
	mGameScene = scene;
}

void PopupUIBase::Init(Vector2 pos)
{
	mPos = pos;
	mSize = { 100,200 };
	mSelectNo = 0;
	mIsOpene = false;

	//��:���ڂ����
	mChoices.clear();
	mChoices.push_back("aaa");
	mChoices.push_back("��Ԗ�");
	mChoices.push_back("3�Ԗ�");


}

void PopupUIBase::Update(void)
{
	int size = mChoices.size();
	if (size > 0)
	{
		//�I������ړ�
		if (keyTrgDown[KEY_P1_UP])
		{
			mSelectNo--;

			if (mSelectNo < 0)
			{
				mSelectNo = 0;
			}
		}

		//�I�������ړ�
		if (keyTrgDown[KEY_P1_DOWN])
		{
			mSelectNo++;

			if (mSelectNo > (size - 1))
			{
				mSelectNo = (size - 1);
			}
		}
	}
}

void PopupUIBase::Draw(void)
{
	//���̎��i
	DrawBox(mPos.x, mPos.y,
		mPos.x + mSize.x, mPos.y + mSize.y,
		0x000000, true);

	//�O�g
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

	DrawFormatString(
		mPos.x + MARGIN_SELECT_X,
		mPos.y + MARGIN_CHOICE_Y
		+ (MARGIN_CHOICE_HEIGHT * mSelectNo),
		0xffffff, "%s", "��"
	);

}

void PopupUIBase::Release(void)
{
}

void PopupUIBase::Open(void)
{
	mIsOpene = true;
}

void PopupUIBase::Close(void)
{
	mIsOpene = false;
}

bool PopupUIBase::IsOpen(void)
{
	return mIsOpene;
}
