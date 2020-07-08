#pragma once
#include <iostream>


namespace Error {
	enum class Type {
		index
	};

	void Write(std::string location, Type type);
}