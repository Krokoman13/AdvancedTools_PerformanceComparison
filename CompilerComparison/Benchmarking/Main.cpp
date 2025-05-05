#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>  
#include <string>
#include <functional>
#include <filesystem>

//O(log n)
double OlogN(unsigned int n_a)
{
	volatile double total = 0;
	double n = n_a;

	while (n > 1)
	{
		for (double x = 0; x < 300000; x++)
		{
			double number = std::sin(n);
			number = std::cos(number);
			number = std::pow(number, 2);
			total += number;
			number = std::sqrt(number);
			number = std::acos(number);
			number = std::asin(number);
			total += number;
		}

		n /= 2;
	}

	return total;
}

//O(n)
double OofN(unsigned int n)
{
	volatile double total = 0;

	for (double i = 0; i < n; i++)
	{
		for (double x = 0; x < 200000; x++)
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
	}

	return total;
}

//O(n^2)
double ONsquared(const unsigned int n)
{
	volatile double total = 0;

	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < n; j++)
		{
			for (unsigned int x = 0; x < 40000; x++)
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
		}
	}

	return total;
}

void TestFunction(unsigned int n, const std::function<double(int)>& function, const std::string& name, unsigned int testCount = 1)
{
	std::vector<double> times;

	for (unsigned int i = 0; i < testCount; i++)
	{
		std::cout << "Test " << (i + 1) << ", " << name << ":";
		auto start = std::chrono::high_resolution_clock::now();
		std::cout << std::to_string(function(n));
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		times.push_back(elapsed.count());
		std::cout << " duration:" << elapsed.count() << "s\n";
	}

	std::cout << "\n";

	double totalTime = 0.0;
	for (double time : times)
	{
		totalTime += time;
	}
	double mean = totalTime / testCount;

	double totalDeviation = 0.0;
	for (double time : times)
	{
		totalDeviation += std::pow(time - mean, 2);
	}
	double standardDeviation = std::sqrt(totalDeviation / testCount);

	std::string elementCountString = std::to_string(n);

	std::cout << "Amount of numbers: " << elementCountString << "\n";
	std::cout << "Amount of test: " << testCount << "\n";
	std::cout << "Total time: " << totalTime << "s\n";
	std::cout << "Average time: " << mean << "s (" << mean - standardDeviation << "s / " << mean + standardDeviation << "s)\n";
	std::cout << "Standard deviation: " << standardDeviation << "s\n";
	std::cout << "Average per n: " << mean / n << "s (" << (mean - standardDeviation) / n << "s / " << (mean + standardDeviation) / n << "s)\n";
	std::cout << "\n";



	std::string folder = name;
	std::filesystem::create_directories(folder);

	std::string filename = folder + '/' + elementCountString + ".csv";
	std::vector<std::string> fileLines;

	std::ofstream file(filename);
	file << elementCountString << "\n";
	for (double time : times)
	{
		file << std::to_string(time) << '\n';
	}
}

int main()
{
	TestFunction(1, [](unsigned int n) { return OlogN(n); },		"O(log N)",		30);
	TestFunction(2, [](unsigned int n) { return OlogN(n); },		"O(log N)",		30);
	TestFunction(3, [](unsigned int n) { return OlogN(n); },		"O(log N)",		30);
	TestFunction(4, [](unsigned int n) { return OlogN(n); },		"O(log N)",		30);
	TestFunction(5, [](unsigned int n) { return OlogN(n); },		"O(log N)",		30);
	TestFunction(6, [](unsigned int n) { return OlogN(n); },		"O(log N)",		30);
	TestFunction(7, [](unsigned int n) { return OlogN(n); },		"O(log N)",		30);
	TestFunction(8, [](unsigned int n) { return OlogN(n); },		"O(log N)",		30);
	TestFunction(9, [](unsigned int n) { return OlogN(n); },		"O(log N)",		30);

	TestFunction(1, [](unsigned int n) { return OofN(n); },			"O(N)",			30);
	TestFunction(2, [](unsigned int n) { return OofN(n); },			"O(N)",			30);
	TestFunction(3, [](unsigned int n) { return OofN(n); },			"O(N)",			30);
	TestFunction(4, [](unsigned int n) { return OofN(n); },			"O(N)",			30);
	TestFunction(5, [](unsigned int n) { return OofN(n); },			"O(N)",			30);
	TestFunction(6, [](unsigned int n) { return OofN(n); },			"O(N)",			30);
	TestFunction(7, [](unsigned int n) { return OofN(n); },			"O(N)",			30);
	TestFunction(8, [](unsigned int n) { return OofN(n); },			"O(N)",			30);
	TestFunction(9, [](unsigned int n) { return OofN(n); },			"O(N)",			30);

	TestFunction(1, [](unsigned int n) { return ONsquared(n); },	"O(N^2)",		30);
	TestFunction(2, [](unsigned int n) { return ONsquared(n); },	"O(N^2)",		30);
	TestFunction(3, [](unsigned int n) { return ONsquared(n); },	"O(N^2)",		30);
	TestFunction(4, [](unsigned int n) { return ONsquared(n); },	"O(N^2)",		30);
	TestFunction(5, [](unsigned int n) { return ONsquared(n); },	"O(N^2)",		30);
	TestFunction(6, [](unsigned int n) { return ONsquared(n); },	"O(N^2)",		30);
	TestFunction(7, [](unsigned int n) { return ONsquared(n); },	"O(N^2)",		30);
	TestFunction(8, [](unsigned int n) { return ONsquared(n); },	"O(N^2)",		30);
	TestFunction(9, [](unsigned int n) { return ONsquared(n); },	"O(N^2)",		30);
	return 0;
}