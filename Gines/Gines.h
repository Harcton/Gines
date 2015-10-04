#ifndef GINES_H
#define GINES_H


struct vec2f
{
	vec2f(float _x, float _y){ x = _x; y = _y; }
	float x, y {0};
};
struct vec3f
{
	vec3f(float _x, float _y, float _z){ x = _x; y = _y; z = _z; }
	float x, y, z {0};
};
struct vec4f
{
	vec4f(float _x, float _y, float _z, float _w){ x = _x; y = _y; z = _z; w = _w; }
	float x, y, z, w {0};
};







#endif