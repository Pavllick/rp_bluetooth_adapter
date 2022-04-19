#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "lib/fileutil.h"
#include "lib/gpio.h"

bool RunScript(char* script_path) {
	if (!FileUtil::IsFile(script_path)) {
		std::cout << "RunScript. No script file";
		
		return false;
	}

	pid_t pid;
	int status;
	
	if((pid = fork()) == 0) {
			int res = execl("/bin/sh", "sh", script_path, (char*)NULL);
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

void ExitFail(GPIO* gpio) {
	gpio->Dispose();

	std::cerr << "ExitFail. Something went wrong." << std::endl;

	exit(1);
}

int main(int argc, char** argv) {
	if(argc < 3) {
		std::cerr << "Usage: " << argv[0] << " BCM_PIN_NUMBER SCRIPT_PATH " << std::endl;
		
		return 1;
	}
	
	int bcm_pin_number = atoi(argv[1]);
	char* script_path = argv[2];
	
	auto gpio = new GPIO(bcm_pin_number);
	
	if(!gpio->Init()) {
		ExitFail(gpio);
	}
	
	if(!gpio->SetDirection(GPIO::Direction::In)) {
		ExitFail(gpio);
	}
		
	if(!gpio->SetEdge(GPIO::Edge::Falling)) {
		ExitFail(gpio);
	}

	while(true) {
		auto status =  gpio->GetStatus();
		if(status == GPIO::Status::Error) {
			ExitFail(gpio);
		}

		if(status == GPIO::Status::Low) {
			if(!RunScript(script_path)) {
				ExitFail(gpio);
			}
		}

		usleep(5000);
	}

  return 0;
}
