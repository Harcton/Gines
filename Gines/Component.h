#ifndef Component_h_
#define Component_h_
#include <glm/vec2.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

class Component
{
public:
	Component(){}
	virtual ~Component(){}; //Destructor hidden so that only removeComponent() or ~GameObject() can properly delete components
	virtual void update(){}
	virtual void render(){}
protected:
};

class MonoComponent : public Component
{
	/*
	If you want a gameobject to have a maxinum of 1 instance of a specific component, 
	you can derive that component from MonoComponent instead of Component
	*/
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