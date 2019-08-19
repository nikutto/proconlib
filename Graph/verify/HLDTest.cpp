#include<vector>
#include<bits/stdc++.h>
#include"../HeavyLightDecomposition.cpp"
#include"../../DataStructure/LazySegmentTree.cpp"
using namespace std;
using namespace ProconLib;

struct Edge {
	int to;
};
using Graph = vector<vector<Edge>>;

struct MUStruct {
	struct Monoid {
		using value_t = pair<int, long long>;
		static constexpr value_t E() { return make_pair(0, 0LL); }
		static value_t op(value_t lhs, value_t rhs) { return make_pair(lhs.first + rhs.first, lhs.second + rhs.second); };
	};
	struct Update {
		using update_t = long long;
		static update_t op(update_t lhs, update_t rhs) { return lhs + rhs; }
	};
	static Monoid::value_t evaluate(Monoid::value_t v, Update::update_t u) { return make_pair(v.first, v.second + v.first*u); }
};

using LS = LazySegmentTree<MUStruct>;

struct HLDQManager {
	struct Monoid {
		using value_t = long long;
		static constexpr value_t E() { return 0; }
		static value_t op(value_t lhs, value_t rhs) { return lhs + rhs; }
	};
	using DataStructure = LS;
	struct Update {
		using update_t = long long;
        using update_single_t = pair<int,long long>;
		static void VertexUpdate(DataStructure& ds, int pos, update_t x) {};
		static void SingleUpdate(DataStructure& ds, int pos, pair<int,long long> p) {ds.update(pos,p);};
		static void RangeUpdate(DataStructure& ds, int l, int r, update_t x) { if(r<l) swap(l,r); ds.apply(l, r, x); };
	};
	struct Query {
		static Monoid::value_t VertexQuery(DataStructure& ds, int pos) { return 0LL; };
		static Monoid::value_t RangeQuery(DataStructure& ds, int l, int r) {if(r<l) swap(l,r); return ds.query(l,r).second;}
	};
};

int main() {
	int n;
	cin >> n;
	Graph g(n);
	vector<int> par(n);
	for (int i = 0; i<n; i++) {
		int k; cin >> k;
		while (k--) {
			int c; cin >> c;
			par[c]=i;
			g[i].push_back(Edge{ c });
			g[c].push_back(Edge{ i });
		}
	}

	HLDecompositionQuery<Graph, HLDQManager> hldQ(0, g);
    for(int i=1;i<n;i++) hldQ.singleUpdate(i,make_pair(1,0LL));
	int q;
	cin >> q;
	while (q--) {
		int type; cin >> type;
		if (type == 0) {
			int v, x;
			cin >> v >> x;
			hldQ.pathUpdate(v, 0, x);
		}
		else {
			int v;
			cin >> v;
			cout << hldQ.pathQuery(v, 0) << endl;
		}

	}
	return 0;
}