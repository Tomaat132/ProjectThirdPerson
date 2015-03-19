#include <SFML/Window.hpp>
#include "glm.hpp"
#include "SpiritController.hpp"
#include "SceneManager.hpp"
#include "AssetManager.hpp"
#include "SoundManager.hpp"
#include "ParticleController.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Body.hpp"
#include "Animation.hpp"
#include "Material.hpp"
#include "Time.hpp"
#include "Camera.hpp"

#define _PI 3.1415926535897932384626433832795
namespace uGE {

	SpiritController::SpiritController( uGE::GameObject * parent, uGE::Player * followee)
	:	Controller( parent ), _followee( followee ), _startPos( _parent->getPosition())
	{

	    _percentSucked = 0.f;
	    _timeTillEmit = 0.0f;
	    _emitTime = 0.3f;
	    _velocity = glm::vec3(0.f, 4.f, 0.f);
        srand(time(NULL));
	    _targeted = false;
	    _innerLength = 2.f;
      //  _startPos = _parent->getPosition();

	}

	SpiritController::~SpiritController()
	{

	}

	void SpiritController::update()
	{


         _timeTillEmit -= Time::step();
        if(_percentSucked >= 0) {//_velocity = (_followee->getPosition()-_parent->getPosition())*_percentSucked/100.f ;
                _parent->setPosition( _startPos + (_followee->getPosition()-_startPos) *_percentSucked/100.f );

            }
        if(_timeTillEmit <= 0)
        {
            _particles.clear();
            // std::cout<< _followee->getPosition() << " --- " << _startPos <<std::endl;

            for(auto i = 0; i < 4; i++)
            {
                //distortion around a position
                float angle = (float(rand())/ float(RAND_MAX))*2.f* _PI;
                float disX;
                float disZ;
                float particleSpeed = 1.f + float(rand())/ float(RAND_MAX) *2;
                disX = (1.0f * float(rand())/ float(RAND_MAX) -0.5f);
                disZ = (1.0f * float(rand())/ float(RAND_MAX) -0.5f);
                _distortion = (glm::vec3 ( disX + glm::cos(angle)*_innerLength, (5.0f * float(rand())/ float(RAND_MAX) -2.5f), disZ + glm::sin(angle)*_innerLength ));
                if(_percentSucked >= 0) _velocity = glm::vec3(0.f, 0.f, 0.f);//(_followee->getPosition()-_parent->getPosition())*_percentSucked/100.f ;
                emit(glm::vec3(glm::cos(angle), 0.f, glm::sin(angle)), particleSpeed);
            }
            _timeTillEmit = _emitTime;
        }

        getSucked();
	}
    void SpiritController::isTargeted( bool value)
    {
        _targeted = value;

    }
    void SpiritController::emit(glm::vec3 aDir, float aSpd)
    {
        uGE::GameObject * particle = new uGE::GameObject( "Particle" );
             uGE::Body * particleBody = new uGE::Body( particle );
                particleBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/particles.obj" ) );
                particleBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Textures/spirit_particle.png") );
                particleBody->getMaterial()->setBlendMode( Material::BlendMode::ALPHA );

            particle->setBody( particleBody );

            particle->setController( new uGE::ParticleController( particle, _parent, aDir, aSpd) );
            particle->setPosition( _parent->getPosition() +_velocity +_distortion);
           uGE::SceneManager::add( particle );
           _particles.push_back( particle );
    }
	void SpiritController::getSucked()
	{
	    if(_targeted ) _percentSucked += Time::step()*80.f + _percentSucked/15;
	    else if(_percentSucked > 0) _percentSucked -= (Time::step()*80.f + _percentSucked/15);
	    if(_percentSucked >= 96)
        {
            _followee->changeShootable(1);
            SoundManager::playSFX("SpiritCollect");
            die();//DIE
        }
	}

	void SpiritController::die()
	{
        SceneManager::del(_parent);
	}
}
