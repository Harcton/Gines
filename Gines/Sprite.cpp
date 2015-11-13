#include "Sprite.h"


Sprite::Sprite()
{
	////
	vboID = 0;
	////
}


Sprite::~Sprite()
{
	////
	if (vboID != 0)
	{
		glDeleteBuffers(1, &vboID);
	}
	////
}

void Sprite::initialize(glm::vec2 pos, int width, int height)
{
	position = pos;
	width = width;
	height = height;

	
	/////////////////////////

	x = x;
	y = y;

	if (vboID == 0)
	{
		glGenBuffers(1, &vboID);
	}

	VertexPositionColor vertexData[6];

	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].color.r = 1;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 1;
		vertexData[i].color.a = 1;
	}

	vertexData[1].color.r = 0;
	vertexData[1].color.g = 0;
	vertexData[1].color.b = 1;
	vertexData[1].color.a = 1;

	vertexData[4].color.r = 1;
	vertexData[4].color.g = 0;
	vertexData[4].color.b = 0;
	vertexData[4].color.a = 1;

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/////////////////////////
}


//////
void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glEnableVertexAttribArray(0);


	//Position attribute pointer

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*)offsetof(VertexPositionColor, position));
	
	//Color attribute pointer
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*)offsetof(VertexPositionColor, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
//////