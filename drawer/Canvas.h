#pragma once

#include "SFML/Graphics.hpp"
#include "Constants.h"

class Canvas {
public:
	Canvas(int mheight, int mwidth, int msize);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getRoot();
	sf::Vector2f getEnd();
	void changePixelColor(sf::Vector2f coordinates, sf::Color color, int thickness = 4);
	void drawLine(sf::Vector2f coords1, sf::Vector2f coords2, sf::Color color, int thickness = 4);
	// void resize(sf::RenderWindow& window);
	sf::Vector2f getSize();
	sf::Image createImage();
	void loadFromImage(sf::Image image);
	void resize(int x, int y);

private:
	int height;
	int width;
	int pixel_size = 0;
	std::vector<sf::RectangleShape> pixels;
	sf::Vector2f root;                       // top-left corner coordinates
};

