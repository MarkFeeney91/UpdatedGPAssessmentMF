#pragma once
#include <string>
#include <GL\glew.h>
#include <vector>
class Texture
{
public:
	Texture();
	Texture(const std::string& fileName);
	GLuint getCubeMap(const std::vector<std::string>& fileName);
	Texture(const std::vector<std::string>& fileName);
	GLuint getTextureID();
	void Bind(unsigned int unit); // bind upto 32 textures

	~Texture();

protected:
private:

	GLuint textureHandler;
};

