#pragma once
#include "Camera.h"

class AbstractRenderSystem {
public:
	virtual void setActiveCamera(Camera* _camera) = 0;
	virtual void setDebugRender(bool _expression) = 0;
	virtual void Init() = 0;
	virtual void PreRender() = 0;
	virtual void RenderObject(GameObject* _gameObject) = 0;
	virtual void EndRender() = 0;
	virtual ~AbstractRenderSystem(){};
};