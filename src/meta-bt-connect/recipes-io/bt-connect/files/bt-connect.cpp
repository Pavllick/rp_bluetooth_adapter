#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "fileutil.h"
#include "gpio.h"

const int BUTTON_PIN = 4;
const char* SCRIPT_PATH = "/usr/bin/btn_click.sh";

bool RunScript() {
	if (!IsFile(SCRIPT_PATH)) {
		std::cout << "RunScript. No script file";
		
		return false;
	}

	pid_t pid;
	int status;
	
	if((pid = fork()) == 0) {
			int res = execl("/bin/sh", "sh", SCRIPT_PATH, (char*)NULL);
			if(res == -1) {
				exit(255);
			}
	}

	wait(&status);

	if(!WIFEXITED(status)) {
		std::cout << "RunScript. Execution error";
	}
	
	usleep(4000000);
	
	return true;
}

int main() {
	bool result = Init(BUTTON_PIN);
	if(!result) return -1;
	
	result = SetDirection(BUTTON_PIN, Direction::In);
	if(!result) return -1;
		
	result = SetEdge(BUTTON_PIN, Edge::Falling);
	if(!result) return -1;

	while(true) {
		auto status =  GetStatus(BUTTON_PIN);
		if(status == Status::Error) {
			return -1;
		}

		if(status == Status::Low) {
			if(!RunScript()) {
			 	return -1;
			}
		}

		usleep(5000);
	}

  return 0;
}
