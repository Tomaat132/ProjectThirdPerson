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
#include "Logger.h"

#include "SoundManager.hpp"

#include "Player.hpp"
#include "Viking.hpp"

//Still missing controls: Melee, Absorbing.

namespace uGE {

	PlayerController::PlayerController( uGE::Player * parent )
	:	Controller( parent )
	{
	    _parent =  parent ;
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
	    float speed = 26.f * Time::step();
        if( _shootTime > 0 ) { _shootTime -= Time::step(); }
        if( _vikingTime > 0) { _vikingTime -= Time::step(); }

		glm::mat4 & transform = _parent->transform;
		glm::vec3 translate;
		glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f);

        bool wasSucking = _isSucking;
        //Absorbing Controls
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::L ) ) {
			if ( _isSucking == false ) {// begin event
				_isSucking = true;      // By setting _isSucking on true, previous frame is separated from current frame.
				_parent->playNow("SUCK");
				_shootTime = 0.5f;
				vacuum();
			}
		} else{
			_isSucking = false;
			for( unsigned int i = 0; i < SpiritSpawnController::spirits.size(); i++){
				Spirit* spirit = SpiritSpawnController::spirits[i];
				spirit->isTargeted( false );
			}
		}
		if ( wasSucking && ! _isSucking ) { //Now that _isSucking is true and wasSucking still false, the spirits are not targeted in current frame.
			for( unsigned int i = 0; i < SpiritSpawnController::spirits.size(); i++){
				Spirit* spirit = SpiritSpawnController::spirits[i];
				spirit->isTargeted( false );
			}
		}
        if(!_isSucking)
        {
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) rotate[2] = 1.0f;
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) rotate[2] = -1.0f;
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) rotate[0] = 1.f;
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) rotate[0] = -1.f;

            //Melee Controls
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::J ) && _shootTime <= 0.f )
			{
			    _isAttacking = true;
                _parent->playNow("MELEE");
                SoundManager::playSFX("PlayerAtk");
				attack();
                _shootTime = 0.3f;
			} else {
                _isAttacking = false;
			}

			//Shooting controls
			if(sf::Keyboard::isKeyPressed( sf::Keyboard::K ) && _shootTime <= 0.f)
			{
			    _isShooting = true;
			    _parent->playNow("SHOOT");
				shoot();
				_shootTime = 0.3f;
			} else {
                _isShooting = false;
			}

        }

		if( glm::length(rotate) > 0 ) {
			rotate = glm::normalize(rotate);
			transform = glm::translate( transform, glm::vec3(0, 0, 1.f) * speed );
			_parent->setDirection( rotate );
			_parent->setRotation( rotate );
			_parent->playNow("WALK");
			//_parent->getBody()->getAnimation()->PlayAnimation(_parent, "true");
		}
		else if(glm::length(rotate) <= 0 && !_isAttacking && !_isShooting && _parent->getHealth() > 0)
		{
			_parent->playNow("IDLE");
			//_parent->getBody()->getAnimation()->StopAnimation();
		}
		//checks here if the zombie is able to hit again Should have made this into a function, really...
		zombieHitTime -=Time::step();
		if(zombieHitTime <= 0){
                zombieHitTime = -1;
		//and makes sure it stay's put at a certain position in time.
		}
		regenerate();
	}//end of update function

	void PlayerController::vacuum()
	{
        SoundManager::playSFX( "Sucking" );
        //---- Spawn particles ----
        //---- End Spawn  ------
        for( unsigned int i = 0; i < SpiritSpawnController::spirits.size(); i++){
            Spirit* spirit = SpiritSpawnController::spirits[i];
            glm::vec3 distanceVec = spirit->getPosition() - _parent->getPosition();
            if( glm::distance( spirit->getPosition(), _parent->getPosition()) < 14.f){
                if(glm::dot( _parent->getDirection(), glm::normalize(distanceVec) ) > 0.5f ||  glm::distance( spirit->getPosition(), _parent->getPosition()) < 4.f){
                    spirit->isTargeted( true );
                    break;
                }
            }
        }
       // _isSucking = true;
	}
    void PlayerController::releaseButton()
    {

    }

	void PlayerController::attack()
	{
	    for( unsigned int i = 0; i < ZombieSpawnController::zombies.size(); i++){
            Zombie* zombie = ZombieSpawnController::zombies[i];
            if(glm::distance(zombie->getPosition(), _parent->getPosition()) < 8.f)
            {
                if(glm::dot(glm::normalize(zombie->getPosition()- _parent->getPosition()), _parent->getDirection()) >= 0.5f)
                {
                    //std::cout<< glm::dot(_parent->getDirection(), glm::normalize(spirit->getPosition()- _parent->getPosition() )) << std::endl;
                    if(zombie->getViking())
                    {
                        SceneManager::del(zombie);
                        _parent->addScore( 100 );
                        break;
                    }
                }
            }
        }
        //particle
        /*uGE::GameObject * particle = new uGE::GameObject( "Particle" );
             uGE::Body * particleBody = new uGE::Body( particle );
                particleBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/particles.obj" ) );
                particleBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Textures/star.png") );
                particleBody->getMaterial()->setBlendMode( Material::BlendMode::ALPHA );

            particle->setBody( particleBody );

            particle->setController( new uGE::ParticleController( particle, SceneManager::_camera, glm::vec3(0.f, 0.f, 1.f), 1.f) );
            particle->setPosition( _parent->getPosition() +_parent->getDirection()*4.f);
           uGE::SceneManager::add( particle );*/
	}

	void PlayerController::shoot()
	{
        if(_parent->getShootable() > 0 ) {
            SoundManager::playSFX( "Launch" );
            uGE::GameObject * bullet = new uGE::GameObject( "Bullet");
                uGE::Body * bulletBody = new uGE::Body( bullet );
                    bulletBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/spirit.obj" ) );  //change model
                    bulletBody->setTexture( uGE::AssetManager::loadTexture( "Assets/Textures/spirit.png") );     //change texture
                bullet->setBody( bulletBody );
                bullet->setCollider(new uGE::SphereCollider(bullet ,1.45f));
                bullet->setController( new uGE::BulletController( bullet, _parent ) );
                bullet->setPosition( _parent->getPosition() );
               uGE::SceneManager::add( bullet );
               _parent->changeShootable(-1);
        }
	}

	void PlayerController::regenerate(){
        regenerateHpT -=Time::step();
        if(regenerateHpT<= -1){
            regenerateHpT = regenerateMax;
            _parent->changeHealth(+5);
            if(_parent->getHealth() > 100) _parent->setHealth(100);
        }
	}

    void PlayerController::onCollision( CollisionResult * result )
    {
        if( result->colliderTypeB == Collider::BOX ) {
            _parent->setPosition( _parent->getPosition() - result->overlap );
        }
        if( result->colliderTypeB == Collider::SPHERE ) {
            if( result->objectB->getName() == "Cone_tree" || result->objectB->getName() == "Tree_dead" ) {
                _parent->setPosition( _parent->getPosition() - result->overlap );
            }
        }
        if( result->colliderTypeB == Collider::SPHERE ) {
            if( result->colliderB == "zombieHitbox"){//check for zombie
                result->objectB->setPosition( result->objectB->getPosition() + result->overlap );//prevent overlapping 2 objects

                if(zombieHitTime <= 0 ){//hits player every second
                    zombieHitTime = zombieHitReset;
                    SoundManager::playSFX( "PlayerHit" );

                    _parent->changeHealth(-10);//lowers health by 10 every second they touch.

                }

            }
        }
        //add stuff
    }
}
