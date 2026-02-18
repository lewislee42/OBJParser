#include <MainScene.hpp>
#include <map>

MainScene::MainScene() {
	std::cerr << "testing" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	// Creates GLFW window
	window = glfwCreateWindow(800, 600, "OBJ Parser", NULL, NULL);
	if (!window) {
		throw CouldNotCreateGLFWWindowException();
	}
	glfwMakeContextCurrent(window);

	// Loads OpenGL functions for us to use later
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw CouldNotLoadGLFunctionsException();
	}

	// Sets the callback function when the screen resizes
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

	// Create and link shader program
	shaderProgram = new ShaderProgram("./shaders/basic.vert", "./shaders/basic.frag");
}

MainScene::~MainScene() {
	glfwTerminate();
}


/* ---------- Methods ---------- */

void MainScene::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && qPressed == false)
		qPressed = true;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE && qPressed == true) {
		qPressed = false;
		isWireframe = (isWireframe ? false : true);
		if (isWireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}

void MainScene::loadModel(const char* modelPath) {
	std::string objPath(modelPath);

	if (objPath.find_last_of(".obj", objPath.length() - 4) == std::string::npos) {
		throw ModelFileNotCorrectFormatException();
	}

	std::vector<std::string> fileContent = readFileIntoVector(objPath);
	std::map<std::string, int> temp;

	// for (const auto i: fileContent) {
	// 	std::string keyChar = i.substr(0, i.find(" "));
	// 	if (temp.find(keyChar) != temp.end()) {
	// 		temp[keyChar]++;
	// 	} else  {
	// 		temp[keyChar] = 1;
	// 	}
	// }
	// for (const auto i: temp) {
	// 	std::cout << "Key: " << i.first << " = " << std::to_string(i.second) << std::endl;
	// }
	// int index = 0;
	// std::cout << "fileContent size: " << std::to_string(fileContent.size()) << std::endl;
	//
	// for (const auto& i: fileContent) {
	// 	if (i.empty())
	// 		continue;
	// 	std::cout << "line: " << std::to_string(index) << std::endl;
	// 	std::string currLine(i);
	//
	// 	currLine = currLine.substr(currLine.find(" ") + 1);
	// 	std::string v1 = currLine.substr(0, currLine.find(" "));
	// 	std::cout << "v1: " << v1 << std::endl;
	//
	// 	currLine = currLine.substr(currLine.find(" ") + 1);
	// 	std::string v2 = currLine.substr(0, currLine.find(" "));
	// 	std::cout << "v2: " << v2 << std::endl;
	//
	// 	currLine = currLine.substr(currLine.find(" ") + 1);
	// 	std::string v3 = currLine;
	// 	std::cout << "v3: " << v3 << std::endl;
	//
	//
	// 	std::string keyChar = i.substr(0, i.find(" "));
	// 	std::cout << "keyChar: " << keyChar << std::endl;
	//
	// 	if (keyChar == "v") {
	// 		vertices.push_back(std::stof(v1));
	// 		vertices.push_back(std::stof(v2));
	// 		vertices.push_back(std::stof(v3));
	// 	} else if (keyChar == "f") {
	// 		indices.push_back(std::stoi(v1));
	// 		indices.push_back(std::stoi(v2));
	// 		indices.push_back(std::stoi(v3));
	// 	}
	//
	// 	index++;
	// }
	// std::cout << "loop finished" << std::endl;
	
	vertices = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	indices = {
		0, 1, 3,
		1, 2, 3,
	};
}

void MainScene::run() {
	// Creates a Vertex Buffer Object that stores all the vertices

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// this binds the VBO to the id of 1
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// this creates the buffer with the type GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// this copies the elements from vertices into the VBO with static draw meaning the data would not change and would be read alot
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	// Copies the indices into the EBO 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// Process input here
		processInput();

		// Rendering commands here
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram->useProgram();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap display buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


/* ---------- EXCEPTIONS ---------- */

/* CouldNotCreateGLFWWindowException */
MainScene::CouldNotCreateGLFWWindowException::CouldNotCreateGLFWWindowException():
	std::runtime_error("Could not create GLFW window.") {
}

/* CouldNotLoadGLFunctionsException */
MainScene::CouldNotLoadGLFunctionsException::CouldNotLoadGLFunctionsException():
	std::runtime_error("Could not load GL functions using GLAD library.") {
}

MainScene::ModelFileNotCorrectFormatException::ModelFileNotCorrectFormatException():
	std::runtime_error("Model file is not expected \"obj\" file format.") {
}
