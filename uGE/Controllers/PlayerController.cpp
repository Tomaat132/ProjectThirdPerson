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
#include "CollisionDetection.hpp"
#include "Time.hpp"

namespace uGE {

	PlayerController::PlayerController( uGE::GameObject * parent )
	:	Controller( parent )
	{
	    _shootTime = 0.0f;
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

		glm::mat4 & transform = _parent->transform;
	//	glm::vec3 direction = _parent->getDirection();    //IS THIS STILL DIRECTION OF PARENT??? OR A COPY OF IT?
		glm::vec3 translate;
		glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 hTranslate(0, 0, 0);
        glm::vec3 vTranslate(0, 0, 0);
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
            bool keyW = sf::Keyboard::isKeyPressed( sf::Keyboard::W );
            bool keyS = sf::Keyboard::isKeyPressed( sf::Keyboard::S );
            bool keyA = sf::Keyboard::isKeyPressed( sf::Keyboard::A );
            bool keyD = sf::Keyboard::isKeyPressed( sf::Keyboard::D );
            if ( keyW ) rotate[2] = 1.0f;
            if ( keyS ) rotate[2] = -1.0f;//vTranslate.z -= speed;//glm::vec3( 0, 0, speed );
            if ( keyA ) rotate[0] = 1.f;//hTranslate.x += speed;
            if ( keyD ) rotate[0] = -1.f;//hTranslate.x -= speed;

            if( glm::length(rotate) > 0 ) {
                rotate = glm::normalize(rotate);
            }

            //if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) hTranslate.x -= speed;
            if(rotate != glm::vec3(0,0,0)) _parent->setDirection(glm::normalize(rotate));   //SET DIRECTION
            if(hTranslate != glm::vec3(0, 0, 0) || vTranslate != glm::vec3(0, 0, 0) ) {
                    _parent->setDirection(glm::normalize(hTranslate + vTranslate));   //SET DIRECTION
                    _parent->getBody()->getAnimation()->PlayAnimation(_parent, "true");
            } else {
                _parent->getBody()->getAnimation()->StopAnimation();
            }

            if(sf::Keyboard::isKeyPressed( sf::Keyboard::F ) && _shootTime <= 0.f)
            {
                shoot();
                _shootTime = 0.3f;
            }
            if(sf::Keyboard::isKeyPressed( sf::Keyboard::T ) && _shootTime <= 0.f)
            {
                attack();
                _shootTime = 0.3f;
            }
            if(sf::Keyboard::isKeyPressed( sf::Keyboard::G ) && _shootTime <= 0.f)
            {
                for( unsigned int i = 0; i < SpiritSpawnController::spirits.size(); i++){
                    Spirit* spirit = SpiritSpawnController::spirits[i];
                    if(glm::distance(spirit->getPosition(), _parent->getPosition()) < 10.f)
                    {
                        if(glm::dot(glm::normalize(spirit->getPosition()- _parent->getPosition()), _parent->getDirection()) >= 0.6f)
                        {
                            std::cout<< glm::dot(glm::normalize(spirit->getPosition()- _parent->getPosition()), _parent->getDirection()) << std::endl;
                            spirit->isTargeted( true );
                            break;
                        }

                    }
                }
                //suck();
                _isSucking = true;
            }
            //transform[0][0] = cos(rotate);
            //transform[0][2] = -cos(rotate+90);
           //transform[2][0] = sin(rotate);
            //transform[2][2] = -sin(rotate+90);
            // note, does not check collision, just moves on xz plane !

            if( keyW || keyS || keyA || keyD) transform = glm::translate( transform, glm::vec3(0, 0, 1.f) * speed );
            if(rotate != glm::vec3(0,0,0)) _parent->setRotation(glm::normalize(rotate));
        }
		//transform = glm::rotate( transform, rotate, glm::vec3( 0,1,0 ) );
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
                bulletBody->setTexture( uGE::AssetManager::loadTexture( "Assets/bricks.jps") );
            bullet->setBody( bulletBody );
            bullet->setCollider(new uGE::SphereCollider(bullet ,1.45f));
            bullet->setController( new uGE::BulletController( bullet, _parent ) );
            bullet->setPosition( _parent->getPosition() );
           uGE::SceneManager::add( bullet );
	}

	void PlayerController::onCollision( CollisionResult * result )
	{
        //std::cout << result->objectB->getName() << std::endl;
	}
}
