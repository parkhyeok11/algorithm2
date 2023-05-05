#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int check(int* arr, int a,int grid,int k) {
	int holsu = 0;
	int temp;
	for (int x = 0; x < k; x++) {
		temp = arr[x] / a;
		if (temp < 2) {
			break;
		}
		else {
			if (!holsu) {
				if (temp > 2) {
					holsu++;
				}
			}
			if (grid == a) {
				if (holsu) {
					grid -= a;
				}
			}
			else {
				if (grid > temp * a) {
					grid -= temp * a;
				}
				else if (grid <= temp * a) {
					if (holsu) {
						grid -= grid;
					}
				}
			}
		}
	}
	return grid;
}

int main() {
	ifstream input; ofstream output;
	input.open("grid.inp");
	output.open("grid.out");
	int t, n, m, k;
	input >> t;
	for (int i = 0; i < t; i++) {
		input >> n >> m >> k;
		int* arr = new int[k];
		for (int j = 0; j < k; j++) {
			input >> arr[j];
		}
		sort(arr, arr + k, greater<int>());
		int grid = n * m;
		if (check(arr, n, grid, k)) {
			if (check(arr, m, grid, k)) {
				output << "No" << endl;
			}
			else {
				output << "Yes" << endl;
			}
		}
		else {
			output << "Yes" << endl;
		}
	}
	input.close();
	output.close();
	return 0;
}