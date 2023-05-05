#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream ifile;
    ofstream ofile;
    ifile.open("gain.inp");
    ofile.open("gain.out");
    int T = 0;

    ifile >> T;
    int N = 0, temp = 0;;
    for (int i = 0; i < T; i++) {
        ifile >> N;
        vector<int> v;
        for (int j = 0; j < N; j++) {
            ifile >> temp;
            v.push_back(temp);
        }
        sort(v.begin(), v.end());
        int result = v[N - 1] + v[N - 2] - v[1] - v[0];
        cout << result << endl;
        ofile << result << endl;
    }
    ifile.close();
    ofile.close();
    return 0;
}
