#include<bits/stdc++.h>
using namespace std;
#define ll				long long int
#define MOD				1000000007
#define rep(i, a, b)	for(i=a; i<=b; ++i)
#define rrep(i, a, b)	for(i=a; i>=b; --i)
#define si(a)			scanf("%d", &a)
#define sl(a)			scanf("%lld", &a)
#define pi(a)			printf("%d", a)
#define pl(a)			printf("%lld", a)
#define pn 				printf("\n")
ll pow_mod(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}
struct Edge {
	int src, dest;
	ll wght;
};
bool compare(Edge e1, Edge e2) {
	return e1.wght < e2.wght;
}
int rnk[1000005], par[1000005];
void init(int n) {
	for(int i = 0; i <= n; ++i) {
		rnk[i] = 0;
		par[i] = i;
	}
}
int Find(int nd) {
	if(par[nd] != nd) {
		par[nd] = Find(par[nd]);
	}
	return par[nd];
}
void Union(int nd1, int nd2) {
	int x = Find(nd1);
	int y = Find(nd2);
	if(rnk[x] > rnk[y]) {
		par[y] = x;
	} else if(rnk[x] < rnk[y]) {
		par[x] = y;
	} else {
		par[y] = x;
		rnk[x]++;
	}
}
vector<Edge> mst;
void Kruskal(vector<Edge> graph, int n) {
	init(n);
	sort(graph.begin(), graph.end(), compare);
	ll mst_wt = 0;
	for(int i = 0; i < (int)(graph.size()); ++i) {
		int x = Find(graph[i].src);
		int y = Find(graph[i].dest);
		if(x != y) {
			mst.push_back(graph[i]);
			Union(x, y);
			mst_wt += graph[i].wght;
		}
	}
	cout << mst_wt << endl;
}
int main() {
	int n, m;
	cin >> n >> m;
	vector<Edge> graph;
	Edge e;
	for(int i = 0; i < m; ++i) {
		cin >> e.src >> e.dest >> e.wght;
		e.src--;
		e.dest--;
		graph.push_back(e);
	}
	Kruskal(graph, n);
	return 0;
}