#include <SFML/Window.hpp>
#include "SpiritController.hpp"
#include "SceneManager.hpp"
#include "ParticleEmitterController.hpp"
#include "GameObject.hpp"
#include "Body.hpp"
#include "Animation.hpp"
#include "Time.hpp"

namespace uGE {

	SpiritController::SpiritController( uGE::GameObject * parent, uGE::GameObject * followee)
	:	Controller( parent )
	{
	    _percentSucked = 0;
	    _particleEmitter = new uGE::GameObject ( "SpiritParticle" );
        _particleEmitter->setController( new uGE::ParticleEmitterController (_particleEmitter, _parent));

        uGE::SceneManager::add( _particleEmitter);
	}

	SpiritController::~SpiritController()
	{

	}

	void SpiritController::update()
	{
		glm::mat4 & transform = _parent->transform;

        //interpolated vec3 between player and ghost
		if(_percentSucked >= 0) _particleEmitter->getController()->setVelocity((_followee->getPosition()-_parent->getPosition())*_percentSucked/100.f );
        getSucked();
	}

	void SpiritController::getSucked()
	{
	    _percentSucked += Time::step()*20.f;
	    if(_percentSucked >= 90) _percentSucked = 0;//DIE
	}
}
