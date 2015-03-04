#include "SphereCollider.hpp"


namespace uGE{
    SphereCollider::SphereCollider(GameObject * aParent , float aRadius)
    :Collider(aParent)
    {
        cType = 1;
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
