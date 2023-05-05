#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

ifstream ifile("drive.inp");
ofstream ofile("drive.out");

int dp[100][100][201][2];
int fuel[2][100][100];

int main() {
    int T;
    ifile >> T;
    for (int t = 0; t < T; t++) {
        int n, m, l, g;
        ifile >> n >> m >> l >> g;
        for (int i = 0; i < n; i++) {//오른쪽 연료
            for (int j = 0; j < m - 1; j++) {
                ifile >> fuel[0][i][j];
            }
        }
        for (int i = 0; i < n - 1; i++) {//아래 연료
            for (int j = 0; j < m; j++) {
                ifile >> fuel[1][i][j];
            }
        }
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0][0][0] = dp[0][0][0][1] = 0;//처음 시작부분은 turn conner 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k <= n + m; k++) {
                    if (i != 0) {
                        dp[i][j][k][1] = dp[i - 1][j][k][1] + fuel[1][i - 1][j];
                        if (k != 0) {
                            dp[i][j][k][1] = min(dp[i][j][k][1], dp[i - 1][j][k - 1][0] + fuel[1][i - 1][j]);
                        }
                    }
                    if (j != 0) {
                        dp[i][j][k][0] = dp[i][j - 1][k][0] + fuel[0][i][j - 1];
                        if (k != 0) {
                            dp[i][j][k][0] = min(dp[i][j][k][0], dp[i][j - 1][k - 1][1] + fuel[0][i][j - 1]);
                        }
                    }
                }
            }
        }
        int result = -1;
        for (int i = 0; i <= n + m; i++) {
            for (int j = 0; j < 2; j++) {
                if (dp[n - 1][m - 1][i][j] <= g) {
                    if (result == -1 || result > (n + m - 2) * l + i) {
                        result = (n + m - 2) * l + i;
                    }
                }
            }
        }
        cout << result << '\n';
    }
    return 0;
}
