#include "ParticleEmitterController.hpp"
#include "ParticleController.hpp"
#include "GameObject.hpp"
#include "Body.hpp"
#include "GameObject.hpp"
#include "SceneManager.hpp"
#include "AssetManager.hpp"
#include "Material.hpp"
#include "Camera.hpp"


#include "Time.hpp"
#include <iostream>
namespace uGE {
	ParticleEmitterController::ParticleEmitterController( GameObject * parent, GameObject * followee )
	:	Controller( parent ), _followee( followee )
	{
	    _timeTillEmit = 0.0f;
	    _emitTime = 0.4f;

	    std::cout << SceneManager::_camera->getName() << std::endl;
	}

	ParticleEmitterController::~ParticleEmitterController()
	{
		//dtor
	}

	void ParticleEmitterController::update()
	{
	    _timeTillEmit -= Time::step();
		glm::mat4 & transform = _parent->transform;
        transform = _followee->transform;
        /*std::cout<< transform << std::endl;
		transform = glm::inverse( glm::lookAt( glm::vec3( transform[3] ), glm::vec3( _followee->transform[3] ), glm::vec3( 0,1,0 ) ) );
		transform[2] *= -1;
        */
		//transform = glm::translate( transform, _velocity * Time::step() );

		//shoot particle
        if(_timeTillEmit <= 0)
        {
            _particles.clear();
            for(auto i = 0; i < 4; i++)
                emit();
            _timeTillEmit = _emitTime;
        }

	}
    void ParticleEmitterController::emit()
    {
        uGE::GameObject * particle = new uGE::GameObject( "Particle");
             uGE::Body * particleBody = new uGE::Body( particle );
                particleBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/particles.obj" ) );
                particleBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Textures/spirit.png") );
                particleBody->getMaterial()->setBlendMode( Material::BlendMode::NORMAL );
            particle->setBody( particleBody );

            particle->setController( new uGE::ParticleController( particle, SceneManager::_camera) );
            particle->setPosition( _parent->getPosition() );
           uGE::SceneManager::add( particle );
           _particles.push_back( particle );
    }
	void ParticleEmitterController::setVelocity(glm::vec3 aVelocity)
	{
	    _velocity = aVelocity;
	}
}
