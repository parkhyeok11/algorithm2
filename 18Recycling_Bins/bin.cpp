#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

ifstream input("bin.inp");
ofstream output("bin.out");

int house[501];
int sum[501][501];
int result[501][501];

class bin {
private:
    int a, b;

public:
    void set() {
        memset(result, 1, sizeof(result));
        memset(sum, 0, sizeof(sum));
        input >> a >> b;
        for (int i = 1; i <= a; i++) {
            input >> house[i];
        }
        sort(house + 1, house + 1 + a);
    }
    int solve() {
        for (int i = 0; i <= b; i++) {
            result[0][i] = 0;
        }
        for (int i = 1; i <= a; i++) {
            for (int j = i; j <= a; j++) {
                sum[i][j] = sum[i][j - 1] + house[j] - house[i + (j - i) / 2];
            }
        }

        for (int i = 1; i <= a; i++) {
            for (int j = 1; j <= b; j++) {
                for (int k = 1; k <= i; k++) {
                    result[i][j] = min(result[i][j], result[i - k][j - 1] + sum[i - k + 1][i]);
                }
            }
        }
        return result[a][b];
    }
};

int main() {
    int a, b, count;
    input >> count;
    bin B;
    while (count != 0) {
        B.set();
        output << B.solve() << "\n";
        count--;
    }
}
