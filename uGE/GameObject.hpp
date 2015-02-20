#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "utils/glm.hpp"

#include "Shader.hpp"


namespace uGE {

	class Body;
	class Collider;
	class Controller;
	class GameObject
	{
		public:
			glm::mat4 & transform;

		protected:
			std::string _name;
			glm::mat4 _transform;
			glm::mat4 _animTransform;

			std::vector< GameObject * > children;
			std::vector<Collider * > _colliders;

			Body * _body;
			Controller * _controller;

		public:
			GameObject( std::string name );
			virtual ~GameObject();

			std::string getName();

			void addChild( GameObject * child );
			GameObject * getChildWithName(std::string childName);
			void setBody( Body * body );
			Body * getBody();
			void setCollider( Collider * collider );
			void setController( Controller * controller );
			void setAnimTransform( glm::mat4 & animTransform );
			void render( Shader * shader, glm::mat4 & parentTransform );
			void update();

			void setPosition( glm::vec3 position );
			std::vector<Collider *> getColliders();
			glm::vec3 getPosition();

	};
}
#endif // GAMEOBJECT_H
