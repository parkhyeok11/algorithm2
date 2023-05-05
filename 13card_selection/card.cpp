#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>

using namespace std;

ifstream ifile("card.inp");
ofstream ofile("card.out");

int main() {
    int T, n;
    ifile >> T;
    while (T != 0) {
        ifile >> n;
        vector<int> v(n);
        vector<int> first(n, -1000001);//i-4번째 카드를 뽑았을 경우
        vector<int> second(n, -1000001);//i-3번째 카드를 뽑았을 경우
        vector<int> third(n, -1000001);//i-2번째 카드를 뽑았을 경우
        for (int i = 0; i < n; i++) {//입력
            ifile >> v[i];
        }
        first[0] = v[0]; first[1] = v[1]; first[2] = v[2];//어차피 123중 하나 뽑아야하니까 3장 세이브
        second[3] = v[3] + v[0]; third[3] = v[3] + v[1];
        for (int i = 4; i < n; i++) {
            int temp;
            if (first[i - 4] >= second[i - 4] && first[i - 4] >= third[i - 4]) {
                temp = first[i - 4];
            }
            else if (second[i - 4] >= first[i - 4] && second[i - 4] >= third[i - 4]) {
                temp = second[i - 4];
            }
            else {
                temp = third[i - 4];
            }
            first[i] = v[i] + temp;//i-4를 했을 때 가장 큰 값 더하기
            if (first[i - 3] >= second[i - 3] && first[i - 3] >= third[i - 3]) {
                temp = first[i - 3];
            }
            else if (second[i - 3] >= first[i - 3] && second[i - 3] >= third[i - 3]) {
                temp = second[i - 3];
            }
            else {
                temp = third[i - 3];
            }
            second[i] = v[i] + temp;//i-3을 했을 때 가장 큰 값 더하기
            if (first[i - 2] >= second[i - 2]) {
                temp = first[i - 2];
            }
            else {
                temp = second[i - 2];
            }
            third[i] = v[i] + temp;//i-2를 했을 때 가장 큰 값 더하기
        }
        if (first[n - 1] >= second[n - 1] && first[n - 1] >= third[n - 1]) {
            ofile << first[n - 1] << endl;
        }
        else if (second[n - 1] >= first[n - 1] && second[n - 1] >= third[n - 1]) {
            ofile << second[n - 1] << endl;
        }
        else {
            ofile << third[n - 1] << endl;
        }
        T--;
    }
    return 0;
}
