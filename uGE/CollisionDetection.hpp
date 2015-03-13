#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <vector>
#include "utils/glm.hpp"

namespace uGE{

    class GameObject;
    class SphereCollider;
    class AABBcollision;
    class BoxCollider;

    struct CollisionResult {
        GameObject * objectA;
        GameObject * objectB;
        std::string colliderA, colliderB;
        int colliderTypeA, colliderTypeB;
        glm::vec3 overlap;
    };

    class CollisionDetection
    {
        public:
            CollisionDetection();
            virtual ~CollisionDetection();

            void update(std::vector<GameObject *> _objects);
            void checkCollisions(std::vector<GameObject *> _objects);

            void checkSphereCollision(SphereCollider * sphere1 , SphereCollider * sphere2);
            void checkAABBcollision(AABBcollision * box1, AABBcollision * box2);
            void checkSphereAABB(SphereCollider * sphere , AABBcollision * box);
            void checkBoxCollision( BoxCollider * box1, BoxCollider * box2 );
            void checkSphereBoxCollision( SphereCollider * sphere, BoxCollider * box );

        protected:
        private:
            bool checkLineCollision( glm::vec2 line1a, glm::vec2 line1b, glm::vec2 line2a, glm::vec2 line2b );

            CollisionResult * inverseResult( CollisionResult * result );
    };//end of CollisionDetetction class
}

#endif // COLLISIONDETECTION_H
