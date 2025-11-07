// UI class for frontend

#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>  // Include SFML classes
using namespace std;

class UI {
public:
    UI();             // Constructor
    void run();       // Start the loop

private:
    int width, height;
    sf::RenderWindow m_window;
    sf::Font m_font;
    sf::Text text;

    void processEvents();
    void update();
    void render();

    void setText(sf::Text& text, float x, float y);
    void makeText(sf::Text& text, string str, sf::Font& font, int fontSize, sf::Color color);
    
};
