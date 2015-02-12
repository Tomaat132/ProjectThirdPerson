#include "CollisionDetection.hpp"

#include "utils/glm.hpp"

#include "Colliders/SphereCollider.hpp"
#include "GameObject.hpp"
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

      void CollisionDetection::update(std::vector<GameObject *> _objects){

            //std::cout<< _objects.size() <<std::endl;
            std::vector<Collider *> colliderArray;
        for( GameObject* object : _objects ) {
             //used to get each object position.
           std::vector<Collider *> tempArray;
           tempArray = object->getCollider();//should be a perfect copy of the collider array of the object

            colliderArray.insert(colliderArray.end(),tempArray.begin(),tempArray.end());

            for (unsigned int i = 0; i<colliderArray.size(); i++){
                for (unsigned int j = i+1; j<colliderArray.size() ; j++ ){

                    SphereCollider * colliderA = dynamic_cast <SphereCollider *>(colliderArray[i]);
                    //SphereCollider* collA = dynamic_cast<SphereCollider*>( colliderArray[i] );
                    SphereCollider* colliderB = dynamic_cast <SphereCollider *>(colliderArray[j]);

                    checkSphereCollision(colliderA ,colliderB);
                }//end of J for loop
            }//end of I for loop
        }//end of for-loop-all GO's
      }//end of update();

      void CollisionDetection::checkSphereCollision(SphereCollider * sphere1 ,SphereCollider * sphere2){

        float sumOfRadius = sphere1->getRadius() + sphere2->getRadius();

        //sumOfRadius* = sumOfRadius;

        glm::vec3 difference = sphere2->getPosition() -  sphere1->getPosition();

        float dist = glm::length( difference );

        if(dist <= sumOfRadius){

            std::cout<< "printing collision"<< std::endl;
        }

        //distance = (float radius2 - float radius1);

      //do math here
      }

}//end of namespace
