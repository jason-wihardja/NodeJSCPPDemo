#include "prime_algorithm.hpp"

vector<int> PrimeAlgorithm::GeneratePrime(int number) {
	vector<int> primeNumbers;
	PrimeAlgorithm::GeneratePrime(primeNumbers, number);
	return primeNumbers;
}

void PrimeAlgorithm::GeneratePrime(vector<int>& destination, int number) {
	for (int i = 2; i <= number; i++) {
		bool isPrime = true;
		for (int j = 2; j < i; j++) {
			if (i % j == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) {
			destination.push_back(i);
		}
	}
}