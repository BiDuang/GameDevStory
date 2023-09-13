#include "main.hpp"

/**
* @brief Write string into file.
* 
* @param f The file to write.
* @param str The string to write.
* 
* @return `void`
*/
void WriteStringToFile(FILE* f, const std::string& str)
{
	size_t len = str.length();
	fwrite(&len, sizeof(len), 1, f);
	fwrite(str.c_str(), len * sizeof(char), 1, f);
}


/**
* @brief Read string from file.
* 
* @param f The file to read.
* 
* @return `std::string` The string read from the file.
*/
std::string ReadStringFromFile(FILE* f)
{
	size_t strlength = 0;
	fread(&strlength, sizeof(strlength), 1, f);

	std::string str;
	str.resize(strlength);
	fread(str.data(), strlength * sizeof(char), 1, f);

	return str;
}