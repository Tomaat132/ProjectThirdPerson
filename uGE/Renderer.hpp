#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include "utils/glm.hpp"

namespace uGE
{
    class Body;
    class Renderer
    {
        public:
            Renderer();
            virtual ~Renderer();

            static std::map<Body*, glm::mat4> firstPassRender;
            static std::map<Body*, glm::mat4> secondPassRender;

            static void StartRender();
        protected:
        private:
    };
}

#endif // RENDERER_H
