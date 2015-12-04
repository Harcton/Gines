#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Vertex.h"



namespace gines
{
	struct Glyph
	{
		GLuint tex;
		float drawDepth;

		VertexPositionColorTexture topLeft;
		VertexPositionColorTexture bottomLeft;
		VertexPositionColorTexture topRight;
		VertexPositionColorTexture bottomRight;
	};


	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void initialize();
		void begin();
		void end();
		void draw(const glm::vec4& dRect, const glm::vec4& UVRect, GLuint tex, glm::vec4 color);
		void renderBatch();

	private:

	};
}
#endif

