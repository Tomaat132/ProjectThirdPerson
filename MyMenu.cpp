#include "MyMenu.hpp"

#include "uGE/MenuManager.hpp"
#include "uGE/AssetManager.hpp"
#include "uGE/Animation.hpp"
#include "uGE/Body.hpp"
#include "uGE/Camera.hpp"
#include "uGE/Controller.hpp"
#include "uGE/GameObject.hpp"
#include "uGE/Hud.hpp"
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
////    uGE::MenuManager::del(  );
//    delete camera;
//    uGE::MenuManager::del(  );
//    delete light;
//	delete uGE::MenuManager;
}

bool MyMenu::load()
{
	uGE::MenuManager::add( uGE::Shader::load( "Shaders/diffuse.vs", "Shaders/diffuse.fs") );
    uGE::Camera * camera = new uGE::Camera( "Camera", glm::vec3( 0, 10, -12 ) );
    uGE::Light * light = new uGE::Light( "Sun" );

    uGE::GameObject * menuBoard = new uGE::GameObject( "MenuBoard" );
    menuBoard->setController( new uGE::MenuController( menuBoard ) );

    uGE::MenuManager::add( camera );
    uGE::MenuManager::add( light );
    uGE::MenuManager::add( menuBoard );

	uGE::MenuManager::_hud = new uGE::Hud();

	return true;
}

