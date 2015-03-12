#include "MyMenu.hpp"

#include "uGE/MainMenu/MenuManager.hpp"
#include "uGE/AssetManager.hpp"
#include "uGE/Animation.hpp"
#include "uGE/Body.hpp"
#include "uGE/Camera.hpp"
#include "uGE/Controller.hpp"
#include "uGE/GameObject.hpp"
#include "uGE/Light.hpp"
#include "uGE/Mesh.hpp"
#include "uGE/Texture.hpp"

#include "uGE/Controllers/MenuController.hpp"


MyMenu::MyMenu()
{
	//ctor
}

MyMenu::~MyMenu()
{
	//dtor
}

bool MyMenu::load()
{
	uGE::MenuManager::add( uGE::Shader::load( "Shaders/diffuse.vs", "Shaders/diffuse.fs") );
    uGE::Camera * camera = new uGE::Camera( "Camera", glm::vec3( 0, 10, -12 ) );
    uGE::Light * light = new uGE::Light( "Sun" );

    uGE::GameObject * menuBoard = new uGE::GameObject( "MenuBoard" );
    uGE::Body * menuBody = new uGE::Body( menuBoard );
            menuBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/plane20x20_2tris.obj" ) );
            menuBody->setTexture( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
        menuBoard->setBody( menuBody );
    menuBoard->setPosition( glm::vec3( 0.f, 0.f, 0.f ) );
    menuBoard->setRotation( glm::vec3( -90.f, 0.f, 0.f ) );
    menuBoard->setController( new uGE::MenuController( menuBoard ) );

    uGE::MenuManager::add( camera );
    uGE::MenuManager::add( light );
	return true;
}

