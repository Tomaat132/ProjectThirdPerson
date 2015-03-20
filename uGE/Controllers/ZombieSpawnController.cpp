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
	    _spawnTime = 1.5f;
        srand(time(NULL));
        _maxZombies = 20;

	}

	ZombieSpawnController::~ZombieSpawnController()
	{
		//dtor
	}

	void ZombieSpawnController::update()
	{
	    _timeTillSpawn -= Time::step();


		//spawn zombie
        if(_timeTillSpawn <= 0 && zombies.size() < _maxZombies)
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
                zombieBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/Zombie_walk/Z_W_1.obj" ) );
                zombieBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Models/Zombie_walk/zombie 1 texture1.png") );
                zombieBody->getMaterial()->setBlendMode( Material::BlendMode::NORMAL );
            zombie->setBody( zombieBody );
            zombie->setController( new uGE::ZombieController( zombie, _followee) );
            zombie->setCollider( new uGE::SphereCollider(zombie, 25.0f));
            zombie->setCollider( new uGE::SphereCollider(zombie, 1.25f, "zombieHitbox"));

           auto temp = uGE::SceneManager::_zombieSpawnLocations.size();
            unsigned int r = rand() % temp;//uGE::SceneManager::getSpawnLoc().end();
           zombie->setPosition(uGE::SceneManager::_zombieSpawnLocations[r]);
           zombies.push_back( zombie );
           uGE::SceneManager::add( zombie );
    }
}

