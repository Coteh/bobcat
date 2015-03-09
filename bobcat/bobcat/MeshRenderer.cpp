#include "MeshRenderer.h"

using namespace bobcat;

MeshRenderer::MeshRenderer() {
	meshFilter = nullptr;
}

MeshRenderer::~MeshRenderer() {

}

bool MeshRenderer::CheckShaderMatchup(){
	if (meshFilter == nullptr) return false;
	return (meshFilter->mesh->getBoundShaderProgram() == material->shader->shaderProgram);
}

void MeshRenderer::Render(){
	if (meshFilter == nullptr || material == nullptr || !isEnabled)return; //Don't do any drawing if there's no mesh attached to the object or if isRendering is set to false
	//Material Binding
	material->Bind();
	//Mesh Drawing
	glBindVertexArray(meshFilter->mesh->getVAO());
	if (isWireFrameOn){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	std::vector<GLenum> drawModeVec = meshFilter->mesh->getDrawModes();
	std::vector<int> indiceCountData = meshFilter->mesh->getIndiceCountData();
	int indicesSoFar = 0;
	for (size_t i = 0; i < drawModeVec.size(); i++){
		glDrawElements(drawModeVec[i], indiceCountData[i], GL_UNSIGNED_INT, (void*)(indicesSoFar * sizeof(GLuint)));
		indicesSoFar += indiceCountData[i];
	}
	if (isWireFrameOn){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glBindVertexArray(0);
	//Material Unbinding
	material->Unbind();
}