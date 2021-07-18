#pragma once
#include"Vector2.h"
#include"PopupUIBase.h"
class GameScene;
class StageSelectMenuUI;

class TopMenuUI :public PopupUIBase
{
public:

	TopMenuUI(GameScene* scene);

	void Init(Vector2 pos);
	void Update(void);
	void Draw(void);

private:

	StageSelectMenuUI* mStageSelectMenuUI;

};

