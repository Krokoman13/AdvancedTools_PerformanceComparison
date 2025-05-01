#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>  
#include <string>
#include <functional>

double OofN(unsigned int n)
{
	volatile double total = 0;

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

	unsigned int nDigits = 0;
	{
		unsigned int nCopy = n;
		while (nCopy % 10 == 0)
		{
			nCopy /= 10;
			nDigits++;
		}
	}

	unsigned int base = n / std::pow(10, nDigits);
	std::string elementCountString = std::to_string(base) + "x10^" + std::to_string(nDigits);

	std::cout << "Amount of numbers: " << elementCountString << "\n";
	std::cout << "Amount of test: " << testCount << "\n";
	std::cout << "Total time: " << totalTime << "s\n";
	std::cout << "Average time: " << mean << "s (" << mean - standardDeviation << "s / " << mean + standardDeviation << "s)\n";
	std::cout << "Standard deviation: " << standardDeviation << "s\n";
	std::cout << "Average per n: " << mean / n << "s (" << (mean - standardDeviation) / n << "s / " << (mean + standardDeviation) / n << "s)\n";
	std::cout << "\n";

	std::string filename = name + elementCountString + ".csv";
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
	TestFunction(100000, [](unsigned int n) { return OofN(n); }, "OofN", 30);
	TestFunction(200000, [](unsigned int n) { return OofN(n); }, "OofN", 30);
	TestFunction(300000, [](unsigned int n) { return OofN(n); }, "OofN", 30);
	TestFunction(400000, [](unsigned int n) { return OofN(n); }, "OofN", 30);
	TestFunction(500000, [](unsigned int n) { return OofN(n); }, "OofN", 30);
	TestFunction(600000, [](unsigned int n) { return OofN(n); }, "OofN", 30);
	TestFunction(700000, [](unsigned int n) { return OofN(n); }, "OofN", 30);
	TestFunction(800000, [](unsigned int n) { return OofN(n); }, "OofN", 30);
	TestFunction(900000, [](unsigned int n) { return OofN(n); }, "OofN", 30);
	TestFunction(1000000, [](unsigned int n) { return OofN(n); }, "OofN", 30);
	return 0;
}