#include "SceneManager.hpp"
#include <GL/glew.h>

#include "Utils/glm.hpp"
#include "Utils/FPS.hpp"

#include "Camera.hpp"
#include "Time.hpp"
#include "GameObject.hpp"
#include "Body.hpp"
#include "Light.hpp"
#include "Shader.hpp"
#include "CollisionDetection.hpp"
#include "SpiritSpawnController.hpp"
#include "ZombieSpawnController.hpp"
#include "Renderer.hpp"

#include "Player.hpp"

namespace uGE {


	Camera * SceneManager::_camera;
	Light * SceneManager::_light;
	Shader * SceneManager::_shader;
	Player * SceneManager::_player;
	std::vector< GameObject * > SceneManager::_objects;
	std::vector< GameObject * > SceneManager::_deleteQueue;
    std::vector< glm::vec3 > SceneManager::_spawnLocations;
    std::vector< glm::vec3 > SceneManager::_zombieSpawnLocations;
	CollisionDetection * SceneManager::_collision;

	SceneManager::SceneManager()
	{
		//ctor
	}

	SceneManager::~SceneManager()
	{
		//dtor
	}

	void SceneManager::add( Camera * camera )
	{
		_camera = camera;
	}

	void SceneManager::add( GameObject * object )
	{
		_objects.push_back( object );

	}

	void SceneManager::add( Light * light )
	{
		_light = light;
	}

	void SceneManager::add( Shader * shader )
	{
		_shader = shader;
	}
	void SceneManager::addSpawnLoc( glm::vec3 spawnLoc )
	{
		_spawnLocations.push_back(spawnLoc);
	}
	void SceneManager::addZombieSpawnLoc( glm::vec3 spawnLoc )
	{
		_zombieSpawnLocations.push_back(spawnLoc);
	}
	std::vector< glm::vec3 >& SceneManager::getSpawnLoc()
	{
		return _spawnLocations;
	}
    void SceneManager::del( GameObject * object )
	{
		_deleteQueue.push_back( object );
	}

	bool SceneManager::control( sf::Window * window )
	{
		sf::Event event;
		while( window->pollEvent( event ) ) { // we must empty the event queue
			if ( event.type == sf::Event::Closed ) {
				return false; // stop the game asap
			}
		}
		return true; // continue running
	}

	void SceneManager::render( sf::Window * window )
	{
        glEnable( GL_DEPTH_TEST ); // must be enables after after use program
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        Renderer::firstPassRender.clear();
        Renderer::secondPassRender.clear();

        glm::mat4 parent;
        _player->render( _shader, parent );

        for ( auto i = _objects.begin(); i != _objects.end(); ++i ) {
            GameObject * object = (GameObject*) *i;
            object->render( _shader, parent );
        }

        Renderer::StartRender();
		window->display();
	}
 int k=0;
	void SceneManager::update()
	{
	    Time::update();
	    FPS::update();
        _collision->update(_objects);
		_camera->update();
		_light->update();
		_player->update();

		for ( unsigned int i = 0; i < _objects.size(); i++ ) {
			GameObject * object = _objects[i];
			object->update();
			//std::cout << object->getName() << std::endl;
		}

		//for ( auto j = _deleteQueue.begin(); j != _deleteQueue.end(); ++j ) {
		for ( auto j = 0; j != _deleteQueue.size(); ++j ) {
			GameObject * object = _deleteQueue[j];
			auto position = std::find(_objects.begin(), _objects.end(), object);
			auto positionSpirit = std::find(SpiritSpawnController::spirits.begin(), SpiritSpawnController::spirits.end(), object);
			auto positionZombie = std::find(ZombieSpawnController::zombies.begin(), ZombieSpawnController::zombies.end(), object);

			if( positionSpirit < SpiritSpawnController::spirits.end() ) {
                SpiritSpawnController::spirits.erase( positionSpirit );
			}
			if( positionZombie < ZombieSpawnController::zombies.end() ) {
                ZombieSpawnController::zombies.erase( positionZombie );
			}
			if( position < _objects.end() ) {
                _objects.erase( position );
			}
            delete object;

			//
		}

		_deleteQueue.clear();
	}

}
