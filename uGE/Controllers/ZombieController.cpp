#include "ZombieController.hpp"
#include "Controller.hpp"
#include <stdlib.h>

#include "GameObject.hpp"
#include "Collider.hpp"
#include "Zombie.hpp"
#include "CollisionDetection.hpp"
#include "Body.hpp"
#include "AssetManager.hpp"
#include "SceneManager.hpp"
#include "Time.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include "Collider.hpp"
#include "SphereCollider.hpp"
#include "CollisionDetection.hpp"


#include "utils/glm.hpp"

namespace uGE{

    ZombieController::ZombieController( uGE::GameObject * parent, uGE::GameObject * followee)
	:	Controller( parent ), _followee( followee ), _idleTimer( 0 ), _transformIntervalTimer( 0 ), _transformTimer( 0 ), _eightDir( 0 ), _speed( 5.f )
    {
        _state = IDLE;
        srand(time(NULL));

        _zombieParent = dynamic_cast<Zombie*> ( parent );
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
            checkPlayerRange();//it checks every second compared to the update of every 2 seconds in player;

            _idleTimer -= Time::step();
            break;
        case TRANSFORM:
            if(_transformTimer <= 0.f){
                //can use nice animation here
                _zombieParent->getBody()->setMesh( uGE::AssetManager::loadMesh("Assets/Models/teapot.obj"));
                _zombieParent->setViking(true);
                _state = IDLE;
            }
            if(_transformIntervalTimer <= 0.f){
                _eightDir = rand() %8;//INITIALISE RANDOM DIRECTION between 7 and 0
                _transformIntervalTimer = 0.05f;
            }
            move(_eightDir);

            _transformTimer -= Time::step();
            _transformIntervalTimer -= Time::step();
            break;

        case CHASE:
            //do code

            break;

        }
    }

    void ZombieController::checkPlayerRange(){
        std::vector<glm::vec3> cCrumbs = SceneManager::_player->getCrumbs();//get the player crumbs array for later to follow.
        std::vector<Collider*> tempVec;//make a temporary array
        tempVec = _parent->getColliders();//store all parent colliders in a temporary array
            for(unsigned int i = 0; i < tempVec.size(); i++){//go through all collider types
                if(tempVec[i]->getColliderType() == Collider::SPHERE){//if the collider is a sphere, do stuff
                //std::cout<<"anything"<<std::endl;     //this prints twice?
                //std::cout<<tempVec.size()<<std::endl; //this holds 1
                SphereCollider* sphere = dynamic_cast<SphereCollider *>(tempVec[i]);
                //glm::vec3 closestPoint = sphere->getPosition();
                    for(unsigned int j = 0; j < cCrumbs.size(); j++){
                    glm::vec3 diff = cCrumbs[j] - sphere->getPosition();
                    float dist = glm::length(diff);

                        if(sphere->getRadius() > dist){
                        //_state = State::CHASE;
                        chaseCrumb(cCrumbs[j]);
                            if(cCrumbs[j] == sphere->getPosition()){
                            chaseCrumb(cCrumbs[j]);
                            }
                        return;
                        }
                    //glm::vec3 difference = closestPoint - sphere->getPosition();
                    }
                //SphereCollider * colliderA = dynamic_cast <SphereCollider *>(colliderArray[i]);

                }

            }
    }
    void ZombieController::chaseCrumb(glm::vec3 crumb){
        glm::mat4 & transform = _parent->transform;
        glm::vec3 diff = crumb - _parent->getPosition();
        if (glm::length(diff) < _speed * Time::step()){
            //change target
        }
            diff = glm::normalize(diff);
            _parent->setRotation(diff);
            transform = glm::translate(transform , glm::vec3(0 , 0 , 1.0f)* _speed * Time::step());
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

    void ZombieController::onCollision( CollisionResult* result)
    {
        if( result->colliderTypeB == Collider::SPHERE ) {
            if(result->objectB->getName() == "Bullet") {
                if(_state != TRANSFORM){   //ZOMBIE BEHAVIOUR:
					_state = TRANSFORM;
					_transformTimer = 3.f;
				}
				SceneManager::del( result->objectB );//->setPosition( _parent->getPosition() - result->overlap );
            }
        }
    }

}