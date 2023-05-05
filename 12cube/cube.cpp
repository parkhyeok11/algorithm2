#include <iostream>
#include <fstream>
#include <vector>
#include<cstring>

using namespace std;

int arr[201][201][201];
ifstream ifile("cube.inp");
ofstream ofile("cube.out");

int min(int a, int b) {
	return (a < b) ? a : b;
}

int cube_cut(int w, int l, int h) {
	if (w == l && l == h) return arr[w][l][h] = 1;
	if (w < 0 || l < 0 || h < 0) return 8000001;
	int& result = arr[w][l][h];
	if (result != -1) {
		return result;
	}
	result = w * l * h;//처음엔 1*1*1인 경우의 수 -> 그 뒤부터 자르고 1*1*1의 경우의수
	for (int wtemp = 1; wtemp <= (w + 1) / 2; wtemp++) {
		result = min(result, cube_cut(wtemp, l, h) + cube_cut(w - wtemp, l, h));
	}
	for (int ltemp = 1; ltemp <= (l + 1) / 2;ltemp++){
		result = min(result, cube_cut(w, ltemp, h) + cube_cut(w, l - ltemp, h));
	}
	for (int htemp = 1; htemp <= (h + 1) / 2; htemp++) {
		result = min(result, cube_cut(w, l, htemp) + cube_cut(w, l, h - htemp));
	}
	return result;
}

int main() {
	int T;
	ifile >> T;
	memset(arr, -1, sizeof(arr));
	while (T != 0) {
		int W, L, H;
		ifile >> W >> L >> H;
		ofile << cube_cut(W, L, H) << endl;
		T--;
	}
	return 0;
}
