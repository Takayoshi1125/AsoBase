#pragma once
#include<string>
#include<vector>
#include"Vector2.h"

class GameScene;

class PopupUIBase
{
public:

	//��ʕ`�掞�̒����l
	static constexpr int MARGIN_CHOICE_X = 30;
	static constexpr int MARGIN_CHOICE_Y = 5;
	static constexpr int MARGIN_CHOICE_HEIGHT = 5;

	static constexpr int MARGIN_SELECT_X = 5;

	PopupUIBase(GameScene* scene);

	//�I�[�o�[���C�h����֐��ɂ�virtual������
	virtual void Init(Vector2 pos);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);

	//���j���[�̊J��
	void Open(void);
	void Close(void);

	//���j���[���J���Ă��邩
	bool IsOpen(void);

private:

	GameScene* mGameScene;

	Vector2 mPos;
	Vector2 mSize;

	//���j���[���J���Ă��邩
	bool mIsOpene;

	//���j���[�̑I����
	std::vector<std::string>mChoice;

	//�I��No
	int mSelectMo;
};

