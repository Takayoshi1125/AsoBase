#pragma once
#include<string>
#include<vector>
#include"Vector2.h"

class GameScene;

class PopupUIBase
{
public:

	//画面描画時の調整値
	static constexpr int MARGIN_CHOICE_X = 30;
	static constexpr int MARGIN_CHOICE_Y = 5;
	static constexpr int MARGIN_CHOICE_HEIGHT = 5;

	static constexpr int MARGIN_SELECT_X = 5;

	PopupUIBase(GameScene* scene);

	//オーバーライドする関数にはvirtualをつける
	virtual void Init(Vector2 pos);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);

	//メニューの開閉
	void Open(void);
	void Close(void);

	//メニューが開いているか
	bool IsOpen(void);

private:

	GameScene* mGameScene;

	Vector2 mPos;
	Vector2 mSize;

	//メニューが開いているか
	bool mIsOpene;

	//メニューの選択肢
	std::vector<std::string>mChoice;

	//選択No
	int mSelectMo;
};

