#include "ZombieController.hpp"
#include "Controller.hpp"
#include <stdlib.h>

#include "GameObject.hpp"
#include "Body.hpp"
#include "AssetManager.hpp"
#include "SceneManager.hpp"
#include "Time.hpp"


#include "utils/glm.hpp"

namespace uGE{

    ZombieController::ZombieController( uGE::GameObject * parent, uGE::GameObject * followee)
	:	Controller( parent ), _followee( followee )
    {
        //ctor
        //_parent->setDirection(glm::vec3(-1.f, 0.f, 0.f));
        _state = IDLE;
        _idleTimer = 0.f;
        _eightDir = 0;
        _speed = 5.f;
        srand(time(NULL));
    }

    ZombieController::~ZombieController()
    {
        //dtor
    }

    void ZombieController::healthCheck()
    {

    }

    void ZombieController::update()
    {
        switch(_state)
        {
        case IDLE:
            if(_idleTimer <= 0.f){
               _eightDir = rand() %8;//INITIALISE RANDOM DIRECTION between 7 and 0
               _idleTimer = 1.f; // how many seconds till next direction
            }
            move(_eightDir);

            _idleTimer -= Time::step();
            break;
        }
        //if(rotate != glm::vec3(0,0,0)) _parent->setDirection(glm::normalize(rotate));

		//int direction = rand() %10+1;//INITIALISE RANDOM DIRECTION between 10 and 0
		//this shows that a random number is constantly generated //std::cout<<direction<<std::endl;


		/*float speed = 40.f * Time::step();
		//std::cout<<"startup"<<std::endl;
        glm::mat4 & transform = _parent->transform;
        glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f);

        bool keyI = sf::Keyboard::isKeyPressed( sf::Keyboard::Up );
        bool keyK = sf::Keyboard::isKeyPressed( sf::Keyboard::Down );
        bool keyJ = sf::Keyboard::isKeyPressed( sf::Keyboard::Left );
        bool keyL = sf::Keyboard::isKeyPressed( sf::Keyboard::Right );
		if ( keyI ) rotate[2] = 1.0f;
		if ( keyK ) rotate[2] = -1.0f;//vTranslate.z -= speed;//glm::vec3( 0, 0, speed );
		if ( keyJ ) rotate[0] = 1.f;  //hTranslate.x += speed;
		if ( keyL ) rotate[0] = -1.f;
		*/
    }
	
    void ZombieController::move( int aDir)
    {
        glm::mat4 & transform = _parent->transform;
        glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f);

		if ( aDir == 7 || aDir == 0 || aDir == 1) rotate[2] = 1.0f;
		if ( aDir == 3 || aDir == 4 || aDir == 5) rotate[2] = -1.0f;//vTranslate.z -= speed;//glm::vec3( 0, 0, speed );
		if ( aDir == 1 || aDir == 2 || aDir == 3) rotate[0] = 1.f;//hTranslate.x += speed;
		if ( aDir == 5 || aDir == 6 || aDir == 7) rotate[0] = -1.f;
        if( glm::length(rotate) > 0 ) {
            rotate = glm::normalize(rotate);
        }

        if(rotate != glm::vec3(0,0,0)){ _parent->setDirection(glm::normalize(rotate));}

        if( aDir > -1) {transform = glm::translate( transform, glm::vec3(0, 0, 1.f) * _speed * Time::step());}
		if(rotate != glm::vec3(0,0,0)) {_parent->setRotation(glm::normalize(rotate));}
    }

}
