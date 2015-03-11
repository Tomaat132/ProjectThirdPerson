#include <SFML/Window.hpp>

#include <GL/glew.h>

#include "Utils/glm.hpp"
#include "Utils/FPS.hpp"

#include "BulletController.hpp"
#include "ParticleController.hpp"
#include "SpiritController.hpp"
#include "SpiritSpawnController.hpp"
#include "ZombieSpawnController.hpp"
#include "PlayerController.hpp"
#include "SphereCollider.hpp"
#include "GameObject.hpp"
#include "Zombie.hpp"
#include "Spirit.hpp"
#include "Body.hpp"
#include "Animation.hpp"
#include "Material.hpp"
#include "AssetManager.hpp"
#include "SceneManager.hpp"
#include "Camera.hpp"
#include "Collider.hpp"
#include "CollisionDetection.hpp"
#include "Time.hpp"

#include "SoundManager.hpp"

#include "Player.hpp"
#include "Viking.hpp"

//Still missing controls: Melee, Absorbing.

namespace uGE {

	PlayerController::PlayerController( uGE::GameObject * parent )
	:	Controller( parent )
	{
	    _shootTime = 0.0f;
		_vikingTime = 0.0f;
	    _parent->setDirection(glm::vec3(-1.f, 0.f, 0.f));
	    _isSucking = false;
	}

	PlayerController::~PlayerController()
	{
        //dtor
	}

	void PlayerController::update()
	{
	    float speed = 40.f * Time::step();
        if( _shootTime > 0 ) { _shootTime -= Time::step(); }
        if( _vikingTime > 0) { _vikingTime -= Time::step(); }

		glm::mat4 & transform = _parent->transform;
		glm::vec3 translate;
		glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f);


        if(sf::Keyboard::isKeyPressed( sf::Keyboard::Space))
        {
            for( unsigned int j = 0; j < SpiritSpawnController::spirits.size(); j++){
                Spirit* aSpirit = SpiritSpawnController::spirits[j];
                aSpirit->isTargeted( false );
            }
            _isSucking = false;
        }

        if(!_isSucking)
        {
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) rotate[2] = 1.0f;
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) rotate[2] = -1.0f;
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) rotate[0] = 1.f;
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) rotate[0] = -1.f;

			if( sf::Keyboard::isKeyPressed( sf::Keyboard::J ) ) {
				//Do Melee
			}


			//Shooting controls
			if(sf::Keyboard::isKeyPressed( sf::Keyboard::K ) && _shootTime <= 0.f)
            {
            SoundManager * sfx;
            sfx->playSFX("Rifle");

            shoot();
            _shootTime = 0.3f;
            }
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::L ) ) {
				//Do Absorbing
			}

			//Bury Controls
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::L ) && _vikingTime <= 0.f ) {
				std::cout << Viking::zombieCount << std::endl;
				if( Viking::zombieCount <= 0 )
				{
					Viking::startWinSeq();
					Viking::zombieCount += 101;
				}
				else if( Viking::zombieCount < 100)
				{
					Viking::zombieCount--;
					_vikingTime = 0.3f;
				}
			}

			if( glm::length(rotate) > 0 ) {
				rotate = glm::normalize(rotate);
				transform = glm::translate( transform, glm::vec3(0, 0, 1.f) * speed );
				_parent->setDirection( rotate );
				_parent->setRotation( rotate );
				_parent->getBody()->getAnimation()->PlayAnimation(_parent, "true");
			} else {
				_parent->getBody()->getAnimation()->StopAnimation();
			}
        }

    void PlayerController::createParticle()
	{
        uGE::GameObject * particleEmitter = new uGE::GameObject( "ParticleEmitter");
        particleEmitter->setController( new uGE::SpiritController( particleEmitter, _parent) );
        particleEmitter->setPosition( _parent->getPosition());
        uGE::SceneManager::add( particleEmitter );
	}

	void PlayerController::attack()
	{
	    for( unsigned int i = 0; i < ZombieSpawnController::zombies.size(); i++){
            Zombie* zombie = ZombieSpawnController::zombies[i];
            if(glm::distance(zombie->getPosition(), _parent->getPosition()) < 10.f)
            {
                if(glm::dot(glm::normalize(zombie->getPosition()- _parent->getPosition()), _parent->getDirection()) >= 0.6f)
                {

                    //std::cout<< glm::dot(_parent->getDirection(), glm::normalize(spirit->getPosition()- _parent->getPosition() )) << std::endl;
                    SceneManager::del(zombie);
                    break;
                }

            }
        }
        //particle
        uGE::GameObject * particle = new uGE::GameObject( "Particle" );
             uGE::Body * particleBody = new uGE::Body( particle );
                particleBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/particles.obj" ) );
                particleBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Textures/star02.png") );
                particleBody->getMaterial()->setBlendMode( Material::BlendMode::ALPHA );

            particle->setBody( particleBody );

            particle->setController( new uGE::ParticleController( particle, SceneManager::_camera) );
            particle->setPosition( _parent->getPosition() +_parent->getDirection()*4.f);
           uGE::SceneManager::add( particle );
	}

	void PlayerController::shoot()
	{

        uGE::GameObject * bullet = new uGE::GameObject( "Bullet");
            uGE::Body * bulletBody = new uGE::Body( bullet );
                bulletBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/suzanna.obj" ) );
                bulletBody->setTexture( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
            bullet->setBody( bulletBody );
            bullet->setCollider(new uGE::SphereCollider(bullet ,1.45f));
            bullet->setController( new uGE::BulletController( bullet, _parent ) );
            bullet->setPosition( _parent->getPosition() );
           uGE::SceneManager::add( bullet );
	}

	void PlayerController::onCollision( CollisionResult * result )
	{
        if( result->colliderTypeB == Collider::BOX ) {
            _parent->setPosition( _parent->getPosition() - result->overlap );
        }
	}
}
