#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

namespace uGE
{

    class Hud
    {
        public:
            Hud();
            virtual ~Hud();

            void draw( sf::RenderWindow * window );
        protected:
        private:
            sf::Image hudImage;
            sf::Texture hudTexture;
            sf::Sprite hudSprite;
    };

}

#endif // HUD_H
