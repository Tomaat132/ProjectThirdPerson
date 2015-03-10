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
#include "Renderer.hpp"

namespace uGE {


	Camera * SceneManager::_camera;
	Light * SceneManager::_light;
	Shader * SceneManager::_shader;
	std::vector< GameObject * > SceneManager::_objects;
	std::vector< GameObject * > SceneManager::_deleteQueue;
    std::vector< glm::vec3 > SceneManager::_spawnLocations;
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

		for ( auto i = 0; i < _objects.size(); i++ ) {
			GameObject * object = _objects[i];
			object->update();
		}

		for ( auto j = _deleteQueue.begin(); j != _deleteQueue.end(); ++j ) {
			GameObject * object = (GameObject*) *j;
			auto position = std::find(_objects.begin(), _objects.end(), object);
			delete object;
			if( position != _objects.end() ) {
                _objects.erase( position );
			}

			//delete object;
		}

		_deleteQueue.clear();

		//k++;
         //   uGE::GameObject * zombie = new uGE::GameObject( "Zombie");

         //  uGE::SceneManager::add( zombie );
        //std::cout << k << " zombies created"<<std::endl;
	}

}
