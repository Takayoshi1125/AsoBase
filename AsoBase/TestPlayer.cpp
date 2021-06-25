#include "TestPlayer.h"

void TestPlayer::Update(void)
{
	switch (mState) {
	case STATE::IDLE:
		break;
	case STATE::WALK:
		break;
	case STATE::RUN:
		break;
	case STATE::ATTACK:
		break;
	case STATE::DEAD:
		break;
	}
}

void TestPlayer::ChangeState(STATE state)
{
	//ó‘Ô‚ğ•ÏX
	mState = state;

	//ó‘Ô‚²‚Æ‚Ì‰Šúˆ—‚ğs‚¤
	switch (mState)
	{
	case TestPlayer::STATE::NONE:
		break;
	case TestPlayer::STATE::IDLE:
		break;
	case TestPlayer::STATE::WALK:
		break;
	case TestPlayer::STATE::RUN:
		break;
	case TestPlayer::STATE::ATTACK:
		break;
	case TestPlayer::STATE::DEAD:
		break;
	default:
		break;
	}
}
