#include "BoxCollider.hpp"
#include "../GameObject.hpp"
#include "../Collider.hpp"
namespace uGE
{

    BoxCollider::BoxCollider( GameObject * aParent, std::string aName )
    : AABBcollision( aParent, aName )
    {
        cType = Type::BOX;
    }

    BoxCollider::~BoxCollider()
    {
        //dtor
    }

    std::vector<glm::vec2> BoxCollider::getPoints()
    {
        glm::vec4 lowestBounds = glm::vec4( getMinBounds(), 1.f );
        glm::vec4 highestBounds = glm::vec4( getMaxBounds(), 1.f );
        lowestBounds = parent->transform * lowestBounds;
        highestBounds = parent->transform * highestBounds;

        std::vector<glm::vec2> points;
        points.push_back( glm::vec2( lowestBounds.x, lowestBounds.z ) );
        points.push_back( glm::vec2( highestBounds.x, lowestBounds.z ) );
        points.push_back( glm::vec2( highestBounds.x, highestBounds.z ) );
        points.push_back( glm::vec2( lowestBounds.x, highestBounds.z ) );

        return points;
    }

}
