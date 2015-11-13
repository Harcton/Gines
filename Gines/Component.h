#ifndef Component_h_
#define Component_h_
#include <glm/vec2.hpp>
#include <iostream>

class GameObject;
class Component
{
public:
	Component(){}
	virtual ~Component(){};//Destructor hidden so that only removeComponent() or ~GameObject() can properly delete components
	virtual void update(){}
	virtual void render(){}

protected:
};

class MonoComponent : public Component
{
	//Go figure out a better name
	/*
	If you want a gameobject to have a maxinum of 1 instance of a specific component, 
	you can derive that component from MonoComponent instead of Component
	*/
};


class Transform : public MonoComponent
{
public:
	Transform();
	~Transform(){}

	void update();

	//Rotate object relative to current rotation
	void rotate(float rotate);
	//Set absolute rotation
	void setRotation(float newRotation);
	//Move object relative to current position
	void move(glm::vec2& move);
	//Set absolute position
	void setPosition(glm::vec2& position);
	//Non-Uniform scale
	void setScale(glm::vec2& scale);

	//
	//	Transform members, public or private?
	//

	glm::vec2 position;
	glm::vec2 scale;
	float rotation;

	//Misc
	void print();

private:
};



/*
///////////////////////////////
//  CREATING NEW COMPONENTS  //
///////////////////////////////

1. Create a new class, inherit from Component ( : public Component )
2. Implement void update() and render() functions (if needed). These are automatically called for you from GameObject
3. call gameobject.addComponent<NewComponentYouJustCreated>();
4. ???
5. profit

*/

#endif