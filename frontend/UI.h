// UI class for frontend

#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>  // Include SFML classes
using namespace std;

class UI {
public:
    UI();     
    void run();

private:
    int width, height;
    sf::RenderWindow window;
    sf::Font reg_font;
    sf::Font bold_font;
    sf::Font italic_font;
    sf::Font strong_font;
    sf::Text title;
    sf::Text t1;
    sf::Text t2;
    sf::Text t3;


    void processEvents();
    void update();
    void render();

    // functions below are reused from my minesweeper project from Prog 2
    void setText(sf::Text& text, float x, float y);
    void makeText(sf::Text& text, string str, sf::Font& font, int fontSize, sf::Color color);
    
};
