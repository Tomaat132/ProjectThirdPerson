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

            sf::Font font;
            sf::Text zombieText;
            sf::Text healthText;
            sf::Text spiritText;
    };

}

#endif // HUD_H
