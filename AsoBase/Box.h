#pragma once
#include"Vector2.h"
class GameScene;
class SceneManager;


class Box
{
public:
	//1マス当たりの時間
	static constexpr float TIME_MOVE = 0.4f;


	//状態
	enum class STATE
	{
		NONE,
		IDLE,
		MOVE
	};

	Box(GameScene* scene);

	void Init(Vector2 mapPos);
	void Update(void);
	void Draw(void);
	void DrawTest(void);
	void Release(void);

	//座標の取得
	Vector2 GetPos(void);

	//押し出し処理
	void Push(DIR dir);

	//荷物の移動先の衝突判定
	bool IsPossiblePush(DIR dir);

	bool IsStayStorage(void);

private:
	SceneManager* mSceneManager;
	GameScene* mGameScene;

	STATE mState;

	int mImage;

	//現在のスクリーン座標
	Vector2 mPos;

	//移動元座標
	Vector2 mMvSPos;

	//移動先座標
	Vector2 mMvEPos;

	//移動開始からの経過時間
	float mStepMove;

	//移動方向
	DIR mDir;

	//荷物置き場の上に設置されているか
	bool mIsStayStorage;

	//状態遷移
	void ChangeState(STATE state);

};

