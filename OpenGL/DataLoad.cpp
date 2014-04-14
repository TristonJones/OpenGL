#include "DataLoad.h"


bool DataLoad::WaveFront::Load(const char *path, std::vector<Object> &objects)
{
	materialIndex = -1;

	std::fstream file;
	file.open(path);

	if(file.is_open())
	{
		char line[256];

		// Parse object file line by line
		while(file.good())
		{
			file.getline(line, 255);
			parseLine(line);
		}

		file.close();
	}
	else
	{
		std::cout << "Could not open WFObject file '" << path << "'\n";
		return false;
	}
	objects.push_back(tempObj);
	std::cout << "Object '" << tempObj.name << "' Created Sucessfully \n";
	return true;
}

void Object::Draw()
{
	for(int i = 0; i < faces.size(); i++)
	{
		//Apply material 
		glMaterialfv(GL_FRONT, GL_SPECULAR, materials[i].Ks);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[i].Kd);
		glMaterialfv(GL_FRONT, GL_AMBIENT, materials[i].Ka);
		glMaterialf(GL_FRONT, GL_SHININESS, materials[i].Ns);

		glBegin(GL_TRIANGLES);

		for(int j = 0; j < faces[i].size(); j++)
		{
			glNormal3f(normals[faces[i][j].vnIndices.x - 1].x, 
				normals[faces[i][j].vnIndices.x - 1].y,
				normals[faces[i][j].vnIndices.x - 1].z);
			glVertex3f(vertices[faces[i][j].vIndices.x - 1].x,
				vertices[faces[i][j].vIndices.x - 1].y,
				vertices[faces[i][j].vIndices.x - 1].z);

			glNormal3f(normals[faces[i][j].vnIndices.y - 1].x, 
				normals[faces[i][j].vnIndices.y - 1].y,
				normals[faces[i][j].vnIndices.y - 1].z);
			glVertex3f(vertices[faces[i][j].vIndices.y - 1].x,
				vertices[faces[i][j].vIndices.y - 1].y,
				vertices[faces[i][j].vIndices.y - 1].z);

			glNormal3f(normals[faces[i][j].vnIndices.z - 1].x, 
				normals[faces[i][j].vnIndices.z - 1].y,
				normals[faces[i][j].vnIndices.z - 1].z);
			glVertex3f(vertices[faces[i][j].vIndices.z - 1].x,
				vertices[faces[i][j].vIndices.z - 1].y,
				vertices[faces[i][j].vIndices.z - 1].z);
		}

		glEnd();
	}
}

void DataLoad::WaveFront::parseLine(char *line)
{
	if(!strlen(line))
	{
		return;
	}

	char *type;
	type = strtok(strdup(line), " ");

	if(!strcmp(type, "o"))
	{
		sscanf(line, "o %s", tempObj.name.c_str());
	}
	else if(!strcmp(type, "v"))
	{
		parseVertex(line);
	}
	else if(!strcmp(type, "vn"))
	{
		parseNormal(line);
	}
	else if(!strcmp(type, "f"))
	{
		parseFace(line);
	}
	else if(!strcmp(type, "mtllib"))
	{
		char file[256];
		sscanf(line, "mtllib %s", &file);

		if(strlen(file))
		{
			loadMaterials(file);
		}
		else
		{
			std::cout << "Parse Error: Invalid mtllib" << std::endl;
		}
	}
	else if(!strcmp(type, "usemtl"))
	{
		std::string name;
		materialIndex++;
		sscanf(line, "usemtl %s", name.c_str());

		parseMaterial(name.c_str());
		tempObj.faces.push_back(std::vector<Face>());
	}
	return;
}

void DataLoad::WaveFront::parseVertex(char *line)
{
	tempObj.vertices.push_back(sf::Vector3f());

	sscanf(line, "v %f %f %f", &tempObj.vertices.back().x, &tempObj.vertices.back().y, &tempObj.vertices.back().z);

	return;
}

void DataLoad::WaveFront::parseNormal(char *line)
{
	tempObj.normals.push_back(sf::Vector3f());

	sscanf(line, "vn %f %f %f", &tempObj.normals.back().x, &tempObj.normals.back().y, &tempObj.normals.back().z);

	return;
}

void DataLoad::WaveFront::parseFace(char *line)
{
	tempObj.faces[materialIndex].push_back(Face());

	if(sscanf(line, "f %d//%d %d//%d %d//%d", 
		&tempObj.faces[materialIndex].back().vIndices.x, &tempObj.faces[materialIndex].back().vnIndices.x,
		&tempObj.faces[materialIndex].back().vIndices.y, &tempObj.faces[materialIndex].back().vnIndices.y,
		&tempObj.faces[materialIndex].back().vIndices.z, &tempObj.faces[materialIndex].back().vnIndices.z) <= 1)
	{
		sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
			&tempObj.faces[materialIndex].back().vIndices.x,
			&tempObj.faces[materialIndex].back().vtIndices.x,
			&tempObj.faces[materialIndex].back().vnIndices.x,
			&tempObj.faces[materialIndex].back().vIndices.y,
			&tempObj.faces[materialIndex].back().vtIndices.y,
			&tempObj.faces[materialIndex].back().vnIndices.y,
			&tempObj.faces[materialIndex].back().vIndices.z,
			&tempObj.faces[materialIndex].back().vtIndices.z,
			&tempObj.faces[materialIndex].back().vnIndices.z);
	}

	return;
}

int DataLoad::WaveFront::loadMaterials(char *filename)
{
	std::fstream file;

	file.open(filename);
	if(file.is_open())
	{
		char line[256];
		while(file.getline(line, 256))
		{
			tempObj.mtlFile.push_back(line);
		}
	}
	else
	{
		std::cout << "Unable to open mtl file '" << filename << "'\n";
		return false;
	}

	file.close();
	return true;
}

void DataLoad::WaveFront::parseMaterial(std::string mtlName)
{
	std::string name;
	char *line = new char[256];
	bool mtlFound = false;

	for(int i = 0; i < tempObj.mtlFile.size(); i++)
	{
		strncpy(line, tempObj.mtlFile[i].c_str(), 256);

		if(strlen(line))
		{
			if(sscanf(line, "newmtl %s", name.c_str()))
			{
				if(mtlFound)
				{
					return;
				}

				if(!strcmp(mtlName.c_str(), name.c_str()))
				{
					mtlFound = true;
					tempObj.materials.push_back(Material());
				}
			}
			if(mtlFound)
			{
				if(line[0] == 'N' && line[1] == 's')
				{
					sscanf(line, "Ns %f", &tempObj.materials.back().Ns);
				}
				else if(line[0] == 'K' && line[1] == 'a')
				{
					sscanf(line, "Ka %f %f %f", 
						&tempObj.materials.back().Ka[0],
						&tempObj.materials.back().Ka[1],
						&tempObj.materials.back().Ka[2]);
				}
				else if(line[0] == 'K' && line[1] == 'd')
				{
					sscanf(line, "Kd %f %f %f",
						&tempObj.materials.back().Kd[0],
						&tempObj.materials.back().Kd[1],
						&tempObj.materials.back().Kd[2]);
				}
				else if(line[0] == 'K' && line[1] == 's')
				{
					sscanf(line, "Ks %f %f %f",
						&tempObj.materials.back().Ks[0],
						&tempObj.materials.back().Ks[1],
						&tempObj.materials.back().Ks[2]);
				}
			}
		}
	}

	return;
}