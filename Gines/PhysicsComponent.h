#ifndef PhyiscsComponent_h_
#define PhysicsComponent_h_

#include "Component.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(int asd);
	~PhysicsComponent();
	
	void update();
private:
	size_t sad;
};
#endif