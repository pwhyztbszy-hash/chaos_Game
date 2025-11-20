// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    // Load font
    Font font;
    if (!font.loadFromFile("fonts/Roboto-Italic.ttf"))
    {
        cout << "ERROR: Could not load fonts/Roboto-Italic.ttf" << endl;
        return 1;
    }

    // Instructions text
    Text instructions;
    instructions.setFont(font);
    instructions.setCharacterSize(24);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(10, 10);
    instructions.setString("Click 3 points to place triangle vertices");

    // Store triangle vertices and chaos points
    vector<Vector2f> vertices;
    vector<Vector2f> points;

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the player's input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << "the left button was pressed" << std::endl;
                    cout << "mouse x: " << event.mouseButton.x << std::endl;
                    cout << "mouse y: " << event.mouseButton.y << std::endl;

                    // FIRST 3 CLICKS → TRIANGLE VERTICES
                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));

                        if (vertices.size() == 3)
                        {
                            instructions.setString("Click a 4th point to start Chaos Game");
                        }
                    }
                    // 4TH CLICK → STARTING POINT
                    else if(points.size() == 0)
                    {
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        instructions.setString("Generating fractal...");
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Update (Chaos Game Algorithm)
        ****************************************
        */
        if(points.size() > 0)
        {
            // Generate 100 points each frame (faster fractal)
            for (int i = 0; i < 100; i++)
            {
                int r = rand() % 3;  // pick random vertex
                Vector2f last = points.back(); // last generated point
                Vector2f v = vertices[r];      // chosen vertex
                Vector2f mid(
                    (last.x + v.x) / 2,
                    (last.y + v.y) / 2
                );
                points.push_back(mid);         // store new point
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        // Draw instructions
        window.draw(instructions);

        // Draw the 3 triangle vertices
        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(vertices[i]);
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        // Draw all chaos points
        for(int i = 0; i < points.size(); i++)
        {
            RectangleShape dot(Vector2f(2, 2));
            dot.setPosition(points[i]);
            dot.setFillColor(Color::White);
            window.draw(dot);
        }

        window.display();
    }
}
