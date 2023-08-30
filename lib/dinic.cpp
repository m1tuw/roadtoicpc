// dinic (oliva)
struct Dinic {
	const bool SCALING = false;
	const ll K = 30; // K maximo tal que 2^K <= capacidad maxima
	struct FlowEdge {
		int u, v;
		ll cap, flow = 0;
		FlowEdge(int u, int v, ll cap) : u(u), v(v), cap(cap) {}
	};
	const ll flow_inf = 1e18;
	vector<FlowEdge> edges;
	vector<vector<int>> adj;
	int n, m = 0;
	int s, t;
	vector<int> level, ptr;
	queue<int> q;
	Dinic(int n) : n(n) {
		adj.resize(n);
		level.resize(n);
		ptr.resize(n);
	}
	void add_edge(int u, int v, ll cap) {
		edges.emplace_back(u, v, cap);
		edges.emplace_back(v, u, 0 /* cap si bidireccional */);
		adj[u].push_back(m);
		adj[v].push_back(m + 1);
		m += 2;
	}
	ll LIM = 1;
	bool bfs() {
		while (!q.empty() && level[t] == -1) {
			int u = q.front();
			q.pop();
			for (int id : adj[u]) {
				if (edges[id].cap - edges[id].flow < LIM || level[edges[id].v] != -1)
					continue;
				level[edges[id].v] = level[u] + 1;
				q.push(edges[id].v);
			}
		}
		return level[t] != -1;
	}
	ll dfs(int u, ll pushed) {
		if (pushed == 0)
			return 0;
		if (u == t)
			return pushed;
		for (int& cid = ptr[u]; cid < (int)adj[u].size(); cid++) {
			int id = adj[u][cid];
			int v = edges[id].v;
			if (level[u] + 1 != level[v] || edges[id].cap - edges[id].flow == 0)
				continue;
			ll tr = dfs(v, min(pushed, edges[id].cap - edges[id].flow));
			if (tr == 0)
				continue;
			edges[id].flow += tr;
			edges[id ^ 1].flow -= tr;
			return tr;
		}
		return 0;
	}
	ll flow(int s, int t) {
		this->s = s; this->t = t;
		ll ans = 0;
		for(LIM = (SCALING ? 1LL<<K : 1); LIM > 0; LIM >>= 1) {
			while (true) {
				fill(level.begin(), level.end(), -1);
				level[s] = 0;
				q = queue<int>(); q.push(s);
				if (!bfs()) break;
				fill(ptr.begin(), ptr.end(), 0);
				while (ll pushed = dfs(s, flow_inf)) {
					ans += pushed;
				}
			}
		}
		return ans;
	}
	void reset() {
		for(FlowEdge &e : edges) e.flow = 0;
	}
};
