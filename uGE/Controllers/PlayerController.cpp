#include <SFML/Window.hpp>
#include "PlayerController.hpp"
#include "Time.hpp"
#include "BulletController.hpp"
#include "GameObject.hpp"
#include "Body.hpp"
#include "AssetManager.hpp"
#include "SceneManager.hpp"
#include "SphereCollider.hpp"
#include "Camera.hpp"
#include "ParticleEmitterController.hpp"
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

	}

	void PlayerController::update()
	{
        if( _shootTime > 0 ) { _shootTime -= Time::step(); }

		glm::mat4 & transform = _parent->transform;
	//	glm::vec3 direction = _parent->getDirection();    //IS THIS STILL DIRECTION OF PARENT??? OR A COPY OF IT?
		glm::vec3 translate;
		glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 hTranslate(0, 0, 0);
        glm::vec3 vTranslate(0, 0, 0);

        bool keyW = sf::Keyboard::isKeyPressed( sf::Keyboard::W );
        bool keyS = sf::Keyboard::isKeyPressed( sf::Keyboard::S );
        bool keyA = sf::Keyboard::isKeyPressed( sf::Keyboard::A );
        bool keyD = sf::Keyboard::isKeyPressed( sf::Keyboard::D );
		if ( keyW ) rotate[2] = 1.0f;
		if ( keyS ) rotate[2] = -1.0f;//vTranslate.z -= speed;//glm::vec3( 0, 0, speed );
		if ( keyA ) rotate[0] = 1.f;//hTranslate.x += speed;
		if ( keyD ) rotate[0] = -1.f;//hTranslate.x -= speed;

		//if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) hTranslate.x -= speed;

        if(rotate != glm::vec3(0,0,0)) _parent->setDirection(glm::normalize(rotate));   //SET DIRECTION

        if(sf::Keyboard::isKeyPressed( sf::Keyboard::F ) && _shootTime <= 0.f)
        {
            shoot();
            _shootTime = 0.3f;
        }
        if(sf::Keyboard::isKeyPressed( sf::Keyboard::G ) && _shootTime <= 0.f)
        {
            createParticle();
            _shootTime = 0.3f;
        }
        //transform[0][0] = cos(rotate);
        //transform[0][2] = -cos(rotate+90);
       //transform[2][0] = sin(rotate);
        //transform[2][2] = -sin(rotate+90);
		// note, does not check collision, just moves on xz plane !
		if( keyW || keyS || keyA || keyD) transform = glm::translate( transform, glm::vec3(0, 0, 80.f)*Time::step() );
		if(rotate != glm::vec3(0,0,0)) _parent->setRotation(glm::normalize(rotate));
		//transform = glm::rotate( transform, rotate, glm::vec3( 0,1,0 ) );
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
}
