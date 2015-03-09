#include <SFML/Window.hpp>
#include "BulletController.hpp"
#include "ParticleController.hpp"
#include "ParticleEmitterController.hpp"
#include "PlayerController.hpp"
#include "SphereCollider.hpp"
#include "GameObject.hpp"
#include "Body.hpp"
#include "Animation.hpp"
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

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) rotate[2] = 1.0f;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) rotate[2] = -1.0f;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) rotate[0] = 1.f;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) rotate[0] = -1.f;

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::J ) ) {
            //Do Melee
        }
        if(sf::Keyboard::isKeyPressed( sf::Keyboard::K ) && _shootTime <= 0.f)
        {
            shoot();
            _shootTime = 0.3f;
        }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::L ) ) {
            //Do Absorbing
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
        particleEmitter->setController( new uGE::ParticleEmitterController( particleEmitter, _parent) );
        particleEmitter->setPosition( _parent->getPosition());
        uGE::SceneManager::add( particleEmitter );
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
