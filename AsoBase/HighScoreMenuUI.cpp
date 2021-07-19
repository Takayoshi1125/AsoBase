#include"PopupUIBase.h"
#include "HighScoreMenuUI.h"

HighScoreMenuUI::HighScoreMenuUI(GameScene* scene) :PopupUIBase(scene)
{

}

void HighScoreMenuUI::Init(Vector2 pos)
{
	PopupUIBase::Init(pos);

	mSize = { 180,100 };
}

void HighScoreMenuUI::Update(void)
{
	PopupUIBase::Update();

}

void HighScoreMenuUI::Draw(void)
{
	PopupUIBase::Draw();
}
