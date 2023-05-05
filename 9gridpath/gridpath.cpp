#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include<iomanip>
#define INF 2147483647
using namespace std;

int main() {
	ifstream ifile("gridpath.inp");
	ofstream ofile("gridpath.out");
	int n = 0, m = 0;
	vector<vector<int>> v(200, vector<int>(200, -1));
	vector<vector<int>> path(200, vector<int>(200, 0));
	ifile >> n >> m;
	for (int i = 0; i < n; i++) {//입력과 동시에 가장자리 path값 1로 초기화
		for (int j = 0; j < m; j++) {
			ifile >> v[i][j];
		}
	}
	for (int i = 0; i < n; i++) {//왼쪽 가장자리 weight값
		if (v[i][0] != -1) {
			if (i == 0) {
				path[i][0] = v[i][0];
			}
			else {
				path[i][0] = path[i - 1][0] + v[i][0];
			}
		}
		else {
			break;
		}
	}
	for (int i = 0; i < m; i++) {//위쪽 가장자리 weight값
		if (v[0][i] != -1) {
			if (i == 0) {
				path[0][i] = v[0][i];
			}
			else {
				path[0][i] = path[0][i - 1] + v[0][i];
			}
		}
		else {
			break;
		}
	}
	//temp 2개로 min비교 path가 0인 것은 제외
	int tempRow = 0, tempCol = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (path[i - 1][j] == 0 || v[i][j] == -1) {
				tempRow = INF;
			}
			else {
				tempRow = v[i][j] + path[i - 1][j];
			}
			if (path[i][j - 1] == 0 || v[i][j] == -1) {
				tempCol = INF;
			}
			else {
				tempCol = v[i][j] + path[i][j - 1];
			}
			if (tempRow == INF && tempCol == INF) {
				path[i][j] = 0;
			}
			else if (tempRow >= tempCol) {
				path[i][j] = tempCol;
			}
			else {
				path[i][j] = tempRow;
			}
		}
	}
	if (path[n - 1][m - 1] != 0) {
		ofile << path[n - 1][m - 1] << endl;//최소비용
			vector<int> resultRow;
			vector<int> resultCol;
			resultRow.push_back(n - 1);
			resultCol.push_back(m - 1);
			int i = n - 1, j = m - 1;
			while (i != 0 || j != 0) {
				if (i == 0 && j == 0) break;
				if (i == 0 && j != 0) {
					resultRow.push_back(0);
					resultCol.push_back(j - 1);
					j--;
				}
				else if (i != 0 && j == 0) {
					resultRow.push_back(i - 1);
					resultCol.push_back(0);
					i--;
				}
				else if (path[i][j - 1] == 0 || path[i - 1][j] == 0) {
					if (path[i - 1][j] > path[i][j - 1]) {
						resultRow.push_back(i - 1);
						resultCol.push_back(j);
						i--;
					}
					else {
						resultRow.push_back(i);
						resultCol.push_back(j - 1);
						j--;
					}
				}
				else if (path[i - 1][j] <= path[i][j - 1]) {
					resultRow.push_back(i - 1);
					resultCol.push_back(j);
					i--;
				}
				else if (path[i - 1][j] > path[i][j - 1]) {
					resultRow.push_back(i);
					resultCol.push_back(j - 1);
					j--;
				}
			}
			reverse(resultRow.begin(), resultRow.end());
			reverse(resultCol.begin(), resultCol.end());
			for (int i = 0; i < resultRow.size(); i++) {
				ofile << "(" << resultRow[i] << " " << resultCol[i] << ")" << endl;
			}
	}
	else {
		ofile << "No path." << endl;
	}
	ifile.close();
	ofile.close();
	return 0;
}
