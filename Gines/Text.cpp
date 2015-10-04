#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Text.h"
#include "GLSLProgram.h"

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

namespace gines
{

	static FT_Library* ft = nullptr;
	GLuint vertexArrayID, vertexArrayData;
	GLSLProgram textProgram;
	std::vector<Face*> faces;
	glm::mat4 projectionMatrix;

	bool textRenderingInitialized = false;
	int textCount = 0;
	void initializeTextRendering()
	{
		if (ft != nullptr)
		{
			std::cout << "\nError in freetype library initialization: already exists!";
			return;
		}
		ft = new FT_Library;
		if (FT_Init_FreeType(ft))
		{
			std::cout << "\nError: could not initialize FreeType Library" << std::endl;
			return;
		}

		textProgram.compileShaders("Shaders/text.vertex", "Shaders/text.fragment");
		textProgram.addAttribute("vertex");
		textProgram.linkShaders();

		textRenderingInitialized = true;
		std::cout << "\nFreetype library initialized";
	}
	void uninitializeTextRendering()
	{
		FT_Done_FreeType(*ft);
		delete ft;
		ft = nullptr;

		textRenderingInitialized = false;
		std::cout << "\nFreetype library uninitialized";
	}


	Text::Text()
	{
		textCount++;
		if (!textRenderingInitialized)
		{
			initializeTextRendering();
		}
	}
	Text::~Text()
	{
		//if face becomes useless, remove
		if (--face->referenceCount <= 0)
		{
			for (unsigned int i = 0; i < faces.size(); i++)
				if (faces[i] == face)
				{
				faces.erase(faces.begin() + i);
				delete face;
				}
		}

		textCount--;
		if (textCount == 0)
		{
			uninitializeTextRendering();
		}
	}

	bool Text::setFont(char* fontPath, int size)
	{
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			if (fontPath == faces[i]->fontPath)
			{
				if (size == faces[i]->fontSize)
				{//Already loaded
					face = faces[i];
					face->referenceCount++;
					return true;
				}
			}
		}

		//Create a new face
		faces.push_back(new Face);
		face = faces.back();

		face->ftFace = new FT_Face;

		FT_Error error = FT_New_Face(*ft, fontPath, 0, face->ftFace);
		if (error)
		{
			std::cout << "\nFreetype error: Failed to load font \"" << fontPath << "\" code: " << error;
			return false;
		}

		face->fontPath = fontPath;
		face->fontSize = size;
		face->referenceCount = 1;
		FT_Face* ftFace = face->ftFace;
		FT_Set_Pixel_Sizes(*ftFace, 0, size);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

		for (GLubyte c = 32; c <= 126; c++)
		{
			// Load character glyph
			if (FT_Load_Char(*ftFace, c, FT_LOAD_RENDER))
			{
				std::cout << "\nfreetype error: Failed to load Glyph";
				return false;
			}

			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				(*ftFace)->glyph->bitmap.width,
				(*ftFace)->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				(*ftFace)->glyph->bitmap.buffer
				);

			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2((*ftFace)->glyph->bitmap.width, (*ftFace)->glyph->bitmap.rows),
				glm::ivec2((*ftFace)->glyph->bitmap_left, (*ftFace)->glyph->bitmap_top),
				(*ftFace)->glyph->advance.x
			};
			face->characters.insert(std::pair<GLchar, Character>(c, character));
		}
		face->height = (*face->ftFace)->height / 64.0f;

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		projectionMatrix = glm::ortho(0.0f, float(WINDOW_WIDTH), 0.0f, float(WINDOW_HEIGHT));
		glGenVertexArrays(1, &vertexArrayID);
		glGenBuffers(1, &vertexArrayData);
		glBindVertexArray(vertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayData);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		// The 2D quad requires 6 vertices of 4 floats each so we reserve 6 * 4 floats of memory.
		// Because we'll be updating the content of the VBO's memory quite often we'll allocate the memory with GL_DYNAMIC_DRAW.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return true;
	}


	void Text::render()
	{
		//Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		textProgram.use();
		glUniformMatrix4fv(textProgram.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniform3f(textProgram.getUniformLocation("textColor"), red, green, blue);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vertexArrayID);

		int x = beginX;
		int y = beginY;

		// Iterate through all characters
		std::string::const_iterator c;
		for (c = string.begin(); c != string.end(); c++)
			if (*c != '\n')
			{
			Character ch = face->characters[*c];

			GLfloat xpos = x + ch.bearing.x * scale;
			GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

			GLfloat w = ch.size.x * scale;
			GLfloat h = ch.size.y * scale;

			// Update VBO for each character
			GLfloat vertices[6][4] = {
					{ xpos, ypos + h, 0.0, 0.0 },
					{ xpos, ypos, 0.0, 1.0 },
					{ xpos + w, ypos, 1.0, 1.0 },

					{ xpos, ypos + h, 0.0, 0.0 },
					{ xpos + w, ypos, 1.0, 1.0 },
					{ xpos + w, ypos + h, 1.0, 0.0 }
			};

			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.textureID);

			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, vertexArrayData);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
			}
			else
			{//new line
				x = beginX;
				//y -= (face->top + face->bottom + lineSpacing) * scale;
				y -= face->height + lineSpacing;
			}

		//Unbinds / unuse program
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		textProgram.unuse();
	}
	void Text::setString(std::string str)
	{
		string = str;
	}
	void Text::setPosition(int xPos, int yPos)
	{
		beginX = xPos;
		beginY = yPos;
	}
	void Text::setColor(float r, float g, float b, float a)
	{
		red = r;
		green = g;
		blue = b;
		alpha = a;
	}

	int Text::getFontHeight()
	{
		return face->height;
	}

}