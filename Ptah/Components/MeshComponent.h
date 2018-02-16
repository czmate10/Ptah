#pragma once
#include <vector>
#include "Components/Component.h"
#include "Components/TransformComponent.h"

namespace Ptah
{
	class Mesh;
	class Material;

	class MeshComponent : public Component
	{
	public:
		bool CastShadow = true;
		bool ReceiveShadow = true;

		MeshComponent();

		~MeshComponent();

		void OnParentAdded()
		{}

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

		/**
		 * Sets material to render meshes with
		 */
		inline void SetMaterial(Material* mat)
		{
			material_ = mat;
		}

		/**
		 * Get material
		 */
		inline Material* GetMaterial()
		{
			return material_;
		}

	private:
		std::vector<Mesh*> meshes_;
		Material* material_;
	};
}