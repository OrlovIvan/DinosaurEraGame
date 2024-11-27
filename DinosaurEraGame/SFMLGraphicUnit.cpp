#include "SFMLGraphicUnit.h"
#include <SFML/Graphics.hpp>
#include <time.h>

#include "Person.h"
#include "Position.h"

using namespace sf;
using namespace std;

const int landLengthInTiles = positions::Max_X;
const int landWidthInTiles = positions::Max_Y;
const int tileSize = 32; // in pixels
const int borderSize = 30; // in pixels

vector<vector<int>> landField;
vector<vector<int>> landRecognitionMask;
vector<vector<int>> landLootMap;

struct Point
{
    int x, y;
    int loot;
} a[4], b[4];

bool check()
{
    //for (int i = 0;i < 4;i++)
    int i = 0;
    {
        if (a[i].x < 0 || a[i].x >= landWidthInTiles || a[i].y >= landLengthInTiles || a[i].y < 0) return 0;
        if (landField[a[i].y][a[i].x] == TileType::lava) return 0;
    }
    return 1;
};

void FillField()
{
    for (int x = 0; x < landWidthInTiles; ++x)
    {
        for (int y = 0; y < landLengthInTiles; ++y)
        {
            int tile = rand() % (int)TileType::max;
            landField[y][x] = (tile == 0) ? (tile+1) : tile;// TileType::unknownLand;
            landRecognitionMask[y][x] = 0;

            if (landField[y][x] == TileType::grass || landField[y][x] == TileType::greenField)
            {
                landLootMap[y][x] = rand() % LootType::Max;
            }
        }
    }
}

void CheckAndCorrectPosition(Point& position)
{
    if (position.x < 0) position.x = 0;
    if (position.x >= landWidthInTiles) position.x = landWidthInTiles - 1;
    if (position.y >= landLengthInTiles) position.y = landLengthInTiles - 1;
    if (position.y < 0) position.y = 0;
}

void fillFieldTile(Point& character)
{
    Point& position = character;
    CheckAndCorrectPosition(position);

    for (int x = position.x - 1; x <= position.x + 1;++x)
    {
        for (int y = position.y - 1; y <= position.y + 1; ++y)
        {
            if ((x >= 0 && x < landWidthInTiles) && (y >= 0 && y < landLengthInTiles)
                && landRecognitionMask[y][x] != 1)
            {
                landRecognitionMask[y][x] = static_cast<int>(true);
            }
        }
    }

    if (landLootMap[position.y][position.x] != LootType::Empty)
    {
        landLootMap[position.y][position.x] = LootType::Empty;
        character.loot++;
    }
}

void landFieldInit()
{
    for (int x = 0; x < landWidthInTiles; ++x)
    {
        vector<int> column;
        for (int y = 0; y < landLengthInTiles; ++y)
        {
            column.push_back(0);
        }
        landField.push_back(column);
        landRecognitionMask.push_back(column);
        landLootMap.push_back(column);
    }
}

void refreshLightning(sf::VertexArray& lightning, const int max)
{
    lightning[0].position = sf::Vector2f(200.f, 20.f);
    lightning[0].color = sf::Color::Blue;

    for (int i = 1;i < max;++i)
    {
        lightning[i].position = sf::Vector2f(lightning[0].position.x + i, lightning[i-1].position.y + (rand() % 4) - 2);
        lightning[i].color = sf::Color::Blue;
    }
}

void refreshWaterCircle(sf::VertexArray& waterCircle, const int max)
{

}

void handleKeyPressed(sf::Event::KeyEvent event, int& dx, int& dy, bool& rotate)
{
    switch (event.code)
    {
    case Keyboard::RControl:
    {
        rotate = true;
    }
    break;
    case Keyboard::Left:
    {
        dx = -1;
        dy = 0;
    }
    break;
    case Keyboard::Right:
    {
        dx = 1;
        dy = 0;
    }
    break;
    case Keyboard::Up:
    {
        dx = 0;
        dy = -1;
    }
    break;
    case Keyboard::Down:
    {
        dx = 0;
        dy = 1;
    }
    break;
    }
}

