#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

void bitmap(const vector<vector<int>>& v, int a1, int a2, int b1, int b2, int& p,ofstream& ofile) {
    if (a1 == a2 || b1 == b2) {
        return;
    }
    int z = 0;
    for (int i = a1; i < a2; i++) {
        z += static_cast<int>(count(v[i].begin() + b1, v[i].begin() + b2, 0));
    }
    if (p > 0 && p % 50 == 0) {
        ofile << endl;
    }
    p++;
    if (z == (a2 - a1) * (b2 - b1)) {
        ofile << "0";
    }
    else if (z == 0) {
        ofile << "1";
    }
    else {
        ofile << "D";
        int rowH = (a1 + a2 + 1) / 2;
        int colH = (b1 + b2 + 1) / 2;
        bitmap(v, a1, rowH, b1, colH, p, ofile);
        bitmap(v, a1, rowH, colH, b2, p, ofile);
        bitmap(v, rowH, a2, b1, colH, p, ofile);
        bitmap(v, rowH, a2, colH, b2, p, ofile);
    }
}
void decomposed(vector<vector<int>>& v, int a1, int a2, int b1, int b2, ifstream& ifile) {
    if (a1 == a2 || b1 == b2 || a1 > a2 || b1 > b2) {
        return;
    }
    cout << "col: " << b2-1 << " row: " << a2-1 << endl;
    int temp = ifile.get();
    if (temp == '\n') {
        temp = ifile.get();
    }
    if (temp == 48 || temp == 49) {
        for (int i = a1; i < a2; i++) {
            for (int j = b1; j < b2; j++) {
                v[i][j] = temp - 48;
            }
        }
        return;
    }
    else {
        int rowH = (a1 + a2 + 1) / 2;
        int colH = (b1 + b2 + 1) / 2;
        decomposed(v, a1, rowH, b1, colH, ifile);
        decomposed(v, a1, rowH, colH, b2, ifile);
        decomposed(v, rowH, a2, b1, colH, ifile);
        decomposed(v, rowH, a2, colH, b2, ifile);
    }
}
int main() {
    ifstream ifile("bitmap.inp");
    ofstream ofile("bitmap.out");
    char temp;
    while (ifile >> temp, temp != '#') {
        int row, col;
        ifile >> row >> col;
        ifile.ignore();
        ofile << (temp == 'B' ? "D" : "B") << right << setw(4) << row << right << setw(4) << col << endl;
        cout << (temp == 'B' ? "D" : "B") << right << setw(4) << row << right << setw(4) << col << endl;

        vector<vector<int>> v(row, vector<int>(col));
        if (temp == 'B') {
            string s;
            while (s.size() < row * col) {
                string s_temp;
                getline(ifile, s_temp);
                s = s + s_temp;
            }
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    v[i][j] = s[i * col + j] - 48;
                }
            }
            int p = 0;
            bitmap(v, 0, row, 0, col, p, ofile);
            ofile << endl;
        }
        else {
            decomposed(v, 0, row, 0, col, ifile);
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    if (i + j > 0 && (i * col + j) % 50 == 0) {
                        ofile << endl;
                    }
                    ofile << v[i][j];
                }
            }
            ofile << endl;
        }
    }
    ifile.close();
    ofile.close();
    return 0;
}
