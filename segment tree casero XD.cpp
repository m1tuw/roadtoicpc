#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define vll vector<ll>
#define vvll vector<vector<ll>>
#define vpll vector<pair<ll,ll>>
#define spll set<pair<ll,ll>>
#define vi vector<int>
#define vvi vector<vector<int>>
#define mp make_pair
#define ld long double
// debugging macros
#define printv(v) for(auto x: v){cout<<x<<" ";}cout<<'\n'
#define deb1(s) cout<<s<<'\n'
#define deb2(s, s2) cout<<s<<" "<<s2<<'\n'
#define deb3(s, s2, s3) cout<<s<<" "<<s2<<" "<<s3<<'\n'
//====EN CASO DE EMERGENCIA SACAR EL COMENTARIO====//
#define int long long
//=================================================//
using namespace std;
int mod = 998244353;

struct edge{
    int a,b,cost;
};

ll log2f(ll x){
    return x ? __builtin_clzll(1) - __builtin_clzll(x) : -1;
}
ll log2c(ll x){
    if(x&(x-1)){
        return log2f(x) + 1;
    }
    else{
        return log2f(x);
    }
}

// =================================================
int merge(int a, int b){
    return min(a,b);
}

int query(int L, int R, vector<int>& tree, int s){
    // queries por índice (L,R 0-based)
    int ans = 1e17; // cambiar por el neutro
    L+=s; R+=s;
    while(L<=R){
        if(L%2 == 1){
            ans = merge(ans,tree[L++]);
        }
        if(R%2 == 0){
            ans = merge(ans,tree[R--]);
        }
        L/=2;
        R/=2;
    }
    return ans;
}

void update(int i, int val, vector<int>& tree, int s){
    // i esta en 0 based
    i+=s;
    tree[i] = val;
    while(i!=0){
        int j = i;
        i>>=1;
        if(i==0){
            break;
        }
        if(j%2==1){
            tree[i]=merge(tree[j], tree[j-1]);
        }
        else{
            tree[i]=merge(tree[j], tree[j+1]);
        }
    }
}
// =================================================

void solve(){

    int n,q;
    cin>>n>>q;
    vector<int> v(n);
    for(int i = 0; i<n; i++){
        cin>>v[i];
    }
    int s = 1<<log2c(n);
    vector<int> tree(2*s, 0);
    for(int i = s; i<tree.size(); i++){
        if(s-i<n){
            tree[i] = v[i-s];
        }
    }

    int j = s;
    int i = j/2;

    int a,b;
    for(int w = s/2; w>0; w>>=1){
        a = i; b = j;
        for(int k = 0; k<w; k++){
            //deb3(i,j,w);
            tree[i] = merge(tree[j], tree[j+1]);
            i++;
            j+=2;
        }
        i = a/2; j = b/2;
    }
    // process L,R query
    while(q--){
        int t,L,R;
        cin>>t>>L>>R;
        if(t==2){
            L--; R--;
            cout<<query(L,R,tree,s)<<'\n';
        }
        else{
            L--;
            update(L, R, tree, s);
        }
    }
}

signed main(){
    // línea magica
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
