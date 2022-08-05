#ifndef __STANDINGSTATE_H_
#define __STANDINGSTATE_H_

#include <SDL.h>
#include "playerstates.h"

//Forward declarations
class BackBuffer;

class StandingState : public PlayerStates
{
public:
	StandingState();
	~StandingState();

	void Initialise(Player* player);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void HandleInput(SDL_Keycode key);

protected:
private:

public:

protected:
private:

};
#endif __STANDINGSTATE_H_

