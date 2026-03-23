#pragma once

#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>

#include <Utils.hpp>

class Image {
private:
	std::string readNextToken(std::ifstream& file);

public:
	unsigned int				id;
	std::string					type;
	int 						width;
	int							height;
	int							maxPixelVal;
	std::vector<unsigned char>	pixels;

	Image(const std::string& filepath);
	~Image();

	void clearImageData();

	class ImageCouldNotOpenFile: public std::runtime_error {
	public:
		ImageCouldNotOpenFile(const std::string& filepath);
	};

	class ImageCorrupted: public std::runtime_error {
	public:
		ImageCorrupted(const std::string& cause);
	};
};

