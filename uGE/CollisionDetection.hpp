#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <vector>
#include "utils/glm.hpp"

namespace uGE{

    class GameObject;
    class SphereCollider;
    class AABBcollision;

    struct CollisionResult {
        GameObject * objectA;
        GameObject * objectB;
        glm::vec3 overlap;
    };

    class CollisionDetection
    {
        public:
            CollisionDetection();
            virtual ~CollisionDetection();
            //add stuff under here

            void checkSphereCollision(SphereCollider * sphere1 , SphereCollider * sphere2);
            void update(std::vector<GameObject *> _objects);
            void checkCollisions(std::vector<GameObject *> _objects);
            //new stuff area
            void checkAABBcollision(AABBcollision * box1, AABBcollision * box2);
            void checkSphereAABB(SphereCollider * sphere , AABBcollision * box);
            //
        protected:
        private:
    };//end of CollisionDetetction class
}

#endif // COLLISIONDETECTION_H
