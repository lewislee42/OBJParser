#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <MainScene.hpp>


int main(int argc, const char** argv) {
	std::cout << "Program Successfully Started." << std::endl;
	
	if (argc != 2) {
		std::cerr << "Error: invalid input, must provide the path to the .obj file." << std::endl;
		return 1;
	}

	MainScene mainScene;
	mainScene.loadModel(argv[1]);
	mainScene.run();

	std::cout << "Program Successfully Finished." << std::endl;
	return (0);
}
