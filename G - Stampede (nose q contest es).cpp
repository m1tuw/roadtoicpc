#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define fi first
#define se second
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpi vector<pair<int,int>>
#define vb vector<bool>
#define vvb vector<vector<bool>>
#define mp make_pair
#define ld long double
#define printv(v) for(auto x: v){cout<<x<<" ";}cout<<endl
#define printm(v) for(auto w: v){printv(w);}cout<<endl
#define deb1(s) cout<<s<<endl
#define deb2(s, s2) cout<<s<<" "<<s2<<endl
#define deb3(s, s2, s3) cout<<s<<" "<<s2<<" "<<s3<<endl
#define all(x) begin(x), end(x)
#define mod 998244353 // cambiar sg el problema
#define LINE deb1("=====================")
using namespace std;

struct Dinic {
	const bool SCALING = false;
	const ll K = 1; // K maximo tal que 2^K <= capacidad maxima
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

int tc = 1;

vi di = {0, -1, 0, 1};
vi dj = {-1, 0, 1, 0};

int id(int i, int j, int t, int n){ // 0 based indexing
	return t*n*n + i + (j*n) + 1;
}

int nodes = 1e6;

bool solve(){
	int n;
	cin >> n;
	if(n == 0) return true;
	vector<vector<bool>> grid(n, vector<bool>(n, 0));
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			char c;
			cin >> c;
			if(c == 'X') grid[i][j] = 1;
		}
	}
	// build a graph st source node is 0, max amount of time will be bounded by nxn so we will want our nodes to go like this
	int maxflow = 0;
	// sink = n⁴ + 1
	Dinic network(nodes);	
	
	vector<vector<bool>> toggled(n, vector<bool>(n)); // note the 1-based indexing
	
	for(int i = 0; i<n; i++){
		network.add_edge(0, i+1, 1);
		toggled[i][0] = 1;
	}
	// add edges from each layer top down
	for(int time = 0; time<n*n; time++){
		for(int i = 0; i<n; i++){
			network.add_edge(id(i, n-1, time, n), id(i, n-1, time+1, n), 1);
			//deb1(id(i, n-1, time, n));
		}
	}
	// add edges from last layer to the sink
	for(int i = 0; i<n; i++){
		network.add_edge(id(i, n-1, n*n, n), nodes-1, 1);
	}
	int t = 1;
	
	//deb2(id(n-1, n-1, n*n, n), nodes-1);
	
	stack<pair<int,int>> toggle_next;
	while(maxflow < n){
		// build the next layer and check flow
		// from all toggled nodes, add 
		for(int i = 0; i<n; i++){
			for(int j = 0; j<n; j++){
				if(toggled[i][j]){ // toggle all adjacent cells
					for(int k = 0; k<4; k++){
						if(i+di[k] < 0 || i+di[k] >= n || j+dj[k] < 0 || j+dj[k] >= n) continue;
						if(grid[i+di[k]][j+dj[k]]) continue; // check if there's an obstacle
						network.add_edge(id(i, j, t-1, n), id(i+di[k], j+dj[k], t, n), 1);
						toggle_next.push({i+di[k], j+dj[k]});
					}
					network.add_edge(id(i, j, t-1, n), id(i, j, t, n), 1);
				}
			}
		}
		while(!toggle_next.empty()){
			auto p = toggle_next.top();
			toggle_next.pop();
			toggled[p.fi][p.se] = 1;
		}
		//printm(toggled);
		maxflow += network.flow(0, nodes-1);
		//deb3("t, maxfloW:",t, maxflow);
		
		t++;
	}
	cout << "Case " <<tc<<": "<< t-1 << '\n';
	tc++;
	return false;
}
 
signed main(){
    // linea magica
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //
    while(true){
    	if(solve()) break;
    }
    return 0;
}
