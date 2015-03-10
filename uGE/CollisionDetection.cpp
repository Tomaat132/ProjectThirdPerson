#include "CollisionDetection.hpp"
#include "Colliders/SphereCollider.hpp"
#include "Colliders/AABBcollision.hpp"

#include "GameObject.hpp"
#include "Controller.hpp"
#include "utils/glm.hpp"

#include <iostream>
#include <vector>

namespace uGE{

    CollisionDetection::CollisionDetection()
    {
        //ctor
    }

    CollisionDetection::~CollisionDetection()
    {
        //dtor
    }

      void CollisionDetection::update( std::vector<GameObject *> _objects )
      {
            checkCollisions( _objects );
      }

    void CollisionDetection::checkCollisions(std::vector<GameObject *> _objects)
    {
        std::vector<Collider *> colliderArray;
        for( GameObject* object : _objects ) {

            std::vector<Collider *> tempArray;
            tempArray = object->getColliders();
            colliderArray.insert(colliderArray.end(),tempArray.begin(),tempArray.end());
        }

        for (unsigned int i = 0; i<colliderArray.size(); i++){
            for (unsigned int j = i+1; j<colliderArray.size() ; j++ ){

                int typeX = colliderArray[i]->getColliderType();
                int typeY = colliderArray[j]->getColliderType();

                if ( typeX == 1 && typeY == 1 ){

                    SphereCollider * colliderA = dynamic_cast <SphereCollider *>(colliderArray[i]);
                    SphereCollider * colliderB = dynamic_cast <SphereCollider *>(colliderArray[j]);
                    checkSphereCollision(colliderA ,colliderB);
                }
                else if (typeX == 2 && typeY == 2 ){

                    AABBcollision * colliderA = dynamic_cast <AABBcollision *>(colliderArray[i]);
                    AABBcollision * colliderB = dynamic_cast <AABBcollision *>(colliderArray[j]);

                    checkAABBcollision(colliderA , colliderB);
                }
                else if (typeX == 1 && typeY == 2){
                   SphereCollider * colliderA = dynamic_cast <SphereCollider *>(colliderArray[i]);
                   AABBcollision * colliderB = dynamic_cast <AABBcollision *>(colliderArray[j]);

                    checkSphereAABB(colliderA , colliderB);

                }
                else if(typeX == 2 && typeY == 1){
                    AABBcollision * colliderA = dynamic_cast <AABBcollision *>(colliderArray[i]);
                    SphereCollider * colliderB = dynamic_cast <SphereCollider *>(colliderArray[j]);

                    checkSphereAABB(colliderB , colliderA);
                }
            }
        }
    }

    void CollisionDetection::checkSphereCollision( SphereCollider * sphere1, SphereCollider * sphere2 )
    {
            float sumOfRadius = sphere1->getRadius() + sphere2->getRadius();
            glm::vec3 difference = sphere2->getPosition() -  sphere1->getPosition();

            float dist = glm::length(difference);
            if(dist <= sumOfRadius){
                CollisionResult * res = new CollisionResult();
                res->objectA = sphere1->getParent();
                res->objectB = sphere2->getParent();
                res->overlap = glm::normalize( difference ) * ( sumOfRadius - dist ); //glm::vec3 with distance and size of overlap

                res->objectA->getController()->onCollision( res ); //Run onCollision in the controller of the first GameObject
                res->objectB->getController()->onCollision( res );
            }
    }

    void CollisionDetection::checkAABBcollision(AABBcollision * box1, AABBcollision * box2){
    //run the check to see if obj 1 and 2 collide, if they do, then start function doAABBcollision
    //box 1 left and right boundary lines.
    float maxRightSide1 = box1->getPosition().x + box1->getMaxBounds().x;
    float maxLeftSide1 = box1->getPosition().x + box1->getMinBounds().x;
    //box 2 left and right boundary lines.
    float maxRightSide2 = box2->getPosition().x + box2->getMaxBounds().x;
    float maxLeftSide2 = box2->getPosition().x + box2->getMinBounds().x;
    //box 1 up and down boundary lines.
    float maxUpSide1 = box1->getPosition().z + box1->getMaxBounds().z;
    float maxDownSide1 = box1->getPosition().z + box1->getMinBounds().z;
    //box 2 up and down boundary lines.
    float maxUpSide2 = box2->getPosition().z + box2->getMaxBounds().z;
    float maxDownSide2 = box2->getPosition().z + box2->getMinBounds().z;

        if (maxRightSide1 < maxLeftSide2){ //check right
            if(maxLeftSide1 > maxRightSide2){ //check left
                if (maxUpSide1 < maxDownSide2){ //check top
                    if (maxDownSide1 > maxUpSide2){ //check bottom
                        CollisionResult * res = new CollisionResult();
                        res->objectA = box1->getParent();
                        res->objectB = box2->getParent();
                        res->overlap = glm::vec3(0,0,0);

                        res->objectA->getController()->onCollision( res );
                        res->objectB->getController()->onCollision( res );
                    }
                }
            }
        }//end of 4 checks for collision
    }//end of checkAABBCollision

    void CollisionDetection::checkSphereAABB(SphereCollider * sphere , AABBcollision * box){

        float maxRightSide = box->getPosition().x + box->getMaxBounds().x;
        float maxLeftSide = box->getPosition().x + box->getMinBounds().x;
        float maxUpSide = box->getPosition().z + box->getMaxBounds().z;
        float maxDownSide = box->getPosition().z + box->getMinBounds().z;


        glm::vec3 closestPoint = sphere->getPosition();

        if(closestPoint.x > maxRightSide){//right side check
            closestPoint.x = maxRightSide;
        }
        if(closestPoint.x < maxLeftSide){//left side check
            closestPoint.x = maxLeftSide;
        }
        if(closestPoint.z > maxUpSide){//up side check
            closestPoint.z = maxUpSide;
        }
        if(closestPoint.z < maxDownSide){//up side check
            closestPoint.z = maxDownSide;
        }

        //--calculating diff between closespoint and sphere Radius--
        float radius = sphere->getRadius();
        glm::vec3 difference = closestPoint - sphere->getPosition();

        if(glm::length(difference) <= radius){
            CollisionResult * res = new CollisionResult();
            res->objectA = sphere->getParent();
            res->objectB = box->getParent();
            res->overlap = glm::normalize( difference ) * ( radius - glm::length( difference ) );

            if( res->objectA->getController() ) {
                res->objectA->getController()->onCollision( res );
            }
            if( res->objectB->getController() ) {
                res->objectB->getController()->onCollision( res );
            }
        }
        //--end of calculation--
    }//end of checkSphereAABB func();
}//end of namespace
