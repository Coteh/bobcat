#pragma once
#include "Component.h"
#include <glm\glm.hpp>

namespace bobcat {

	/**
	* Camera is a component that represents a view in graphics rendering environments.
	* A view represents the position from which a scene will be viewed.
	* Camera also contains the viewing frustum.
	*/
	class Camera : public Component {
	private:
		glm::mat4 view;
		glm::mat4 projection;
		int screenWidth, screenHeight;
		float zoom;

		Camera* parentCamera;
	public:
		Camera();
		virtual ~Camera();

		/**
		* Get a Matrix4x4 representing the View.
		* @return Matrix4x4 that represents View.
		*/
		glm::mat4 getView();

		/**
		* Get a Matrix4x4 representing the viewing frustum.
		* @return Matrix4x4 that represents the viewing frustum.
		*/
		glm::mat4 getProjection();

		/**
		* Set the size of the viewing frustum.
		* @param _width Width of the viewing plane.
		* @param _height Height of the viewing plane.
		*/
		void setCameraScreenDimensions(int _width, int _height);

		/**
		* Set zoom of the viewing frustum.
		* @param _zoom Float value representing camera zoom.
		*/
		void setZoom(float _zoom);

		/**
		* Increment viewing frustum zoom.
		* @param _zoom Float value representing amount to increase zoom by.
		*/
		void IncrementZoom(float _zoom);

		/**
		* Update the camera View matrix.
		*/
		void UpdateCamera();

		/**
		* Update the camera viewing frustum/projection matrix.
		*/
		void UpdateProjection();

		virtual void Update(float _deltaTime);
	};

}