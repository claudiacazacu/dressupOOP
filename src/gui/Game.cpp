#include "gui/Game.h"
#include <iostream>

Game::Game() : hasFont(false) {
    window.create(sf::VideoMode(800, 600), "DressUp Game");

    if (font.loadFromFile("assets/fonts/angelica.ttf")) {
        hasFont = true;
    } else if (font.loadFromFile("C:/Windows/Fonts/darling.ttf")) {
        hasFont = true;
    } else {
        std::cout << "Warning: Could not load font, text will not be displayed.\n";
    }

    if (hasFont) {
        title.setFont(font);
        title.setString("DressUp");
        title.setCharacterSize(50);
        title.setFillColor(sf::Color::White);
        title.setPosition(300, 250); // Center-ish
    }
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        if (hasFont) {
            window.draw(title);
        }
        window.display();
    }
}