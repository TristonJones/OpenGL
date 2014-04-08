#include "GLRenderer.h"

#define WIDTH 800
#define HEIGHT 600

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 2;

	GLRenderer Renderer(800, 600, "OpenGL Test", sf::Style::Default, settings);
	Renderer.Run();

	return 0;
}
