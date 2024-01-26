const int maxn = 200010;
int n;
vector<int> adj[maxn];
int subtree_size[maxn];

// usar get_subtree_size dsp de armar adj
// y luego get_centroid

int get_subtree_size(int node, int parent = -1){
	int &res = subtree_size[node];
	res = 1;
	for (int i : adj[node]){
		if (i == parent) { continue };
		res += get_subtree_size(i, node);
	}
	return res;
}

int get_centroid(int node, int parent = -1){
	for (int i : adj[node]) {
		if (i == parent) { continue };
		if (subtree_size[i] * 2 > n) { return get_centroid(i, node); }
	}
	return node;
}
