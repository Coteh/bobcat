#pragma once

#include "Clock.h"
#include "AbstractWindower.h"
#include "LogManager.h"
#include "ConfigHolder.h"
#include "AbstractInputSystem.h"
#include "AbstractRenderSystem.h"
#include "ShaderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "PLYModelReader.h"
#include "CollisionMath.h"
#include "Ray.h"
#include "GameObjectCreator.h"

#define GAME_RUNNING true
#define GAME_END false

#define ENGINE_INIT 1
#define ENGINE_CONSTRUCT 0

//#define WINDOWING_GLFW
#define WINDOWING_SFML

#define CONFIG_FILE "bobcat.config"

namespace bobcat {

	/**
	* The heart of the game engine.
	* Centralizes all the main parts of the engine as
	* well as contains the proper initalization methods to start.
	*/
	class Engine {
	private:
		Camera* m_mainCamera; /**< Private reference to the main camera of the Engine. Can be publicly accessed from the mainCamera property. */
	protected:
		AbstractWindower* window; /**< The current window in use by the engine. */
		LogManager* logManager; /**< The log manager instance used by the engine. */
		ConfigHolder* configHolder; /**< The config holder. */
		AbstractInputSystem* inputSystem; /**< The current input system in use by the engine. */
		AbstractRenderSystem* renderer; /**< The current rendering system used by the engine. */
		SceneManager* sceneManager; /**< The scene manager used by the engine. */
		ResourceManager* resourceManager; /**< The resource manager used by the engine. */
		ShaderManager* shaderManager; /**< The shader manager used by the engine. */

		/**
		* Returns the main camera of the Engine.
		* @note This is used in the mainCamera property and can also be called from there.
		*/
		Camera* getMainCamera();
		/**
		* Sets the main camera of the Engine.
		* @note This is used in the mainCamera property and can also be called from there.
		*/
		void setMainCamera(Camera* _camera);
		/**
		* Property to access the main camera used in the Engine.
		*/
		__declspec(property(get = getMainCamera, put = setMainCamera)) Camera* mainCamera;

		float gameTime = 0.0f; /**< Total game time since the engine started. */
		float deltaTime = 0.016f; /**< Total time for the current frame. */
		bool isGameRunning; /**< Is the engine/game currently running? */
	public:
		/**
		* Default constructor for the engine.
		* Will construct the engine with default settings.
		*/
		Engine();

		/**
		* Run the default constructor as well as provide
		* custom settings for the engine upon construction.
		*/
		Engine(int _engineCmd);

		/**
		* Engine destructor.
		*/
		virtual ~Engine();

		/**
		* Returns a bool indicating whether the game is running or not.
		*/
		bool getIsGameRunning();

		/**
		* Returns a bool indicating whether there is a window running or not.
		*/
		bool getIsWindowRunning();

		/**
		* Set screen dimensions of a window directly from the Engine.
		*/
		void setScreenDimensions(int _width, int _height);

		/**
		* Set the Game Running boolean state.
		*/
		void setGameRunning(bool _expression);

		/**
		* Initalize the game engine.
		*/
		virtual void Init();

		/**
		* Key Event callback method.
		*/
		virtual void OnKeyEvent();

		/**
		* Window Resize callback method.
		*/
		virtual void OnWindowResize(int _width, int _height);

		/**
		* Update method for the game engine.
		*/
		virtual void Update();

		/**
		* Separate update method for input checking.
		*/
		virtual void InputUpdate();

		/**
		* Calls that will be made before rendering begins.
		*/
		void DrawBegin();

		/**
		* The main draw/rendering method.
		*/
		virtual void Draw();

		/**
		* Calls that will be made after rendering finishes.
		*/
		void DrawEnd();

		/**
		* Call the game loop.
		*/
		void Run();

		/**
		* Returns the Windowing System currently in use.
		* @note Right now it's really only used to set observers.
		*/
		AbstractWindower* getWindower();

		/**
		* Returns the Input System currently in use.
		* @note Right now it's really only used to set observers.
		*/
		AbstractInputSystem* getInputSystem();
	};

}