#include "Drawer.h"

Drawer::Drawer() : d_window(sf::VideoMode(default_window_width, default_window_height), "Drawer")
, canvas(400, 300, 1), windowWidth(default_window_width), windowHeight(default_window_height)
{
	sf::Image icon;
	icon.loadFromFile("media/cat_32_32.png");
	d_window.setIcon(32, 32, icon.getPixelsPtr());
	view.setCenter(320, 240);
	view.setSize(640, 480);
	d_window.setView(view);
}

void Drawer::run()
{
	// canvas.resize(d_window);
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (d_window.isOpen())
	{
		process_events();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			process_events();
			update();
		}

		render();
	}
}

void Drawer::process_events()
{
	sf::Event event;
	while (d_window.pollEvent(event))        // SFML is saving all events in a queue, so checking them all
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:

			if (sf::Mouse::getPosition(d_window).x >= canvas.getRoot().x
				&& sf::Mouse::getPosition(d_window).x <= canvas.getEnd().x
				&& sf::Mouse::getPosition(d_window).y >= canvas.getRoot().y
				&& sf::Mouse::getPosition(d_window).y <= canvas.getEnd().y)
			{
				sf::Vector2f prev_coords = d_window.mapPixelToCoords(sf::Mouse::getPosition(d_window));
				sf::Vector2f cur_coords = d_window.mapPixelToCoords(sf::Mouse::getPosition(d_window));
				if (event.key.code == sf::Mouse::Button::Left)
				{
					canvas.changePixelColor(prev_coords, gui.get_drawing_color());

				}

				else if (event.key.code == sf::Mouse::Button::Right)
				{
					canvas.changePixelColor(prev_coords, gui.get_erasing_color());

				}

				while (d_window.pollEvent(event) != sf::Event::MouseButtonReleased &&
					(sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
						sf::Mouse::isButtonPressed(sf::Mouse::Right)) &&
					sf::Mouse::getPosition(d_window).x >= canvas.getRoot().x
					&& sf::Mouse::getPosition(d_window).x <= canvas.getEnd().x
					&& sf::Mouse::getPosition(d_window).y >= canvas.getRoot().y
					&& sf::Mouse::getPosition(d_window).y <= canvas.getEnd().y)
				{
					cur_coords = d_window.mapPixelToCoords(sf::Mouse::getPosition(d_window));

					if (cur_coords != prev_coords)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{ 
							canvas.drawLine(cur_coords, prev_coords, gui.get_drawing_color());
						}

						else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
						{
							canvas.drawLine(cur_coords, prev_coords, gui.get_erasing_color());
						}

						prev_coords = cur_coords;
					}

				}
			}

			else
			{
				if (event.key.code == sf::Mouse::Button::Left &&
					sf::Mouse::getPosition(d_window).x >= canvas.getEnd().x
					&& sf::Mouse::getPosition(d_window).y >= canvas.getEnd().y)
					canvas.resize(50, 50);
				else if (event.key.code == sf::Mouse::Button::Left)
					gui.left_click(d_window.mapPixelToCoords(sf::Mouse::getPosition(d_window)));

				else if (event.key.code == sf::Mouse::Button::Right)
					gui.right_click(d_window.mapPixelToCoords(sf::Mouse::getPosition(d_window)));
			}
			break;

		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::E)
			{
				undo();
			}
			break;
		}

		case  sf::Event::Closed:
			d_window.close();
			break;

		case sf::Event::Resized:
		{
			sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
			d_window.setView(sf::View(visibleArea));
			break;
		}

		default:
			break;
		}
	}
}

void Drawer::update()
{
	gui.update(d_window);

	if (d_window.getSize().x != windowWidth ||
		d_window.getSize().y != windowHeight)
		resize();
}

void Drawer::render()
{
	d_window.clear(sf::Color(135, 206, 235, 5));                  // making black (without anything)

	gui.draw(d_window);

	canvas.draw(d_window);

	d_window.display();                // drawing display (screen)
}

void Drawer::resize()
{
	// canvas.resize(d_window);
}

void Drawer::undo()
{
	// sf::Image im = *changes.end();
	//changes.pop_back();
	// canvas.loadFromImage(im);
}

void Drawer::save()
{
	picture = std::move(canvas.createImage());
	picture.saveToFile("mypict.png");
}