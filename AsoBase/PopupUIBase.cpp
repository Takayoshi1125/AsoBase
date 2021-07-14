#include<DxLib.h>
#include "PopupUIBase.h"

PopupUIBase::PopupUIBase(GameScene* scene)
{
}

void PopupUIBase::Init(Vector2 pos)
{
	mPos = pos;
	mSize = { 100,200 };

	mIsOpene = false;
}

void PopupUIBase::Update(void)
{
}

void PopupUIBase::Draw(void)
{
	//’†‚ÌŽ‘Ši
	DrawBox(mPos.x, mPos.y,
		mPos.x + mSize.x, mPos.y + mSize.y,
		0x000000, true);

	//ŠO˜g
	DrawBox(mPos.x, mPos.y,
		mPos.x + mSize.x, mPos.y + mSize.y,
		0xffffff, false);
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
