#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int x, int y) {
    return y < x;
}

int main() {
    ifstream ifile;
    ofstream ofile;
    ifile.open("grid.inp");
    ofile.open("grid.out");
    int T = 0;
    ifile >> T;
    int N, M, K;
    
    for (int i = 0; i < T; i++) {
        vector<int> v;
        int temp, size, size1;
        ifile >> N >> M >> K;
        for (int j = 0; j < K; j++) {
            ifile >> temp;
            v.push_back(temp);
        }
        sort(v.begin(), v.end(),cmp);
        temp = N;
        size = N * M;
        bool spare = false;
        for (int k = 0; k < v.size(); k++) {
            if ((v[k] / temp) >= 2) {
                if (!spare && (v[k] / temp) > 2) {
                    spare = true;
                }
                if (size == temp && spare) {
                    size -= temp;
                }
                else {
                    if (size > ((v[k] / temp) * temp)) {
                        size -= (v[k] / temp) * temp;
                    }
                    else if (size <= ((v[k] / temp) * temp) && spare) {
                        size -= size;
                    }
                }
            }
            else {
                break;
            }
        }
        temp = M;
        size1 = N * M;
        spare = false;
        for (int k = 0; k < v.size(); k++) {
            if ((v[k] / temp) >= 2) {
                if (!spare && (v[k] / temp) > 2) {
                    spare = true;
                }
                if (size1 == temp && spare) {
                    size1 -= temp;
                }
                else {
                    if (size1 > ((v[k] / temp) * temp)) {
                        size1 -= (v[k] / temp) * temp;
                    }
                    else if (size1 <= ((v[k] / temp) * temp) && spare) {
                        size1 -= size1;
                    }
                }
            }
            else {
                break;
            }
        }
        if (size == 0 || size1 == 0) {
            cout << "Yes" << endl;
            ofile << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
            ofile << "No" << endl;
        }
    }

    ifile.close();
    ofile.close();

    return 0;
}
