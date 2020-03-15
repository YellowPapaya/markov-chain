#include <unistd.h>
#include "markovChain.h"

int main() {
	std::string input;
	std::cout << "lol type" << std::endl;
	std::cin >> input;
	markovChain mc(input);
	mc.process();
	mc.makeMap(false);
	sleep(1);

	while (true) {
		std::string sentence;
		sentence = mc.run();
		std::cout << sentence << std::endl;
		sleep(1);
	}		
}
