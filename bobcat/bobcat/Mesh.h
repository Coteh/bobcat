#pragma once

#include <vector>
#include <string>
#include <glm\glm.hpp>
#include "vgl.h"
#include "Shader.h"

namespace bobcat {

	class Mesh {
	private:
		GLuint vbo, ebo, vao;
		std::vector<GLfloat> m_vertices;
		std::vector<int> indiceCountData;
		std::vector<GLenum> drawModeVec;
		int vertexCount;
		int indiceCount;
		std::string m_name;
		std::vector<glm::vec3> m_positions;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_uv;
		std::vector<glm::vec3> m_color;

		GLuint boundShaderProgram;

		void refreshMeshAttribMembers();
		void updateMeshBufferData(std::vector<GLfloat> _vertices);
	public:
		Mesh(){}
		Mesh(std::vector<GLfloat> _vertices, std::vector<GLuint> _elements, std::string _name, std::vector<int> _indiceCountData);
		~Mesh();

		GLuint getVAO();
		GLuint getVBO();
		GLuint getEBO();
		int getVertexCount();
		int getIndiceCount();
		std::vector<int> getIndiceCountData();
		std::vector<GLenum> getDrawModes();

		std::string getName();
		std::vector<glm::vec3> getPositions();
		std::vector<glm::vec3> getNormals();
		std::vector<glm::vec2> getUVs();
		std::vector<glm::vec3> getColor();

		GLuint getBoundShaderProgram();

		void setName(std::string _name);
		void setPositions(std::vector<glm::vec3> _pos);
		void setNormals(std::vector<glm::vec3> _normals);
		void setUVs(std::vector<glm::vec2> _uvs);
		void setColor(std::vector<glm::vec3> _color);

		void setBoundShaderProgram(GLuint _shaderProgram);

		__declspec(property(get = getName, put = setName)) std::string name;
		__declspec(property(get = getPositions, put = setPositions)) std::vector<glm::vec3> positions;
		__declspec(property(get = getNormals, put = setNormals)) std::vector<glm::vec3> normals;
		__declspec(property(get = getUVs, put = setUVs)) std::vector<glm::vec2> uv;
		__declspec(property(get = getColor, put = setColor)) std::vector<glm::vec3> color;

		void clearBuffers();
		void updateDrawModes();
		void updateDrawModes(int _glDrawMode);
		void updateDrawModes(std::vector<GLenum> _drawModesVec);
	};

}