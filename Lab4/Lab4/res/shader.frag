#version 330 core


in vec3 pos;
in vec3 nor;
out vec4 fc;
uniform float time;
void main()
{

float n = floor(pos.y*5. - time*1.5);//
float j = mod(n, 2);
vec4 color = mix(vec4(1., 1., 1., 1.), vec4(0., 1., 0., 1.),j);
fc = color*((nor.x+nor.y+nor.z)/3.);
}
