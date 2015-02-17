#include "MyGame.hpp"

#include "uGE/SceneManager.hpp"
#include "uGE/AssetManager.hpp"
#include "uGE/Animation.hpp"
#include "uGE/Body.hpp"
#include "uGE/Camera.hpp"
#include "uGE/Controller.hpp"
#include "uGE/GameObject.hpp"
#include "uGE/Light.hpp"
#include "uGE/Mesh.hpp"
#include "uGE/Texture.hpp"
//
#include "uGE/Colliders/SphereCollider.hpp"
#include "Collider.hpp"
//
#include "uGE/Controllers/FollowController.hpp"
#include "uGE/Controllers/WasdController.hpp"
#include "uGE/Controllers/RotateController.hpp"
#include "uGE/Controllers/ParticleController.hpp"


MyGame::MyGame()
{
	//ctor
}

MyGame::~MyGame()
{
	//dtor
}
/*
bool MyGame::load()
{
	uGE::SceneManager::add( uGE::Shader::load( "Shaders/basic.vs", "Shaders/basic.fs") );
		uGE::Camera * camera = new uGE::Camera( "Camera", glm::vec3( 0, 3, -8 ) );
		uGE::Light * light = new uGE::Light( "Sun" );

		uGE::GameObject * floor = new uGE::GameObject( "Floor" );
			uGE::Body * floorBody = new uGE::Body( floor );
				floorBody->setMesh( uGE::AssetManager::loadMesh( "Assets/plane.obj" ) );
				floorBody->setTexture( uGE::AssetManager::loadTexture( "Assets/land.jpg") );
			floor->setBody( floorBody );
			floor->setController( new uGE::ParticleController( floor, camera ) );
			glm::mat4 & transform = floor->transform;
			transform = glm::scale( transform, glm::vec3( 2.0f, 1.0f, 2.0f ) );
            camera->setController( new uGE::WasdController(camera));
	uGE::SceneManager::add( camera );
	uGE::SceneManager::add( light );
	uGE::SceneManager::add( floor );

	return true; // success
}*/

bool MyGame::load()
{
	uGE::SceneManager::add( uGE::Shader::load( "Shaders/basic.vs", "Shaders/basic.fs") );
		uGE::Camera * camera = new uGE::Camera( "Camera", glm::vec3( 0, 3, -8 ) );
		uGE::Light * light = new uGE::Light( "Sun" );

		uGE::GameObject * floor = new uGE::GameObject( "Floor" );
			uGE::Body * floorBody = new uGE::Body( floor );
				floorBody->setMesh( uGE::AssetManager::loadMesh( "Assets/plane.obj" ) );
				floorBody->setTexture( uGE::AssetManager::loadTexture( "Assets/land.jpg") );
			floor->setBody( floorBody );
			glm::mat4 & transform = floor->transform;
			transform = glm::scale( transform, glm::vec3( 2.0f, 1.0f, 2.0f ) );
		uGE::GameObject * player = new uGE::GameObject( "Player" );
			uGE::Body * playerBody = new uGE::Body( player );
                    //working area.
                    player->setCollider(new uGE::SphereCollider(player,1.45f));
                    playerBody->setAnimation( uGE::Animation::LoadAnimation("Assets/eyes.mov") );
                    //
				playerBody->setMesh( uGE::AssetManager::loadMesh( "Assets/teapot.obj" ) );
				playerBody->setTexture( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
				playerBody->setShader(uGE::Shader::load( "Shaders/diffuse.vs", "Shaders/diffuse.fs"));
			player->setBody( playerBody );
			player->setController( new uGE::WasdController( player ) );

		uGE::GameObject * enemy = new uGE::GameObject( "Enemy" );
			enemy->setPosition( glm::vec3( -2, 0, 0 ) );
			uGE::Body * enemyBody = new uGE::Body( enemy );
				//working area.
				enemy->setCollider(new uGE::SphereCollider(enemy,1.45f));
				//
				enemyBody->setMesh( uGE::Mesh::load( "Assets/suzanna.obj") );
				enemyBody->setTexture( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
				enemy->setBody( enemyBody );
				enemy->setController( new uGE::ParticleController( enemy , camera ) );

		camera->setController( new uGE::FollowController( camera, player ) );

	uGE::SceneManager::add( camera );
	uGE::SceneManager::add( light );
	uGE::SceneManager::add( floor );
	uGE::SceneManager::add( player );
	uGE::SceneManager::add( enemy );

	return true; // success
}

