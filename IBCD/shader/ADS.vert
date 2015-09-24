#version 450

layout(location=0) in vec3 vertex_position;
layout(location=1) in vec3 vertex_normal;

out vec3 Position;
out vec3 Normal;



layout(location=8) uniform mat4 ModelViewMatrix;
layout(location=9) uniform mat3 NormalMatrix;
layout(location=10) uniform mat4 ProjectionMatrix;
layout(location=11) uniform mat4 MVP;


void main()
{
	
	Normal = normalize(NormalMatrix * vertex_normal);
	Position = vec3(ModelViewMatrix * vec4(vertex_position, 1.0));

	// Convert postion to clip coordinates and pass along
	gl_Position =  MVP * vec4(vertex_position, 1.0);
}


