#include "../include/utils.h"

int converter::string_to_int(std::string str)
{
	try {
		return std::stoi(str);
	}
	catch (const std::exception& e) {
		return 0;
	}
}