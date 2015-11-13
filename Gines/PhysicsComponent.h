#ifndef PhyiscsComponent_h_
#define PhysicsComponent_h_

#include "Component.h"

class GameObject;
class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	
	void update();
private:
};
#endif