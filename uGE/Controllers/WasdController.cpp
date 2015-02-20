#include <SFML/Window.hpp>
#include "WasdController.hpp"
#include "GameObject.hpp"
#include "Body.hpp"
#include "Animation.hpp"

namespace uGE {

	WasdController::WasdController( uGE::GameObject * parent )
	:	Controller( parent )
	{
	}

	WasdController::~WasdController()
	{

	}

	void WasdController::update()
	{
		glm::mat4 & transform = _parent->transform;
		glm::vec3 translate;
		float rotate = 0.0f;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) translate += glm::vec3( 0,0,0.1 );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) translate -= glm::vec3( 0,0,0.1 );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) rotate += 0.05;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) rotate -= 0.05;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Z ) ) translate += glm::vec3( 0,0.1,0 );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::X ) ) translate -= glm::vec3( 0,0.1,0 );
		/*if ( sf::Keyboard::isKeyPressed( sf::Keyboard::P ) ) */
            _parent->getBody()->getAnimation()->PlayAnimation(_parent, false);

		// note, does not check collision, just moves on xz plane !
		transform = glm::translate( transform, translate );
		transform = glm::rotate( transform, rotate, glm::vec3( 0,1,0 ) );
	}
}
