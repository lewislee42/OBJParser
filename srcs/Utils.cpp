#include <Utils.hpp>


std::string readFileIntoString(const std::string& filepath) {
	std::fstream file(filepath, std::ios::in);

	if (!file.is_open())
		throw FileNotOpened(filepath);

	std::string fileContents;
	std::string line;

	while (getline(file, line)) {
		fileContents += line + '\n';
	}

	file.close();

	return fileContents;
}

std::vector<std::string> readFileIntoVector(const std::string& filepath) {
	std::vector<std::string> fileContents;
	std::string line;
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		file.open(filepath);

		while (getline(file, line)) {
			fileContents.push_back(line);
		}

		file.close();
	} catch (std::ifstream::failure e) {
		throw FileNotOpened(filepath);
	}

	return fileContents;
}

// resizes the viewport to the new window width & height
void framebufferResizeCallback(GLFWwindow* window, int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
}


FileNotOpened::FileNotOpened(const std::string& filepath):
	std::runtime_error("Could not open file: " + filepath) {
}
