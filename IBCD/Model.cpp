#include "Model.h"

Model::Model(std::string basePath, std::string name):
	position{0,0,0}
{
	std::vector<tinyobj::shape_t> s;
	std::vector<tinyobj::material_t> m;
	std::string err = tinyobj::LoadObj(s, m, (basePath + name).c_str(), basePath.c_str());
	if (!err.empty()) {
		LOG(INFO) << err;
		throw std::runtime_error("model load failed.");
	}
	this->mesh = s[0].mesh;
	this->material = m[0];

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (mesh.positions.size() + mesh.normals.size()), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * mesh.positions.size(), mesh.positions.data());
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * mesh.positions.size(), sizeof(float) * mesh.normals.size(), mesh.normals.data());

	
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (const void*)(sizeof(float) * mesh.positions.size()));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	
}

void Model::setPosition(glm::vec3 p)
{
	position = p;
	
}

void Model::setMaterial(tinyobj::material_t material)
{
	this->material = material;
}



void Model::render(GLuint program, Camera & cam)
{
	glm::mat4& View = cam.GetViewMatrix();
	glm::mat4& Projection = cam.GetProjectionMatrix();

	modelMatrix = glm::translate(position);
	MV = View * modelMatrix;
	normalMatrix = glm::transpose(glm::inverse(glm::mat3{ MV }));
	MVP = Projection * MV;
	

	glUniform3fv(4, 1, material.ambient);
	glUniform3fv(5, 1, material.diffuse);
	glUniform3fv(6, 1, material.specular);
	glUniform1f(7,  material.shininess);

	glUniformMatrix4fv(8, 1, false, glm::value_ptr(MV));
	glUniformMatrix3fv(9, 1, false, glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(10, 1, false, glm::value_ptr(Projection));
	glUniformMatrix4fv(11, 1, false, glm::value_ptr(MVP));

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, nullptr);

}
