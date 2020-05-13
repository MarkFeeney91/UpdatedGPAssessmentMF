#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normals;


out vec3 pos;
uniform mat4 transform;

void main()
{
pos = position;
	gl_Position = transform * vec4(position, 1.0);

}