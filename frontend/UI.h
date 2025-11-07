#pragma once

#include <SFML/Graphics.hpp>  // Include SFML classes

class UI {
public:
    UI();            // Constructor
    void run();       // Start the loop

private:
    sf::RenderWindow m_window;
    sf::CircleShape m_shape;

    void processEvents();
    void update();
    void render();
};
