#include <iostream>
#include "Error.h"

namespace Error {
	void Write(std::string location, Type type) {
		std::cout << "Error(" << location << "): ";
		if (type == Type::index) {
			std::cout << "index out of boundaries";
		}
		system("pause");
		std::cout << std::endl;
	}
}