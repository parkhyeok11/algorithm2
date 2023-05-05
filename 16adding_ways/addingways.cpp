#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>

using namespace std;

ifstream ifile("addingways.inp");
ofstream ofile("addingways.out");

unsigned long long DP[301][21];
void addingways() {
    for (int i = 1; i <= 300; i++) {
        for (int j = 1; j <= 20; j++) {
            if (i < j) DP[i][j] = 0;
            else if (i == j || j == 1) DP[i][j] = 1;
            else DP[i][j] = (DP[i - 1][j - 1] + DP[i - j][j]);
        }
    }
}

int main() {
    int n, k;
    addingways();
    while (true) {
        ifile >> n >> k;
        if (n == 0 && k == 0) break;
        else {
            unsigned long long result = DP[n][k] % 1000000007;
            ofile << result << '\n';
        }
    }
    return 0;
}
