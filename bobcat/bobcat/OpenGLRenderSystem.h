#pragma once
#include "AbstractRenderSystem.h"
#include "External\gl_core_3_3.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "GameObject.h"

namespace bobcat {

	/**
	* The OpenGL-specific implementation of AbstractRenderSystem.
	* Facilitates OpenGL rendering tasks.
	*/
	class OpenGLRenderSystem : public AbstractRenderSystem {
	private:
		Camera* activeCamera;

		ShaderManager* shaderManager;
		Shader* currShader;
		GLuint modelLoc, viewLoc, projectionLoc, normalLoc;

		glm::mat4 cam;
		glm::mat4 proj;

		Mesh* boxColliderMesh;
		Mesh* sphereColliderMesh;

		Shader* debugShader;
		bool isDebugOn;
		void RenderDebugMesh(Mesh* _mesh);
	public:
		OpenGLRenderSystem();
		virtual ~OpenGLRenderSystem();
		virtual void setActiveCamera(Camera* _camera);
		virtual void setDebugRender(bool _expression);
		virtual void Init();
		virtual void PreRender();
		virtual void RenderObject(GameObject* _gameObject);
		virtual void EndRender();
	};

}