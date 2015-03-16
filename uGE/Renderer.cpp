#include "Renderer.hpp"
#include "Body.hpp"
#include "MenuManager.hpp"
#include "SceneManager.hpp"
#include "Camera.hpp"
#include "Light.hpp"

namespace uGE
{
    std::map<Body*, glm::mat4> Renderer::firstPassRender = {};
    std::map<Body*, glm::mat4> Renderer::secondPassRender = {};

    typedef std::map<Body*,glm::mat4>::iterator rIterator;

    Renderer::Renderer()
    {
        //ctor
    }
    Renderer::~Renderer()
    {
        //dtor
    }


    void Renderer::StartRender( sf::RenderWindow * window , std::string source )
    {
    //MENUMANAGER
        if( source == "Menu" )
        {
            for( rIterator i = firstPassRender.begin(); i != firstPassRender.end(); ++i ) {
                Body * body = i->first;

                Shader * shader = body->getShader();
                if( !shader ) { shader = MenuManager::_shader; }
                shader->use();

                MenuManager::_camera->render( shader );
                MenuManager::_light->render( shader );

                body->render( shader, i->second );
            }

            // Second render pass, for transparent objects
            for( rIterator i = secondPassRender.begin(); i != secondPassRender.end(); ++i ) {
                Body * body = i->first;

                Shader * shader = body->getShader();
                if( !shader ) { shader = MenuManager::_shader; }
                shader->use();

                MenuManager::_camera->render( shader );
                MenuManager::_light->render( shader );

                body->render( shader, i->second );
            }
        }
    //SCENEMANAGER
        else if( source == "Game" )
        {
            for( rIterator i = firstPassRender.begin(); i != firstPassRender.end(); ++i ) {
                Body * body = i->first;

                Shader * shader = body->getShader();
                if( !shader ) { shader = SceneManager::_shader; }
                shader->use();

                SceneManager::_camera->render( shader );
                SceneManager::_light->render( shader );

                body->render( shader, i->second );
            }

            // Second render pass, for transparent objects
            for( rIterator i = secondPassRender.begin(); i != secondPassRender.end(); ++i ) {
                Body * body = i->first;

                Shader * shader = body->getShader();
                if( !shader ) { shader = SceneManager::_shader; }
                shader->use();

                SceneManager::_camera->render( shader );
                SceneManager::_light->render( shader );

                body->render( shader, i->second );
            }
        }
    }
}
