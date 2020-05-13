#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "Camera.h"
#include <vector>
class Shader
{
public:
	Shader(const std::string& filename);

	void Bind(); //Set gpu to use our shaders
	void Update(const Transform& transform, const Camera& camera);
	GLuint getShaderProgram() {
		return program;
	}
	std::string Shader::LoadShader(const std::string& fileName);
	void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint Shader::CreateShader(const std::string& text, unsigned int type);

	Shader(const char* vertexSource, const char* fragmentSource, const char* geometrySoure);

	~Shader();


protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint program; // Track the shader program
	std::vector<GLuint> shaders; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
