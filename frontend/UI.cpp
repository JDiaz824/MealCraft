#include "UI.h"
#include <SFML/Graphics.hpp>  // Include SFML classes
using namespace std;

// Constructor
UI::UI()
: width(1500), height(1000), m_window(sf::VideoMode(width, height), "MealCraft")
{
    // Load font once
    if (!m_font.loadFromFile("../frontend/assets/regular.otf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    makeText(text, "Welcome to MealCraft!", m_font, 100, sf::Color::White);
    setText(text, width / 2,(height / 2) - 75);
}


void UI::run() {
    while (m_window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void UI::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void UI::update() {
    // Update logic (currently empty)
}

void UI::render() {
    m_window.clear();
    m_window.draw(text);
    m_window.display();
}

void UI::setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
};

void UI::makeText(sf::Text &text, string str, sf::Font &font, int fontSize, sf::Color color) {
    // sf::Uint32 integer type allows for a combo of one or more styles
    //  -- https://www.sfml-dev.org/documentation/2.0/classsf_1_1Text.php
    // sets font - same font is used for all text
    // declare text object, set string, font, characterSize, color, and style(s)
    text.setString(str);
    text.setFont(font);
    text.setCharacterSize(fontSize);
    text.setFillColor(color);
};
