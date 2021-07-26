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
	mSize = { 180,200 };
	mSelectNo = 0;
	mIsOpene = false;

	//仮:項目を作る
	mChoices.clear();
	/*mChoices.push_back("aaa");
	mChoices.push_back("二番目");
	mChoices.push_back("3番目");*/


}

void PopupUIBase::Update(void)
{
	if (keyTrgDown[KEY_P1_B])
	{
		Close();
	}

	int size = mChoices.size();
	if (size > 0)
	{
		//選択肢上移動
		if (keyTrgDown[KEY_P1_UP])
		{
			mSelectNo--;

			if (mSelectNo < 0)
			{
				mSelectNo = 0;
			}
		}

		//選択肢下移動
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

	DrawFormatString(
		mPos.x + MARGIN_SELECT_X,
		mPos.y + MARGIN_CHOICE_Y
		+ (MARGIN_CHOICE_HEIGHT * mSelectNo),
		0xffffff, "%s", "→"
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
