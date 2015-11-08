#ifndef GameObject_h_
#define GameObject_h_

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Component.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void draw();
	void update();
	void addComponent(std::string componentName, Component* component);
	void removeComponent(std::string componentName);

	//Rotate object relative to current rotation
	void rotate(float rotate);

	//Set absolute rotation
	void rotation(float rotation);

	//Move object relative to current position
	void move(vector2 move);

	//Set absolute position
	void setPosition(vector2 position);

	//Uniform scale
	void scale(size_t scale);

	//Non-Uniform scale
	void scale(vector2 scale);

	//Gets
	vector2 getPosition() { return objectPosition; }
	float getRotation() { return objectRotation; }
	vector2 getScale() { return objectScale; }
private:
	vector2 objectPosition;
	float objectRotation;
	vector2 objectScale;
	std::vector<Component*> components;
	std::map<std::string, size_t> componentPosition;
};
#endif