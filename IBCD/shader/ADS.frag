#version 450

in vec3 Position;
in vec3 Normal;

struct LightInfo{
	vec3 Position; //eyeCoords
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


layout(location=0) out float FragColor;

vec3 phongModel()
{
	vec3 s = normalize(vec3(Light.Position - Position));
	vec3 v = normalize(-Position);
	vec3 r = reflect(-s, Normal);
	vec3 ambient = Light.La * Material.Ka;
	float sDotN = max(dot(s, Normal), 0.0);
	vec3 diffuse = Light.Ld * Material.Kd * sDotN;
	vec3 spec = vec3(0.0);
	if(sDotN > 0.0)
		spec = Light.Ls * Material.Ks * pow(max(dot(r,v), 0.0), Material.Shiness);
		
	return ambient + diffuse + spec;
}

void main()
{
	
	FragColor = gl_FragCoord.z;
}