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
inline const char* GPIO_UNEXPORT = "/sys/class/gpio/unexport";
inline const std::string GPIO_BASE(int pin) { return "/sys/class/gpio/gpio" + std::to_string(pin); }
inline const std::string GPIO_DIRECTION(int pin) { return GPIO_BASE(pin) + "/direction"; }
inline const std::string GPIO_EDGE(int pin) { return GPIO_BASE(pin) + "/edge"; }
inline const std::string GPIO_VALUE(int pin) { return GPIO_BASE(pin) + "/value"; }

int BCMPin;

char* DirectionToString(enum GPIO::Direction direction) {
	switch(direction) {
	  case GPIO::Direction::In:
		  return strdup("in");
	  default:
		  return strdup("out");
	}
}

char* EdgeToString(enum GPIO::Edge edge) {
	switch(edge) {
	  case GPIO::Edge::Rising:
		  return strdup("rising");
	  case GPIO::Edge::Falling:
		  return strdup("falling");
		case GPIO::Edge::Both:
		  return strdup("both");
	  default:
		  return strdup("none");
	}
} 

GPIO::GPIO(int bcm_pin) {
	BCMPin = bcm_pin;
}

bool GPIO::Init() {
	if(FileUtil::IsDir(GPIO_BASE(BCMPin))) {		
		return true;
	}
		
	FILE *fp = fopen(GPIO_EXPORT, "w");
	if(fp == NULL) {
		std::cout << "Init. Cannot open export file";

		return false;
	}
		
	fprintf(fp, "%d\n", BCMPin);
	fclose(fp);

	// gpio directories are initially owned by 'root'.  If you have
	// udev rules that change this, it may take a moment for those 
	// changes to happen.
	sleep(1);

	return true;
}

bool GPIO::Dispose() {
	if(!FileUtil::IsDir(GPIO_BASE(BCMPin))) {		
		return true;
	}
		
	FILE *fp = fopen(GPIO_UNEXPORT, "w");
	if(fp == NULL) {
		std::cout << "Dispose. Cannot open unexport file";

		return false;
	}
		
	fprintf(fp, "%d\n", BCMPin);
	fclose(fp);

	// gpio directories are initially owned by 'root'.  If you have
	// udev rules that change this, it may take a moment for those 
	// changes to happen.
	sleep(1);

	return true;
}

bool GPIO::SetDirection(enum Direction direction) {
	if(!FileUtil::IsDir(GPIO_BASE(BCMPin))) {
		std::cout << "SetDirection. No base dir";
		
		return false;
	}

	if(!FileUtil::IsFile(GPIO_DIRECTION(BCMPin))) {
		std::cout << "SetDirection. No direction file";
				
		return false;
	}

	FILE *fp = fopen(GPIO_DIRECTION(BCMPin).c_str(), "w");
	if(fp == NULL) {
		std::cout << "SetDirection. Cannot open direction file";
		
		return false;
	}

	fprintf(fp, "%s\n", DirectionToString(direction));
	fclose(fp);

	return true;
}

bool GPIO::SetEdge(enum Edge edge) {
	if(!FileUtil::IsDir(GPIO_BASE(BCMPin))) {
		std::cout << "SetEdge. No base dir";
		
		return false;
	}

	if(!FileUtil::IsFile(GPIO_EDGE(BCMPin))) {
		std::cout << "SetEdge. No edge file";
		
		return false;
	}
		
	FILE *fp = fopen(GPIO_EDGE(BCMPin).c_str(), "w");
	if(fp == NULL) {
		std::cout << "SetEdge. Cannot open edge file";
		
		return false;
	}

	fprintf(fp, "%s\n", EdgeToString(edge));
	fclose(fp);

	return true;
}

enum GPIO::Status GPIO::GetStatus() {
	if(!FileUtil::IsDir(GPIO_BASE(BCMPin))) {
		std::cout << "GetStatus. No base dir";
		
		return Status::Error;
	}

	if(!FileUtil::IsFile(GPIO_VALUE(BCMPin))) {
		std::cout << "GetStatus. No value file";
		
		return Status::Error;
	}
		
	FILE *fp = fopen(GPIO_VALUE(BCMPin).c_str(), "r");
	if(fp == NULL) {
		std::cout << "GetStatus. Cannot open value file";
		
		return Status::Error;
	}

	char valbuf[2];
	fread(valbuf, sizeof(valbuf), 1, fp);
	fclose(fp);

	return valbuf[0] == '1' ? Status::High : Status::Low;	
}
