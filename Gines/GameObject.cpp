#include "GameObject.h"

GameObject::GameObject() {
	
}

GameObject::~GameObject() {
	//Free component memory
	while (!components.empty())
	{
		delete components.back();
		components.pop_back();
	}
}
void GameObject::update() {
	for (unsigned i = 0; i < components.size(); i++)
	{
		components[i]->update();
	}
}
void GameObject::render() {
	for (unsigned i = 0; i < components.size(); i++)
	{
		components[i]->render();
	}
}
