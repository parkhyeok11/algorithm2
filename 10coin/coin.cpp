#include <iostream>
#include <fstream>
using namespace std;

ifstream input("coin.inp");
ofstream output("coin.out");
int arr[4][4][4];
int main() {
    arr[1][1][1] = -1; arr[0][0][1] = -1; arr[0][1][0] = -1; arr[1][0][0] = -1; arr[0][2][2] = -1; arr[2][0][2] = -1; arr[2][2][0] = -1; arr[0][3][3] = -1;
    arr[3][0][3] = -1; arr[3][3][0] = -1; arr[1][2][3] = -1; arr[1][3][2] = -1; arr[2][1][3] = -1; arr[2][3][1] = -1; arr[3][1][2] = -1; arr[3][2][1] = -1;
    int n;
    input >> n;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        input >> a >> b >> c;
        output << "(" << a << " " << b << " " << c << ") : ";
        a %= 4; b %= 4; c %= 4;
        if (arr[a][b][c] == 0) {
            output << "1" << endl;
        }
        else {
            output << arr[a][b][c] << endl;
        }
    }
}
