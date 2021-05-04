#include <iostream>
#include <fstream>
#include <iomanip>

bool readFile(std::ifstream& file, double** matrix, double* b, int N) {
	while (!file.eof()) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				file >> matrix[i][j];
			}
			file >> b[i];
		}
	}

	return true;
}

void printMatrix(double** matrix, double* b, int N) {
	std::cout.setf(std::ios::fixed);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << std::setprecision(3) << matrix[i][j] << '\t';
		}
		std::cout << std::setprecision(3) << b[i] << '\n';
	}
	std::cout << '\n';
}

void printArray(double* arr, int N) {
	std::cout.setf(std::ios::fixed);
	for (int i = 0; i < N; i++) {
		std::cout << "x" << i + 1 << " = " << std::setprecision(3) << arr[i] << '\n';
	}
}

double* TridiagonalMatrixAlgorithm(double** matrix, double* d, int N) {
	double* a = new double[N];
	double* b = new double[N];
	double* x = new double[N];
	double tmp, max;
	int idx;

	for (int i = 0; i < N; i++) {
		a[i] = 0;
		b[i] = 0;
	}

	// Коэффициенты для первой строки
	a[0] = -matrix[0][1] / matrix[0][0];
	b[0] = d[0] / matrix[0][0];

	// Прямой ход
	for (int i = 1; i < N - 1; i++) {
		tmp = matrix[i][i - 1] * a[i - 1] + matrix[i][i];
		a[i] = -matrix[i][i + 1] / tmp;
		b[i] = (d[i] - matrix[i][i - 1] * b[i - 1]) / tmp;
	}

	// Коэффициенты для последней строки
	a[N - 1] = 0;
	b[N - 1] = (d[N - 1] - matrix[N - 1][N - 2] * b[N - 2]) / (matrix[N - 1][N - 2] * a[N - 2] + matrix[N - 1][N - 1]);

	// Обратный ход
	for (int i = N - 1; i >= 0; i--) {
		x[i] = a[i] * x[i + 1] + b[i];
	}

	delete[] a;
	delete[] b;

	return x;
}

int main() {
	std::ifstream file("input.txt");
	if (!file) {
		std::cout << "File input.txt not found";
		return -1;
	}

	int N;
	file >> N;
	if (N < 1) {
		std::cout << "Error while reading input.txt. Invalid matrix dimension.";
		return -2;
	}

	double** matrix = new double* [N];
	for (int i = 0; i < N; i++) {
		matrix[i] = new double[N];
	}
	double* b = new double[N];
	double* x;

	readFile(file, matrix, b, N);

	std::cout << "Init matrix:\n";
	printMatrix(matrix, b, N);

	x = TridiagonalMatrixAlgorithm(matrix, b, N);

	std::cout << "Solve:\n";
	printArray(x, N);

	for (int i = 0; i < N; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] b;
	delete[] x;

	return 0;
}