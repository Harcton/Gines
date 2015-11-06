#ifndef Component_h_
#define Component_h_

class GameObject;

class Component
{
public:
	Component();
	~Component();

	void update();

	void setParent(GameObject* parent) { this->parent = parent; }
private:
	GameObject* parent;
};
#endif