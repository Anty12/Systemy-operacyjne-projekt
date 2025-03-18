#include <iostream>
#include <vector>
#include <thread>
#include <random>

bool running = true;

void philosopher(int id) {
	// Generate random eating and thinking time
	std::random_device rd;
	std::mt19937 gen(rd());
	// Drawing time from a to b (seconds)
	std::uniform_int_distribution<> dis(3, 6);

	while (running) {
		// Philosopher thinking
		int time = dis(gen);
		printf("Philosopher %d thinking\n", id);
		std::this_thread::sleep_for(std::chrono::seconds(time));

		// Philosopher try grab forks

		// Philosopher eats
		time = dis(gen);
		printf("Philosopher %d eats\n", id);
		std::this_thread::sleep_for(std::chrono::seconds(time));
	}
}

int main(int argc, char* argv[]) {
	int n_philosophers;
	// Loading the argument
	if (argc > 1) {
		// Checking if the number
		try {
			n_philosophers = std::stoi(argv[1]);
			if (n_philosophers < 1 || n_philosophers > 10000) {
				printf("Wrong number of philosophers (acceptable values: 1 - 10000)\n");
				return -1;
			}

		} catch (const std::exception& e) {
			printf("Unknown error: %s\n", e.what());
			return -1;
		}
	} else {
		printf("The number of philosophers is not given\n");
		return -1;
	}

	// Vector to store threads
	std::vector<std::thread> threads;

	// Create threads
	threads.reserve(n_philosophers);
	for (int i = 0; i < n_philosophers; ++i) {
		threads.emplace_back(philosopher, i + 1);
	}

	// Wait until the user finishes the program
	printf("Press enter to exit the program\n");
	std::cin.get();

	// Close threads
	running = false;

	// Waiting for threads to close
	printf("Waiting for threads to close\n");
	for (int i=0; i<threads.size();i++) {
		threads[i].join();
		printf("Thread %d close\n", i+1);
	}

	return 0;
}