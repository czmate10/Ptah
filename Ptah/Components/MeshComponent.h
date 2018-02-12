#pragma once
#include <vector>
#include "Components/Component.h"
#include "Components/TransformComponent.h"

namespace Ptah
{
	class Mesh;

	class MeshComponent : public Component
	{
	public:
		bool CastShadow = true;
		bool ReceiveShadow = true;

		MeshComponent();

		~MeshComponent();

		void OnParentAdded();

		MeshComponent* Clone()
		{
			// TODO
			return new MeshComponent();
		}

		/**
		 * Get all meshes registered
		 * @return meshes
		 */
		inline std::vector<Mesh*> GetMeshes()
		{
			return meshes_;
		}

		/**
		 * Register a mesh
		 * @param mesh mesh to register
		 */
		void AddMesh(Mesh* mesh);

		/**
		 * Registers meshes to be rendered by the global renderer
		 * Should be called by event-system only
		 */
		void PreRender(Event* ev);

	private:
		std::vector<Mesh*> meshes_;
		TransformComponent* transform_;
	};
}