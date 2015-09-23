#version 450

layout(location=0) in vec3 vertex_position;
layout(location=1) in vec3 vertex_normal;

out vec3 light_intensity;

struct LightInfo{
	vec4 Position; //eyeCoords
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};

layout(location=0) uniform LightInfo Light;


struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shiness;
};

layout(location=4) uniform MaterialInfo Material;

layout(location=8) uniform mat4 ModelViewMatrix;
layout(location=9) uniform mat3 NormalMatrix;
layout(location=10) uniform mat4 ProjectionMatrix;
layout(location=11) uniform mat4 MVP;

void main()
{
	vec3 tnorm = normalize(NormalMatrix * vertex_normal);
	vec4 eyeCoords = ModelViewMatrix * vec4(vertex_position, 1.0);
	vec3 s = normalize(vec3(Light.Position - eyeCoords));
	vec3 v = normalize(-eyeCoords.xyz);
	vec3 r = reflect(-s, tnorm);
	vec3 ambient = Light.La * Material.Ka;
	float sDotN = max(dot(s, tnorm), 0.0);
	vec3 diffuse = Light.Ld * Material.Kd * sDotN;
	vec3 spec = vec3(0.0);
	if(sDotN > 0.0)
		spec = Light.Ls * Material.Ks * pow(max(dot(r,v), 0.0), Material.Shiness);

	// The ADS shading equation
	light_intensity = ambient + diffuse +  spec;


	// Convert postion to clip coordinates and pass along
	gl_Position =  MVP * vec4(vertex_position, 1.0);
}


