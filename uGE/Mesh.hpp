#ifndef MESH_H
#define MESH_H

#include <cstring> // for memcopy
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include "Utils/glm.hpp"

#include "Shader.hpp"

namespace uGE {
	class Shader;
	class Mesh
	{
		private:

			GLuint _name;
			GLuint _vbos[6];

			glm::vec3 _tangent;
			glm::vec3 _bitangent;

			std::vector< unsigned int > _indices; // index to the v/n/t/u/
			std::vector< glm::vec3 > _vertices; // all the vertices
			std::vector< glm::vec3 > _normals; // normal to the vertex
			std::vector< glm::vec2 > _uvs; // uv to the vertex
			std::vector< glm::vec3 > _tangents; // tangents
			std::vector< glm::vec3 > _bitangents; // bitangents

		public:
			Mesh();
			virtual ~Mesh();

			GLuint getIndexBuffer();
			GLuint getVertexBuffer();
			GLuint getNormalBuffer();
			GLuint getUvBuffer();
			GLuint getTangentBuffer();
			GLuint getBitangentBuffer();
			unsigned int size();


			static Mesh * load( std::string );
            void calculateTangents();


		private:
			GLuint createBuffers();

			struct Face { // for loading and converting to indexed arrays
				unsigned int v, n, t;
				bool operator<(const Face other) const{ // needed for use as key in map
					return memcmp((void*)this, (void*)&other, sizeof(Face))>0;
				}
			};

	};
}
#endif // MESH_H
