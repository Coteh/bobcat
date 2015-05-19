#include "ParticleSystem.h"
#include "../ShaderManager.h"
#include <stdlib.h>
#include <glm/gtc/random.hpp>

ParticleSystem::ParticleSystem() {

}

ParticleSystem::~ParticleSystem() {
	delete mesh;
	delete partiMat;
}

void ParticleSystem::Awake(){
	/*Create the mesh data*/
	//Create the vertices
	vertices.reserve(2000 * 11);
	elements.reserve(2000);
	indiceCountData.reserve(2000);
	for (size_t i = 0; i < 2000; i++){
		//Setting position
		vertices.push_back(0);
		vertices.push_back(0);
		vertices.push_back(0);
		//Setting normals
		glm::vec3 randyNorms = glm::sphericalRand(1.0f);
		vertices.push_back(randyNorms.x);
		vertices.push_back(randyNorms.y);
		vertices.push_back(randyNorms.z);
		//We don't use UV coords
		vertices.push_back(glm::linearRand(10.0f, 100.0f)); //use this value for random particle speed
		vertices.push_back(0);
		//Setting color
		vertices.push_back(glm::linearRand<float>(0, 1.0f));
		vertices.push_back(glm::linearRand<float>(0, 1.0f));
		vertices.push_back(glm::linearRand<float>(0, 1.0f));
	}
	//Create the indices for each particle point
	for (size_t i = 0; i < 2000; i++){
		elements.push_back(i);
		indiceCountData.push_back(1);
	}
	//Create mesh
	mesh = new Mesh(vertices, elements, "ParticleMesh", indiceCountData);
	//Right now, we'll just overwrite the GameObject's mesh with this one
	gameObject->renderer->meshFilter->mesh = mesh;
	//Get Particle Shader from the Shader Manager
	shada = ShaderManager::getInstance()->getShader("ParticleShader");
	//Create new particle material and put shader on that
	partiMat = new Material();
	partiMat->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	partiMat->shader = shada;
	gameObject->renderer->material = partiMat;
	//Setting the time location from shader
	shaderTimeLoc = shada->getShaderUniform("Time");
	//Setting default max time
	maxTime = 3.0f;
	//Inital particle system reset
	Reset();
}

float ParticleSystem::getMaxTime(){
	return m_maxTime;
}

void ParticleSystem::setMaxTime(float _maxTime){
	m_maxTime = _maxTime;
}

void ParticleSystem::Update(float _deltaTime){
	if (shada != nullptr){
		shada->setShaderUniformFloat(shaderTimeLoc, elapsedTime);
	}
	elapsedTime += _deltaTime;
	if (elapsedTime > m_maxTime){
		Reset();
	}
}

void ParticleSystem::Reset(){
	elapsedTime = 0.0f;
}