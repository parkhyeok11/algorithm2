#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>
#define INF 1000000
using namespace std;

ifstream ifile("color.inp");
ofstream ofile("color.out");

int dp[5005][5005], c[5005][5005], stp1[26], stp2[26], enp1[26], enp2[26];
char p1[5005], p2[5005];

int main() {
    int T;
    ifile >> T;
    for(int i = 0; i < T; i++) {
        ifile >> p1 + 1;
        ifile >> p2 + 1;
        int n1 = strlen(p1 + 1), n2 = strlen(p2 + 1);
        for(int i = 1; i <= n1; i++) { p1[i] -= 'A'; }
        for(int j = 1; j <= n2; j++) { p2[j] -= 'A'; }
        for (int i = 0; i < 26; i++) {
            stp1[i] = stp2[i] = 5005;
            enp1[i] = enp2[i] = 0;
        }
        for(int i = 1; i <= n1; i++) {
            stp1[p1[i]] = min(stp1[p1[i]], i);
            enp1[p1[i]] = i;
        }
        for(int i = 1; i <= n2; i++) {
            stp2[p2[i]] = min(stp2[p2[i]], i);
            enp2[p2[i]] = i;
        }
        for(int i = 0; i <= n1; i++) {
            for(int j = 0; j <= n2; j++) {
                if(i == 0 && j == 0) continue;
                int p1v = INF, p2v = INF;
                if(i) p1v = dp[i - 1][j] + c[i - 1][j];
                if(j) p2v = dp[i][j - 1] + c[i][j - 1];
                dp[i][j] = min(p1v, p2v);
                if (dp[i][j] == p1v) {
                    c[i][j] = c[i - 1][j];
                    if(stp1[p1[i]] == i && stp2[p1[i]] > j) c[i][j]++;
                    if(enp1[p1[i]] == i && enp2[p1[i]] <= j) c[i][j]--;
                }
                else {
                    c[i][j] = c[i][j - 1];
                    if (stp2[p2[j]] == j && stp1[p2[j]] > i) c[i][j]++;
                    if (enp2[p2[j]] == j && enp1[p2[j]] <= i) c[i][j]--;
                }
            }
        }
        ofile << dp[n1][n2] << '\n';
    }
    return 0;
}
