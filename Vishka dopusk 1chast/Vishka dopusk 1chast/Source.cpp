#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using mas = vector<vector<int>>;

//создание вектора
void creatMas(mas& array, int N) {
	array.resize(N);
	for (int i{}; i < N; ++i) {
		array[i].resize(N);
	}
}

//вывод векторов
void printMas(mas& array, int N) {
	for (int i{}; i < N; ++i) {
		cout << i << ": ";
		for (int j{}; j < N; ++j) {
			cout << array[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

int opredelitel(mas& array, int N) {
	return (array[0][0] * array[1][1] * array[2][2] + array[0][1] * array[1][2] * array[2][0] + array[0][2] * array[1][0] * array[2][1] - array[2][0] * array[1][1] * array[2][0] - array[0][0] * array[1][2] * array[2][1] - array[0][1] * array[1][0] * array[2][1]);
}

int main() {
	system("chcp 1251"); system("cls");
	int N{ 3 };
	vector<int> array(2*N + 1);
	mas A{}; creatMas(A, N);
	for (int i{}; i < N; ++i) {												//по строкам сверху 1
		for (int j{}; j < N; ++j) {
			for (int k{}; k < N; ++k) {
				for (int p{}; p < N; ++p) {
					if (A[k][p] != 1) {
						printMas(A, N);
						if (k == 0 && p > 0) --A[k][p - 1];					//0 строка после элем [0]
						else if (k > 0 && p == 0) --A[k - 1][N - 1];		//переход на след строку
						else if (k > 0 && p > 0) --A[k][p - 1];				//переход на след строку
						if (opredelitel(A, N)>=0) ++array[opredelitel(A, N)];
						else ++array[opredelitel(A, N)+2*N+1];
						++A[k][p];
					}
				}
			}
		}
	}
	for (int i{}; i < N; ++i) {												//по строкам сверху 0
		for (int j{}; j < N; ++j) {
			for (int k{}; k < N; ++k) {
				for (int p{}; p < N; ++p) {
					if (A[k][p] != 0) {
						printMas(A, N);
						if (k == 0 && p > 0) ++A[k][p - 1];					//0 строка после элем [0]
						else if (k > 0 && p == 0) ++A[k - 1][N - 1];		//переход на след строку
						else if (k > 0 && p > 0) ++A[k][p - 1];				//переход на след строку
						if (opredelitel(A, N) >= 0) ++array[opredelitel(A, N)];
						else ++array[opredelitel(A, N) + 2 * N + 1];
						--A[k][p];
					}
				}
			}
		}
	}

	for (int i{}; i < N; ++i) {												//по строкам снизу 1
		for (int j{}; j < N; ++j) {
			for (int k{}; k < N; ++k) {
				for (int p{}; p < N; ++p) {
					if (A[k][p] != 1) {
						printMas(A, N);
						if (k == 0 && p > 0) --A[k][p - 1];					//0 строка после элем [0]
						else if (k > 0 && p == 0) --A[k - 1][N - 1];		//переход на след строку
						else if (k > 0 && p > 0) --A[k][p - 1];				//переход на след строку
						if (opredelitel(A, N) >= 0) ++array[opredelitel(A, N)];
						else ++array[opredelitel(A, N) + 2 * N + 1];
						++A[k][p];
					}
				}
			}
		}
	}
	printMas(A, N);
		cout << endl << "0\t1\t2\t3\t-3\t-2\t-1" << endl;
	for (int j{}; j < 2*N + 1; ++j) {
		cout << array[j] << "\t";
	}
	system("pause");
	return 0;
}