#include "CollisionDetection.hpp"

#include "utils/glm.hpp"

#include <iostream>
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
            doSphereCollision(_objects);

            //// THIS HERE IS FOR FUTURE UPDATING ON ALL COLLISION
            //// SO SPHERE ON AABB ,,, AABB ON AABB
            //// SPHERE ON SPHERE IS ALREADY DONE

      }//end of update();

      void CollisionDetection::checkSphereCollision(SphereCollider * sphere1 ,SphereCollider * sphere2){

        float sumOfRadius = sphere1->getRadius() + sphere2->getRadius();

        //sumOfRadius* = sumOfRadius;

        glm::vec3 difference = sphere2->getPosition() -  sphere1->getPosition();

        float dist = glm::length(difference);

        if(dist <= sumOfRadius){

            std::cout<< "printing collision"<< std::endl;
        }
    }
        //working area
    void CollisionDetection::doSphereCollision(std::vector<GameObject *> _objects){

        std::vector<Collider *> colliderArray;
        for( GameObject* object : _objects ) {
             //used to get each object position.
             //CheckRuns
             //std::cout<< object << "Object at the start" << std::endl;
             //
           std::vector<Collider *> tempArray;
           tempArray = object->getCollider();//should be a perfect copy of the collider array of the object

            //std::cout<< tempArray.size() << "tempArray after get kollider" << std::endl;

            colliderArray.insert(colliderArray.end(),tempArray.begin(),tempArray.end());

            for (unsigned int i = 0; i<colliderArray.size(); i++){
                for (unsigned int j = i+1; j<colliderArray.size() ; j++ ){
                    //std::cout<< colliderArray.size() << "collider Array AFTER both for loops" << std::endl;

                    SphereCollider * colliderA = dynamic_cast <SphereCollider *>(colliderArray[i]);
                    //SphereCollider* collA = dynamic_cast<SphereCollider*>( colliderArray[i] );
                    //std::cout<< colliderA->getRadius() << "Collider A after the 1st loop " << std::endl;
                    SphereCollider* colliderB = dynamic_cast <SphereCollider *>(colliderArray[j]);

                    //std::cout<< colliderArray.size() << std::endl;

                    //std::cout<< colliderA->getRadius() << " Collider A after everything"<< std::endl;
                    //std::cout<< colliderB->getRadius() << "Collider B for scale" << std::endl;

                    glm::vec3 DifferencE = colliderB->getPosition() - colliderA->getPosition() ;

                    //std::cout<< DifferencE << " the difference of A&B "<< std::endl;
                    std::cout<< glm::length(DifferencE)<<"the lenght of the difference" << std::endl;
                    //std::cout<< colliderA->getPosition() << " the collider A position " << std::endl;
                    //std::cout<< colliderB->getPosition() << " colliderB position"<< std::endl;

                    checkSphereCollision(colliderA ,colliderB);
                }//end of J for loop
            }//end of I for loop
        }//end of for-loop-all GO's

        //end of working area


        //distance = (float radius2 - float radius1);

      //do math here
      }

}//end of namespace
