//Local include

#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

class AnimatedSpriteManager;
// Forward Declarations:
class Player;
class StandingState;
class JumpingState;
class WalkingState;
class FallingState;
class LandPState;

class StateManager 
{
	// --- Member methods ---
public:
	StateManager();
	~StateManager();

	void Initialise(Player* player);

	//Get states
	StandingState* GetStandingState();
	JumpingState* GetJumpingState();
	WalkingState* GetWalkingState();

	FallingState * GetFallingState();

	LandPState * GetLandPState();
	   
protected:

private:

	// --- Member data ---
public:

protected:

private:
	StandingState* m_pStandingState;
	JumpingState* m_pJumpingState;
	WalkingState* m_pWalkingState;
	FallingState* m_pFallingState;
	LandPState* m_pLandPState;
};

#endif //__STATEMANAGER_H__