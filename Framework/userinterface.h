#pragma once
#include <list>

#include "interfacecomponent.h"

class UserInterface
{
public:
	UserInterface();
	~UserInterface();
	
	/*Draws all components in the interface*/
	void DrawInterface(BackBuffer& backBuffer);
	
	/*Adds a component to this interface*/
	void AddComponent(InterfaceComponent* component);
	
	/*Returns an interface component if given x and y coordinates are within the bounds of a component.
	 * Otherwise returns null pointer.
	 */
	InterfaceComponent* HandleClick(int x, int y);

private:
	
protected:
	std::list<InterfaceComponent*> components;

public:
private:
protected:
};

