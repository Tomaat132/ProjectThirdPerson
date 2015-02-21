#include "CollisionDetection.hpp"
#include "Colliders/SphereCollider.hpp"
#include "GameObject.hpp"
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
            doSphereCollision( _objects );

            //// THIS HERE IS FOR FUTURE UPDATING ON ALL COLLISION
            //// SO SPHERE ON AABB ,,, AABB ON AABB
            //// SPHERE ON SPHERE IS ALREADY DONE
      }

      void CollisionDetection::checkSphereCollision( SphereCollider * sphere1, SphereCollider * sphere2 )
      {
            float sumOfRadius = sphere1->getRadius() + sphere2->getRadius();
            glm::vec3 difference = sphere2->getPosition() -  sphere1->getPosition();

            float dist = glm::length(difference);
            if(dist <= sumOfRadius){
                //std::cout<< "printing collision"<< std::endl;
            }
    }

    void CollisionDetection::doSphereCollision(std::vector<GameObject *> _objects)
    {
        std::vector<Collider *> colliderArray;
        for( GameObject* object : _objects ) {

            std::vector<Collider *> tempArray;
            tempArray = object->getColliders();
            colliderArray.insert(colliderArray.end(),tempArray.begin(),tempArray.end());
        }

        for (unsigned int i = 0; i<colliderArray.size(); i++){
            for (unsigned int j = i+1; j<colliderArray.size() ; j++ ){
                SphereCollider * colliderA = dynamic_cast <SphereCollider *>(colliderArray[i]);
                SphereCollider* colliderB = dynamic_cast <SphereCollider *>(colliderArray[j]);
                checkSphereCollision(colliderA ,colliderB);
            }
        }
    }
}//end of namespace
