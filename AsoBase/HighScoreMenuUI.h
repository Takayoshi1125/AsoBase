#pragma once
#include<vector>
#include<string>
#include<map>
#include"PopupUIBase.h"
class HighScoreMenuUI:public PopupUIBase
{
public:
	HighScoreMenuUI(GameScene* scene);

	void Init(Vector2 pos);
	void Update(void);
	void Draw(void);

};

