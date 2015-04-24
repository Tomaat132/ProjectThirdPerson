#include "MyGame.hpp"

#include "uGE/SceneManager.hpp"
#include "uGE/AssetManager.hpp"
#include "uGE/Animation.hpp"
#include "uGE/SoundManager.hpp"
#include "uGE/Body.hpp"
#include "uGE/Camera.hpp"
#include "uGE/Controller.hpp"
#include "uGE/GameObject.hpp"
#include "uGE/LevelLoader.hpp"
#include "uGE/Hud.hpp"
#include "uGE/Light.hpp"
#include "uGE/Material.hpp"
#include "uGE/Mesh.hpp"
#include "uGE/Texture.hpp"
#include "uGE/Viking.hpp"
#include "uGE/WinSequence.hpp"
//
#include "uGE/Colliders/SphereCollider.hpp"
#include "uGE/Colliders/BoxCollider.hpp"
#include "Collider.hpp"
//
#include "uGE/Controllers/FollowController.hpp"
#include "uGE/Controllers/WasdController.hpp"
#include "uGE/Controllers/RotateController.hpp"
#include "uGE/Controllers/PlayerController.hpp"
#include "uGE/Controllers/ParticleController.hpp"
#include "uGE/Controllers/ZombieSpawnController.hpp"
#include "uGE/Controllers/SpiritSpawnController.hpp"
#include "uGE/SoundManager.hpp"


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
    uGE::AssetManager::loadMesh( "Assets/Models/Zombie_walk/Zombie_idle.obj" );
	uGE::AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_1.obj" );
	uGE::AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_2.obj" );
	uGE::AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_3.obj" );
	uGE::AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_4.obj" );
    uGE::AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_5.obj" );
	uGE::AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_6.obj" );
	uGE::AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_7.obj" );
    uGE:: AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_8.obj" );
    uGE::AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_9.obj" );
	uGE::AssetManager::loadMesh( "Assets/Models/Zombie_attack/Z_A_1.obj" );
    uGE::AssetManager::loadMesh( "Assets/Models/Zombie_attack/Z_A_2.obj" );
    uGE::AssetManager::loadMesh( "Assets/Models/Zombie_death/Z_D_1.obj" );
    uGE::AssetManager::loadMesh( "Assets/Models/Zombie_death/Z_D_2.obj" );
    uGE::AssetManager::loadTexture( "Assets/Models/Undertaker_walk/UV_texture.png");
    uGE::AssetManager::loadMesh( "Assets/Models/bullet.obj" );  //change model
    uGE::AssetManager::loadTexture( "Assets/Textures/bullet.png");     //change texture
    uGE::AssetManager::loadTexture( "Assets/Textures/hitUV.png");
    uGE::AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_1.obj" ) ;
    uGE::AssetManager::loadTexture( "Assets/Models/Zombie_walk/zombie 1 texture1.png");
    uGE::AssetManager::loadTexture( "Assets/Textures/viking.png" ); // Load texture beforehand. So it won't do it ingame which causes lag
	uGE::SceneManager::add( uGE::Shader::load( "Shaders/diffuse.vs", "Shaders/diffuse.fs") );
    uGE::Camera * camera = new uGE::Camera( "Camera", glm::vec3( 0, 10, -12 ) );
    uGE::Light * light = new uGE::Light( "Sun" );

    uGE::Player * player = new uGE::Player();
        uGE::Body * playerBody = new uGE::Body( player );
            playerBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/Undertaker_walk/U_W_Idle.obj" ) );
            //playerBody->setAnimation( uGE::Animation::LoadAnimation("Assets/Animations/eyes.mov") );
            playerBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Models/Undertaker_walk/UV_texture.png") );
        player->setBody( playerBody );
        //player->setCollider( new uGE::BoxCollider(player) );
        player->setCollider( new uGE::SphereCollider( player, 0.75f ) );
        player->setController( new uGE::PlayerController( player ) );
        player->getMaterial()->setBlendMode( uGE::Material::BlendMode::NORMAL );
    uGE::SceneManager::_player = player;

    uGE::LevelLoader loader = uGE::LevelLoader();
    loader.loadLevel( "week 5 level tuesday" );

    //loader.loadLevel( "last level" );

    uGE::GameObject * zombieSpawn = new uGE::GameObject( "ZombieSpawn" );
        zombieSpawn->setController(new uGE::ZombieSpawnController( zombieSpawn, camera ));

    uGE::GameObject * spiritSpawn = new uGE::GameObject( "SpiritSpawn" );
        spiritSpawn->setController(new uGE::SpiritSpawnController( spiritSpawn, player ));

    camera->setController( new uGE::FollowController( camera, player ) );
    //camera->setController( new uGE::PlayerController( camera ) );

	uGE::SceneManager::add( camera );
	uGE::SceneManager::add( light );
	uGE::SceneManager::add( zombieSpawn );
	uGE::SceneManager::add( spiritSpawn );

	uGE::SceneManager::_hud = new uGE::Hud();
    uGE::SoundManager::init();
    uGE::SoundManager::getBGM("background_sound");
	return true;
}

