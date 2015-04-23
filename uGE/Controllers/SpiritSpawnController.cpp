#include "SpiritSpawnController.hpp"
#include "SpiritController.hpp"
#include "RotateController.hpp"

#include "GameObject.hpp"
#include "Spirit.hpp"
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

	SpiritSpawnController::SpiritSpawnController( GameObject * parent, Player * followee )
	:	Controller( parent ), _followee( followee )
	{
	    _timeTillSpawn = 1.0f;
	    _spawnTime = 2.50f;
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
        bool cantSpawn = false;
        uGE::Spirit * spirit = new uGE::Spirit( "Spirit");
            uGE::Body * spiritBody = new uGE::Body( spirit );
                spiritBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/spirit.obj"));
                spiritBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Textures/spirit.png") );
                spiritBody->getMaterial()->setBlendMode( uGE::Material::BlendMode::ALPHA );
            spirit->setBody( spiritBody );

           auto temp = uGE::SceneManager::getSpawnLoc().size();
            unsigned int r = rand() % temp;
            for (unsigned int i = 0; i < spirits.size(); i++){
                if(glm::length(spirits[i]->getPosition()- uGE::SceneManager::getSpawnLoc()[r]) < 12.f)
                {
                    cantSpawn = true;
                }
               // std::cout<< glm::length(spirits[i]->getPosition()- uGE::SceneManager::getSpawnLoc()[r]) << std::endl;
            }
          if(!cantSpawn){
               spirit->setPosition(uGE::SceneManager::getSpawnLoc()[r]+glm::vec3(0.f, 3.f, 0.f));
               spirit->setController( new uGE::SpiritController( spirit, _followee) );

               spirits.push_back( spirit );
               uGE::SceneManager::add( spirit );
          }
    }
}

