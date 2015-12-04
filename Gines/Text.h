#ifndef TEXT_H
#define TEXT_H


#include <map>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Component.h"




namespace gines
{
	void uninitializeTextRendering();
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

		FT_Face* ftFace = nullptr;
		char* fontPath;
		int fontSize;
		std::map<GLchar, Character> characters;
		int referenceCount = 0;
		int height = 0;
	};

	class Text : public Component
	{
	public:
		Text();
		Text(const Text& original);
		~Text();
		void operator=(const Text& original);

		bool setFont(char* fontPath, int size);
		bool setFontSize(int size);
		void render();
		void setString(std::string str);
		void setColor(glm::vec4& col);
		void setColor(float r, float g, float b, float a = 1.0f);
		void setPosition(glm::vec2& vec);
		void translate(glm::vec2& vec);

		void updateGlyphsToRender();
		void updateBuffers(); 

		//Getters
		int getFontHeight();
		glm::vec4& getColorRef();
		int getGlyphsToRender();
		std::string getString();

	private:
		int glyphsToRender = 0;
		GLuint vertexArrayData = 0;
		GLuint* textures = nullptr;
		glm::vec2 position;
		glm::vec4 color;
		float scale = 1.0f;
		int lineSpacing = 0;
		bool doUpdate = true;
		std::string string;
		Font* font = nullptr;
		void unreferenceFont();
		glm::vec2 gameObjectPosition;//Game object position tracking
	};
}
#endif