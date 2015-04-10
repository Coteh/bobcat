#pragma once
#include "../Component.h"
#include "../MeshRenderer.h"
#include "../GameObject.h"

using namespace bobcat;

class ParticleSystem : public Component {
public:
	ParticleSystem();
	~ParticleSystem();

	__declspec(property(get = getMaxTime, put = setMaxTime)) float maxTime;

	float getMaxTime();
	void setMaxTime(float _maxTime);

	virtual void Update(float _deltaTime);
	void Reset();
protected:
	virtual void Awake();
private:
	float m_maxTime;

	Mesh* mesh;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> elements;
	std::vector<int> indiceCountData;
	Shader* shada;
	GLuint shaderTimeLoc;

	float elapsedTime;
};

