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

    // Load font for instructions text
    Font font;
    if (!font.loadFromFile("fonts/Roboto-Italic.ttf"))
    {
        cout << "ERROR: Could not load fonts/Roboto-Italic.ttf" << endl;
        return 1;
    }

    // Setup instruction message
    Text instructions;
    instructions.setFont(font);
    instructions.setCharacterSize(35);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(10, 10);
    instructions.setString("Click 3 points to place triangle vertices");

    // Vectors to store triangle vertices and Chaos Game points
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
            // Close the window
            if (event.type == Event::Closed)
            {
                window.close();
            }

            // Handle left mouse clicks
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                float mx = event.mouseButton.x;
                float my = event.mouseButton.y;

                cout << "Left click at: " << mx << ", " << my << endl;

                // First 3 clicks → triangle vertices
                if (vertices.size() < 3)
                {
                    vertices.push_back(Vector2f(mx, my));

                    if (vertices.size() == 3)
                        instructions.setString("Click a 4th point to start Chaos Game");
                }
                // 4th click → starting point for Chaos Game
                else if (points.size() == 0)
                {
                    points.push_back(Vector2f(mx, my));
                    instructions.setString("Generating fractal...");
                }
            }
        }

        // ESC key closes program
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Update (Chaos Game Algorithm)
        ****************************************
        */
        if (points.size() > 0)
        {
            // Generate 100 Chaos Game points per frame
            for (int i = 0; i < 100; i++)
            {
                int r = rand() % 3; // pick 0, 1, or 2 (a vertex)

                Vector2f last = points.back();  // last chaos point
                Vector2f v = vertices[r];       // chosen vertex

                // Midpoint formula
                Vector2f mid(
                    (last.x + v.x) / 2,
                    (last.y + v.y) / 2
                );

                // Save the new point
                points.push_back(mid);
            }
        }

        /*
        ****************************************
        Draw everything
        ****************************************
        */
        window.clear();

        // Draw instruction text
        window.draw(instructions);

        // Draw triangle vertices
        for (auto &v : vertices)
        {
            RectangleShape vertexDot(Vector2f(10, 10));
            vertexDot.setPosition(v);
            vertexDot.setFillColor(Color::Blue);
            window.draw(vertexDot);
        }

        // Draw all Chaos Game points
        for (auto &p : points)
        {
            RectangleShape dot(Vector2f(2, 2));
            dot.setPosition(p);
            dot.setFillColor(Color::White);
            window.draw(dot);
        }

        window.display();
    }
}
