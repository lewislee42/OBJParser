#include <Image.hpp>

// PPM image parser

Image::Image(const std::string& filepath) {
	// lines
	// first type of parsing either P3 or P6
	// 		P3 is using the characters
	// 		P6 is using the binary value
	// second width height
	// max value for the pixels
	// Rest are all the pixel values
	std::ifstream file(filepath, std::ios::binary);
	if (!file.is_open())
		throw ImageCouldNotOpenFile(filepath);

	type		= readNextToken(file);
	width		= std::stoi(readNextToken(file));
	height		= std::stoi(readNextToken(file));
	maxPixelVal	= std::stoi(readNextToken(file));

	if (maxPixelVal > 255)
		throw ImageCorrupted("Found max pixel value bigger than 255.");

	// use this to get rid of the \n
	file.get();

	pixels.resize(width * height * 3);
	if (type == "P3") {
		for (size_t i = 0; i < pixels.size(); i++) {
			int val;
			file >> val;
			if (!file)
				throw ImageCorrupted("Unexpected end of P3 file.");
			pixels[i] = static_cast<unsigned char>(val);
		}
	} else if (type == "P6") {
		file.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
		if (file.gcount() != static_cast<std::streamsize>(pixels.size()))
			throw ImageCorrupted("Unexpected end of P6 file.");
	} else {
		throw ImageCorrupted("Type \"" + type + "\" not supported.");
	}

	file.close();
}

Image::~Image() {

}

void Image::clearImageData() {
	pixels.clear();
	pixels.shrink_to_fit();
}

std::string Image::readNextToken(std::ifstream& file) {
	std::string token;
	while (true) {
		file >> token;
		if (token.empty())
			continue;
		if (token[0] == '#') {
			std::getline(file, token);
			continue;
		}
		break;
	}
	return token;
}


Image::ImageCouldNotOpenFile::ImageCouldNotOpenFile(const std::string& filepath):
	std::runtime_error("Image could not be loaded: " + filepath) {
}

Image::ImageCorrupted::ImageCorrupted(const std::string& cause):
	std::runtime_error("Image failed to be processed. Cause: " + cause) {
}
