#include <iostream>
#include <vector>
#include <thread>
#include <random>

// Thread run control variable
bool running = true;
// Pointer to an array of atomic variables
std::atomic<bool>* forks;
// Number of philosophers
int n_philosophers;

void philosopher(int id) {
	// Generate random eating and thinking time
	std::random_device rd;
	std::mt19937 gen(rd());
	// Drawing time from a to b (milliseconds)
	std::uniform_int_distribution<> dis(1000, 2000);

	while (running) {
		// Philosopher thinking
		int time = dis(gen);
		printf("Philosopher %d thinking\n", id);
		std::this_thread::sleep_for(std::chrono::milliseconds (time));

		// Philosopher try grab forks
		// Calculate id forks
		int left_fork = id-1;
		int right_fork = id % n_philosophers;

		// Fork with smaller id on the left
		if (left_fork > right_fork) {
			std::swap(left_fork, right_fork);
		}
//		printf("Philosopher %d take: %d and %d\n", id, left_fork, right_fork);

//		printf("Philosopher %d wait to take left fork\n", id);
		// Taking a fork with a smaller id
		bool expected = true;
		while (!forks[left_fork].compare_exchange_weak(expected, false)) {
			expected = true;
			std::this_thread::yield();  // Czekaj, aż widelec będzie dostępny
		}

//		printf("Philosopher %d wait to take right fork\n", id);
		// Taking a fork with a larger id
		expected = true;
		while (!forks[right_fork].compare_exchange_weak(expected, false)) {
			expected = true;
			std::this_thread::yield();  // Czekaj, aż widelec będzie dostępny
		}

		// Philosopher eats
		time = dis(gen);
		printf("Philosopher %d eats\n", id);
		std::this_thread::sleep_for(std::chrono::milliseconds(time));

		printf("Philosopher %d puts down fork\n", id);
		// The philosopher puts down the fork
		forks[right_fork].store(true);
		forks[left_fork].store(true);
	}
}

int main(int argc, char* argv[]) {
	// Loading the argument
	if (argc > 1) {
		// Checking if the number
		try {
			n_philosophers = std::stoi(argv[1]);
			if (n_philosophers < 2 || n_philosophers > 10000) {
				printf("Wrong number of philosophers (acceptable values: 2 - 10000)\n");
				return -1;
			}

		} catch (const std::exception& e) {
			printf("Unknown error: %s\n", e.what());
			return -1;
		}
	} else {
		std::cerr << "Usage: project1 <number_of_philosophers>\n";
		return -1;
	}

	printf("Create %d philosophers\n", n_philosophers);

	// Vector to store threads
	std::vector<std::thread> threads;

	// Stworzenie początkowych widelców dostępnych
	forks = new std::atomic<bool> [n_philosophers];
	for (int i = 0; i < n_philosophers; ++i) {
		forks[i] = true;
	}

	printf("Press enter to exit the program\n");

	// Create threads
	threads.reserve(n_philosophers);
	for (int i = 0; i < n_philosophers; ++i) {
		threads.emplace_back(philosopher, i+1);
	}

	// Wait until the user finishes the program
	std::cin.get();

	// Close threads
	running = false;

	// Waiting for threads to close
	printf("Waiting for threads to close\n");
	for (int i=0; i<threads.size();i++) {
		threads[i].join();
		printf("Thread %d close\n", i+1);
	}

	// Zwolnienie pamięci
	delete[] forks;

	return 0;
}