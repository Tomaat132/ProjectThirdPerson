#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include "utils/glm.hpp"

namespace uGE
{
    class Material
    {
        public:
            enum BlendMode {
                NORMAL,
                ALPHA,
                ADD,
                SUB
            };

            Material();
            virtual ~Material();

            void setOverhang( bool value, float alpha = .5f );
            void setAlpha( float value );
            void setColor( glm::vec3 rgb );
            void setColor( glm::vec4 rgba );
            void setBlendMode( BlendMode mode );

            bool isOverhang();
            float getOverhangAlpha();
            float getAlpha();
            glm::vec3 getColor();
            BlendMode getBlendMode();

            void applyBlendMode();

        protected:

        private:
            bool overhang;
            float overhangAlpha;
            float alpha;

            glm::vec3 color;
            BlendMode blend;
    };
}

#endif // MATERIAL_H
