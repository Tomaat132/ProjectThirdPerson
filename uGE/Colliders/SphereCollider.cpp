#include "SphereCollider.hpp"


namespace uGE{
    SphereCollider::SphereCollider(GameObject * aParent , float aRadius)
    :Collider(aParent)
    {

        radius = aRadius;

    }

    SphereCollider::~SphereCollider()
    {
        //dtor
    }

    float SphereCollider::getRadius(){

    return radius;
    }//end of getRadius
}//end of namespace uGE
