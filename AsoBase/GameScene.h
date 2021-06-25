#pragma once
#include "GameCommon.h"
#include<vector>
#include"Vector2.h"

#include "SceneBase.h"
class SceneManager;
class Fader;
class Stage;
class Unit;
class Box;
class Storage;

class GameScene : public SceneBase
{

public:

	static constexpr int MAX_STAGE_NO = 2;

	//状態
	enum class STATE
	{
		GAME,
		CLEAR,
		CHANGE_STATE
	};

	GameScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	Stage* GetStage(void);

	//荷物との衝突判定
	Box* GetCollisionBox(Vector2 pos);

	//荷物置き場との衝突判定
	Storage* GetCollisionStorage(Vector2 pos);

private:
	Stage* mStage;
	Unit* mUnit;
	Fader* mFader;
	
	//デルタタイム
	float mTickCount;
	float mDeltTime;

	bool mIsFading;

	//動的配列
	std::vector<Box*>mBoxes;

	std::vector<Storage*>mStorages;

	int mStageNo;

	//状態管理
	STATE mState;

	void ChangeState(void);

	void ChangeStage(void);

	void SetStage(void);

};
