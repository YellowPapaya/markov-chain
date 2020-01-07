#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <random>

class markovChain {
	private:
		std::unordered_map<std::string, std::vector<std::string> > chain;
		std::ifstream ifs;
		std::string file;
	public:
		markovChain(std::string fl) : file(fl) {}
	
		void makeMap() {
			std::vector<std::string> info;
			std::string input;
			std::vector<std::string> sVec;
	
			ifs.open(file);
			while (ifs >> input) info.push_back(input); // Placeholder vec for key search
	
			for (auto iter = info.begin(); iter != info.end(); ++iter) {
				if (*iter != "/END") { // Ignore /END
					if (chain.find(*iter) == chain.end()) { // If key not found
						sVec.clear(); // Clear sVec before using to insert
						sVec.push_back(*(iter+1));
						chain.insert(std::make_pair(*iter, sVec)); // This is still okay even if the word is followed by /END, because run() will terminate at /END
					}
					else chain[*iter].push_back(*(iter+1));
				}
			}
		}
	
		std::string run() {
			srand(time(NULL)); // Set the random seed
			long randIndex = std::rand()%chain["/BEGIN"].size(); // Choose random start
			std::string input = chain["/BEGIN"][randIndex]; // Get value from the random index
			std::string sentence = input;
			
			while (true) {
				randIndex = std::rand()%chain[input].size();
				input = chain[input][randIndex];
				
				if (input != "/END") { // To not append a "/END" at the end
					sentence += " " + input;
				} else break;
			}
			return sentence;
		}
	
		void printMap() {
			for (auto const& pair: chain) {
				std::cout << "{" << pair.first << ": ";
				for (auto &s: pair.second) std::cout << s << ", ";
				std::cout << "\b\b}\n";
			}
		}
};

int main() {
	std::cout << "File name? (Don't include extension) ";
	std::string userIn;
	std::cin >> userIn;
	markovChain sampleChain(userIn + ".txt");
	sampleChain.makeMap();

	while (true) {
		std::cin.clear();
		std::cin.ignore(99999,'\n');
		std::cin;
		std::cout << sampleChain.run() << '\n';
	}
}