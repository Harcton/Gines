#ifndef TEXT_H
#define TEXT_H


#include <map>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H


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

	FT_Face* ftFace = nullptr;
	char* fontPath;
	int fontSize;
	std::map<GLchar, Character> characters;
	int referenceCount = 0;
	int height = 0;
	int bearingY = 0;
	int cellar = 0;
};

class Text
{
public:
	Text();
	~Text();

	bool setFont(char* fontPath, int size);
	void render();
	void setString(std::string str);
	void setColor(float r, float g, float b, float a);
	void setPosition(int xPos, int yPos);

	int getFontHeight();

private:
	float red = 0.0f, green = 0.0f, blue = 0.0f, alpha = 1.0f;
	std::string string;
	int beginX = 0, beginY = 0;
	float scale = 1.0f;
	Face* face;
	int lineSpacing = 1;
};

#endif