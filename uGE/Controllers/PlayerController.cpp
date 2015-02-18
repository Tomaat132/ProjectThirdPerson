#include <SFML/Window.hpp>
#include "PlayerController.hpp"
#include "GameObject.hpp"
namespace uGE {

	PlayerController::PlayerController( uGE::GameObject * parent )
	:	Controller( parent )
	{
	}

	PlayerController::~PlayerController()
	{

	}

	void PlayerController::update()
	{
	    float speed = 0.1f;
		glm::mat4 & transform = _parent->transform;
		glm::vec3 translate;
		float rotate = 0.0f;
		glm::vec3 hTranslate(0, 0, 0);
        glm::vec3 vTranslate(0, 0, 0);
       // int keysPressed = 0;
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

		// note, does not check collision, just moves on xz plane !
		transform = glm::translate( transform, (hTranslate + vTranslate) );
		transform = glm::rotate( transform, rotate, glm::vec3( 0,1,0 ) );
	}
}
