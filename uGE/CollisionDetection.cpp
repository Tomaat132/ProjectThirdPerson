#include "CollisionDetection.hpp"

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
        ////for( GameObject* object : _objects ) {
            //object->getPosition(); //used to get each object position.

            ////// ->std::cout << object->getPosition() << std::endl;

        ////}//end of for-loop-all GO's
      }//end of update();
}//end of namespace
