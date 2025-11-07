#include "UI.h"

// Constructor — NO return type
UI::UI()
: m_window(sf::VideoMode(800, 600), "MealCraft"), m_shape(100.f)
{
    m_shape.setFillColor(sf::Color::Green);
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
    m_window.draw(m_shape);
    m_window.display();
}
