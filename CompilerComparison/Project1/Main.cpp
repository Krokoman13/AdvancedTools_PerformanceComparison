#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>  
#include <string>

double OofN(unsigned int n)
{
	double total = 0;

	for (double i = 0; i < n; i++)
	{
		double number = std::sin(i);
		number = std::cos(number);
		number = std::pow(number, 2);
		total += number;
		number = std::sqrt(number);
		number = std::acos(number);
		number = std::asin(number);
		total += number;
	}

	return total;
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	std::cout << std::to_string(OofN(100000));
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;

	std::cout << "\nElapsed time: " << elapsed.count() << " seconds\n";
	return 0;
}