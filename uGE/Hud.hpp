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
            void setEndGame( std::string text );
        protected:
        private:
            sf::Texture healthImg;
            sf::Texture spiritImg;
            sf::Texture timeImg;
            sf::Texture scoreImg;
            sf::Texture endImg;

            sf::Sprite healthSprite;
            sf::Sprite spiritSprite;
            sf::Sprite timeSprite;
            sf::Sprite scoreSprite;
            sf::Sprite endSprite;

            sf::Font font;
            sf::Text healthText;
            sf::Text spiritText;
            sf::Text timeText;
            sf::Text scoreText;
            sf::Text endText;
            sf::Text endScoreText;

            bool gameEnd;
            float endAlpha;
            float endAlpha2;
            int scoreCounter;

            void drawWithOutline( sf::Text* text, sf::RenderWindow* window, sf::Color color = sf::Color::White, int lineSize = 1 );
            std::string formatTime( int time );
    };

}

#endif // HUD_H
