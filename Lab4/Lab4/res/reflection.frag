#version 330 core
out vec4 FragColor;

in vec3 pos;
in vec3 nor;
uniform samplerCube skybox;

void main()
{    
vec3 N = normalize(nor);
vec3 ref = reflect(-pos,nor);
    FragColor = texture(skybox, ref);
}