#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "Vertex.h"




namespace gines
{
	enum class SortType
	{
		NONE,
		FRONT_BACK,
		BACK_FRONT,
		TEXTURE
	};


	struct Glyph
	{
		GLuint tex;
		float drawDepth;

		VertexPositionColorTexture topLeft;
		VertexPositionColorTexture bottomLeft;
		VertexPositionColorTexture topRight;
		VertexPositionColorTexture bottomRight;
	};

	class Batch
	{
	public:
		Batch(GLuint off, GLuint verAm, GLuint tex) : offset(off), verticeAmount(verAm),
			texture(tex){};
		GLuint offset;
		GLuint verticeAmount;
		GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void initialize();
		void begin(SortType sortType = SortType::TEXTURE);
		void end();
		void draw(const glm::vec4& dRect, const glm::vec4& UVRect, GLuint texture, float depth, const glm::vec4& color);
		void renderBatch();

	private:
		void createBatches();
		void sort();

		static bool compareFrontBack(Glyph* a, Glyph* b);
		static bool compareBackFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		SortType type;
		GLuint vbo;
		
		std::vector<Glyph*> glyphs;
		std::vector<Batch> batches;
	};
}
#endif

