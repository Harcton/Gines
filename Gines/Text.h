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
	struct Font
	{
		~Font()
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
		bool setFontSize(int size);
		void render();
		void setString(std::string str);
		void setColor(vec4f& col);
		void setPosition(vec2f& vec);
		void translate(vec2f& vec);

		int getFontHeight();

		//TESTING
		int glyphsToRender = 0;
	private:
		float red = 0.0f;
		float green = 0.0f;
		float blue = 0.0f;
		float alpha = 1.0f;
		float scale = 1.0f;
		int beginX = 0;
		int beginY = 0;
		int lineSpacing = 0;

		std::string string;
		Font* font = nullptr;

		void unreferenceFont();

	};
}
#endif