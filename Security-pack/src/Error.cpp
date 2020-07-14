#include <iostream>
#include "Error.h"

namespace Error {
	void Write(std::string location, Type type) {
		std::cout << "Error(" << location << "): ";
		if (type == Type::index) {
			std::cout << "index out of boundaries";
		}
		else if (type == Type::instantiate) {
			std::cout << "cannot create an object";
		}
		else if (type == Type::database) {
			std::cout << "cannot access the database";
		}
		std::cout << std::endl;
		system("pause");
		std::cout << std::endl;
	}
}