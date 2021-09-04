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
// change origin of ball to the bottom to avoid offsets?
// Lag when power not plugged in
// small bounce at start when ball drops initially 

// Add step distance 

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
	// Platform Position
	float xPos1 = 100.f;
	float yPos1 = 400.f;
	// Sprite Vector
	vector <Sprite> spriteV;

	RenderWindow window(VideoMode(800, 600), "Bouncy Ball");
	Texture texture;
	Texture texture1;
	if (!texture.loadFromFile("Textures/rock_texture.jpg")) {
		// Error loading texture
	}
	// Unsure if this is applied or the shape itself is low res
	texture.setSmooth(true);
	CircleShape circle(ballSize);

	// Create sprite
	circle.setTexture(&texture);

	// Sprite position in float - initial
	circle.setPosition(Vector2f(xPos, yPos));
	// Platforms
	/*
	if (!texture1.create(50, 100)) {

	}
	*/

	if (!texture1.loadFromFile("Textures/rock_texture.jpg", IntRect(50, 100, 150, 75))) {
		// Error loading texture
	}
	//IntRect platform(50, 100, 10, 10);
	Sprite platform;
	platform.setTexture(texture1);
	platform.setPosition(Vector2f(xPos1, yPos1));
	spriteV.push_back(platform);

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (yPos == groundPlane || yPos == (yPos1 - (ballSize*2))))
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
		// X collision - "teleport" or dont allow? - use less ifs 
		if (xPos < 0) {
			xPos = 0;
		}
		// "window width - ball width"
		if (xPos > 760) {
			xPos = 760;
		}
		// Pos +/- Velocity == predicted position
		// "hitboxes"
		if (yPos + yVelocity > (yPos1 - (ballSize * 2))) {
			if (xPos > (xPos1 - ballSize*2) && xPos < (xPos1 + (150 - (ballSize*2)))) {
				yVelocity = 0;
				yPos = yPos1 - (ballSize * 2);
			}
		}

		// Slight overshoot
		xPos += xVelocity;
		yPos += yVelocity;

		cout << "yVelocity: " << yVelocity;
		cout << "yPos: " << yPos << "\n";

		// Move the actual graphics
		circle.setPosition(Vector2f(xPos, yPos));
		// Draw everything in the frame
		for (int i = 0; i < spriteV.size(); i++) {
			window.draw(spriteV[i]);
		}
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