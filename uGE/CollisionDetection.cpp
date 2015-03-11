#include "CollisionDetection.hpp"
#include "Colliders/SphereCollider.hpp"
#include "Colliders/BoxCollider.hpp"
#include "Colliders/AABBcollision.hpp"
#include "Collider.hpp"

#include "GameObject.hpp"
#include "Controller.hpp"
#include "SceneManager.hpp"
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
        std::vector<Collider *> tempArray;
        tempArray = ( (GameObject*) SceneManager::_player )->getColliders();
        colliderArray.insert(colliderArray.end(),tempArray.begin(),tempArray.end());

        for (unsigned int i = 0; i<colliderArray.size(); i++) {
            for (unsigned int j = i+1; j<colliderArray.size() ; j++ ) {
                if( colliderArray[i]->getParent() == colliderArray[j]->getParent() ){
                    continue;
                }

                int typeX = colliderArray[i]->getColliderType();
                int typeY = colliderArray[j]->getColliderType();

                if ( typeX == Collider::SPHERE && typeY == Collider::SPHERE ) {
                    SphereCollider * colliderA = dynamic_cast <SphereCollider *>(colliderArray[i]);
                    SphereCollider * colliderB = dynamic_cast <SphereCollider *>(colliderArray[j]);
                    checkSphereCollision(colliderA ,colliderB);
                }
                else if( typeX == Collider::SPHERE && typeY == Collider::BOX ) {
                    SphereCollider* colliderA = dynamic_cast<SphereCollider*> ( colliderArray[i] );
                    BoxCollider* colliderB = dynamic_cast<BoxCollider*> ( colliderArray[j] );
                    checkSphereBoxCollision( colliderA, colliderB );
                }
                else if( typeX == Collider::BOX && typeY == Collider::SPHERE ) {
                    SphereCollider* colliderA = dynamic_cast<SphereCollider*> ( colliderArray[j] );
                    BoxCollider* colliderB = dynamic_cast<BoxCollider*> ( colliderArray[i] );
                    checkSphereBoxCollision( colliderA, colliderB );
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
                res->colliderTypeA = sphere1->getColliderType();
                res->colliderTypeB = sphere2->getColliderType();
                res->overlap = glm::normalize( difference ) * ( sumOfRadius - dist ); //glm::vec3 with distance and size of overlap

                res->objectA->getController()->onCollision( res ); //Run onCollision in the controller of the first GameObject
                res->objectB->getController()->onCollision( res );
            }
    }

    void CollisionDetection::checkAABBcollision(AABBcollision * box1, AABBcollision * box2){
        float maxRightSide1 = box1->getPosition().x + box1->getMaxBounds().x;
        float maxLeftSide1 = box1->getPosition().x + box1->getMinBounds().x;
        float maxRightSide2 = box2->getPosition().x + box2->getMaxBounds().x;
        float maxLeftSide2 = box2->getPosition().x + box2->getMinBounds().x;
        float maxUpSide1 = box1->getPosition().z + box1->getMaxBounds().z;
        float maxUpSide2 = box2->getPosition().z + box2->getMaxBounds().z;
        float maxDownSide1 = box1->getPosition().z + box1->getMinBounds().z;
        float maxDownSide2 = box2->getPosition().z + box2->getMinBounds().z;

        if (maxRightSide1 < maxLeftSide2){ //check right
            if(maxLeftSide1 > maxRightSide2){ //check left
                if (maxUpSide1 < maxDownSide2){ //check top
                    if (maxDownSide1 > maxUpSide2){ //check bottom
                        CollisionResult * res = new CollisionResult();
                        res->objectA = box1->getParent();
                        res->objectB = box2->getParent();
                        res->colliderTypeA = box1->getColliderType();
                        res->colliderTypeB = box2->getColliderType();
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
            res->colliderTypeA = sphere->getColliderType();
            res->colliderTypeB = box->getColliderType();
            res->overlap = glm::normalize( difference ) * ( radius - glm::length( difference ) );

            if( res->objectA->getController() ) {
                res->objectA->getController()->onCollision( res );
            }
            if( res->objectB->getController() ) {
                res->objectB->getController()->onCollision( res );
            }
        }

    }

    void CollisionDetection::checkBoxCollision( BoxCollider * box1, BoxCollider * box2 )
    {
        std::vector<glm::vec2> points1 = box1->getPoints();
        std::vector<glm::vec2> points2 = box2->getPoints();

        for( unsigned int a = 0; a < 4; ++a ) {
            glm::vec2 point1a = points1[a];
            glm::vec2 point1b = ( a == 3 ) ? points1[0] : points1[a+1];

            for( unsigned int b = 0; b < 4; ++b ) {
                glm::vec2 point2a = points2[b];
                glm::vec2 point2b = ( b == 3 ) ? points2[0] : points2[b+1];

                if( checkLineCollision( point1a, point1b, point2a, point2b ) ) {
                    CollisionResult* res = new CollisionResult();
                    res->objectA = box1->getParent();
                    res->objectB = box2->getParent();
                    res->colliderTypeA = box1->getColliderType();
                    res->colliderTypeB = box2->getColliderType();
                    res->overlap = box2->getPosition() - box1->getPosition();

                    if( res->objectA->getController() ) {
                        res->objectA->getController()->onCollision( res );
                    }
                    if( res->objectB->getController() ) {
                        res->objectB->getController()->onCollision( res );
                    }
                    return;
                }
            }
        }
    }

    void CollisionDetection::checkSphereBoxCollision( SphereCollider* sphere, BoxCollider* box )
    {
        std::vector<glm::vec2> points = box->getPoints();
        //glm::vec2 closestPoint = glm::vec2( 0, 0 );
        glm::vec2 closestDiff = glm::vec2( 0, 0 );
        glm::vec2 sphereVec = glm::vec2( sphere->getPosition().x, sphere->getPosition().z );

        for( unsigned int i = 0; i < 4; ++i ) {
            glm::vec2 pointA = points[i];
            glm::vec2 pointB = ( i == 3 ) ? points[0] : points[i+1];
            glm::vec2 line = pointB - pointA;
            glm::vec2 toSphere = sphereVec - pointA;

            float magnitude = glm::length2( line );
            float dot = glm::dot( line, toSphere );
            float dotLength = dot / magnitude;
            if( dotLength < 0 ) { dotLength = 0; }
            if( dotLength > 1 ) { dotLength = 1; }

            glm::vec2 pointOnLine = pointA + ( line * dotLength );
            glm::vec2 diff = pointOnLine - sphereVec;
            if( glm::length( closestDiff ) == 0 || glm::length( diff ) <= glm::length( closestDiff ) ) {
                closestDiff = diff;
            }
        }

        if( glm::length( closestDiff ) != 0 ) {
            if( glm::length( closestDiff ) <= sphere->getRadius() ) {
                CollisionResult* res = new CollisionResult();
                res->objectA = sphere->getParent();
                res->objectB = box->getParent();
                res->colliderTypeA = sphere->getColliderType();
                res->colliderTypeB = box->getColliderType();
                res->overlap = glm::normalize( glm::vec3(closestDiff.x, 0, closestDiff.y) ) * ( sphere->getRadius() - glm::length( closestDiff ) );

                if( res->objectA->getController() ) {
                    res->objectA->getController()->onCollision( res );
                }
                if( res->objectB->getController() ) {
                    res->objectB->getController()->onCollision( res );
                }
            }
        }
    }

    bool CollisionDetection::checkLineCollision( glm::vec2 line1a, glm::vec2 line1b, glm::vec2 line2a, glm::vec2 line2b )
    {
        glm::vec2 line1 = line1b - line1a;
        glm::vec2 line2 = line2b - line2a;

        float s = ( -line1.y * ( line1a.x - line2a.x ) + line1.x * ( line1a.y - line2a.y ) ) / ( -line2.x * line1.y + line1.x * line2.y );
        float t = ( line2.x * ( line1a.y - line2a.y ) - line2.y * ( line1a.x - line2a.x ) ) / ( -line2.x * line1.y + line1.x * line2.y );

        return ( s >= 0 && s <= 1 && t >= 0 && t <= 1 );
    }

}//end of namespace
