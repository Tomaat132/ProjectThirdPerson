#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <vector>

namespace uGE{

    class GameObject;//IT WILL EXIST

    class CollisionDetection
    {
        public:
            CollisionDetection();
            virtual ~CollisionDetection();
            //add stuff under here

            void update(std::vector<GameObject *> _objects);

        protected:
        private:
    };//end of CollisionDetetction class
}

#endif // COLLISIONDETECTION_H
