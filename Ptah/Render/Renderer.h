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
	class Light;

	class IRenderer
	{
	public:
		virtual ~IRenderer()
		{}

		/**
		 * Renders the whole world
		 */
		virtual void Render(double dt) = 0;
		
		/**
		 * Adds a mesh to draw on next render
		 */
		virtual void AddMesh(RenderCommandMesh cmd) = 0;
		
		/**
		 * Adds a light to draw on next render
		 */
		virtual void AddLight(RenderCommandLight cmd) = 0;

	private:

		/**
		 * Clears the render commands, should be called on the end of every frame
		 */
		virtual void ClearRenderCommands() = 0;
	};


	class Renderer
	{
	public:
		Renderer();

		void Render(double dt);
		void AddMesh(RenderCommandMesh cmd);
		void AddLight(RenderCommandLight cmd);


	protected:
		std::vector<RenderCommandMesh> render_commands_meshes_;
		std::vector<RenderCommandLight> render_commands_lights_;
		
		/**
		 * Renders given mesh
		 */
		void RenderMesh(Mesh* mesh);
		void ClearRenderCommands();
	};
}