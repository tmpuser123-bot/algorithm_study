#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;

int dist[1010];
int route[1010];

vector<int> ans;
const int inf = 987654321;
int main(void)
{
    int n, m, a, b, c, st, ed;
    cin >> n >> m;

    fill(dist, dist + 1010, inf);
    vector<pii> path[1000];
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        path[a].push_back({b, c});
    }

    cin >> st >> ed;

    priority_queue<pii> pq;
    pq.push({0, st});
    dist[st] = 0;
    while (!pq.empty()) {
        int cost = -pq.top().first;
        int now = pq.top().second;
        pq.pop();

        if (now == ed)
            break;

        for (auto e : path[now]) {
            int nxt = e.first;
            int nxt_cost = e.second;
            if (dist[nxt] > dist[now] + nxt_cost) {
                dist[nxt] = dist[now] + nxt_cost;
                route[nxt] = now;
                pq.push({-dist[nxt], nxt});
            }
        }
    }

    cout << dist[ed] << endl
    int idx = ed;
    while (idx != st) {
        ans.push_back(idx);
        idx = route[idx];
    }
    ans.push_back(idx);
    cout << ans.size() << endl;
    for (int i = ans.size() - 1; i >= 0; i--)
            cout << ans[i] << " ";
    cout << endl;
}