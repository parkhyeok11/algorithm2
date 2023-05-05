#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

ifstream input("mst.inp");
ofstream output("mst.out");

vector<pii> v[10001];
vector<pair<pii, pii> > v2;
queue<int> q;
int* visit;
int getParent(int* visit, int x) {
    if (visit[x] == x)
        return x;
    return visit[x] = getParent(visit, visit[x]);
}
void unionParent(int* visit, int a, int b) {
    a = getParent(visit, a);
    b = getParent(visit, b);
    if (a < b)
        visit[b] = a;
    else
        visit[a] = b;
}
int find(int* visit, int a, int b) {
    a = getParent(visit, a);
    b = getParent(visit, b);
    if (a == b)
        return 1;
    else
        return 0;
}
void kruskal(int n, int m) {
    int result = 0;
    visit = new int[n];
    for (int i = 0; i < n; i++) {
        visit[i] = i;
    }
    for (int i = 0; i < m; i++) {
        if (!find(visit, v2[i].second.first, v2[i].second.second)) {
            result += v2[i].first.first;
            q.push(v2[i].first.second);
            unionParent(visit, v2[i].second.first, v2[i].second.second);
        }
    }
    output << "Tree edges by Kruskal algorithm: " << result << "\n";
    int cnt = q.size();
    for (int i = 0; i < cnt; i++) {
        output << q.front() << "\n";
        q.pop();
    }
}

void prim(int n, int m, int s) {
    int result = 0;
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        visit[i] = 0;
    }
    visit[s] = 1;
    while (1) {
        for (int i = 0; i < m; i++) {
            if ((visit[v2[i].second.second] == 0 && visit[v2[i].second.first] == 0) || (visit[v2[i].second.first] == 1 && visit[v2[i].second.second] == 1)) {
                continue;
            }
            else {
                result += v2[i].first.first;
                q.push(v2[i].first.second);
                visit[v2[i].second.second] = 1;
                visit[v2[i].second.first] = 1;
                tmp++;
                break;
            }
        }
        if (n - 1 == tmp) {
            break;
        }
    }
    output << "Tree edges by Prim algorithm with starting vertex " << s << ": " << result << "\n";
    int cnt = q.size();
    for (int i = 0; i < cnt; i++) {
        output << q.front() << "\n";
        q.pop();
    }
}

int main() {
    int n, m;
    input >> n >> m;
    int tmp = m;
    int i = 0;
    while (m != 0) {
        int a, b, c;
        input >> a >> b >> c;
        v[a].push_back({ b, c });
        v[b].push_back({ a, c });
        v2.push_back({ {c, i}, {a, b} });
        i++;
        m--;
    }
    m = tmp;
    sort(v2.begin(), v2.end());
    kruskal(n, m);
    prim(n, m, 0);
    prim(n, m, n / 2);
    prim(n, m, n - 1);
}
