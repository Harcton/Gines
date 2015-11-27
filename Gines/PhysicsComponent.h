#ifndef PhyiscsComponent_h_
#define PhysicsComponent_h_

#include "Component.h"

namespace gines
{
	//Coming soon
	class PhysicsComponent : public MonoComponent
	{
	public:
		PhysicsComponent();
		~PhysicsComponent();

		void update();
	private:
	};
}
#endif