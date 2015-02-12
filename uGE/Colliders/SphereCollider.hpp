#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H


#include "..\Collider.hpp" //the " .." means that the file is in the folder above

namespace uGE {
    class SphereCollider : public Collider
    {
        public:

            SphereCollider(GameObject * aParent, float aRadius);
            virtual ~SphereCollider();

            float getRadius();

        protected:
        private:

            float radius;
    };//end of SphereCollider class
}//end of uGE
#endif // SPHERECOLLIDER_H
