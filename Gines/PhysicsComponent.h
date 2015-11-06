#ifndef PhyiscsComponent_h_
#define PhysicsComponent_h_

#include "Component.h"
struct vector2 {
	size_t x, y;
};

class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	
private:

};
#endif