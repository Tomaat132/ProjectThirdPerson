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

            sf::Texture healthImg;
            sf::Texture spiritImg;
            sf::Texture timeImg;
            sf::Texture scoreImg;

            sf::Sprite healthSprite;
            sf::Sprite spiritSprite;
            sf::Sprite timeSprite;
            sf::Sprite scoreSprite;

            sf::Font font;
            sf::Text zombieText;

            sf::Text healthText;
            sf::Text spiritText;
            sf::Text timeText;
            sf::Text scoreText;

            void drawWithOutline( sf::Text* text, sf::RenderWindow* window, sf::Color color = sf::Color::White );
            std::string formatTime( int time );
    };

}

#endif // HUD_H
