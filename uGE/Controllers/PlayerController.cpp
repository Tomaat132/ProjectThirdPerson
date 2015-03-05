#include <SFML/Window.hpp>
#include "PlayerController.hpp"
#include "Time.hpp"
#include "BulletController.hpp"
#include "GameObject.hpp"
#include "Body.hpp"
#include "Animation.hpp"
#include "AssetManager.hpp"
#include "SceneManager.hpp"
#include "SphereCollider.hpp"
#include "Camera.hpp"
#include "ParticleController.hpp"
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
	    float speed = 25.f * Time::step();
        if( _shootTime > 0 ) { _shootTime -= Time::step(); }

		glm::mat4 & transform = _parent->transform;
	//	glm::vec3 direction = _parent->getDirection();    //IS THIS STILL DIRECTION OF PARENT??? OR A COPY OF IT?
		glm::vec3 translate;
		float rotate = 0.0f;
		glm::vec3 hTranslate(0, 0, 0);
        glm::vec3 vTranslate(0, 0, 0);

        bool keyW = sf::Keyboard::isKeyPressed( sf::Keyboard::W );
        bool keyS = sf::Keyboard::isKeyPressed( sf::Keyboard::S );
        bool keyA = sf::Keyboard::isKeyPressed( sf::Keyboard::A );
        bool keyD = sf::Keyboard::isKeyPressed( sf::Keyboard::D );
		if ( keyW ) vTranslate.z += speed;
		if ( keyS ) vTranslate.z -= speed;//glm::vec3( 0, 0, speed );
		if ( keyA ) hTranslate.x += speed;
		if ( keyD ) hTranslate.x -= speed;
		if ( ((keyW || keyS) && keyA) || ((keyW || keyS) && keyD))
		{
                if(!(keyD && keyA)) vTranslate *= cos(45);
                if(!(keyW && keyS)) hTranslate *= sin(45);
		}
		//if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) hTranslate.x -= speed;
        if(hTranslate != glm::vec3(0, 0, 0) || vTranslate != glm::vec3(0, 0, 0) ) {
                _parent->setDirection(glm::normalize(hTranslate + vTranslate));   //SET DIRECTION
                _parent->getBody()->getAnimation()->PlayAnimation(_parent, "true");
        } else {
            _parent->getBody()->getAnimation()->StopAnimation();
        }
        if(sf::Keyboard::isKeyPressed( sf::Keyboard::F ) && _shootTime <= 0.f)
        {
            createParticle();
            _shootTime = 0.3f;
        }
		// note, does not check collision, just moves on xz plane !
		transform = glm::translate( transform, (hTranslate + vTranslate) );
		transform = glm::rotate( transform, rotate, glm::vec3( 0,1,0 ) );
	}
    void PlayerController::createParticle()
	{

        uGE::GameObject * particle = new uGE::GameObject( "Particle");
            uGE::Body * particleBody = new uGE::Body( particle );
                particleBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/cube.obj" ) );
                particleBody->setTexture( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
            particle->setBody( particleBody );

            particle->setController( new uGE::ParticleController( particle, SceneManager::_camera) );
            particle->setPosition( _parent->getPosition() );
           uGE::SceneManager::add( particle );
	}
	void PlayerController::shoot()
	{

        uGE::GameObject * bullet = new uGE::GameObject( "Bullet");
            uGE::Body * bulletBody = new uGE::Body( bullet );
                bulletBody->setMesh( uGE::AssetManager::loadMesh( "Assets/Models/particle.obj" ) );
                bulletBody->setTexture( uGE::AssetManager::loadTexture( "Assets/bricks.jpg") );
            bullet->setBody( bulletBody );
            bullet->setCollider(new uGE::SphereCollider(bullet ,1.45f));
            bullet->setController( new uGE::BulletController( bullet, _parent ) );
            bullet->setPosition( _parent->getPosition() );
           uGE::SceneManager::add( bullet );
	}
}
