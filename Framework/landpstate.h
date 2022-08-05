#ifndef __LANDPSTATE_H_
#define __LANDPSTATE_H_

#include <SDL.h>
#include "playerstates.h"

//Forward declarations
class BackBuffer;

class LandPState : public PlayerStates
{
public:
	LandPState();
	~LandPState();

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
#endif __LANDPSTATE_H_

