#include "CommandCenter.h"

bool CommandCenter::ProcessCommand(std::string cmd, std::vector<Object> &objects)
{
	std::string com = cmd.substr(0, cmd.find(" "));
	if(com == "load")
	{
		return DataLoad::Load("C:/Users/Triston/Desktop/monkey.obj", objects);
	}
	if(com == "setpos")
	{
		int s = cmd.find(" ")+1;
		//Get the object
		std::string o = cmd.substr(s, cmd.find(" ", s)-s);
		//Get coordinates
		std::string c = cmd.substr(cmd.find(" ", s)+1, cmd.length()-cmd.find(" ", s));
		std::cout << c << std::endl;
		int fSpace = c.find(" ")+1;
		int sSpace = c.find(" ", fSpace)+1;
		std::string xs = c.substr(0, fSpace);
		std::string ys = c.substr(fSpace, sSpace-fSpace);
		std::string zs = c.substr(sSpace, c.length()-sSpace);
		std::cout << "X: " << xs << " Y: " << ys << " Z: " << zs << std::endl;
		int newX = atoi(xs.c_str());
		int newY = atoi(ys.c_str());
		int newZ = atoi(zs.c_str());

		//Find object
		for(int i = 0; i < objects.size(); i++)
		{
			if(objects[i].name == o)
			{
				//Set objects position
				objects[i].position = sf::Vector3f(newX, newY, newZ);
				break;
			}
		}
		return true;
	}
}