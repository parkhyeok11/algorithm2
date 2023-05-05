#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>

using namespace std;

ifstream ifile("card.inp");
ofstream ofile("card.out");

int DP[2][1001][1001];
int arr[1001];

int dp_card(int turn, int front, int back) {
    if (front == back) {//정중앙 카드일 경우
        if (turn == 0) return arr[front];//내 턴일 때는 카드 리턴
        else return 0;//컴퓨터 턴이면 0리턴
    }
    int &temp = DP[turn][front][back];//참조를 걸어서 DP값을 수정할 수 있게 만들어줌
    if (temp != -1) return temp;//DP배열에 값이 있다면 값을 리턴
    if (turn == 0) {//내 턴일 때
        int temp1 = dp_card(!turn, front + 1, back) + arr[front];//앞에서 뽑았을 때
        int temp2 = dp_card(!turn, front, back - 1) + arr[back];//뒤에서 뽑았을 때
        //2장 비교해서 큰 값을 temp에 저장
        if (temp1 < temp2) temp = temp2;
        else temp = temp1;
    }
    else {//컴퓨터 턴일 때
        int temp1 = dp_card(!turn, front + 1, back);//앞에서 뽑았을 때
        int temp2 = dp_card(!turn, front, back - 1);//뒤에서 뽑았을 때
        //2장 비교해서 작은 값을 temp에 저장
        if (temp1 < temp2) temp = temp1;
        else temp = temp2;
    }
    return temp;
}

int main() {
    int cnt = 0, n = 0, temp = 0;
    ifile >> cnt;
    for (int t = 0; t < cnt; t++) {
        memset(DP, -1, sizeof(DP));
        ifile >> n;
        for (int i = 0; i < n; i++) {
            ifile >> arr[i];
        }
        temp = dp_card(0, 0, n - 1);
        ofile << temp << '\n';
    }
    return 0;
}
