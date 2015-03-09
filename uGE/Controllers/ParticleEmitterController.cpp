#include "ParticleEmitterController.hpp"
#include "ParticleController.hpp"
#include "GameObject.hpp"
#include "Body.hpp"
#include "SceneManager.hpp"
#include "AssetManager.hpp"
#include "Material.hpp"
#include "Camera.hpp"


#include "Time.hpp"
#include <iostream>
#include <stdlib.h>
namespace uGE {
	ParticleEmitterController::ParticleEmitterController( GameObject * parent, GameObject * followee )
	:	Controller( parent ), _followee( followee )
	{
	    _timeTillEmit = 0.0f;
	    _emitTime = 0.1f;
	    _velocity = glm::vec3(0.f, 4.f, 0.f);
        srand(time(NULL));
	}

	ParticleEmitterController::~ParticleEmitterController()
	{
		//dtor
	}
	void ParticleEmitterController::update()
	{
	    _parent->setPosition( _followee->getPosition());
	    _timeTillEmit -= Time::step();
		//glm::mat4 & transform = _parent->transform;
        //transform = _parent->transform;
        /*std::cout<< transform << std::endl;
		transform = glm::inverse( glm::lookAt( glm::vec3( transform[3] ), glm::vec3( _followee->transform[3] ), glm::vec3( 0,1,0 ) ) );
		transform[2] *= -1;
        */
		//transform = glm::translate( transform, _velocity * Time::step() );

		//shoot particle
        if(_timeTillEmit <= 0)
        {
            _particles.clear();
            for(auto i = 0; i < 5; i++)
            {
                //distortion around a position
                setDistortion(glm::vec3((2.0f * float(rand())/ float(RAND_MAX) -1.0f), (2.0f * float(rand())/ float(RAND_MAX) +3.0f), (2.0f * float(rand())/ float(RAND_MAX) -1.0f)));

                emit();
            }
            _timeTillEmit = _emitTime;
        }
        //getSucked();
	}


    void ParticleEmitterController::emit()
    {
        uGE::GameObject * particle = new uGE::GameObject( "Particle");
             uGE::Body * particleBody = new uGE::Body( particle );
                particleBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/particles.obj" ) );
                particleBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Textures/star02.png") );
                particleBody->getMaterial()->setBlendMode( Material::BlendMode::ALPHA );
            particle->setBody( particleBody );

            particle->setController( new uGE::ParticleController( particle, SceneManager::_camera) );
            particle->setPosition( _parent->getPosition() +_velocity +_distortion);
           uGE::SceneManager::add( particle );
           _particles.push_back( particle );
    }
	void ParticleEmitterController::setVelocity(glm::vec3 aVelocity)
	{
	    _velocity = aVelocity;
	}
	void ParticleEmitterController::setDistortion(glm::vec3 aDistortion)
	{
	    _distortion = aDistortion;
	}
}

