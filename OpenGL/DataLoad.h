#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

struct Face
{
	sf::Vector3i vIndices;
	sf::Vector3i vnIndices;
	sf::Vector3i vtIndices;
};

struct Color
{
	float r;
	float g;
	float b;
};

struct TexCoord
{
	float u;
	float v;
};

struct Material
{
	float Ka[3];
	float Kd[3];
	float Ks[3];
	float Ns;		//Specular Coefficient 
};

struct Object
{
	std::string name;

	std::vector<sf::Vector3f> vertices;
	std::vector<sf::Vector3f> normals;

	std::vector<TexCoord> texCoords;
	std::vector<Material> materials;
	std::vector<std::vector<Face>> faces;	//Each material contains a group of verticies

	std::vector<std::string> mtlFile;		//Stores material files

	sf::Vector3f position;



	void Draw();
};

namespace DataLoad
{
	namespace WaveFront
	{
		static Object tempObj;
		static char filePath[256];
		static int materialIndex;

		void parseLine(char *line);

		void parseVertex(char *line);
		void parseNormal(char *line);
		void parseFace(char *line);
		void parseMaterial(std::string line);

		int loadMaterials(char *filename);

		bool Load(const char *path, std::vector<Object> &objects);
	};
};


