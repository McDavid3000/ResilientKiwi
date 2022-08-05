#ifndef __WALKINGSTATE_H_
#define __WALKINGSTATE_H_

#include <SDL.h>
#include "playerstates.h"

//Forward declarations
class BackBuffer;

class WalkingState : public PlayerStates
{
public:
	WalkingState();
	~WalkingState();

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
#endif __WALKINGSTATE_H_

