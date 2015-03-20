#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Utils/glm.hpp"

namespace uGE {

	class Camera;
	class GameObject;
	class Light;
	class Shader;
	class Player;
	class Hud;
	class CollisionDetection;

	class SceneManager
	{
		private:
			static std::vector< GameObject * > _objects;
			static std::vector< GameObject * > _deleteQueue;

			static CollisionDetection * _collision;

		public:
			SceneManager();
			virtual ~SceneManager();

			static Camera * _camera;
			static Light * _light;
			static Hud * _hud;
			static Shader * _shader;
			static Player * _player;

			static bool paused;
			static bool fullscreen;

            static std::vector< glm::vec3 > _spawnLocations;
            static std::vector< glm::vec3 > _zombieSpawnLocations;
			static void add( Camera * camera );
			static void add( GameObject * object );
			static void del( GameObject * delObject );
			static void add( Light * light );
			static void add( Shader * shader );
			static void addSpawnLoc( glm::vec3 aSpawnLoc );
			static void addZombieSpawnLoc( glm::vec3 aSpawnLoc );
			static std::vector< glm::vec3 >& getSpawnLoc();

			static bool control( sf::RenderWindow * window );

			static void render( sf::RenderWindow * window );
			static void update();

	};
}
#endif // SCENEMANAGER_H
