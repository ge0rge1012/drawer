#include "GUI.h"

GUI::GUI() : colours(num_of_colours), colours_back1(num_of_colours), colours_back2(num_of_colours), colour_boxes(num_of_colours),
chosen_colours(2), ch_colours_back1(2), ch_colours_back2(2), t_colors(4)
{
	font.loadFromFile("fonts/CyrilicOld.TTF");
	top_line.setFillColor(sf::Color(245, 245, 245));
	top_line.setPosition(sf::Vector2f(0, 0));
	top_line.setSize(sf::Vector2f(default_window_width, 80));

	left_line.setFillColor(sf::Color(245, 245, 245));
	left_line.setPosition(sf::Vector2f(0, 40));
	left_line.setSize(sf::Vector2f(3, default_window_height));

	colours[0].setFillColor(sf::Color::Black);
	colours[1].setFillColor(sf::Color::White);
	colours[2].setFillColor(sf::Color::Red);
	colours[3].setFillColor(sf::Color::Blue);
	colours[4].setFillColor(sf::Color::Green);
	colours[5].setFillColor(sf::Color::Yellow);
	colours[6].setFillColor(sf::Color::Cyan);
	colours[7].setFillColor(sf::Color::Magenta);
	chosen_colours[0].setFillColor(drawingColor);
	chosen_colours[1].setFillColor(erasingColor);
	ch_colours_back1[0].setFillColor(sf::Color::White);
	ch_colours_back1[1].setFillColor(sf::Color::White);
	ch_colours_back2[0].setFillColor(sf::Color(128, 128, 128));
	ch_colours_back2[1].setFillColor(sf::Color(128, 128, 128));

	chosen_colours[0].setPosition(sf::Vector2f(default_window_width / 2 - 40, 7));
	chosen_colours[1].setPosition(chosen_colours[0].getPosition().x + 54, 7);
	ch_colours_back1[0].setPosition(chosen_colours[0].getPosition() - sf::Vector2f(1, 1));
	ch_colours_back1[1].setPosition(chosen_colours[1].getPosition() - sf::Vector2f(1, 1));
	ch_colours_back2[0].setPosition(chosen_colours[0].getPosition() - sf::Vector2f(2, 2));
	ch_colours_back2[1].setPosition(chosen_colours[1].getPosition() - sf::Vector2f(2, 2));

	t_colors[0].setPosition(ch_colours_back2[0].getPosition().x + 5, ch_colours_back2[0].getPosition().y + 40);
	t_colors[1].setPosition(ch_colours_back2[1].getPosition().x + 5, ch_colours_back2[0].getPosition().y + 40);
	t_colors[2].setPosition(t_colors[0].getPosition().x + 14, t_colors[0].getPosition().y + 10);
	t_colors[3].setPosition(t_colors[1].getPosition().x + 14, t_colors[0].getPosition().y + 10);


	chosen_colours[0].setSize(sf::Vector2f(36, 36));
	chosen_colours[1].setSize(sf::Vector2f(36, 36));
	ch_colours_back1[0].setSize(sf::Vector2f(38, 38));
	ch_colours_back1[1].setSize(sf::Vector2f(38, 38));
	ch_colours_back2[0].setSize(sf::Vector2f(40, 40));
	ch_colours_back2[1].setSize(sf::Vector2f(40, 40));

	for (int i = 0; i < 4; i++)
	{
		t_colors[i].setFont(font);
		t_colors[i].setCharacterSize(13);
		t_colors[i].setFillColor(sf::Color::Black);
	}

	t_colors[0].setString("Color");
	t_colors[1].setString("Color");
	t_colors[2].setString("1");
	t_colors[3].setString("2");


	for (int i = 0; i < num_of_colours; i++)
		colours[i].setSize(sf::Vector2f(27, 27));

	for (int i = 0; i < num_of_colours; i++)
	{
		colours_back1[i].setFillColor(sf::Color::White);
		colours_back1[i].setSize(sf::Vector2f(29, 29));
	}

	for (int i = 0; i < num_of_colours; i++)
	{
		colours_back2[i].setFillColor(sf::Color(128, 128, 128));
		colours_back2[i].setSize(sf::Vector2f(31, 31));
	}

	colours[0].setPosition(sf::Vector2f(default_window_width / 2 + 80, 4));

	for (int i = 1; i < num_of_colours; i++)
	{
		if (i % 2 == 1)
			colours[i].setPosition(colours[i - 1].getPosition() + sf::Vector2f(0, 38));

		else
			colours[i].setPosition(colours[i - 1].getPosition() + sf::Vector2f(38, -38));
	}

	for (int i = 0; i < num_of_colours; i++)
	{
		colours_back1[i].setPosition(colours[i].getPosition() - sf::Vector2f(1, 1));
		colours_back2[i].setPosition(colours[i].getPosition() - sf::Vector2f(2, 2));

		colour_boxes[i].left = colours_back2[i].getPosition().x;
		colour_boxes[i].top = colours_back2[i].getPosition().y;
		colour_boxes[i].width = 31;
		colour_boxes[i].height = 31;
	}
}

sf::Color GUI::get_drawing_color()
{
	return drawingColor;
}

sf::Color GUI::get_erasing_color()
{
	return erasingColor;
}

void GUI::left_click(sf::Vector2f coordinates)
{
	for (int i = 0; i < num_of_colours; i++)
		if (colour_boxes[i].contains(coordinates.x, coordinates.y))
			drawingColor = colours[i].getFillColor();
}

void GUI::right_click(sf::Vector2f coordinates)
{
	for (int i = 0; i < num_of_colours; i++)
		if (colour_boxes[i].contains(coordinates.x, coordinates.y))
			erasingColor = colours[i].getFillColor();
}

void GUI::draw(sf::RenderWindow& window)
{
	window.draw(top_line);
	window.draw(left_line);

	for (int i = 0; i < colours.size(); i++)
	{
		window.draw(colours_back2[i]);
		window.draw(colours_back1[i]);
		window.draw(colours[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		window.draw(ch_colours_back2[i]);
		window.draw(ch_colours_back1[i]);
		window.draw(chosen_colours[i]);

	}

	for (int i = 0; i < 4; i++)
		window.draw(t_colors[i]);
}

void GUI::update(sf::RenderWindow& window)
{
	top_line.setSize(sf::Vector2f(window.getSize().x, 80));
	left_line.setSize(sf::Vector2f(3, window.getSize().y));

	chosen_colours[0].setFillColor(drawingColor);
	chosen_colours[1].setFillColor(erasingColor);
}