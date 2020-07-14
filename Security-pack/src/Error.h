#pragma once
#include <iostream>


namespace Error {
	enum class Type {
		index,
		instantiate,
		database
	};

	void Write(std::string location, Type type);
}