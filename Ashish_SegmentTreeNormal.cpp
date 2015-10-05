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
/*Simple sum in range segment tree*/
struct seg_node {
	ll res;
};
seg_node tree[4 * 100000 + 5];
int ar[100005];
void build_tree(int node, int lft, int rgt) {
	if(lft == rgt) {
		tree[node].res = ar[lft];
		return;
	}
	int mid = (lft + rgt) >> 1;
	build_tree(2 * node, lft, mid);
	build_tree(2 * node + 1, mid + 1, rgt);
	tree[node].res = tree[2 * node].res + tree[2 * node + 1].res;
}
void update_tree(int node, int lft, int rgt, int idx, int val) {
	if(lft == rgt) {
		tree[node].res = val;
		return;
	}
	int mid = (lft + rgt) >> 1;
	if(idx <= mid) {
		update_tree(2 * node, lft, mid, idx, val);
	} else {
		update_tree(2 * node + 1, mid + 1, rgt, idx, val);
	}
	tree[node].res = tree[2 * node].res + tree[2 * node + 1].res;
}
ll query_tree(int node, int lft, int rgt, int l, int r) {
	if(lft > rgt || lft > r || rgt < l) {
		return 0;
	}
	if(lft >= l && rgt <= r) {
		return tree[node].res;
	}
	int mid = (lft + rgt) >> 1;
	ll q1 = query_tree(2 * node, lft, mid, l, r);
	ll q2 = query_tree(2 * node + 1, mid + 1, rgt, l, r);
	return q1 + q2;
}
int main() {
	int n, q;
	cin >> n >> q;
	for(int i = 0; i < n; ++i) {
		cin >> ar[i];
	}
	build_tree(1, 0, n - 1);
	int type, l, r;
	for(int i = 0; i < q; ++i) {
		cin >> type >> l >> r;
		if(type == 1) {
			update_tree(1, 0, n - 1, l - 1, r);
		} else {
			cout << query_tree(1, 0, n - 1, l - 1, r - 1) << endl;
		}
	}
	return 0;
}