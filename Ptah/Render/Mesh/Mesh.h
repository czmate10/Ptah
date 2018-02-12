#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Ptah {
	class Mesh {
	public:
		std::vector<glm::vec3> vertices_;
		std::vector<glm::vec3> normals_;
		std::vector<glm::vec2> uvs_;

		std::vector<unsigned int> triangles_;

		~Mesh();

		inline unsigned int GetVao()
		{
			return vao_;
		}

		inline void SetVertices(std::vector<glm::vec3> vertices)
		{
			vertices_ = vertices;
			modified_ = true;
		}
		inline void SetNormals(std::vector<glm::vec3> normals)
		{
			normals_ = normals;
			modified_ = true;
		}
		inline void SetUVs(std::vector<glm::vec2> uvs)
		{
			uvs_ = uvs;
			modified_ = true;
		}
		inline void SetTriangles(std::vector<unsigned int> triangles)
		{
			triangles_ = triangles;
			modified_ = true;
		}

		void Finalize();
	protected:
		unsigned int vao_ = 0; // vertex array object
		unsigned int vbo_ = 0; // vertex buffer object
		unsigned int ebo_ = 0; // element buffer object

		/**
		 * Indicates that the mesh should be reloaded on next render
		 */
		bool modified_ = false;
	};
}