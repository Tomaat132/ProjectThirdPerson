#include "SpiritSpawnController.hpp"
#include "SpiritController.hpp"
#include "RotateController.hpp"

#include "GameObject.hpp"
#include "Spirit.hpp"
#include "Body.hpp"

#include "SceneManager.hpp"
#include "AssetManager.hpp"

#include "Material.hpp"
#include "Camera.hpp"


#include "Time.hpp"
#include <iostream>
#include <stdlib.h>

namespace uGE {

    std::vector< Spirit *> SpiritSpawnController::spirits;

	SpiritSpawnController::SpiritSpawnController( GameObject * parent, GameObject * followee )
	:	Controller( parent ), _followee( followee )
	{
	    _timeTillSpawn = 1.0f;
	    _spawnTime = 5.20f;
        srand(time(NULL));

	}

	SpiritSpawnController::~SpiritSpawnController()
	{
		//dtor
	}

	void SpiritSpawnController::update()
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
    void SpiritSpawnController::spawn()
    {
        uGE::Spirit * spirit = new uGE::Spirit( "Spirit");
            uGE::Body * spiritBody = new uGE::Body( spirit );
                spiritBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/spirit.obj" ) );
                spiritBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Textures/bricks.jpg") );
                spiritBody->getMaterial()->setBlendMode( uGE::Material::BlendMode::NORMAL );
            spirit->setBody( spiritBody );

            spirit->setController( new uGE::SpiritController( spirit, _followee) );
           auto temp = uGE::SceneManager::getSpawnLoc().size();
            unsigned int r = rand() % temp;//uGE::SceneManager::getSpawnLoc().end();
           spirit->setPosition(glm::vec3(0.f, 0.f, 0.f));//uGE::SceneManager::getSpawnLoc()[r]);
           spirits.push_back( spirit );
           uGE::SceneManager::add( spirit );
    }
}

