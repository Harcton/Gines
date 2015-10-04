#ifndef TEXT_H
#define TEXT_H


#include <map>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Gines.h"


namespace gines
{
	struct Character
	{
		GLuint     textureID;  // ID handle of the glyph texture
		glm::ivec2 size;       // Size of glyph
		glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
		GLuint     advance;    // Offset to advance to next glyph
	};
	struct Face
	{
		~Face()
		{
			if (ftFace != nullptr)
			{
				FT_Done_Face(*ftFace);
				delete ftFace;
			}
		}

		GLuint vertexArrayID = 0, vertexArrayData = 0;
		FT_Face* ftFace = nullptr;
		char* fontPath;
		int fontSize;
		std::map<GLchar, Character> characters;
		int referenceCount = 0;
		int height = 0;
	};

	class Text
	{
	public:
		Text();
		~Text();

		bool setFont(char* fontPath, int size);
		void render();
		void updateVertexData();
		void setString(std::string str);
		void setColor(vec4f& col);
		void setPosition(vec2f& vec);
		void updatePositionTo(vec2f& vec);
		void translate(vec2f& vec);

		int getFontHeight();

		//TESTING
		int glyphsToRender = 0;
	private:
		bool doUpdate = true;
		float red = 0.0f, green = 0.0f, blue = 0.0f, alpha = 1.0f;
		std::string string;
		int beginX = 0, beginY = 0;
		float scale = 1.0f;
		Face* face;
		int lineSpacing = 0;

	};
}
#endif