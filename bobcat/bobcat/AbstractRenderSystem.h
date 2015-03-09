#pragma once
#include "Camera.h"

namespace bobcat {

	/**
	* An abstract class that all Render Systems must derive from and use.
	* A Render System can use its methods to communicate with graphics libraries.
	*/
	class AbstractRenderSystem {
	public:
		/**
		* Set the active camera that the Render System will use.
		*/
		virtual void setActiveCamera(Camera* _camera) = 0;

		/**
		* Turn on/off debug rendering. (e.g. rendering colliders, etc.)
		*/
		virtual void setDebugRender(bool _expression) = 0;

		/**
		* Initalize the renderer.
		*/
		virtual void Init() = 0;

		/**
		* Calls that should happen before rendering begins.
		*/
		virtual void PreRender() = 0;

		/**
		* Render supplied GameObject.
		*/
		virtual void RenderObject(GameObject* _gameObject) = 0;

		/**
		* Calls that occur after rendering finishes.
		*/
		virtual void EndRender() = 0;

		virtual ~AbstractRenderSystem(){};
	};

}