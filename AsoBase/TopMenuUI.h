#pragma once
#include"PopupUIBase.h"
class GameScene;
class StageSelectMenuUI;
class HighScoreMenuUI;

class TopMenuUI :public PopupUIBase
{
public:

	TopMenuUI(GameScene* scene);

	void Init(Vector2 pos);
	void Update(void);
	void Draw(void);

private:

	StageSelectMenuUI* mStageSelectMenuUI;
	HighScoreMenuUI* mHighScoreMenuUI;

};

