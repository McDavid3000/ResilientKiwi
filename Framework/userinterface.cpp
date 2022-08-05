#include "userinterface.h"

UserInterface::UserInterface()
{
	
}

UserInterface::~UserInterface()
{
	for (auto component : components)
	{
		delete component;
		component = nullptr;
	}
}

void UserInterface::DrawInterface(BackBuffer& backBuffer)
{
	for (auto component : components)
	{
		component->Draw(backBuffer);
	}
}

void UserInterface::AddComponent(InterfaceComponent* component)
{
	components.push_back(component);
}

InterfaceComponent* UserInterface::HandleClick(int x, int y)
{
	for (auto component : components)
	{
		if (component->CheckClicked(x, y))
		 	return component;
	}
	return nullptr;
	
}
	


