#pragma once
#define FPS 144.0
#define MS_PER_UPDATE (1.0/FPS) // FPS

// Game applications using this engine should be able to use most of the engine's stuff by including this file
#include "World.h"
#include "Window.h"
#include "Events/EventDispatcher.h"
#include "Entities/EntityManager.h"

namespace Ptah
{
	class Renderer;

	class Engine
	{
	public:
		~Engine();

		/**
		 * Returns the instance of the engine
		 */
		static Engine& Instance();

		/**
		 * Initialize the engine
		 */
		void Init();

		/**
		 * Frees up resources used by the engine and closes window
		 */
		void Shutdown();

		/**
		 * Enter the game loop
		 */
		void StartLoop();

		/**
		 * Returns smart pointer of window
		 */
		inline Window* GetWindow()
		{
			return window_;
		}

		/**
		 * Sets the window title
		 */
		void SetWindowTitle(const char* title);

		/**
		 * Returns contents of file relative to the working dir
		 */
		std::string ReadFile(std::string path);

		/**
		 * Sets the active camera
		 */
		inline void SetCamera(CameraComponent* camera)
		{
			camera_ = camera;
		}

		/**
		 * Gets the active camera
		 */
		inline CameraComponent* GetCamera()
		{
			return camera_;
		}

		/**
		 * Get the renderer
		 */
		inline Renderer* GetRenderer()
		{
			return renderer_;
		}

		/**
		 * Get the game world
		 */
		inline World* GetWorld()
		{
			return world_;
		}

		/**
		 * Set the game world
		 */
		inline void SetWorld(World* world)
		{
			world_ = world;
		}

		/**
		 * Get the event_dispatcher object
		 */
		inline EventDispatcher* GetEventDispatcher()
		{
			return event_dispatcher_;
		}

	protected:
		Window* window_;
		EventDispatcher* event_dispatcher_;
		Renderer* renderer_;
		World* world_;
		CameraComponent* camera_ = nullptr;

	private:
		static Engine instance_;
		Engine();
	};
}
