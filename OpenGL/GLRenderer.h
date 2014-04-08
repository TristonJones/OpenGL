#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <iostream>
#include <string>
#include <vector>

#include "DataLoad.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")


class GLRenderer
{
public:
	GLRenderer(unsigned int width, unsigned int height, const char* title, int style);
	GLRenderer(unsigned int width, unsigned int height, const char* title, int style, sf::ContextSettings &settings);
	GLRenderer(const GLRenderer &other);
	GLRenderer& operator=(const GLRenderer&);

	~GLRenderer();
	
	//Draws and Updates
	void Run();

	bool Init();
	void Update(sf::Time &time);
	void Render(sf::Time &time);

	//Take in a console command
	bool Command(std::string cmd);

	std::vector<Object> objects;

	//Test Render
	void drawCube();

private:
	sf::Window window;
	sf::Clock clock;

};