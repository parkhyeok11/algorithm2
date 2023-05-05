#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

vector<vector<char>> V;
vector<vector<char>> temp;

void printN(int N,ofstream & ofile) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ofile << V[i][j];
            cout << V[i][j];
        }
        ofile << "\n";
        cout << "\n";
    }
    ofile << "\n";
    cout << "\n";
}
void slide(int N) {
    temp.assign(N, vector<char>(N, '.'));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp[i][j] = V[j][i];
        }
    }
    for (int i = 0; i < N; i++) {
        temp[i].erase(remove(temp[i].begin(), temp[i].end(), '.'),temp[i].end());
    }
    for (int i = 0; i < N; i++) {
        int tmpSize = temp[i].size();
        for (int j = 0; j < N - tmpSize; j++) {
            temp[i].insert(temp[i].begin(), '.');
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            V[i][j] = temp[j][i];
        }
    }
}
void spin(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp[i][j] = V[N - j - 1][i];
        }
    }
    V.assign(temp.begin(), temp.end());
    slide(N);
}


int main() {
    ifstream ifile;
    ofstream ofile;
    ifile.open("spinslide.inp");
    ofile.open("spinslide.out");
    if (!ifile.is_open()) { cout << "파일 열기 실패!" << endl; }
    int T = 0;
    int N = 0, M = 0;
    //입력
    ifile >> T;
    for (int i = 0; i < T; i++) {
        ifile >> N;
        ifile >> M;
        V.assign(N, vector<char>(N, ' '));
        temp.assign(N, vector<char>(N, ' '));
        //��������
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                ifile >> V[j][k];
            }
        }
        for (int t = 0; t < M; t++) {
            spin(N);
        }
        ofile << "Case #" << i + 1 << ":" << endl;
        cout << "Case #" << i + 1 << ":" << endl;
        printN(N,ofile);
    }



    ifile.close();
    ofile.close();
    return 0;
}
