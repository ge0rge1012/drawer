#pragma once

#include "SFML/Graphics.hpp"
#include "Constants.h"

class GUI {
public:
	GUI();
	void draw(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	sf::Color get_drawing_color();
	sf::Color get_erasing_color();
	void left_click(sf::Vector2f coordinates);
	void right_click(sf::Vector2f coordinates);

private:
	sf::Font font;
	std::vector<sf::Text> t_colors;
	size_t num_of_colours = 8;
	sf::RectangleShape top_line;
	sf::RectangleShape left_line;

	std::vector<sf::RectangleShape> colours;
	std::vector<sf::RectangleShape> colours_back1;
	std::vector<sf::RectangleShape> colours_back2;
	std::vector<sf::IntRect> colour_boxes;
	std::vector<sf::RectangleShape> chosen_colours;
	std::vector<sf::RectangleShape> ch_colours_back1;
	std::vector<sf::RectangleShape> ch_colours_back2;

	sf::Color drawingColor = sf::Color::Black;
	sf::Color erasingColor = sf::Color::White;
};
