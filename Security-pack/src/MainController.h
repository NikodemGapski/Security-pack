#pragma once

class MainController {
private:
	static bool isLoggedIn;
	static void setLoggedIn(bool isLogged);
public:
	static void Run(); // runs the whole program
	static bool getLoggedIn();
};
