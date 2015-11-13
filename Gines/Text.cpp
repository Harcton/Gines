#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Gines.h"
#include "Text.h"
#include "GLSLProgram.h"

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

namespace gines
{
	static bool textRenderingInitialized = false;
	static int textCount = 0;
	static FT_Library* ft = nullptr;
	static GLSLProgram textProgram;
	static std::vector<Font*> fonts;
	static glm::mat4 projectionMatrix;

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
	
	Text::~Text()
	{
		glDeleteBuffers(1, &vertexArrayData);
		unreferenceFont();
		textCount--;
		if (textCount == 0)
		{
			uninitializeTextRendering();
		}
	}
	Text::Text()
	{
		textCount++;
	}
	Text::Text(const Text& original)
	{
		textCount++;
		std::cout << "\nCopy constructor called";
		glGenBuffers(1, &vertexArrayData);
		string = original.string;
		position = original.position;
		color = original.color;
		updateGlyphsToRender();
		textures = nullptr;
		font = nullptr;
		scale = original.scale;
		lineSpacing = original.lineSpacing;


		if (original.font != nullptr)
		{
			setFont(original.font->fontPath, original.font->fontSize);//Increases reference count
			updateBuffers();
		}
	}
	void Text::operator=(const Text& original)
	{
		std::cout << "\nText = operator called";
	}
	void Text::unreferenceFont()
	{
		if (font == nullptr)
		{
			return;
		}
		//if face becomes useless, remove
		if (--font->referenceCount <= 0)
		{
			for (unsigned int i = 0; i < fonts.size(); i++)
				if (fonts[i] == font)
				{
				fonts.erase(fonts.begin() + i);
				delete font;
				font = nullptr;
				return;
				}
		}
	}
	bool Text::setFontSize(int size)
	{
		//No font loaded
		if (font == nullptr)
		{
			return false;
		}
		
		//The size already matches
		if (font->fontSize == size)
		{
			return true;
		}

		//Get new font face
		char* fontPath = font->fontPath;
		unreferenceFont();
		setFont(fontPath, size);
		return true;
	}
	bool Text::setFont(char* fontPath, int size)
	{
		//make sure text is initialized
		if (!textRenderingInitialized)
		{
			initializeTextRendering();
		}

		if (font != nullptr)
		{
			unreferenceFont();
		}

		for (unsigned int i = 0; i < fonts.size(); i++)
		{
			if (fontPath == fonts[i]->fontPath)
			{
				if (size == fonts[i]->fontSize)
				{//Already loaded
					std::cout << "\nFace already loaded";
					font = fonts[i];
					font->referenceCount++;
					doUpdate = true;
					return true;
				}
			}
		}

		//Create a new font
		fonts.push_back(new Font);
		font = fonts.back();
		font->ftFace = new FT_Face;

		FT_Error error = FT_New_Face(*ft, fontPath, 0, font->ftFace);
		if (error)
		{
			std::cout << "\nFreetype error: Failed to load font \"" << fontPath << "\" code: " << error;
			return false;
		}

		font->fontPath = fontPath;
		font->fontSize = size;
		font->referenceCount = 1;
		FT_Face* ftFace = font->ftFace;
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
			Character character =
			{
				texture,
				glm::ivec2((*ftFace)->glyph->bitmap.width, (*ftFace)->glyph->bitmap.rows),
				glm::ivec2((*ftFace)->glyph->bitmap_left, (*ftFace)->glyph->bitmap_top),
				(*ftFace)->glyph->advance.x
			};
			font->characters.insert(std::pair<GLchar, Character>(c, character));
		}

		font->height = (*font->ftFace)->size->metrics.height >> 6;
		projectionMatrix = glm::ortho(0.0f, float(WINDOW_WIDTH), 0.0f, float(WINDOW_HEIGHT));

		doUpdate = true;

