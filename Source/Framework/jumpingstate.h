#ifndef __JUMPINGSTATE_H_
#define __JUMPINGSTATE_H_

#include <SDL.h>
#include "playerstates.h"

//Forward declarations
class BackBuffer;

class JumpingState : public PlayerStates
{
public:
	JumpingState();
	~JumpingState();

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
#endif __JUMPINGSTATE_H_

