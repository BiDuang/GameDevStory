#include "main.hpp"

void WriteStringToFile(FILE* f, const std::string& str)
{
	size_t len = str.length();
	fwrite(&len, sizeof(len), 1, f);
	fwrite(str.c_str(), len * sizeof(char), 1, f);
}

std::string ReadStringFromFile(FILE* f)
{
	size_t strlength = 0;
	fread(&strlength, sizeof(strlength), 1, f);

	std::string str;
	str.resize(strlength);
	fread(str.data(), strlength * sizeof(char), 1, f);

	return str;
}