#version 450

in vec3 light_intensity;
out vec4 FragColor;

void main()
{
	FragColor = vec4(light_intensity, 1.0);
	//FragColor = vec4(1,0,0,1);
}