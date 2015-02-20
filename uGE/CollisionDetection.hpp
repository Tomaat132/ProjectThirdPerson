#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <vector>

namespace uGE{

    class GameObject;
    class SphereCollider;

    class CollisionDetection
    {
        public:
            CollisionDetection();
            virtual ~CollisionDetection();
            //add stuff under here

            void checkSphereCollision(SphereCollider * sphere1 , SphereCollider * sphere2);
            void update(std::vector<GameObject *> _objects);
            void doSphereCollision(std::vector<GameObject *> _objects);

        protected:
        private:
    };//end of CollisionDetetction class
}

#endif // COLLISIONDETECTION_H
