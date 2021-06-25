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

	//���
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

	//�ו��Ƃ̏Փ˔���
	Box* GetCollisionBox(Vector2 pos);

	//�ו��u����Ƃ̏Փ˔���
	Storage* GetCollisionStorage(Vector2 pos);

private:
	Stage* mStage;
	Unit* mUnit;
	Fader* mFader;
	
	//�f���^�^�C��
	float mTickCount;
	float mDeltTime;

	bool mIsFading;

	//���I�z��
	std::vector<Box*>mBoxes;

	std::vector<Storage*>mStorages;

	int mStageNo;

	//��ԊǗ�
	STATE mState;

	void ChangeState(void);

	void ChangeStage(void);

	void SetStage(void);

};
