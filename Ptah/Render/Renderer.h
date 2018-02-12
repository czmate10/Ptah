#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Render/RenderCommand.h"


namespace Ptah
{
	class World;
	class Window;
	class Mesh;

	class Renderer
	{
	public:
		Renderer();

		/**
		 * Sets window to render to
		 */
		inline void AttachWindow(Window* window)
		{
			window_ = window;
		}

		/**
		 * Renders the assigned world
		 */
		void Render(double dt);

		/**
		 * Renders given mesh
		 * @param mesh
		 */
		void RenderMesh(Mesh* mesh);

		/**
		 * Pushes a render command to be processed on the next frame
		 * @param mesh
		 */
		void PushRenderCommand(Mesh* mesh, glm::mat4 transform);

	protected:
		Window* window_;

		std::vector<RenderCommand> render_commands_;


		// Variables used for rendering
		unsigned int depth_buf_;
		unsigned int deferred_fbo_;


		/**
		 * Clears the render commands, should be called on the end of every frame
		 */
		void ClearRenderCommands();
	};
}