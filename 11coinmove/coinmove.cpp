#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>

using namespace std;

ifstream ifile("coinmove.inp");
ofstream ofile("coinmove.out");

int dp[1000001][8];

int main() {
    int T = 0, P = 0, K = 0, S = 0, temp = 1;
    bool out = false;
    ifile >> T;
    for (int i = 0; i < T; i++) {
        out = false;
        ifile >> P >> K >> S;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i < 8; i++) {
            dp[0][i] = -1;
        }
        for (int i = 1; i < S + 1; i++) {
            for (int j = 1; j < K + 1; j++) {
                temp = 1;
                for (int t = 1; t < K + 1; t++) {
                    if (t == j) {
                        continue;
                    }
                    if (i - j < 0) {
                        temp = -1;
                        break;
                    }
                    if (dp[i - j][t] == 1 || (i - j != 0) && ((i - j) % P) == 0) {
                        temp = -1;
                        break;
                    }
                }
                dp[i][j] = temp;
            }
        }
        for (int i = 1; i < K + 1; i++) {
            if (dp[S][i] == 1) {
                ofile << S - i << endl;
                out = true;
                break;
            }
        }
        if (!out) {
            ofile << "-1" << endl;
        }
    }
    return 0;
}
