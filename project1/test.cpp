#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

int main(int argc, char* argv[]) {
	// Read filename
	if (argc < 2) {
		std::cerr << "Usage: test <filename>\n";
		return 1;
	}

	// Check file
	std::ifstream file(argv[1]);
	if (!file.is_open()) {
		std::cerr << "Cannot open file\n";
		return 1;
	}
	printf("Open file: %s\n", argv[1]);

	std::string line;
	int num_philosophers = 0;
	std::regex create_regex("Create (\\d+) philosophers");
	std::regex eat_regex("Philosopher (\\d+) eats");
	std::regex down_fork_regex("Philosopher (\\d+) puts down fork");

	std::vector<bool> eating;
	int line_number = 0;

	while (std::getline(file, line)) {
		line_number++;
		std::smatch match;

		// Load number of philosopher
		if (std::regex_search(line, match, create_regex)) {
			num_philosophers = std::stoi(match[1]);
			eating.resize(num_philosophers, false);
			continue;
		}

		// Check philosopher eat
		if (std::regex_search(line, match, eat_regex)) {
			int id = std::stoi(match[1]) - 1;
			eating[id] = true;

			int left = (id - 1 + num_philosophers) % num_philosophers;
			int right = (id + 1) % num_philosophers;

			if (eating[left] || eating[right]) {
				printf("Error detected at line %d: philosopher %d", line_number, id + 1);
				if(eating[left] ) {
					printf(" and philosopher %d are eating!\n", left+1);
				} else {
					printf(" and philosopher %d are eating!\n", right+1);
				}
			}
		}

		// Check philosopher down fork
		if (std::regex_search(line, match, down_fork_regex)) {
			int id = std::stoi(match[1]) - 1;
			eating[id] = false;
		}
	}

	file.close();
	return 0;
}
