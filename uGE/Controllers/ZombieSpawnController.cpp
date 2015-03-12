#include "ZombieSpawnController.hpp"
#include "ParticleController.hpp"
#include "ZombieController.hpp"

#include "GameObject.hpp"
#include "Zombie.hpp"

#include "SceneManager.hpp"
#include "AssetManager.hpp"

#include "Body.hpp"
#include "Material.hpp"
#include "Camera.hpp"


#include "Time.hpp"
#include <iostream>
#include <stdlib.h>

namespace uGE {

    std::vector< Zombie *> ZombieSpawnController::zombies;

	ZombieSpawnController::ZombieSpawnController( GameObject * parent, GameObject * followee )
	:	Controller( parent ), _followee( followee )
	{
	    _timeTillSpawn = 1.0f;
	    _spawnTime = 5.10f;
        srand(time(NULL));

	}

	ZombieSpawnController::~ZombieSpawnController()
	{
		//dtor
	}

	void ZombieSpawnController::update()
	{
	    _timeTillSpawn -= Time::step();


		//spawn zombie
        if(_timeTillSpawn <= 0)
        {
            for(auto i = 0; i < 1; i++)
                spawn();
            _timeTillSpawn = _spawnTime;
        }

	}
    void ZombieSpawnController::spawn()
    {
        /*uGE::Zombie* zombie = new uGE::Zombie( "Zombie");
             uGE::Body * zombieBody = new uGE::Body( zombie );
                zombieBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/suzanna.obj" ) );
                zombieBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Textures/bricks.jpg") );
                zombieBody->getMaterial()->setBlendMode( Material::BlendMode::NORMAL );
            zombie->setBody( zombieBody );
            zombie->setController( new uGE::ZombieController( zombie, _followee) );
           auto temp = uGE::SceneManager::getSpawnLoc().size();
            unsigned int r = rand() % temp;//uGE::SceneManager::getSpawnLoc().end();
           zombie->setPosition(uGE::SceneManager::getSpawnLoc()[r]);
           zombies.push_back( zombie );
<<<<<<< HEAD
           uGE::SceneManager::add( zombie );
           std::cout << "ZOMBIE" << std::endl;
=======
           uGE::SceneManager::add( zombie );*/
    }
}

