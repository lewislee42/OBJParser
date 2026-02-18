#include <Utils.hpp>


std::string readFileIntoString(const std::string& filePath) {
	std::fstream file(filePath, std::ios::in);

	if (!file.is_open())
		throw FileNotOpened();

	std::string fileContents;
	std::string line;

	while (getline(file, line)) {
		fileContents += line + '\n';
	}

	file.close();

	return fileContents;
}

std::vector<std::string> readFileIntoVector(const std::string& filePath) {
	std::fstream file(filePath, std::ios::in);

	if (!file.is_open())
		throw FileNotOpened();

	std::vector<std::string> fileContents;
	std::string line;

	while (getline(file, line)) {
		fileContents.push_back(line);
		std::cout << "line: " << line << std::endl;
	}

	file.close();

	return fileContents;
}

// resizes the viewport to the new window width & height
void framebufferResizeCallback(GLFWwindow* window, int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
}


const char *FileNotOpened::what() const throw() {
	return "File could not be opened, this can be due to lack of permission or the file does not exist.";
}
