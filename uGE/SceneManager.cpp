#include "SceneManager.hpp"
#include <GL/glew.h>

#include "Utils/glm.hpp"

#include "Camera.hpp"
#include "GameObject.hpp"
#include "Light.hpp"
#include "Shader.hpp"

namespace uGE {

	Camera * SceneManager::_camera;
	Light * SceneManager::_light;
	Shader * SceneManager::_shader;
	std::vector< GameObject * > SceneManager::_objects;

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

			_shader->use(); // select the shader to use
				glEnable( GL_DEPTH_TEST ); // must be enables after after use program
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

				if( _camera ) _camera->render( _shader );
				if( _light ) _light->render( _shader );

				glm::mat4 parent; // id
				for ( auto i = _objects.begin(); i != _objects.end(); ++i ) {
					GameObject * object = (GameObject*) *i;
					object->render( _shader, parent );
				}
		window->display();
	}

	void SceneManager::update()
	{
		_camera->update();
		_light->update();
		for ( auto i = _objects.begin(); i != _objects.end(); ++i ) {
			GameObject * object = (GameObject*) *i;
			object->update();
		}

	}

}
