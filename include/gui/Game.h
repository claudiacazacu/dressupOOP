#pragma once

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    bool hasFont;
};