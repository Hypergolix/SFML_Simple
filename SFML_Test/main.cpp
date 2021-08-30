#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// Movement stuff here
/*
void moveBall(int xVelocity, int yVelocity) {
    // Update position of sprite

}
*/

// change velocity to acceleration?

int main()
{
    float const ballSize = 20.f;
    float const groundPlane = 600.f - (ballSize * 2);
    // Ball Position
    float xPos = 10.f;
    float yPos = 50.f;
    // Ball Velocity
    float xVelocity = 0.f;
    float yVelocity = 0.f;
    
    RenderWindow window(VideoMode(800, 600), "Bouncy Ball");
    Texture texture;
    if (!texture.loadFromFile("Textures/rock_texture.jpg")) { 
        // Error loading texture
    }
    texture.setSmooth(true);
    CircleShape circle(ballSize);

    // Create sprite
    Sprite sprite;
    circle.setTexture(&texture);
    
    // Sprite position in float - initial
    circle.setPosition(Vector2f(xPos, yPos));

    // Start clock
    Clock clock;

    while (window.isOpen())
    {
        // Outside "frame" - should it be?
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && yPos == groundPlane)
        {
            yVelocity = -24.f;
            cout << "SPACE PRESSED";
            // Wait until yPos == 0 OR yPos?
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            xPos += 8.f;
            cout << "D PRESSED";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            xPos -= 8.f;
            cout << "A PRESSED";
        }

        // Reset clock - start of frame
        clock.restart();

        window.clear();
        // Move sprite
        if (yPos < (groundPlane - yVelocity)) {
            xVelocity += 0.f;
            // Rate at which ball falls
            yVelocity += 1.f;
        }
        else {
            //yVelocity -= 1.f;
            yVelocity = 0.f;
        }

        // Slight overshoot
        xPos += xVelocity;
        yPos += yVelocity;

        cout << "yVelocity: " << yVelocity;
        cout << "yPos: " << yPos << "\n";

        // Move the actual graphics
        circle.setPosition(Vector2f(xPos, yPos));
        // Draw everything in the frame
        window.draw(circle);
        // 
        window.display();
        // Delay? how would interrupts/keystrokes work - sfml or Windows. 16ms frametime 
        Time frameTime = milliseconds(16);
        Time time = clock.getElapsedTime();

        while (clock.getElapsedTime() < milliseconds(16)) {
            // Kill remaining time NOPs? 
            // If frametime exceeded should result in lower framerate
        }
        // Next frame
        // frameTime += 16;
        // Update/Modify x/y velocity "gravity"
    }
    
    return 0;
}