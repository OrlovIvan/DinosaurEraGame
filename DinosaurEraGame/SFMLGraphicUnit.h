#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Person;

enum LootType
{
    Empty = 0,
    Scroll,
    Max
};

enum TileColor
{
    Blue = 0,
    Purple,
    Red,
    Green,
    Yellow,
    SkyBlue,
    Orange
};

enum TileType
{
    unknownLand = 0,
    greenField,
    grass,
    lava,
    max
};

class SFMLGraphicUnit
{
public:
    SFMLGraphicUnit();
    void showIntro(sf::RenderWindow& window);
    void showMenu(sf::RenderWindow& window);
	void showMainWindow();
	void init();
    void setCharacters(std::vector<Person*>& persons);

private:
    void initText(const std::string& initialText);

    //std::unique_ptr<sf::RenderWindow> window;
	sf::Texture t1, t2, t3, landscapeUnknown, greenField, grass, lava;
	sf::Texture scroll;
	sf::Text text;
	sf::Font font;

    std::vector<Person*> characters;
	const std::string lootCollected{ "Scrolls: " };
};