		return true;
	}
	void Text::updateBuffers()
	{
		if (!textRenderingInitialized)
		{
			return;
		}

		//This function should be called everytime the number of glyphs to render changes
		updateGlyphsToRender();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glDeleteBuffers(1, &vertexArrayData);
		glGenBuffers(1, &vertexArrayData);
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayData);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4 * glyphsToRender, NULL, GL_DYNAMIC_DRAW);
		// The 2D quad requires 6 vertices of 4 floats each so we reserve 6 * 4 floats of memory.
		// Because we'll be updating the content of the VBO's memory quite often we'll allocate the memory with GL_DYNAMIC_DRAW.

		int x = position.x;
		int y = position.y;

		// Iterate through all characters
		if (textures != nullptr)
		{
			delete[] textures;
		}
		textures = new GLuint[glyphsToRender];
		GLfloat* vertices = new GLfloat[24 * glyphsToRender];
		int _index = 0;
		for (auto c = string.begin(); c != string.end(); c++)
			if (*c != '\n')
			{
			Character ch = font->characters[*c];

			GLfloat xpos = x + ch.bearing.x * scale;
			GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

			GLfloat w = ch.size.x * scale;
			GLfloat h = ch.size.y * scale;

			// Update VBO for each character
			vertices[_index * 24 + 0] = xpos;
			vertices[_index * 24 + 1] = ypos + h;
			vertices[_index * 24 + 2] = 0.0f;
			vertices[_index * 24 + 3] = 0.0f;

			vertices[_index * 24 + 4] = xpos;
			vertices[_index * 24 + 5] = ypos;
			vertices[_index * 24 + 6] = 0.0f;
			vertices[_index * 24 + 7] = 1.0f;

			vertices[_index * 24 + 8] = xpos + w;
			vertices[_index * 24 + 9] = ypos;
			vertices[_index * 24 + 10] = 1.0f;
			vertices[_index * 24 + 11] = 1.0f;

			vertices[_index * 24 + 12] = xpos;
			vertices[_index * 24 + 13] = ypos + h;
			vertices[_index * 24 + 14] = 0.0f;
			vertices[_index * 24 + 15] = 0.0f;

			vertices[_index * 24 + 16] = xpos + w;
			vertices[_index * 24 + 17] = ypos;
			vertices[_index * 24 + 18] = 1.0f;
			vertices[_index * 24 + 19] = 1.0f;

			vertices[_index * 24 + 20] = xpos + w;
			vertices[_index * 24 + 21] = ypos + h;
			vertices[_index * 24 + 22] = 1.0f;
			vertices[_index * 24 + 23] = 0.0f;

			// Render glyph texture over quad
			textures[_index] = ch.textureID;

			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
			_index++;
			}
			else
			{//new line
				x = position.x;
				y -= font->height + lineSpacing;
			}


		//Submit data
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayData);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 24 * glyphsToRender, vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		delete[] vertices;
		doUpdate = false;

	}
	void Text::updateGlyphsToRender()
	{
		glyphsToRender = 0;
		for (auto c = string.begin(); c != string.end(); c++)
			if (*c != '\n')
			{
				glyphsToRender++;
			}
	}

	void Text::render()
	{
		if (doUpdate)
			updateBuffers();

		//Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		textProgram.use();

		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayData);
		glUniformMatrix4fv(textProgram.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniform4f(textProgram.getUniformLocation("textColor"), color.r, color.g, color.b, color.a);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glActiveTexture(GL_TEXTURE0);
		for (int i = 0; i < glyphsToRender; i++)
		{//Draw
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
		}

		//Unbinds / unuse program
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		textProgram.unuse();
	}
	
	void Text::setString(std::string str)
	{
		string = str;
		doUpdate = true;
	}
	void Text::setPosition(glm::vec2& vec)
	{
		position.x = vec.x;
		position.y = vec.y;
		doUpdate = true;
	}
	void Text::translate(glm::vec2& vec)
	{
		position.x += vec.x;
		position.y += vec.y;
		doUpdate = true;
	}
	void Text::setColor(glm::vec4& vec)
	{
		color = vec;
	}
	int Text::getFontHeight()
	{
		return font->height;
	}
	glm::vec4& Text::getColorRef()
	{
		return color;
	}
	int Text::getGlyphsToRender()
	{
		return glyphsToRender;
	}
	std::string Text::getString()
	{
		return string;
	}
}