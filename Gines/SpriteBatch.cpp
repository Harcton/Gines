#include "SpriteBatch.h"

#include <algorithm>

namespace gines
{

	SpriteBatch::SpriteBatch() : vbo(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::initialize()
	{

	}

	void SpriteBatch::begin(SortType sortType /* default sorting type is SortType::TEXTURE */)
	{
		type = sortType;
		batches.clear();
		glyphs.clear();
	}

	void SpriteBatch::end()
	{
		sort();
		createBatches();
	}

	void SpriteBatch::draw(const glm::vec4& dRect, const glm::vec4& UVRect, GLuint texture, float depth, const glm::vec4& color)
	{
		Glyph* nGlyph = new Glyph;

		nGlyph->tex = texture;
		nGlyph->drawDepth = depth;

		nGlyph->topLeft.color = color;
		nGlyph->topLeft.position.x = dRect.x;
		nGlyph->topLeft.position.y = dRect.y + dRect.w;
		nGlyph->topLeft.uv.x = UVRect.x;
		nGlyph->topLeft.uv.y = UVRect.y + UVRect.w;

		nGlyph->bottomLeft.color = color;
		nGlyph->bottomLeft.position.x = dRect.x;
		nGlyph->bottomLeft.position.y = dRect.y;
		nGlyph->bottomLeft.uv.x = UVRect.x;
		nGlyph->bottomLeft.uv.y = UVRect.y;

		nGlyph->bottomRight.color = color;
		nGlyph->bottomRight.position.x = dRect.x + dRect.z;
		nGlyph->bottomRight.position.y = dRect.y;
		nGlyph->bottomRight.uv.x = UVRect.x + UVRect.z;
		nGlyph->bottomRight.uv.y = UVRect.y;

		nGlyph->topRight.color = color;
		nGlyph->topRight.position.x = dRect.x + dRect.z;
		nGlyph->topRight.position.y = dRect.y + dRect.w;
		nGlyph->topRight.uv.x = UVRect.x + UVRect.z;
		nGlyph->topRight.uv.y = UVRect.y + UVRect.w;

		glyphs.push_back(nGlyph);
	}

	void SpriteBatch::renderBatch()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)offsetof(VertexPositionColorTexture, position));

		//Color attribute pointer
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)offsetof(VertexPositionColorTexture, color));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)offsetof(VertexPositionColorTexture, uv));

		for (int i = 0; i < batches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, batches[i].texture);
			
			glDrawArrays(GL_TRIANGLES, batches[i].offset, batches[i].verticeAmount);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::createBatches()
	{
		std::vector<VertexPositionColorTexture> vertices;
		vertices.resize(glyphs.size() * 6);

		if (glyphs.empty())
		{
			return;
		}

		int offs = 0;
		int currVertex = 0;

		batches.emplace_back(offs, 6, glyphs[0]->tex);

		vertices[currVertex++] = glyphs[0]->topLeft;
		vertices[currVertex++] = glyphs[0]->bottomLeft;
		vertices[currVertex++] = glyphs[0]->bottomRight;
		vertices[currVertex++] = glyphs[0]->bottomRight;
		vertices[currVertex++] = glyphs[0]->topRight;
		vertices[currVertex++] = glyphs[0]->topLeft;

		offs += 6;

		for (int i = 1; i < glyphs.size(); i++)
		{
			if (glyphs[i]->tex != glyphs[i - 1]->tex)
			{
				batches.emplace_back(offs, 6, glyphs[i]->tex);
			}
			else
			{
				batches.back().verticeAmount += 6;
			}
			
			vertices[currVertex++] = glyphs[i]->topLeft;
			vertices[currVertex++] = glyphs[i]->bottomLeft;
			vertices[currVertex++] = glyphs[i]->bottomRight;
			vertices[currVertex++] = glyphs[i]->bottomRight;
			vertices[currVertex++] = glyphs[i]->topRight;
			vertices[currVertex++] = glyphs[i]->topLeft;
			offs += 6;
		}
		
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexPositionColorTexture), nullptr, GL_DYNAMIC_DRAW); // Orphan the buffer.
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(VertexPositionColorTexture), vertices.data()); // Upload data.

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	}


	void SpriteBatch::sort()
	{
		switch (type) // Switch by sorting method
		{
		case SortType::BACK_FRONT:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareBackFront);
			break;
		case SortType::FRONT_BACK:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareFrontBack);
			break;
		case SortType::TEXTURE:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareTexture);
			break;
		}
	}

	bool SpriteBatch::compareFrontBack(Glyph* a, Glyph* b)
	{
		return(a->drawDepth < b->drawDepth);
	}

	bool SpriteBatch::compareBackFront(Glyph* a, Glyph* b)
	{
		return(a->drawDepth > b->drawDepth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return(a->tex < b->tex);
	}

}
