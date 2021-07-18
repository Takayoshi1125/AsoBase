#pragma once
#include"PopupUIBase.h"
class StageSelectMenuUI:public PopupUIBase
{
public:
	StageSelectMenuUI(GameScene* scene);

	void Init(Vector2 pos);
	void Update(void);
	void Draw(void);
};

