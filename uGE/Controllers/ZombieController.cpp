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

    ZombieController::ZombieController( uGE::GameObject * parent )
	:	Controller( parent )
    {
        //ctor
        //_parent->setDirection(glm::vec3(-1.f, 0.f, 0.f));
        srand(time(NULL));
    }

    ZombieController::~ZombieController()
    {
        //dtor
    }

    void ZombieController::healthCheck(){



        }
        //if(rotate != glm::vec3(0,0,0)) _parent->setDirection(glm::normalize(rotate));

    void ZombieController::update(){
    //update variables here such as health location etc/
    void healthCheck();

    //int direction = rand() %10+1;//INITIALISE RANDOM DIRECTION between 10 and 0
    //this shows that a random number is constantly generated //std::cout<<direction<<std::endl;


    float speed = 40.f * Time::step();
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

        if( glm::length(rotate) > 0 ) {
            rotate = glm::normalize(rotate);
        }

        if(rotate != glm::vec3(0,0,0)){ _parent->setDirection(glm::normalize(rotate));}

        if( keyI || keyK || keyJ || keyL) {transform = glm::translate( transform, glm::vec3(0, 0, 1.f) * speed );}
		if(rotate != glm::vec3(0,0,0)) {_parent->setRotation(glm::normalize(rotate));}

    }
}
