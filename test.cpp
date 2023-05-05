#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

ifstream ifile("test.inp");
ofstream ofile("test.out");

struct Name {
    int originNumber, count;
    string firstName, lastName;
};
bool sort_cmp(const Name& a, const Name& b) {
    if (a.originNumber < b.originNumber) return true;
    return false;
}
bool sort_cmp2(const Name& a, const Name& b) {
    if (a.lastName < b.lastName) return true;
    return false;
}
int main() {
    int N = 0;
    ifile >> N;
    vector<struct Name> T(N);
    int str_length = 0;
    for (int i = 0; i < N; i++) {
        ifile >> T[i].originNumber;
        ifile >> T[i].firstName;
        if (T[i].firstName.size() > str_length) {
            str_length = T[i].firstName.size();
        }
        ifile >> T[i].lastName;
    }
    sort(T.begin(), T.end(), sort_cmp);
    for (auto i : T) {
        cout << right << setfill('0') << setw(5) << i.originNumber << " " << left << setfill(' ') << setw(str_length) << i.firstName << " " << i.lastName << endl;
        ofile << right << setfill('0') << setw(5) << i.originNumber << " " << left << setfill(' ') << setw(str_length) << i.firstName << " " << i.lastName << endl;
    }
    vector<struct Name> cp;
    for (int i = 0; i < N; i++) {
        int count = 1;
        bool check = false;
        if (cp.size() != 0) {
            for (int k = 0; k < cp.size(); k++) {
                if (T[i].lastName.compare(cp[k].lastName) == 0) {
                    check = true;
                    break;
                }
            }
        }
        if (!check) {
            for (int j = i + 1; j < N; j++) {
                if (T[i].lastName.compare(T[j].lastName) == 0) {
                    count++;
                    if (count == 2) {
                        cp.push_back(T[i]);
                        cp.back().count = count;
                    }
                    else if (count > 2) {
                        cp.back() = T[i];
                        cp.back().count = count;
                    }
                }
            }
        }
    }
    if (cp.size() > 0) {
        ofile << "\n";
        sort(cp.begin(), cp.end(), sort_cmp2);
        for (int i = 0; i < cp.size(); i++) {
            ofile << cp[i].lastName << " " << cp[i].count << endl;
            cout << cp[i].lastName << " " << cp[i].count << endl;
        }
    }
    ifile.close();
    ofile.close();
    return 0;
}
