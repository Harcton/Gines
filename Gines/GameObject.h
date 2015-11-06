#ifndef GameObject_h_
#define GameObject_h_

#include <vector>

class Sprite;
class Component;
class PhysicsComponent;
struct vector2 {
	int x;
	int y;
};

enum Components {
	Physics,
	asd,
	asdasd,
};

class GameObject
{
public:
	GameObject();
	~GameObject();

	void draw();
	void update();
	void addComponent(Component* component);
private:
	vector2 position;
	Sprite* sprite;
	std::vector<Component*> components;
};
#endif