SFMLGraphicUnit::SFMLGraphicUnit()
{
    //window = new sf::RenderWindow(VideoMode(landWidthInTiles * tileSize + borderSize * 2, landLengthInTiles * tileSize + borderSize * 2), "DinosaurEra");
    //window = make_unique<sf::RenderWindow>(VideoMode(landWidthInTiles * tileSize + borderSize * 2, landLengthInTiles * tileSize + borderSize * 2), "DinosaurEra")
//    
}

void SFMLGraphicUnit::initText(const string& initialText)
{
    if (!font.loadFromFile("images/BELL.ttf"))
    {
        int i = 0;
    }
    text.setFont(font);
    text.setString(initialText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(0, 0);
    text.setStyle(sf::Text::Bold);
}

void SFMLGraphicUnit::init()
{
    landFieldInit();
    initText(lootCollected);

    t1.loadFromFile("images/Icons_13.png");
    //t2.loadFromFile("images/background.png");
    //t3.loadFromFile("images/frame.png");
    landscapeUnknown.loadFromFile("images/Map_tile_20.png");
    greenField.loadFromFile("images/Map_tile_23.png");
    grass.loadFromFile("images/Map_tile_17.png");   //where a hero already have been
    lava.loadFromFile("images/Map_tile_98.png");
    scroll.loadFromFile("images/scroll.png");
}

void SFMLGraphicUnit::setCharacters(vector<Person*>& persons)
{
    for (auto person : persons)
        characters.push_back(person);
}

struct Particle
{
    Particle(size_t coordX, size_t coordY, int speed_X, int speed_Y, size_t mass) :
        x(coordX), y(coordY), speedX(speed_X), speedY(speed_Y), mass(mass) {}
    size_t x;
    size_t y;
    int speedX;
    int speedY;

    size_t mass;
};

typedef vector<Particle> ParticlesVec;

void particlesInit(ParticlesVec& paticles, sf::VertexArray& particlesImage, const int count)
{
    const int particlePeneratorPositionX = 10;
    const int particlePeneratorPositionY = landWidthInTiles*tileSize / 2;

    for (int i = 0; i < count; ++i)
    {
        paticles.push_back(Particle(particlePeneratorPositionX, particlePeneratorPositionY, 5, rand() % 4 - 2, 1));
        particlesImage[i].position = sf::Vector2f(particlePeneratorPositionX, particlePeneratorPositionY);
        particlesImage[i].color = sf::Color::Black;
    }
}

void particlesMovement(const ParticlesVec& paticles, sf::VertexArray& particles, const int count)
{
    for (int i = 0;i < count;++i)
    {
        particles[i].position = sf::Vector2f(particles[0].position.x + paticles[i].speedX, particles[i].position.y + paticles[i].speedY);
        particles[i].color = sf::Color::Black;
    }
}

void SFMLGraphicUnit::showIntro(sf::RenderWindow& window)
{
    window.clear(Color::White);

    //const int maxLightningPointIntro = 100;
    //sf::VertexArray lightning(sf::Points, maxLightningPointIntro);

    ParticlesVec particles;
    const int particleCount = 10;
    sf::VertexArray particlesImage(sf::Points, particleCount);
    particlesInit(particles, particlesImage, particleCount);

    Clock clock, clockTimer;
    float timer = 0, delay = 0.3;
    float time = clock.getElapsedTime().asSeconds();
    float timeStart = time;
    clock.restart();
    clockTimer.restart();
    timer += clockTimer.getElapsedTime().asSeconds();
    
    while (clock.getElapsedTime().asSeconds() - timeStart < 10) // Intro 3 sec
    {
        window.clear(Color::White);
        if (timer > delay)
        {
            //refreshLightning(lightning, maxLightningPointIntro);
            particlesMovement(particles, particlesImage, particleCount);
            timer = 0;
            clockTimer.restart();
        }

        
        timer += clockTimer.getElapsedTime().asSeconds();

        window.draw(particlesImage);
        window.display();
    }
}

void SFMLGraphicUnit::showMenu(sf::RenderWindow& window)
{
    constexpr int landWidth = landWidthInTiles * tileSize + borderSize * 2;
    constexpr int landLength = landLengthInTiles * tileSize + borderSize * 2;
    constexpr int landCenterX = landWidth / 2;
    constexpr int landCenterY = landLength / 2;

    Texture t2;
    t2.loadFromFile("images/bg.png");
    Sprite background(t2);

    sf::VertexArray button(sf::Quads, 4);
    button[0].position = sf::Vector2f(landCenterX - 50, landCenterY - 20);
    button[0].color = sf::Color::Blue;

    button[1].position = sf::Vector2f(landCenterX + 50, landCenterY - 20);
    button[1].color = sf::Color::Blue;

    button[2].position = sf::Vector2f(landCenterX + 50, landCenterY + 20);
    button[2].color = sf::Color::Blue;

    button[3].position = sf::Vector2f(landCenterX - 50, landCenterY + 20);
    button[3].color = sf::Color::Blue;

    sf::Text buttonText;
    if (!font.loadFromFile("images/BELL.ttf"))
    {
        int i = 0;
    }
    buttonText.setFont(font);
    buttonText.setString("Play");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(landCenterX - 20, landCenterY - 15);
    buttonText.setStyle(sf::Text::Bold);

    window.clear(Color::White);
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window.close();
                return;
            }
            else if (e.type == Event::MouseMoved)
            {
                
                sf::Vector2i mousePosition = sf::Mouse::getPosition();
                mousePosition.x -= window.getPosition().x;
                mousePosition.y -= window.getPosition().y + 40;
                /*int butt0x = button[0].position.x;
                int butt0y = button[0].position.y;
                int butt1x = button[1].position.x;
                int butt1y = button[1].position.y;

                int butt2x = button[2].position.x;
                int butt2y = button[2].position.y;*/

                if (mousePosition.x >= button[0].position.x && mousePosition.x <= button[1].position.x
                    && mousePosition.y >= button[0].position.y && mousePosition.y <= button[2].position.y)
                {
                    buttonText.setFillColor(sf::Color::Red);
                }
                else
                {
                    buttonText.setFillColor(sf::Color::Black);
                }
            }
            else if (e.type == Event::MouseButtonPressed)
            {
                if (e.key.code == Mouse::Button::Left)
                {
                    buttonText.setFillColor(sf::Color::Yellow);
                    return;
                }
            }
        }
        window.draw(background);
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }

}

