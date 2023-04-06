/*
 * encode.cpp
 *
 *  Created on: 2021/10/13
 *      Author: luker
 */
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <cstddef>
#include <cstring>


int const max_size = 30528;
const char * extension = ".efbt";

int main(int argc, char **argv)
{

	//DETERMINE INPUT
	if(argc < 2) {
		std::cout << "No file passed." <<std::endl;
		system("PAUSE");
		return 10;
	}


	//SEPARATE STRING INTO PARTS
	std::string pathname = argv[1];
	std::string prefix = pathname.substr(0, pathname.find_last_of("\\") + 1);
	std::string fullName = pathname.substr(pathname.find_last_of("\\") + 1);
	std::string ext = fullName.substr(fullName.find_last_of("."));
	std::string name = fullName.substr(0, fullName.find_last_of("."));

	char buffer [max_size];
	char temp;
	FILE * fileId;
	FILE * outId;
	int red;

	char * filepath = new char[pathname.length()+1];
	char * aFile = new char[fullName.length()+6];

	if(ext == ".efbt") {
		fullName = name;
		std::cout << "DECODE" <<std::endl;
	}
	else {
		fullName = fullName + ".efbt";
		std::cout << "ENCODE" <<std::endl;
	}

	std::strcpy(filepath, pathname.c_str());
	std::strcpy(aFile, fullName.c_str());

	fileId = fopen (filepath, "rb");
	if(fileId == NULL){
		std::cout << "ERROR ON OPEN in";
		return 1;
	}

	outId = fopen (aFile, "wb");
	if(outId == NULL){
		std::cout << "ERROR ON OPEN out";
		return 2;
	}

	red = 0;

	while(! feof(fileId)) {
		red = fread(buffer, sizeof(char), max_size, fileId);
		if(red < max_size){
			for(int j = red; j < max_size; j++){
				buffer[j] = 0;
			}
		}

		for(int i = 0; i < red/2; i++) {
		   temp = buffer[i];
		   buffer[i] = buffer[red-i-1];
		   buffer[red-i-1] = temp;
		}

		fwrite(buffer, sizeof(char), red, outId);
	}
	fclose(outId);
	fclose(fileId);
	std::cout << "Type y to finish." << std::endl;
	std::string del;
	std::cin >> del;

	return 0;
}




