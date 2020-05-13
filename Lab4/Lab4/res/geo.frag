//Version number
#version 400
//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;
//Unfrom variable
uniform float randColourX;
uniform float randColourY;
uniform float randColourZ;
 in vec3 nor;
void main()
{
//Setting each vector component to uniform varaible then setting final colour
	vec4 color;
	color = vec4(1.,0.,0.,1.0);
    fragcolor = vec4(nor,1.);
}