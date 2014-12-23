#include "MeshRenderer.h"
#include <glm\gtc\type_ptr.hpp>

MeshRenderer::MeshRenderer() {
	mesh = nullptr;
	color = glm::vec4(1.0f);
}

MeshRenderer::~MeshRenderer() {

}

/**
* Saving copies of various mesh information
* in order to increase performance.
*/
void MeshRenderer::CalibrateMeshData(){
	drawModeVec = mesh->getDrawModes();
	indiceCountData = mesh->getIndiceCountData();
}

void MeshRenderer::setColor(glm::vec4 _color){
	color = _color;
}

void MeshRenderer::Render(Shader* _shader){
	if (mesh == nullptr || !isEnabled)return; //Don't do any drawing if there's no mesh attached to the object or if isRendering is set to false
	//Send uniform color information to the shader
	glUniform4fv(_shader->colorLoc, 1, glm::value_ptr(color));
	glBindVertexArray(mesh->getVAO());
	if (isWireFrameOn){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	int indicesSoFar = 0;
	for (size_t i = 0; i < drawModeVec.size(); i++){
		glDrawElements(drawModeVec[i], indiceCountData[i], GL_UNSIGNED_INT, (void*)(indicesSoFar * sizeof(GLuint)));
		indicesSoFar += indiceCountData[i];
	}
	if (isWireFrameOn){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glBindVertexArray(0);
}