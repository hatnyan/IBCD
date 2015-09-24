#version 450

in vec2 texcoord;
out vec4 FragColor;

uniform sampler2D tex1;

void main()
{
	
	FragColor = vec4(texture(tex1, texcoord).r);
	//FragColor = vec4(texcoord,0,1);
}