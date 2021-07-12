#pragma once
#include<vector>
#include<string>
#include<stack>
#include<map>
#include"GameCommon.h"
#include"Vector2.h"
#include"SceneBase.h"
class SceneManager;
class TimeLimit;
class Fader;
class Stage;
class Unit;
class Box;
class Storage;

class GameScene : public SceneBase
{

public:

	static constexpr int MAX_STAGE_NO = 5;

	static constexpr float TIME_CLEAR_MSG = 3.0f;

	//���
	enum class STATE
	{
		GAME,
		CLEAR,
		CHANGE_STAGE
	};

	//�����߂��p�\����
	struct History
	{
		DIR dir;
		Vector2 unitPos;
		Box* box;
		Vector2 boxPos;
	};

	GameScene(SceneManager* manager);
	void Init(void) override;

	void Update(void) override;
	void UpdateGame(void);
	void UpdateClear(void);
	void UpdateChangeStage(void);

	void Draw(void) override;
	void DrawGame(void);
	void DrawClear(void);
	void DrawChangeStage(void);

	void DrawScore(void);

	void Release(void) override;

	Stage* GetStage(void);

	//�ו��Ƃ̏Փ˔���
	Box* GetCollisionBox(Vector2 pos);

	//�ו��u����Ƃ̏Փ˔���
	Storage* GetCollisionStorage(Vector2 pos);

	Fader* mFader;

	//�X�e�[�W�\���p�X���擾
	std::string GetCsvPathGround(int stageNo);

	//�M�~�b�N�\���p�X���擾
	std::string GetCsvPathGimmick(int stageNo);

	std::string GetCsvPathScore(void);

	//���엚���ɓo�^
	void RegistHistory(DIR dir, Vector2 pos, Box* box);

	void PlusCntMove(void);

	void MinusCntMove(void);

private:
	Stage* mStage;
	Unit* mUnit;
	
	TimeLimit* mTimelimit;

	//�N���A�摜
	int mImageC;

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

	//�����߂�
	std::stack<History> mHistoryBack;

	float mStepClear;

	//�ړ�����
	int mCntMove;

	//���݂̃X�e�[�W��Best�X�R�A
	int mBestScore;

	//�X�e�[�W���Ƃ�BestScore
	std::map<int, int>mBestScores;

	void ChangeState(STATE state);

	void ChangeStage(void);

	void SetStage(void);

	void LoadGimicData(void);

	void LoadScore(void);

	//���݂̃X�e�[�W��BestScore���擾
	int GetBestScore(void);

};
