#include "DataLoad.h"


bool DataLoad::Load(const char *path, std::vector<Object> &objects)
{
	//std::string objectName;
	std::vector<sf::Vector3f> faceV;
	std::vector<sf::Vector3f> faceU;
	std::vector<unsigned int> vertexI, uvI, normalI;
	std::vector<sf::Vector3f> verts;
	std::vector<sf::Vector2f> uvs;
	std::vector<sf::Vector3f> norms;

	const int lineLen = 256;

	Object o;

	FILE *file = fopen(path, "r");
	
	if(file == NULL)
	{
		std::cout << "Unable to load file: " << path << std::endl;
		return false;
	}

	while(1)
	{
		//Change to more than 256 later
		char line[lineLen];
		int res = fscanf(file, "%s", line);
		if(res == EOF)
			break;
		else
		{
			//Load Object Name
			if(strcmp(line, "o") == 0)
			{
				char n[128];
				fscanf(file, "%s", n); 
				o.name = n;
				std::cout << n << std::endl;
			}
			//Load Vertex
			if(strcmp(line, "v") == 0)
			{
				sf::Vector3f vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				verts.push_back(vertex);
			}
			//Load UV
			else if(strcmp(line, "vt") == 0)
			{
				sf::Vector2f uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				uvs.push_back(uv);
			}
			//Load Normal
			else if(strcmp(line, "vn") == 0)
			{
				sf::Vector3f normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				norms.push_back(normal);
			}
			//Load Face
			else if(strcmp(line, "f") == 0)
			{
				std::string test = line;
				unsigned int vIndex[3], uIndex[3], nIndex[3]; 
				if(test.find("//") != NULL)
				{
					//Read and store the indecies for the face data
					int n = fscanf(file, "%d//%d %d//%d %d//%d\n", 
						&vIndex[0], &nIndex[0], 
						&vIndex[1], &nIndex[1], 
						&vIndex[2], &nIndex[2]);

					vertexI.push_back(vIndex[0]);
					vertexI.push_back(vIndex[1]);
					vertexI.push_back(vIndex[2]);
					normalI.push_back(nIndex[0]);
					normalI.push_back(nIndex[1]);
					normalI.push_back(nIndex[2]);
				}
				else
				{
					int n = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
						&vIndex[0], &uIndex[0], &nIndex[0],
						&vIndex[1], &uIndex[1], &nIndex[1], 
						&vIndex[2], &uIndex[2], &nIndex[2]);
					uvI.push_back(uIndex[0]);
					uvI.push_back(uIndex[1]);
					uvI.push_back(uIndex[2]);
					vertexI.push_back(vIndex[0]);
					vertexI.push_back(vIndex[1]);
					vertexI.push_back(vIndex[2]);
					normalI.push_back(nIndex[0]);
					normalI.push_back(nIndex[1]);
					normalI.push_back(nIndex[2]);
				}
			}
		}
	}
	for(unsigned int i = 0; i < vertexI.size(); i++)
	{
		sf::Vector3f vertex = verts[vertexI[i]-1];
		o.verticies.push_back(vertex);
		
	}
	for(unsigned int i = 0; i < uvI.size(); i++)
	{
		sf::Vector2f uv = uvs[uvI[i]-1];
		o.uvs.push_back(uv);
	}
	for(unsigned int i = 0; i < normalI.size(); i++)
	{
		sf::Vector3f normal = norms[normalI[i]-1];
		o.normals.push_back(normal);
	}
	o.position.x = 0.0f;
	o.position.y = 0.0f;
	o.position.z = 0.0f;

	objects.push_back(o);

	std::cout << "Load Sucessful" << std::endl;
	return true;
}