#include "MyGame.hpp"

#include "uGE/SceneManager.hpp"
#include "uGE/AssetManager.hpp"
#include "uGE/Body.hpp"
#include "uGE/Camera.hpp"
#include "uGE/Controller.hpp"
#include "uGE/GameObject.hpp"
#include "uGE/Light.hpp"
#include "uGE/Mesh.hpp"
#include "uGE/Animation.hpp"
#include "uGE/Texture.hpp"
#include "uGE/Material.hpp"
#include "uGE/LevelLoader.hpp"
//
#include "uGE/Colliders/SphereCollider.hpp"
#include "Collider.hpp"
//
#include "uGE/Controllers/FollowController.hpp"
#include "uGE/Controllers/WasdController.hpp"
#include "uGE/Controllers/RotateController.hpp"
#include "uGE/Controllers/PlayerController.hpp"
#include "uGE/Controllers/ParticleController.hpp"
#include "uGE/Controllers/ZombieController.hpp"


MyGame::MyGame()
{
	//ctor
}

MyGame::~MyGame()
{
	//dtor
}

bool MyGame::load()
{
	uGE::SceneManager::add( uGE::Shader::load( "Shaders/diffuse.vs", "Shaders/diffuse.fs") );
    uGE::Camera * camera = new uGE::Camera( "Camera", glm::vec3( 0, 10, -12 ) );
    uGE::Light * light = new uGE::Light( "Sun" );

    uGE::Player * player = new uGE::Player();
        uGE::Body * playerBody = new uGE::Body( player );
            playerBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/suzanna.obj" ) );
            playerBody->setAnimation( uGE::Animation::LoadAnimation("Assets/Animations/eyes.mov") );
            playerBody->setTexture( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
        player->setBody( playerBody );
        player->setCollider(new uGE::SphereCollider(player,1.45f));
        player->setController( new uGE::PlayerController( player ) );
        player->getMaterial()->setBlendMode( uGE::Material::BlendMode::NORMAL );
        //player->getMaterial()->setAlpha( 0.95f );

    uGE::GameObject * enemy = new uGE::GameObject( "Enemy" );
        enemy->setPosition( glm::vec3( -2, 0, 0 ) );
        uGE::Body * enemyBody = new uGE::Body( enemy );
            enemyBody->setMesh( uGE::Mesh::load( "Assets/Models/suzanna.obj") );
            enemyBody->setTexture( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
        enemy->setBody( enemyBody );
        enemy->setCollider(new uGE::SphereCollider(enemy, 1.45f));
        enemy->setController( new uGE::ParticleController( enemy, camera ) );

    camera->setController( new uGE::FollowController( camera, player ) );
    //camera->setController( new uGE::PlayerController( camera ) );

    uGE::GameObject * water = new uGE::GameObject( "Water" );
        water->setPosition( glm::vec3( 0, 1.5, 0 ) );
        uGE::Body * waterBody = new uGE::Body( water );
            waterBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/water.obj" ) );
            waterBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Textures/water.png" ) );
            waterBody->setShader( uGE::Shader::load( "Shaders/diffuse.vs", "Shaders/water.fs" ) );
        water->setBody( waterBody );
            glm::mat4 &transform = water->transform;
            //transform = glm::rotate( transform, 180.f, glm::vec3(1,0,0) );
//transform = glm::scale( transform, glm::vec3( 80.f, 1.f, 80.f ) );
        water->getMaterial()->setBlendMode( uGE::Material::BlendMode::ALPHA );
        water->getMaterial()->setAlpha( 2.0f );



	uGE::SceneManager::add( camera );
	uGE::SceneManager::add( light );
	//uGE::SceneManager::add( player );
	uGE::SceneManager::_player = player;
	uGE::SceneManager::add( enemy );
	uGE::SceneManager::add( water );


    //working area
        uGE::GameObject * zombie = new uGE::GameObject( "Zombie" );
        uGE::Body * zombieBody = new uGE::Body( zombie );
            zombieBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/test/stump.obj" ) );
            zombieBody->setTexture( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
        zombie->setBody( zombieBody );
        zombie->setController( new uGE::ZombieController( zombie ) );
        uGE::SceneManager::add( zombie );
    //end of working area


	uGE::LevelLoader loader = uGE::LevelLoader();
    loader.loadLevel( "LEVEL v4" );

	return true;
}

