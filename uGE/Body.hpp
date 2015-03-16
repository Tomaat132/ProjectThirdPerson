#ifndef BODY_H
#define BODY_H

#include "GameObject.hpp"
#include "Utils/glm.hpp"
#include "Shader.hpp"

namespace uGE {

    class Material;
	class Mesh;
	class Animation;

	class Body
	{
		private:
			GameObject * _parent;
			Mesh * _mesh;
			Animation * _animation;
			Texture * _texture;
			Shader * _shader;
			Material * _material;
			glm::vec4 _outlineColor;

		public:
			Body( GameObject * parent );
			virtual ~Body();

			void render( Shader * shader, glm::mat4 & transform );
			void setMesh( Mesh * mesh );
			Mesh * getMesh();
			std::string getParentName();
			void setAnimation( Animation * animation );
			Animation * getAnimation();
			void setTexture( Texture * texture );
			void setShader( Shader * shader);
			void setMaterial( Material * material );
            void setOutlineColor( glm::vec4 color );
			Shader * getShader();
			Material * getMaterial();
	};
}
#endif // BODY_H
