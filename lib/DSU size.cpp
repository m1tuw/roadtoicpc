#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define vll vector<ll>
#define vvll vector<vector<ll>>
#define vpll vector<pair<ll,ll>>
#define spll set<pair<ll,ll>>
#define mp make_pair
#define int long long
using namespace std;

// ===== DSU con unión segun el tamaño de los árboles =====
// modificar sg el limite del problema
vector<int> parent(1e5+1, 0);
vector<int> sizes(1w5+1, 0);

int find_set(int v){
    if(v==parent[v]){
        return v;
    }
    parent[v]=find_set(parent[v]);
    return parent[v];
}

void union_sets(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a!=b){
        if(sizes[b]>sizes[a]){
            swap(a,b);
        }
        parent[b]=a;
        sizes[a]+=sizes[b];
    }
}

void make_set(int v){
    parent[v]=v;
    sizes[v]=1;
}
// =======================================================

signed main(){
    // línea magica
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //


return 0;
}
