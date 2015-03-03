#ifndef AABBCOLLISION_H
#define AABBCOLLISION_H

#include "..\Collider.hpp"

namespace uGE{
    class AABBcollision : public Collider
    {
        public:
            AABBcollision(GameObject * aParent);
            virtual ~AABBcollision();

            glm::vec3 getMinBounds();
            glm::vec3 getMaxBounds();


        protected:
        private:


    };
}

#endif // AABBCOLLISION_H
