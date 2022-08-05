#ifndef __FALLINGSTATE_H_
#define __FALLINGSTATE_H_

#include <SDL.h>
#include "playerstates.h"

//Forward declarations
class BackBuffer;

class FallingState : public PlayerStates
{
public:
	FallingState();
	~FallingState();

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
#endif __FALLINGSTATE_H_

