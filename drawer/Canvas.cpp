#include "Canvas.h"

Canvas::Canvas(int mwidth, int mheight, int msize)
	: width(mwidth), height(mheight), pixel_size(msize)
	, pixels(mheight* mwidth)
{
	root = sf::Vector2f(10, 90);

	int width_counter = 0;
	int height_counter = 0;
	for (size_t i = 0; i < pixels.size(); i++)
	{
		pixels[i].setPosition(sf::Vector2f(width_counter * msize + root.x, height_counter * msize + root.y));
		width_counter++;

		if (width_counter == mwidth)
		{
			width_counter = 0;
			height_counter += 1;
		}

		pixels[i].setFillColor(sf::Color::White);
		pixels[i].setSize(sf::Vector2f(msize, msize));
	}
}

void Canvas::draw(sf::RenderWindow& window)
{
	sf::Texture texture;
	texture.loadFromImage(std::move(createImage()));
	sf::Sprite sprite;
	sprite.setPosition(root);
	sprite.setScale(pixel_size, pixel_size);
	sprite.setTexture(texture);

	window.draw(sprite);
}

void Canvas::resize(int x, int y)
{
	std::vector<sf::RectangleShape> new_pixels;
	new_pixels.resize((height + x) * (width + y));

	int width_counter = 0;
	int height_counter = 0;
	for (size_t i = 0; i < new_pixels.size(); i++)
	{
		new_pixels[i].setPosition(sf::Vector2f(width_counter * pixel_size + root.x, height_counter * pixel_size + root.y));
		width_counter++;

		if (width_counter == width + y)
		{
			width_counter = 0;
			height_counter += 1;
		}

		new_pixels[i].setFillColor(sf::Color::White);
		new_pixels[i].setSize(sf::Vector2f(pixel_size, pixel_size));
	}

	for (size_t i = 0; i < pixels.size(); i++)
	{
		int new_index = (i / width) * (width + y) + i % width;
		if (new_index > new_pixels.size())
			new_pixels[new_index].setFillColor(pixels[i].getFillColor());
	}

	pixels.erase(pixels.begin(), pixels.end());
	pixels.insert(pixels.begin(), std::make_move_iterator(new_pixels.begin()), std::make_move_iterator(new_pixels.end()));
	width = width + x;
	height = height + y;
}

void Canvas::loadFromImage(sf::Image image)
{
	sf::Vector2u size = image.getSize();
	width = size.x;
	height = size.y;
	if (pixel_size == 0) pixel_size = 1;
	pixels.resize(width * height);

	int width_counter = 0;
	int height_counter = 0;
	for (size_t i = 0; i < pixels.size(); i++)
	{
		pixels[i].setPosition(sf::Vector2f(width_counter * pixel_size + root.x, height_counter * pixel_size + root.y));
		pixels[i].setFillColor(image.getPixel(width_counter, height_counter));
		width_counter++;

		if (width_counter == pixel_size)
		{
			width_counter = 0;
			height_counter += 1;
		}

		pixels[i].setFillColor(image.getPixel(width_counter, height_counter));
		pixels[i].setSize(sf::Vector2f(pixel_size, pixel_size));
	}
}

sf::Vector2f Canvas::getRoot()
{
	return root;
}

sf::Vector2f Canvas::getEnd()
{
	return sf::Vector2f(root.x + width * pixel_size, root.y + height * pixel_size);
}

sf::Vector2f Canvas::getSize()
{
	return sf::Vector2f(width, height);
}

