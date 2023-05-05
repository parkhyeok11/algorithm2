#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;



void result(int first, int last, vector<int>& v,vector<int>& depth) {
    int max_idx, max = 0;
    for (int i = first; i <= last; i++) {
        if (v[i] > max) {
            max = v[i]; max_idx = i;
        }
    }
    for (int i = first; i <= last; i++) {
        if (i != max_idx) {
            depth[i] += 1;
        }
    }
    if (max_idx - first >= 2) {
        int left = max_idx - 1;
        result(first, left, v, depth);
    }
    if (last - max_idx >= 2) {
        int right = max_idx + 1;
        result(right, last, v, depth);
    }
}

void go(vector<int>& v, int n, vector<int>& depth) {
    int first = 0, last = n - 1;
    result(first, last, v, depth);
}

int main() {
    ifstream ifile;
    ofstream ofile;
    ifile.open("permutation.inp");
    ofile.open("permutation.out");
    int T = 0;
    ifile >> T;
    int n, max, max_idx;
    for (int t = 0; t < T; t++) {
        ifile >> n;
        vector<int> v(n);
        vector<int> depth(n, 0);
        for (int i = 0; i < n; i++) {
            ifile >> v[i];
        }
        go(v, n, depth);
        for (int i = 0; i < n; i++) {
            ofile << depth[i] << " ";
        }
        ofile << endl;
    }
    ifile.close();
    ofile.close();

    return 0;
}
