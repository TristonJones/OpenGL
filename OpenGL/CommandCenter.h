#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include <iostream>
#include <vector>
#include <string>
#include "DataLoad.h"

namespace CommandCenter{
	//Process all incoming commands
	bool ProcessCommand(std::string cmd, std::vector<Object> &objects);

	bool SetPos(int object, sf::Vector3f pos);
}

#endif //COMMANDCENTER_H