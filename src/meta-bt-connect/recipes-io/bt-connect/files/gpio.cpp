#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <stdbool.h>
#include <iostream>

#include "gpio.h"
#include "fileutil.h"

inline const char* GPIO_EXPORT = "/sys/class/gpio/export";
inline const std::string GPIO_BASE(int pin) { return "/sys/class/gpio/gpio" + std::to_string(pin); }
inline const std::string GPIO_DIRECTION(int pin) { return GPIO_BASE(pin) + "/direction"; }
inline const std::string GPIO_EDGE(int pin) { return GPIO_BASE(pin) + "/edge"; }
inline const std::string GPIO_VALUE(int pin) { return GPIO_BASE(pin) + "/value"; }


char* DirectionToString(enum Direction direction) {
	switch(direction) {
	  case Direction::In:
		  return strdup("in");
	  default:
		  return strdup("out");
	}
}

char* EdgeToString(enum Edge edge) {
	switch(edge) {
	  case Edge::Rising:
		  return strdup("rising");
	  case Edge::Falling:
		  return strdup("falling");
		case Edge::Both:
		  return strdup("both");
	  default:
		  return strdup("none");
	}
} 

bool Init(int pin) {
	if(IsDir(GPIO_BASE(pin))) {		
		return true;
	}
		
	FILE *fp = fopen(GPIO_EXPORT, "w");
	if(fp == NULL) {
		std::cout << "Init. Cannot open export file";

		return false;
	}
		
	fprintf(fp, "%d\n", pin);
	fclose(fp);

	// gpio directories are initially owned by 'root'.  If you have
	// udev rules that change this, it may take a moment for those 
	// changes to happen.
	sleep(1);

	return true;
}

bool SetDirection(int pin, enum Direction direction) {
	if(!IsDir(GPIO_BASE(pin))) {
		std::cout << "SetDirection. No base dir";
		
		return false;
	}

	if(!IsFile(GPIO_DIRECTION(pin))) {
		std::cout << "SetDirection. No direction file";
				
		return false;
	}

	FILE *fp = fopen(GPIO_DIRECTION(pin).c_str(), "w");
	if(fp == NULL) {
		std::cout << "SetDirection. Cannot open direction file";
		
		return false;
	}

	fprintf(fp, "%s\n", DirectionToString(direction));
	fclose(fp);

	return true;
}

bool SetEdge(int pin, enum Edge edge) {
	if(!IsDir(GPIO_BASE(pin))) {
		std::cout << "SetEdge. No base dir";
		
		return false;
	}

	if(!IsFile(GPIO_EDGE(pin))) {
		std::cout << "SetEdge. No edge file";
		
		return false;
	}
		
	FILE *fp = fopen(GPIO_EDGE(pin).c_str(), "w");
	if(fp == NULL) {
		std::cout << "SetEdge. Cannot open edge file";
		
		return false;
	}

	fprintf(fp, "%s\n", EdgeToString(edge));
	fclose(fp);

	return true;
}

enum Status GetStatus(int pin) {
	if(!IsDir(GPIO_BASE(pin))) {
		std::cout << "GetStatus. No base dir";
		
		return Status::Error;
	}

	if(!IsFile(GPIO_VALUE(pin))) {
		std::cout << "GetStatus. No value file";
		
		return Status::Error;
	}
		
	FILE *fp = fopen(GPIO_VALUE(pin).c_str(), "r");
	if(fp == NULL) {
		std::cout << "GetStatus. Cannot open value file";
		
		return Status::Error;
	}

	char valbuf[2];
	fread(valbuf, sizeof(valbuf), 1, fp);
	fclose(fp);

	return valbuf[0] == '1' ? Status::High : Status::Low;	
}
