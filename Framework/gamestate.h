#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

// Local includes:

// Forward Declarations:
class BackBuffer;
class Game;

class GameState
{
	//Member Methods:
public:
	~GameState();

	virtual bool Initialise(Game* game) = 0;
	virtual void CleanUp() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Process(float deltaTime) = 0;
	virtual void Draw(BackBuffer& backBuffer) = 0;
	virtual void HandleEvents() = 0;   

	void ChangeState(GameState* state);

protected:
	GameState();

private:

	GameState(const GameState& gState);
	GameState& operator=(const GameState& gState);

	//Member Data:
public:
	Game* m_pGameEngine;

protected:


private:

};

#endif __GAMESTATE_H__
