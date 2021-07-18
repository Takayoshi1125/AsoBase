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

	//âº:çÄñ⁄ÇçÏÇÈ
	mChoices.clear();
	mChoices.push_back("aaa");
	mChoices.push_back("ìÒî‘ñ⁄");
	mChoices.push_back("3î‘ñ⁄");


}

void PopupUIBase::Update(void)
{
	int size = mChoices.size();
	if (size > 0)
	{
		//ëIëéàè„à⁄ìÆ
		if (keyTrgDown[KEY_P1_UP])
		{
			mSelectNo--;

			if (mSelectNo < 0)
			{
				mSelectNo = 0;
			}
		}

		//ëIëéàâ∫à⁄ìÆ
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
	//íÜÇÃéëäi
	DrawBox(mPos.x, mPos.y,
		mPos.x + mSize.x, mPos.y + mSize.y,
		0x000000, true);

	//äOòg
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
		0xffffff, "%s", "Å®"
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
