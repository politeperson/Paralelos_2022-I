#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <stdlib.h>
using namespace std;
#define MAX 10000

int ge_random_int(int a, int b) {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(a, b);

	return distrib(gen);
}


int main()
{
	vector<vector<double>> A(MAX, vector<double>(MAX, 0));
	vector<double> x(MAX, 0), y(MAX, 0);

	//double A[MAX][MAX], x[MAX], y[MAX];
	// initializing A, x and y with 0's
	/*for (int i = 0; i < MAX; ++i) {
		x[i] = y[i] = 0;
		for (int j = 0; j < MAX; ++j) {
			A[i][j] = 0;
		}
	}*/

	auto t_start = std::chrono::high_resolution_clock::now();

	// doing some calculations on the arrays
	// First way
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			y[i] += A[i][j] * x[j];
		}
	}
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	std::cout << "First way (ms): " << elapsed_time_ms << "\n";
	
	t_start = std::chrono::high_resolution_clock::now();
	// assigning y = 0
	for (int j = 0; j < MAX; ++j) {
		for (int i = 0; i < MAX; ++i) {
			y[i] += A[i][j] * x[j];
		}
	}
	t_end = std::chrono::high_resolution_clock::now();
	elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	std::cout << "Second way (ms): " << elapsed_time_ms << "\n";


	return 0;
}