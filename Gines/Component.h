#ifndef Component_h_
#define Component_h_

struct vector2 {
	size_t x, y;
};

class Component
{
public:
	Component();
	~Component();

	virtual void update();
private:
};
#endif