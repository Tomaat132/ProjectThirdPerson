#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Utils/glm.hpp"

namespace uGE {

	class Camera;
	class GameObject;
	class Light;
    class Hud;
	class Shader;

	class CollisionDetection;

	//empty space to add classes above
	class MenuManager
	{
		private:
			static std::vector< GameObject * > _objects;
			static std::vector< GameObject * > _deleteQueue;


			static CollisionDetection * _collision;

		public:
			MenuManager();
			virtual ~MenuManager();

			static Camera * _camera;
			static Hud * _hud;
			static Light * _light;
			static Shader * _shader;

            static std::vector< glm::vec3 > _spawnLocations;
			static void add( Camera * camera );
			static void add( GameObject * object );
			static void del( GameObject * delObject );
			static void add( Light * light );
			static void add( Shader * shader );
			static void addSpawnLoc( glm::vec3 aSpawnLoc );
			static std::vector< glm::vec3 >& getSpawnLoc();

			static bool control( sf::Window * window );

			static void render( sf::RenderWindow * window );
			static void update();

	};
}
#endif // MENUMANAGER_H
