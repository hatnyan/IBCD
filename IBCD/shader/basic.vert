#version 450

layout(location=0) in vec3 vertex_position;
layout(location=1) in vec3 vertex_normal;

out vec3 light_intensity;

layout(location=0) uniform vec4 light_position;
layout(location=1) uniform vec3 Kd;
layout(location=2) uniform vec3 Ld;

layout(location=3) uniform mat4 ModelViewMatrix;
layout(location=4) uniform mat3 NormalMatrix;
layout(location=5) uniform mat4 ProjectionMatrix;
layout(location=6) uniform mat4 MVP;

void main()
{
	vec3 tnorm = normalize(NormalMatrix * vertex_normal);
	vec4 eyeCoords = ModelViewMatrix * vec4(vertex_position, 1.0);
	vec3 s = normalize(vec3(light_position - eyeCoords));

	// The diffuse shading equation
	light_intensity = Ld * Kd * max(dot(s, tnorm), 0);


	// Convert postion to clip coordinates and pass along
	gl_Position =  MVP * vec4(vertex_position, 1.0);
}


