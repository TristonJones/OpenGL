#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <iostream>
#include <string>
#include <vector>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

struct Object
{
	std::string name;

	std::vector<sf::Vector3f> verticies;
	std::vector<sf::Vector2f> uvs;
	std::vector<sf::Vector3f> normals;

	sf::Vector3f position;
};

namespace DataLoad
{
	//Load a 3d model
	bool Load(const char *path, std::vector<Object> &objects);
};


