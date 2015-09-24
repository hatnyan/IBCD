#pragma once

#include <glm\glm.hpp>

struct Light
{
	glm::vec3 eyecoords;
	glm::vec3 La;
	glm::vec3 Ld;
	glm::vec3 Ls;
};