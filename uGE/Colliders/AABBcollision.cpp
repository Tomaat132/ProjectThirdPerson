#include "AABBcollision.hpp"
#include "Mesh.hpp"
#include "GameObject.hpp"
#include "Body.hpp"

namespace uGE{

    AABBcollision::AABBcollision(GameObject * aParent, std::string aName)
    :Collider(aParent, aName)
    {
        cType = Type::AABB;
        //sizeX = aSizeX;
        //sizeY = aSizeY;
        //sizeZ = aSizeZ;
    }

    AABBcollision::~AABBcollision()
    {
        //dtor
    }

    glm::vec3 AABBcollision::getMinBounds(){
        return parent->getBody()->getMesh()->getLowestBounds();
    }

    glm::vec3 AABBcollision::getMaxBounds(){
        return parent->getBody()->getMesh()->getHighestBounds();
    }
    //working area

    //end of working area

}
