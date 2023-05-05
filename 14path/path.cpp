#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>

using namespace std;

ifstream ifile("path.inp");
ofstream ofile("path.out");

int mini(int x, int y) {
    if (x > 0 && y > 0) {
        return x > y ? y : x;
    }
    else {
        return x > y ? x : y;
    }
}

struct cost {
    int right;
    int down;
};

int existK[101][101];//격자에서의 K위치 1이면 K
long long root[201][101][101];//k의 값에 따른 경로의 수
long long root_cost[201][101][101];//k의 값에 따른 경로의 가중치
struct cost path_cost[101][101];//격자의 가중치

int main() {
    int C, TestCase = 1;
    ifile >> C;
    while (C != 0) {
        int M, N, K;
        ifile >> M >> N >> K;
        memset(root, 0, sizeof(root));
        memset(root_cost, 0, sizeof(root_cost));
        memset(existK, 0, sizeof(existK));
        memset(path_cost, 0, sizeof(path_cost));
        for (int i = 0; i < K; i++) {//existK에 K값 표시
            int temp1, temp2;
            ifile >> temp1 >> temp2;
            existK[temp1][temp2] = 1;
        }
        for (int i = 0; i < M; i++) {//오른쪽 가중치
            for (int j = 0; j < N - 1; j++) {
                int temp;
                ifile >> temp;
                path_cost[i][j].right = temp;
            }
        }
        for (int i = 0; i < M - 1; i++) {//아래 가중치
            for (int j = 0; j < N; j++) {
                int temp;
                ifile >> temp;
                path_cost[i][j].down = temp;
            }
        }
        int k = 0;
        for (int i = 1; i < N; i++) {//맨 윗 줄
            if (existK[0][i] == 1) {
                k++;
                root_cost[k][0][i] = root_cost[k - 1][0][i - 1] + path_cost[0][i - 1].right;
            }
            else {
                root_cost[k][0][i] = root_cost[k][0][i - 1] + path_cost[0][i - 1].right;
            }
            root[k][0][i] = 1;
        }
        k = 0;
        for (int i = 1; i < M; i++) {//맨 왼쪽 줄
            if (existK[i][0] == 1) {
                k++;
                root_cost[k][i][0] = root_cost[k - 1][i - 1][0] + path_cost[i - 1][0].down;
            }
            else {
                root_cost[k][i][0] = root_cost[k][i - 1][0] + path_cost[i - 1][0].down;
            }
            root[k][i][0] = 1;
        }
        for (int t = 0; t <= K; t++) {
            for (int i = 1; i < M; i++) {
                for (int j = 1; j < N; j++) {
                    if (root[t][i - 1][j] != 0 || root[t][i][j - 1] != 0) {//오는 길이 있을 때
                        if (existK[i][j] == 1) {//현재 위치가 K일 때
                            root[t + 1][i][j] = root[t][i - 1][j] + root[t][i][j - 1];
                            int temp1 = 0, temp2 = 0;
                            if (root[t][i - 1][j] != 0) {
                                temp1 = root_cost[t][i - 1][j] + path_cost[i - 1][j].down;
                            }
                            if (root[t][i][j - 1] != 0) {
                                temp2 = root_cost[t][i][j - 1] + path_cost[i][j - 1].right;
                            }
                            root_cost[t + 1][i][j] = mini(temp1, temp2);
                            root[t + 1][i][j] %= 100000;
                        }
                        else {
                            root[t][i][j] = root[t][i - 1][j] + root[t][i][j - 1];
                            int temp1 = 0, temp2 = 0;
                            if (root[t][i - 1][j] != 0) {
                                temp1 = root_cost[t][i - 1][j] + path_cost[i - 1][j].down;
                            }
                            if (root[t][i][j - 1] != 0) {
                                temp2 = root_cost[t][i][j - 1] + path_cost[i][j - 1].right;
                            }
                            root_cost[t][i][j] = mini(temp1, temp2);
                            root[t][i][j] %= 100000;
                        }
                    }
                }
            }
        }
        //TestCase 출력
        //cout << "Test Case No:" << TestCase << endl;
        ofile << "Test Case No:" << TestCase << endl;
        TestCase++;
        //최단경로 + 가중치는 구했음
        //좌표 구하고 뱉어내면 될 듯
        for (int t = 0; t <= K; t++) {
            if (root[t][M - 1][N - 1] == 0) continue;
            //cout << "k:" << t << " count:" << root[t][M - 1][N - 1];
            //cout << " cost:" << root_cost[t][M - 1][N - 1] << endl;
            ofile << "k:" << t << " count:" << root[t][M - 1][N - 1];
            ofile << " cost:" << root_cost[t][M - 1][N - 1] << endl;
            vector<int> row;
            vector<int> col;
            row.push_back(M - 1);
            col.push_back(N - 1);
            int k = t;
            while (row.back() != 0 || col.back() != 0) {
                int temp_row = row.back(), temp_col = col.back();
                if (existK[temp_row][temp_col] && k >= 0) {
                    k--;
                    if (temp_col >= 0 && root_cost[k][temp_row][temp_col - 1] + path_cost[temp_row][temp_col - 1].right == root_cost[k + 1][temp_row][temp_col]) {
                        row.push_back(temp_row);
                        col.push_back(temp_col - 1);
                    }
                    else {
                        row.push_back(temp_row - 1);
                        col.push_back(temp_col);
                    }
                }
                else {
                    if (temp_col >= 0 && root_cost[k][temp_row][temp_col - 1] + path_cost[temp_row][temp_col - 1].right == root_cost[k][temp_row][temp_col]) {
                        row.push_back(temp_row);
                        col.push_back(temp_col - 1);
                    }
                    else {
                        row.push_back(temp_row - 1);
                        col.push_back(temp_col);
                    }
                }
            }
            //row.push_back(0);
            //col.push_back(0);
            while (!row.empty() && !col.empty()) {
                ofile << "(" << row.back() << "," << col.back() << ")";
                row.pop_back();
                col.pop_back();
                if (!row.empty() && !col.empty()) {
                    ofile << "->";
                }
            }

            //reverse(row.begin(), row.end());
            //reverse(col.begin(), col.end());
            //for (int i = 0; i < N + M - 1; i++) {
            //    //cout << "(" << row[i] << ",";
            //    ofile << "(" << row[i] << ",";
            //    //cout << col[i] << ")";
            //    ofile << col[i] << ")";
            //    if (i != N + M - 2) {
            //        //cout << "->";
            //        ofile << "->";
            //    }
            //}
            //cout << endl;
            ofile << endl;
        }
        //cout << endl;
        ofile << endl;

        C--;
    }
    return 0;
}
