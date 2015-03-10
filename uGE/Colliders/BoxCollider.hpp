#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "AABBcollision.hpp"
#include "../utils/glm.hpp"

#include <vector>

namespace uGE
{
    class BoxCollider : public AABBcollision
    {
        public:
            BoxCollider( GameObject * aParent );
            virtual ~BoxCollider();

            std::vector<glm::vec2> getPoints();
        protected:
        private:
    };
}

#endif // BOXCOLLIDER_H
