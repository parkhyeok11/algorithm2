#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void find_p(long long n, long long w,long long *x,long long *y) {
    long long p = 0;
    long long temp = 0;
    long long temp2 = 0;
    int test;
    while (1) {
        temp += (n - 1 - 2 * p) * 4 - (((2 * (p + 1)) - 1) - 2 * p) + 1;
        
        if (w <= temp) {
            break;
        }
        if (temp == ((n * n) - 1)) temp = n * n;
        temp2 = temp;
        p++;
    }
    if (w <= (((temp + temp2)+2) / 2)) {
        w -= 4 * (p * n - (p * p));
        temp = (((temp + temp2) + 2) / 2) - 4 * (p * n - (p * p));
        if (w <= (temp+1)/2) {
            w += 2 * p - 1;
            *x = w - p;
            *y = w - *x;
            cout << "상" << *x << " " << *y << endl;
        }
        else {
            *y += w - ((temp + 1) / 2) + p;
            w += 2 * p - 1;
            *x = w - *y;
            cout << "우" << *x << " " << *y << endl;
        }
    }
    else {
        w -= 4 * (p * n - (p * p));
        temp = (((temp + temp2) + 2) / 2) - 4 * (p * n - (p * p));
        temp = temp + (n-1) - p * 2;
        if (w <= temp) {//��
            w = (n - 1 - 2 * p) * 4 + 1 - w + 2 * p;
            *y = n - 1 - p;
            *x = w - *y;
            cout << "하" << *x << " " << *y << endl;
        }
        else {//��
            w = (n - 1 - 2 * p) * 4 + 1 - w + 2 * p;
            *x = p;
            *y = w - *x;
            cout << "좌" << *x << " " << *y << endl;
        }
    }
    
}

int main() {
    ifstream ifile;
    ofstream ofile;
    ifile.open("snail.inp");
    ofile.open("snail.out");
    int T = 0;
    ifile >> T;
    long long N, A, B;
    for (int i = 0; i < T; i++) {
        long long p = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        ifile >> N >> A >> B;
        find_p(N, A, &x1, &y1);
        find_p(N, B, &x2, &y2);
        if (abs(x1 - x2) == abs(y1 - y2)) {
            cout << "YES" << endl;
            ofile << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
            ofile << "NO" << endl;
        }
    }

    ifile.close();
    ofile.close();

    return 0;
}
