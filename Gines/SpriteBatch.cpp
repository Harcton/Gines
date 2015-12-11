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

	void SpriteBatch::begin(SortType sortType)// default sorting type is SortType::TEXTURE 
	{
		type = sortType;
		batches.clear();
		SpriteData.clear();
	}

	void SpriteBatch::end()
	{
		sort();
		createBatches();
	}

	void SpriteBatch::draw(const glm::vec4& dRect, const glm::vec4& UVRect, GLuint texture, float depth, const glm::vec4& color)
	{
		SpriteInfo* SInfo = new SpriteInfo;

		SInfo->tex = texture;
		SInfo->drawDepth = depth;

		SInfo->topLeft.color = color;
		SInfo->topLeft.position.x = dRect.x;
		SInfo->topLeft.position.y = dRect.y + dRect.w;
		SInfo->topLeft.uv.x = UVRect.x;
		SInfo->topLeft.uv.y = UVRect.y + UVRect.w;

		SInfo->bottomLeft.color = color;
		SInfo->bottomLeft.position.x = dRect.x;
		SInfo->bottomLeft.position.y = dRect.y;
		SInfo->bottomLeft.uv.x = UVRect.x;
		SInfo->bottomLeft.uv.y = UVRect.y;

		SInfo->bottomRight.color = color;
		SInfo->bottomRight.position.x = dRect.x + dRect.z;
		SInfo->bottomRight.position.y = dRect.y;
		SInfo->bottomRight.uv.x = UVRect.x + UVRect.z;
		SInfo->bottomRight.uv.y = UVRect.y;

		SInfo->topRight.color = color;
		SInfo->topRight.position.x = dRect.x + dRect.z;
		SInfo->topRight.position.y = dRect.y + dRect.w;
		SInfo->topRight.uv.x = UVRect.x + UVRect.z;
		SInfo->topRight.uv.y = UVRect.y + UVRect.w;

		SpriteData.push_back(SInfo);
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
		vertices.resize(SpriteData.size() * 6);

		if (SpriteData.empty()) // If there is nothing in the glyph vector to make batches from
		{
			return;
		}

		int offs = 0;
		int currVertex = 0;

		batches.emplace_back(offs, 6, SpriteData[0]->tex); // Creates and pushes back an item

		vertices[currVertex++] = SpriteData[0]->topLeft;
		vertices[currVertex++] = SpriteData[0]->bottomLeft;
		vertices[currVertex++] = SpriteData[0]->bottomRight;
		vertices[currVertex++] = SpriteData[0]->bottomRight;
		vertices[currVertex++] = SpriteData[0]->topRight;
		vertices[currVertex++] = SpriteData[0]->topLeft;

		offs += 6;

		for (int i = 1; i < SpriteData.size(); i++)
		{
			if (SpriteData[i]->tex != SpriteData[i - 1]->tex)
			{
				batches.emplace_back(offs, 6, SpriteData[i]->tex);
			}
			else
			{
				batches.back().verticeAmount += 6;
			}
			
			vertices[currVertex++] = SpriteData[i]->topLeft;
			vertices[currVertex++] = SpriteData[i]->bottomLeft;
			vertices[currVertex++] = SpriteData[i]->bottomRight;
			vertices[currVertex++] = SpriteData[i]->bottomRight;
			vertices[currVertex++] = SpriteData[i]->topRight;
			vertices[currVertex++] = SpriteData[i]->topLeft;
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
			std::stable_sort(SpriteData.begin(), SpriteData.end(), compareBackFront);
			break;
		case SortType::FRONT_BACK:
			std::stable_sort(SpriteData.begin(), SpriteData.end(), compareFrontBack);
			break;
		case SortType::TEXTURE:
			std::stable_sort(SpriteData.begin(), SpriteData.end(), compareTexture);
			break;
		}
	}

	bool SpriteBatch::compareFrontBack(SpriteInfo* a, SpriteInfo* b)
	{
		return(a->drawDepth < b->drawDepth);
	}

	bool SpriteBatch::compareBackFront(SpriteInfo* a, SpriteInfo* b)
	{
		return(a->drawDepth > b->drawDepth);
	}

	bool SpriteBatch::compareTexture(SpriteInfo* a, SpriteInfo* b)
	{
		return(a->tex < b->tex);
	}

}
