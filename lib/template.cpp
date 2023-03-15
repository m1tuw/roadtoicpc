#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpi vector<pair<int,int>>
#define vb vector<bool>
#define mp make_pair
#define ld long double
#define printv(v) for(auto x: v){cout<<x<<" ";}cout<<'\n'
#define deb1(s) cout<<s<<endl
#define deb2(s, s2) cout<<s<<" "<<s2<<endl
#define deb3(s, s2, s3) cout<<s<<" "<<s2<<" "<<s3<<endl
#define mod 998244353 // cambiar sg el problema
#define LINE deb1("=====================")
using namespace std;
//====== EN CASO DE EMERGENCIA SACAR EL COMENTARIO =======//
//#define int long long
//========================================================//
// for grid problems

vi di = {0, -1, 0, 1};
vi dj = {-1, 0, 1, 0};
string ds = "LURD";

/* int n,m;
bool possible(int i, int j){
    return (i<n&&i>=0&&j<m&&j>=0);
} */
// for edge lists or similar
]
struct edge{
    int a,b,cost;
};

// integer log base 2 (floor)
ll log2f(ll x){
    return x ? __builtin_clzll(1) - __builtin_clzll(x) : -1;
}

// ============= funciones utiles =================//
// 
// ============== solucion abajo ==================//
void solve(){
    
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
