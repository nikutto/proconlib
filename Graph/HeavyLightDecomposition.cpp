#include<vector>
#include"LCA.cpp"

namespace ProconLib {

	template<class graph_t>
	class HeavyLightDecomposition {
		int N;
		int K = 0;
		std::vector<int> hId;
		std::vector<int> subId;
		std::vector<int> sz;
		std::vector<int> hPar;
		std::vector<int> hSz;
		int dfsSZ(int v, int pre, const graph_t& g);
		int dfsHL(int v, int pre, const graph_t& g);
	public:
		void build(int root, const graph_t& g);
		HeavyLightDecomposition(std::vector<int> roots, const graph_t& g) :N(g.size()), hId(N, -1), subId(N, -1), sz(N, -1), hPar(1, 0), hSz(N) { for (auto root : roots) build(root, g); }
		HeavyLightDecomposition(int root, const graph_t& g) :HeavyLightDecomposition(std::vector<int>(1, root), g) {}

		int size() { return K; }
		int size(int h) { return hSz[h]; }
		int getHId(int v) { return hId[v]; }
		int getSubId(int v) { return subId[v]; }
		int getHPar(int v) { return hPar[v]; }
	};


	template<class graph_t>
	int HeavyLightDecomposition<graph_t>::dfsSZ(int v, int pre, const graph_t& g) {
		sz[v] = 1;
		for (auto& e : g[v]) {
			if (e.to == pre) continue;
			sz[v] += dfsSZ(e.to, v, g);
		}
		return sz[v];
	}

	template<class graph_t>
	int HeavyLightDecomposition<graph_t>::dfsHL(int v, int pre, const graph_t& g) {
		int maxC = -1;
		int maxSZ = -1;
		for (auto &e : g[v]) {
			if (e.to == pre) continue;
			if (maxSZ<sz[e.to]) {
				maxC = e.to;
				maxSZ = sz[e.to];
			}
		}
		if (maxC == -1) subId[v] = 0;
		else {
			for (auto &e : g[v]) {
				if (e.to == pre) continue;
				if (e.to == maxC) {
					hId[e.to] = hId[v];
					subId[v] = dfsHL(e.to, v, g) + 1;
				}
				else {
					hId[e.to] = K++;
					hPar.push_back(v);
					assert(hPar.size() == K);
					dfsHL(e.to, v, g);
				}
			}
		}
		hSz[hId[v]] = subId[v] + 1;
		return subId[v];
	}

	template<class graph_t>
	void HeavyLightDecomposition<graph_t>::build(int root, const graph_t& g) {
		dfsSZ(root, -1, g);
		hId[root] = K++;
		dfsHL(root, -1, g);
	}


	struct HLDQManagerInterface {
		struct Monoid;
		struct DataStructure;
		struct Update {
			struct update_t;
            struct update_single_t;
            static void VertexUpdate(DataStructure& ds, int pos, update_t x);
            static void RangeUpdate(DataStructure& ds, int l, int r, update_t x);
            static void SingleUpdate(DataStructure& ds, int pos, update_single_t x);
		};
		struct Query {
			static void VertexQuery(DataStructure& ds, int pos);
			static void RangeQuery(DataStructure& ds, int l, int r);
		};
	};

	template<class graph_t, class HLDQManager>
	class HLDecompositionQuery {
		using HLD = HeavyLightDecomposition<graph_t>;
		using DS = typename HLDQManager::DataStructure;

		using Monoid = typename HLDQManager::Monoid;
		using value_t = typename Monoid::value_t;

		using Update = typename HLDQManager::Update;
		using Query = typename HLDQManager::Query;
		using update_t = typename Update::update_t;

		HLD hld;
		LCA<graph_t> _lca;
		std::vector<DS> dsv;

		struct UStruct {
			value_t x;
			UStruct(value_t x) :x(x) {}
			void doForVertex(int hid, int v, std::vector<DS>& dsv) { Update::VertexUpdate(dsv[hid], v, x); }
			void doForRange(int hid, int l, int r, std::vector<DS>& dsv) { Update::RangeUpdate(dsv[hid], l, r, x); }
		};
		struct QStruct {
			value_t res = Monoid::E();
			void doForVertex(int hid, int id, std::vector<DS>& dsv) { res = Monoid::op(res, Query::VertexQuery(dsv[hid], id)); }
			void doForRange(int hid, int l, int r, std::vector<DS>& dsv) { res = Monoid::op(res, Query::RangeQuery(dsv[hid], l, r)); }
		};

		template<typename Struct>
		void pathImpl(int u, int v, Struct& st);

	    public:
		HLDecompositionQuery(std::vector<int> roots, const graph_t& g) :hld(roots, g), _lca(roots, g) {for (int i = 0; i<hld.size(); i++) dsv.emplace_back(hld.size(i));}
		HLDecompositionQuery(int root, const graph_t& g) :HLDecompositionQuery(std::vector<int>(1, root), g) {};

		void pathUpdate(int u, int v, value_t x) { UStruct st(x); pathImpl(u, v, st); }
		value_t pathQuery(int u, int v) { QStruct st; pathImpl(u, v, st); return st.res;}
		int lca(int u, int v) { return _lca.query(u, v);}
		int depth(int v) { return _lca.depth(v); }
		void singleUpdate(int v,typename Update::update_single_t x){ Update::SingleUpdate(dsv[hld.getHId(v)],hld.getSubId(v),x);}
	};

    template<class graph_t,class HLDQManager>
    template<typename Struct>
	void HLDecompositionQuery<graph_t,HLDQManager>::pathImpl(int u, int v, Struct& st) {
		int w = lca(u, v);
		// [u,w)
		while (u != w) {
			int to = hld.getHPar(hld.getHId(u));
            if (depth(to)<depth(w)) to = w;
			int l = hld.getSubId(u);
			int r = (hld.getHId(u) != hld.getHId(to) ? hld.size(hld.getHId(u)) : hld.getSubId(to));
			st.doForRange(hld.getHId(u), l, r, dsv);
			u = to;
		}
		// [w,w]
		st.doForVertex(hld.getHId(w), hld.getSubId(w), dsv);
		// (w,v]
		using T3 = std::tuple<int, int, int>;
		std::vector<T3> rs;
		while (v != w) {
			int to = hld.getHPar(hld.getHId(v));
			if (depth(to)<depth(w)) to = w;
            int l = hld.getSubId(v);
			int r = (hld.getHId(v) != hld.getHId(to) ? hld.size(hld.getHId(v)) : hld.getSubId(to));
			rs.push_back(T3(hld.getHId(v), r, l));
			v = to;
		}
		for (int i = (int)(rs.size()) - 1; i >= 0; i--) st.doForRange(std::get<0>(rs[i]), std::get<1>(rs[i]), std::get<2>(rs[i]), dsv);
		return;
	}
}