void SFMLGraphicUnit::showMainWindow()
{
    sf::RenderWindow window(VideoMode(landWidthInTiles * tileSize + borderSize * 2, landLengthInTiles * tileSize + borderSize * 2), "DinosaurEra");
    showIntro(window);
    showMenu(window);

    //Sprite s(t1), background(t2), frame(t3);
    Sprite character(t1);
    Sprite lavaLand(lava);
    Sprite land(landscapeUnknown);
    Sprite landGreenField(greenField);
    Sprite landGrass(grass);
    Sprite scrolls(scroll);

    const int maxLightningPoint = 100;
    sf::VertexArray lightning(sf::Points, maxLightningPoint);
    sf::VertexArray str(sf::LineStrip, 3);
    str[0].position = Vector2f(20.f, 60.f);
    str[0].color = sf::Color::Red;
    str[1].position = Vector2f(20.f, 100.f);
    str[1].color = sf::Color::White;
    str[2].position = Vector2f(20.f, 140.f);
    str[2].color = sf::Color::Blue;

    init();

    window.clear(Color::White);
    Clock clock;
    int dx = 0;
    int dy = 0;
    bool rotate = 0;
    int colorNum = 0;
    TileColor tileColor{TileColor::Green};
    float timer = 0, delay = 0.3;

    int figureNumber = 0;
    FillField();
    a[0].y = 1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window.close();
                return;
            }

            if (e.type == Event::KeyPressed)
            {
                handleKeyPressed(e.key, dx, dy, rotate);
            }

            /*if (e.type == Event::MouseButtonPressed)
            {
                if(e.key.code == Mouse::Button::Left)
                    
            }*/
        }

        //// <- Move -> ///
        if (Keyboard::isKeyPressed(Keyboard::Down)
            || Keyboard::isKeyPressed(Keyboard::Up)
            || Keyboard::isKeyPressed(Keyboard::Left)
            || Keyboard::isKeyPressed(Keyboard::Right))
        {
            for (int i = 0;i < 4;i++)
            {
                b[i] = a[i];
                a[i].x += dx;
                a[i].y += dy;
            }
        }

        if (!check())
        {
            // moving a character back if he can't stand on prohibited place
            for (int i = 0;i < 4;i++)
                a[i] = b[i];
        }
        else
        {
            fillFieldTile(a[0]);
        }

        if (timer > delay)
        {
            refreshLightning(lightning, maxLightningPoint);
            timer = 0;
        }

        //////Rotate//////
        /*if (rotate)
        {
            Point p = a[1]; //center of rotation
            for (int i = 0;i < 4;i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }

            if (!check())
            {
                for (int i = 0;i < 4;i++)
                    a[i] = b[i];
            }
        }*/

        dx = 0; dy = 0; rotate = 0;

        /////////draw//////////
        window.clear(Color::White);
        //window.draw(background);

        static int rectLength = tileSize;// old tile size 18;

        for (int x = 0;x < landWidthInTiles;x++)
            for (int y = 0;y < landLengthInTiles;y++)
            {
                if (landRecognitionMask[y][x] == true)
                {
                    switch (landField[y][x])
                    {
                    case TileType::greenField:
                    {
                        landGreenField.setTextureRect(IntRect(0, 0, rectLength, rectLength));
                        landGreenField.setPosition(x * rectLength, y * rectLength);
                        landGreenField.move(tileSize, tileSize); //constant offset (border)
                        window.draw(landGreenField);
                    }
                    break;
                    case TileType::grass:
                    {
                        landGrass.setTextureRect(IntRect(0, 0, rectLength, rectLength));
                        landGrass.setPosition(x * rectLength, y * rectLength);
                        landGrass.move(tileSize, tileSize); //constant offset (border)
                        window.draw(landGrass);
                    }
                    break;
                    case TileType::lava:
                    {
                        lavaLand.setTextureRect(IntRect(0, 0, rectLength, rectLength));
                        lavaLand.setPosition(x * rectLength, y * rectLength);
                        lavaLand.move(tileSize, tileSize); //constant offset (border)
                        window.draw(lavaLand);
                    }
                    break;
                    }

                    if (landLootMap[y][x] != LootType::Empty)
                    {
                        scrolls.setTextureRect(IntRect(0, 0, 49, 49));
                        scrolls.setColor(Color(255, 255, 255, 250));
                        scrolls.setPosition(x * rectLength, y * rectLength);
                        scrolls.move(tileSize, tileSize);
                        window.draw(scrolls);
                    }
                }
                else
                {
                    land.setTextureRect(IntRect(0, 0, rectLength, rectLength));
                    land.setPosition(x * rectLength, y * rectLength);
                    land.move(tileSize, tileSize); // constant offset (border)
                    window.draw(land);
                }
            }

        //for (int i = 0;i < 4;i++)
        {
            character.setTextureRect(IntRect(colorNum * rectLength, 0, rectLength, rectLength));
            character.setPosition(a[0].x * rectLength, a[0].y * rectLength);
            character.move(tileSize, tileSize); //offset
            window.draw(character);
        }

        text.setString(lootCollected + std::to_string(a[0].loot));
        window.draw(this->text);
        window.draw(lightning);
        window.draw(str);

        //window.draw(frame);
        window.display();
    }
}
