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
	    _timeTillSpawn = 5.0f;
	    _spawnTime = 2.0f;
        srand(time(NULL));
        _maxZombies = 25;
        _zombieLvlUpTimer = 20.f;

	}

	ZombieSpawnController::~ZombieSpawnController()
	{
		//dtor
	}

	void ZombieSpawnController::update()
	{
	    //if( zombies.size() == 0 )
        _timeTillSpawn -= Time::step();
        _zombieLvlUpTimer -= Time::step();


		//spawn zombie
        if(_timeTillSpawn <= 0 && zombies.size() < _maxZombies)
        {
            for(auto i = 0; i < 1; i++)
                spawn();
            _timeTillSpawn = _spawnTime;
        }
        if(_zombieLvlUpTimer <= 0) {
                SceneManager::zombieLevel += 1;
                _zombieLvlUpTimer = 10*_spawnTime;

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

