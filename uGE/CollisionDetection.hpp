#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <vector>

namespace uGE{

    class GameObject;
    class SphereCollider;
    class AABBcollision;

    class CollisionDetection
    {
        public:
            CollisionDetection();
            virtual ~CollisionDetection();
            //add stuff under here

            void checkSphereCollision(SphereCollider * sphere1 , SphereCollider * sphere2);
            void update(std::vector<GameObject *> _objects);
            void doSphereCollision(std::vector<GameObject *> _objects);
            //new stuff area
            void checkAABBcollision(AABBcollision * box1, AABBcollision * box2);
            void checkSphereAABB(SphereCollider * sphere , AABBcollision * box);
            //
        protected:
        private:
    };//end of CollisionDetetction class
}

#endif // COLLISIONDETECTION_H
