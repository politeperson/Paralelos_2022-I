#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <stdlib.h>

typedef std::vector<float> vf;
typedef std::vector<std::vector<float>> vvf;

std::random_device rd;  // Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

float getRandomFloat(float a, float b) {
	std::uniform_real_distribution<float> dis(a, b);
	// Use dis to transform the random unsigned int generated by gen into a 
	// double in [1, 2). Each call to dis(gen) generates a new random double
	return dis(gen);
}


vvf MatrixMult_1(vvf& A, vvf& B) {
	int R1 = A.size(), R2 = B.size(), C1 = A[0].size(), C2 = B[0].size();

	vvf C(R1, vf(C2, 0));

	for (int i = 0; i < R1; i++) {
		for (int j = 0; j < C2; j++) {
			for (int k = 0; k < R2; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}

		}
	}
	return C;
}

// solo acepta matrices cuadradas, es decir de dimensi?n: N x N, con N siendo par
vvf MatrixMult_2(vvf& A, vvf& B) {
	int N = A.size();
	int NB = 2; // n?mero de bloques en N, como son 2 partimos las filas y clomunas en 2, en total 4 sub matrices
	int b = N / NB; // b es el tama?o del bloque
	vvf C(N, vf(N, 0));

	for (int ii = 1; ii <= NB; ii++) {
		for (int jj = 1; jj <= NB; jj++) {
			for (int kk = 1; kk <= NB; kk++) {
				for (int i = (ii - 1) * b; i < ii * b; ++i) {
					for (int j = (jj - 1) * b; j < jj * b; ++j) {
						for (int k = (kk - 1) * b; k < kk * b; ++k) {
							C[i][j] += A[i][k] * B[k][j];
						}
					}
				}
			}

		}
	}
	return C;
}

void ShowMatrix(vvf& A) {
	int R = A.size(), C = A[0].size();
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			std::cout << " " << A[i][j];
		}
		std::cout << "\n";
	}
}


int main()
{
	vvf A;

	vvf B;

	int n;
	do {
		std::cout << "Inserte la dimensi?n de las matrices a generar, (solo NxN, con N siendo par): ";
		std::cin >> n;
	} while (n % 2);
	std::cout << "Valores de las matrices entre -1.0 a 1.0\n";
	std::cout << "Generando matrices A y B, espere...\n";
	for (int i = 0; i < n; ++i) {
		A.push_back(vf());
		B.push_back(vf());
		for (int j = 0; j < n; ++j) {
			A[i].push_back(getRandomFloat(-1.0, 1.0));
			B[i].push_back(getRandomFloat(-1.0, 1.0));
		}
	}

	// Mostrar solo cuando las matrices sean peque?as
	//ShowMatrix(A);
	//ShowMatrix(B);

	std::cout << "Ejecutando multiplicacion de matrices clasica...\n";
	auto started = std::chrono::high_resolution_clock::now();
	vvf rslt1 = MatrixMult_1(A, B);
	auto done = std::chrono::high_resolution_clock::now();
	std::cout << "Tiempo de ejecucion (ms): " << 
		std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << "\n\n";
	// solo mostrar si la matriz es peque?a
	// ShowMatrix(rslt1);

	std::cout << "Ejecutando multiplicacion de matrices por bloques...\n";
	started = std::chrono::high_resolution_clock::now();
	vvf rslt2 = MatrixMult_2(A, B);
	done = std::chrono::high_resolution_clock::now();
	std::cout << "Tiempo de ejecucion (ms): " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << "\n\n";
	// solo mostrar si la matriz es peque?a
	 //ShowMatrix(rslt2);

	return 0;
}