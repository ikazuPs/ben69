#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <process.h>
#include <windows.h>
#include <vector>
#include <time.h>
#include <cstdlib>

using namespace std;


std::string form = "ben.png";
sf::RenderWindow app(sf::VideoMode(800, 600), "Ben 69");
float benX = 400.0f, benY = 513.0f;
bool canjump = true;
bool transformed = false;
float enemyX[]{};
float enemyY[]{};
int enemycount = 0;
bool shooting = false;
bool one = true;

void spawnEnemy()
{
    srand(time(0));
    sf::Texture texture;
    texture.loadFromFile("enemy.png");
    if(one == true)
    {
        one = false;
        for(int i = 0; i < 1; i++)
        {
            enemyX[i] = 100+(rand() % 300);
            enemyY[i] = 513;
        }
    }
    for(int i = 0; i < 1; i++)
    {
        sf::Sprite enemy(texture);
        enemy.setPosition(enemyX[i], enemyY[i]);
        app.draw(enemy);
    }
    int pick = rand() % 2;
    if(pick == 1)
    {
        enemyX[0] -= 0.5;
    }else{
        enemyX[0] += 0.5;
    }
}

void loadAlien(std::string name)
{
    if(name == "redguy")
    {
        form = "redguy.png";
        return;
    }
}
float bulX = benX, bulY = benY;
void Bullet()
{
    if(bulX >= 735)
    {
        shooting = false;
        bulX = benX;
        std::cout << "hit" << std::endl;
    }
    bulX += 1;
    sf::Texture texture;
    texture.loadFromFile("bullet.png");
    sf::Sprite bullet(texture);
    bullet.setPosition(bulX, bulY);
    app.draw(bullet);
}

void loadDirt()
{
    sf::Texture texture;
    texture.loadFromFile("dirt.png");
    for(int i = 0; i < 50 *15; i += 50)
    {
        sf::Sprite dirt(texture);
        dirt.setPosition(0 + i, 500);
        app.draw(dirt);
    }
}


void loadPlayer()
{
    sf::Texture ben2;
    ben2.loadFromFile(form);
    sf::Sprite ben(ben2);
    ben.setPosition(benX, benY);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        if(!transformed)
        {
            transformed = true;
             loadAlien("redguy");
             benY -= 20;
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        ben.setPosition(benX + 0.5f, benY);
        benX += 0.5f;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        benX -= 0.5f;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        shooting = true;
    }
    /*else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if(canjump)benY -= 69.0f;
        canjump = false;
    }*/
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        std::cout << "X :  | " << benX << " Y : " << benY << std::endl;
    }
    app.draw(ben);
}
int main()
{
    // Create the main window
    // Load a sprite to display

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();
        if(shooting)
        {
            Bullet();
        }
        loadPlayer();
        loadDirt();
        spawnEnemy();
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
