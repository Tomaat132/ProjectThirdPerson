#include <SFML/Window.hpp>
#include "SpiritController.hpp"
#include "SceneManager.hpp"
#include "AssetManager.hpp"
#include "ParticleController.hpp"
#include "GameObject.hpp"
#include "Body.hpp"
#include "Animation.hpp"
#include "Material.hpp"
#include "Time.hpp"
#include "Camera.hpp"

namespace uGE {

	SpiritController::SpiritController( uGE::GameObject * parent, uGE::GameObject * followee)
	:	Controller( parent ), _followee( followee )
	{

	    _percentSucked = 0;
	    _timeTillEmit = 0.0f;
	    _emitTime = 0.1f;
	    _velocity = glm::vec3(30.f, 4.f, 0.f);
        srand(time(NULL));
	    _targeted = false;

	}

	SpiritController::~SpiritController()
	{

	}

	void SpiritController::update()
	{
         _timeTillEmit -= Time::step();

        if(_timeTillEmit <= 0)
        {
            _particles.clear();
            for(auto i = 0; i < 5; i++)
            {
                //distortion around a position
                _distortion = (glm::vec3((2.0f * float(rand())/ float(RAND_MAX) -1.0f), (2.0f * float(rand())/ float(RAND_MAX) +3.0f), (2.0f * float(rand())/ float(RAND_MAX) -1.0f)));
                if(_percentSucked >= 0) _velocity = (_followee->getPosition()-_parent->getPosition())*_percentSucked/100.f ;
                emit();
            }
            _timeTillEmit = _emitTime;
        }


        getSucked();
	}
    void SpiritController::isTargeted( bool value)
    {
        _targeted = value;

    }
    void SpiritController::emit()
    {
        uGE::GameObject * particle = new uGE::GameObject( "Particle" );
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
	void SpiritController::getSucked()
	{
	    if(_targeted ) _percentSucked += Time::step()*35.f;
	    else if(_percentSucked > 0) _percentSucked -= 2*Time::step()*35.f;
	    if(_percentSucked >= 98) die();//DIE
	}

	void SpiritController::die()
	{
        SceneManager::del(_parent);
	}
}
