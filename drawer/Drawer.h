#pragma once

#include <iostream>
#include <thread>
#include "SFML/Graphics.hpp"
#include "GUI.h"
#include "Canvas.h"
#include "Constants.h"

class Drawer {
public:
	Drawer();
	void run();
	void resize();
	void process_events();
	void update();
	void render();
	void save();
	void undo();

private:
	sf::RenderWindow d_window;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60 * 1.f);

	Canvas canvas;
	GUI gui;
	sf::Image picture;
	sf::View view;
	// std::list<sf::Image> changes;
	int windowWidth;
	int windowHeight;
};