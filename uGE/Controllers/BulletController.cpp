#include "BulletController.hpp"
#include "GameObject.hpp"
#include "SceneManager.hpp"
#include "Time.hpp"

namespace uGE {
	BulletController::BulletController( GameObject * parent, GameObject * shooter)
	:	Controller( parent ), _shooter( shooter )
	{
	    _destroyTime = 2.f;//.5f
	    _speed = 75.f;//100.f
	    _direction = _shooter->getDirection(); // Uses his own direction - the actual gameobject should have direction
        //std::cout<< _parent->getName() << std::endl;
        //std::cout << _shooter->getName() << std::endl;
	}

	BulletController::~BulletController()
	{
		//dtor
	}

	void BulletController::update()
	{
	    _destroyTime -= Time::step();
       // std::cout<< _direction << std::endl;
	    _parent->transform = glm::translate( _parent->transform, _direction * _speed * Time::step() );
	    //_parent->setPosition( _followee->getPosition() + glm::vec3( 0.f, 10.f, -15.f ) );
		//glm::mat4 & transform = _parent->transform;
		//transform = glm::inverse( glm::lookAt( glm::vec3( transform[3] ), glm::vec3( _followee->transform[3] ), glm::vec3( 0,1,0 ) ) );
		//std::cout << "Point A" << std::endl;
		/*glm::vec3 bulletPos = this->getParent()->getPosition();
		std::cout << "bulletPos = " << bulletPos << "." << std::endl;
		glm::vec3 playerPos = _shooter->getPosition();
		std::cout << "playerPos = " << playerPos << "." << std::endl;
		glm::vec3 diff = bulletPos - playerPos;
		std::cout << "diff = bulletPos - playerPos = " << diff << "." << std::endl;
		glm::vec3 offset1 = playerPos - (bulletPos + bulletPos);
		std::cout << "offset1 = playerPos - bulletPos*2 = " << offset1 << "." << std::endl;
		glm::vec3 offset2 = bulletPos - diff;
		std::cout << "offset2 = bulletPos - diff = " << offset2 << "." << std::endl;

		if( this->isGreaterThan( offset1, offset2 ) )
        {
            uGE::SceneManager::del(_parent);
        }
        //std::cout << "Point B" << std::endl;*/
        if( _destroyTime <= 0.0f ) { uGE::SceneManager::del(_parent); }
	}

    //Is input1 smaller than input2 ?
	bool BulletController::isGreaterThan( glm::vec3 input1, glm::vec3 input2 )
	{
/*	    std::cout << input1[0] << " > " << input2[0] << std::endl;
	    std::cout << input1[1] << " > " << input2[1] << std::endl;
	    std::cout << input1[2] << " > " << input2[2] << std::endl;
*/      if(input1[0] > input2[0] || input1[1] > input2[1] || input1[2] > input2[2])
        {
            return true;
        } else {
            return false;
        }
	}
}
