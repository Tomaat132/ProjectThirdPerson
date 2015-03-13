#include "MenuManager.hpp"
#include <GL/glew.h>

#include "Utils/glm.hpp"
#include "Utils/FPS.hpp"

#include "Camera.hpp"
#include "Time.hpp"
#include "GameObject.hpp"
#include "Body.hpp"
#include "Hud.hpp"
#include "Light.hpp"
#include "Shader.hpp"
#include "CollisionDetection.hpp"
#include "Renderer.hpp"

namespace uGE {


	Camera * MenuManager::_camera;
	Light * MenuManager::_light;
	Shader * MenuManager::_shader;
    Hud * MenuManager::_hud;
	std::vector< GameObject * > MenuManager::_objects;
	std::vector< GameObject * > MenuManager::_deleteQueue;
    std::vector< glm::vec3 > MenuManager::_spawnLocations;
	CollisionDetection * MenuManager::_collision;

	MenuManager::MenuManager()
	{
		//ctor
	}

	MenuManager::~MenuManager()
	{
	}

	void MenuManager::add( Camera * camera )
	{
		_camera = camera;
	}

	void MenuManager::add( GameObject * object )
	{
		_objects.push_back( object );

	}

	void MenuManager::add( Light * light )
	{
		_light = light;
	}

	void MenuManager::add( Shader * shader )
	{
		_shader = shader;
	}
	void MenuManager::addSpawnLoc( glm::vec3 spawnLoc )
	{
		_spawnLocations.push_back(spawnLoc);
	}
	std::vector< glm::vec3 >& MenuManager::getSpawnLoc()
	{
		return _spawnLocations;
	}
    void MenuManager::del( GameObject * object )
	{
		_deleteQueue.push_back( object );
	}

	bool MenuManager::control( sf::Window * window )
	{
		sf::Event event;
		while( window->pollEvent( event ) ) { // we must empty the event queue
			if ( event.type == sf::Event::Closed ) {
				return false; // stop the game asap
			}
		}
		return true; // continue running
	}

	void MenuManager::render( sf::RenderWindow * window )
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

        Renderer::StartRender( window, "Menu");
        //window->clear( sf::Color::White );
        _hud->draw( window );
		window->display();
	}

    int u=0;

	void MenuManager::update()
	{
	    Time::update();
	    FPS::update();
		_camera->update();
		_light->update();

		for ( unsigned int i = 0; i < _objects.size(); i++ ) {
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

		//u++;
         //   uGE::GameObject * zombie = new uGE::GameObject( "Zombie");

         //  uGE::MenuManager::add( zombie );
        //std::cout << u << " zombies created"<<std::endl;
	}
}
