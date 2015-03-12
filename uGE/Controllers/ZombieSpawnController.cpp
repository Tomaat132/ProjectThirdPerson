#include "ZombieSpawnController.hpp"
#include "ParticleController.hpp"
#include "ZombieController.hpp"

#include "GameObject.hpp"
#include "Zombie.hpp"

#include "SphereCollider.hpp"

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
	    _spawnTime = 10.10f;
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
        if(_timeTillSpawn <= 0 && zombies.size() < 2)
        {
            for(auto i = 0; i < 1; i++)
                spawn();
            _timeTillSpawn = _spawnTime;
        }

	}
    void ZombieSpawnController::spawn()
    {
        uGE::Zombie* zombie = new uGE::Zombie( "Zombie");
             uGE::Body * zombieBody = new uGE::Body( zombie );
                zombieBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/zombie1.obj" ) );
                zombieBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Textures/zombie1.png") );
                zombieBody->getMaterial()->setBlendMode( Material::BlendMode::NORMAL );
            zombie->setBody( zombieBody );
            zombie->setController( new uGE::ZombieController( zombie, _followee) );
            zombie->setCollider( new uGE::SphereCollider(zombie, 1.75f));
           auto temp = uGE::SceneManager::_zombieSpawnLocations.size();
            unsigned int r = rand() % temp;//uGE::SceneManager::getSpawnLoc().end();
           zombie->setPosition(uGE::SceneManager::_zombieSpawnLocations[r]);
           zombies.push_back( zombie );
           uGE::SceneManager::add( zombie );
    }
}

