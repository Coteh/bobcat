#include "MeshRenderer.h"

MeshRenderer::MeshRenderer() {
	name = "MeshRenderer";
	mesh = nullptr;
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

bool MeshRenderer::CheckShaderMatchup(){
	return (mesh->getBoundShaderProgram() == material->shader->shaderProgram);
}

void MeshRenderer::Render(){
	if (mesh == nullptr || material == nullptr || !isEnabled)return; //Don't do any drawing if there's no mesh attached to the object or if isRendering is set to false
	//Material Binding
	material->Bind();
	//Mesh Drawing
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
	//Material Unbinding
	material->Unbind();
}