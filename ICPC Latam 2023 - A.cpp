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

//====== EN CASO DE EMERGENCIA SACAR EL COMENTARIO =======//
//#define int long long
//========================================================//
void dfs(int s, vvi& adj, vb& vis, vi& cnt, int a, int b, int p){
    if(vis[s]){
        return;
    }
    vis[s] = 1;
    cnt[s]++;
    for(int x: adj[s]){
        if(s == a && x == p){
            continue;
        }
        if(s == b && x == p){
            continue;
        }
        dfs(x, adj, vis, cnt, a, b, p);
    }
}

void solve(){
    int n;
    cin >> n;
    vvi adj(n);
    vvi adjrev(n);
    vb ans(n);
    for(int i = 0; i<n; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[i].pb(a);
        adj[i].pb(b);
        adjrev[a].pb(i);
        adjrev[b].pb(i);
    }
    for(int i = 0; i<n; i++){
        vi cnt(n);
        vb vis(n);
        vb vis2(n);
        vb vis3(n);
        dfs(adj[i][0], adjrev, vis, cnt, adj[i][0], adj[i][1], i);
        dfs(adj[i][1], adjrev, vis2, cnt, adj[i][0], adj[i][1], i);
        dfs(i, adjrev, vis3, cnt, -1, -1, -1);
        for(int j = 0; j<n; j++){
            if(cnt[j] == 3){
                ans[i] = 1;
                break;
            }
        }
    }
    for(int i = 0; i<n; i++){
        if(ans[i]){
            cout<<"Y";
        }
        else{
            cout<<"N";
        }
    }
    cout<<'\n';
    return;
}

signed main(){
    // linea magica
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //
    int tc = 1;
    //cin>>tc;
    while(tc--){
      solve();
    }
 
    return 0;
}