void Canvas::drawLine(sf::Vector2f coords1, sf::Vector2f coords2, sf::Color color, int thickness)
{
	if (std::abs(coords1.x - coords2.x) <= 1 && std::abs(coords1.y - coords2.y) <= 1)
	{
		changePixelColor(coords1, color, thickness);
		return;
	}

	if (std::abs(coords1.x - coords2.x) <= 1)
	{
		if (coords1.y > coords2.y)
		{
			sf::Vector2f temp = coords1;
			coords1 = coords2;
			coords2 = temp;
		}

		for (coords1.y; coords1.y < coords2.y; coords1.y += 1)
			changePixelColor(coords1, color, thickness);

		return;
	}

	if (std::abs(coords1.y - coords2.y) <= 1)
	{
		if (coords1.x > coords2.x)
		{
			sf::Vector2f temp = coords1;
			coords1 = coords2;
			coords2 = temp;
		}

		for (coords1.x; coords1.x < coords2.x; coords1.x += 1)
			changePixelColor(coords1, color, thickness);

		return;
	}

	if (coords1.x > coords2.x ||
		(coords1.x > coords2.x && coords1.y > coords2.y)) {
		sf::Vector2f temp = coords1;
		coords1 = coords2;
		coords2 = temp;
	}

	float mouseX1 = coords1.x - root.x;
	float mouseY1 = coords1.y - root.y;
	float mouseX2 = coords2.x - root.x;
	float mouseY2 = coords2.y - root.y;

	if (mouseX1 <= thickness / 2) mouseX1 = thickness / 2;
	if (mouseX1 >= (width * pixel_size - thickness / 2)) mouseX1 = width * pixel_size - thickness / 2;
	if (mouseY1 <= thickness / 2) mouseY1 = thickness / 2;
	if (mouseY1 >= (height * pixel_size - thickness / 2)) mouseY1 = height * pixel_size - thickness / 2;

	if (mouseX2 <= thickness / 2) mouseX2 = thickness / 2;
	if (mouseX2 >= (width * pixel_size - thickness / 2)) mouseX2 = width * pixel_size - thickness / 2;
	if (mouseY2 <= thickness / 2) mouseY2 = thickness / 2;
	if (mouseY2 >= (height * pixel_size - thickness / 2)) mouseY2 = height * pixel_size - thickness / 2;

	mouseX1 -= thickness / 2;
	mouseY1 -= thickness / 2;
	mouseX2 -= thickness / 2;
	mouseY2 -= thickness / 2;

	float k = (mouseY2 - mouseY1) / (mouseX2 - mouseX1);
	float b = (mouseX2 * mouseY1 - mouseX1 * mouseY2) / (mouseX2 - mouseX1);

	float Y_cor_prev = k * mouseX1 + b;

	for (int x = mouseX1; x < mouseX2; x += 1)
	{
		float X_cor = x;
		float Y_cor = k * x + b;

		if (std::abs(Y_cor - static_cast<int>(Y_cor)) > 0.0049)
			Y_cor = static_cast<int>(Y_cor) + 1;

		for (int i = 0; i < thickness; i++)
			for (int j = 0; j < thickness; j++)
				pixels[X_cor / pixel_size + (Y_cor / pixel_size) * width + i + j * width].setFillColor(color);

		Y_cor_prev = Y_cor;
	}
}

void Canvas::changePixelColor(sf::Vector2f coordinates, sf::Color color, int thickness)
{
	int mouseX = coordinates.x - root.x;
	int mouseY = coordinates.y - root.y;

	if (mouseX <= thickness / 2) mouseX = thickness / 2;
	if (mouseX >= (width * pixel_size - thickness / 2)) mouseX = width * pixel_size - thickness / 2;
	if (mouseY <= thickness / 2) mouseY = thickness / 2;
	if (mouseY >= (height * pixel_size - thickness / 2)) mouseY = height * pixel_size - thickness / 2;

	mouseX -= thickness / 2;
	mouseY -= thickness / 2;

	for (int i = 0; i < thickness; i++)
		for (int j = 0; j < thickness; j++)
			pixels[mouseX / pixel_size + (mouseY / pixel_size) * width + i + j * width].setFillColor(color);
}

/*void Canvas::resize(sf::RenderWindow& window)
{
	root.x = (window.getSize().x - pixels[0].getSize().x * width) / 2 + 50;
	root.y = (window.getSize().y - pixels[0].getSize().y * height) / 2 + 50;

	int width_counter = 0;
	int height_counter = 0;
	for (size_t i = 0; i < pixels.size(); i++)
	{
		pixels[i].setPosition(sf::Vector2f(width_counter * pixel_size + root.x, height_counter * pixel_size + root.y));
		width_counter++;

		if (width_counter == width)
		{
			width_counter = 0;
			height_counter += 1;
		}
	}
}*/

sf::Image Canvas::createImage()
{
	sf::Image image;
	image.create(width, height, sf::Color::White);

	int width_counter = 0;
	int height_counter = 0;
	for (size_t i = 0; i < pixels.size(); i++)
	{
		image.setPixel(width_counter, height_counter, pixels[i].getFillColor());
		width_counter++;

		if (width_counter == width)
		{
			width_counter = 0;
			height_counter += 1;
		}
	}

	return image;
}
