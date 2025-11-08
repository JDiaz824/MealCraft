#include "UI.h"
#include <SFML/Graphics.hpp>  // Include SFML classes
using namespace std;

/**
 * Constructor
 */
UI::UI() : width(1500), height(1000), window(sf::VideoMode(width, height), "MealCraft") {

    if (!reg_font.loadFromFile("../frontend/assets/regular.otf")) {
        cerr << "Failed to load regular font!" << endl;
    }
    if (!bold_font.loadFromFile("../frontend/assets/bold.otf")) {
        cerr << "Failed to load bold font!" << endl;
    }
    if (!italic_font.loadFromFile("../frontend/assets/italic.otf")) {
        cerr << "Failed to load italic font!" << endl;
    }
    if (!strong_font.loadFromFile("../frontend/assets/bold-italic.otf")) {
        cerr << "Failed to load strong font!" << endl;
    }        

    makeText(title, "MealCraft!", reg_font, 200, sf::Color::White);
    setText(title, width / 2,(height / 2) - 400);

    // makeText(t1, "Welcome to MealCraft!", reg_font, 50, sf::Color::White);
    // setText(t1, width / 2,(height / 2) - 125);

    // makeText(t2, "Welcome to MealCraft!", italic_font, 50, sf::Color::White);
    // setText(t2, width / 2,(height / 2) - 75);
    
    // makeText(t3, "Welcome to MealCraft!", strong_font, 50, sf::Color::White);
    // setText(t3, width / 2,(height / 2) - 25);
}

/**
 * "main" function that combines event handling, backend logic, and rendering UI
 */
void UI::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

/**
 * Processes user input and window events (ex. keyboard/mouse inputs)
 */
void UI::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

/**
 * Updates logic (recipe searching)
 */
void UI::update() {
    // Update logic (currently empty)
}

/**
 * Handles rendering UI
 */
void UI::render() {
    window.clear();
    window.draw(title);
    window.draw(t1);
    window.draw(t2);
    window.draw(t3);
    window.display();
}


/**
 * Positions Text
 */
void UI::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
};

/**
 * Declare text object, string, font, font size, and color
 */
void UI::makeText(sf::Text &text, string str, sf::Font &font, int fontSize, sf::Color color) {
    text.setString(str);
    text.setFont(font);
    text.setCharacterSize(fontSize);
    text.setFillColor(color);
};
