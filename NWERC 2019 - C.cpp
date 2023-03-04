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

// ================================================//
// 
// ============== solucion abajo ==================//
void solve(){
    int n;
    cin >> n;
    vpi seg;
    vi peg;
    vi pcnt(n, 0);
    map<int, bool> line;
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        seg.pb({l, r});
    }
    int p;
    cin >> p;
    for(int i = 0; i < p; i++){
        int x;
        cin >> x;
        peg.pb(x);
        line[x] = 1;
    }
    int i = 0;
    int j = 0;
    if(p != 0){
        while(i < n){
            int l = seg[i].fi; int r = seg[i].se;
            while(peg[j] < l && j != p){
                j++;
            }
            if(j == p){
                break;
            }
            int cnt = 0;
            while(peg[j] < r){
                cnt++;
                j++;
                if(j == p){
                    pcnt[i] = cnt;
                    break;
                }
            }
            if(j == p){
                pcnt[i] = cnt;
                break;
            }
            if(peg[j] == r){
                cnt++;
                pcnt[i] = cnt;
                i++;
                continue;
            }
            else{
                pcnt[i] = cnt;
                i++;
            }
        }
    }
    // code works so far
    // revisar si se puede crear la respuesta
    for(int i = 0; i<n; i++){
        if(pcnt[i] > 2){
            cout<<"impossible"<<'\n';
            return;
        }
    }
    vi ans;
    // aqui empezamos a colocar los pegs, solamente si los 2 segmentos son adyacentes!!
    for(int i = 0; i < n-1; i++){
        int target = seg[i].se;
        if(pcnt[i] < 2 && pcnt[i+1] < 2 && line[target] == false){
            // verificar si los segmentos son adyacentes
            if(seg[i].se == seg[i+1].fi){
                pcnt[i]++; pcnt[i+1]++;
                line[target] == true;
                ans.pb(target);
            }
        }
    }
    // ahora colocamos los pegs que faltan
    // NO OLVIDAR REVISAR CUANDO LA RESPUESTA ES IMPOSIBLE
    for(int i = 0; i < n; i++){
        if(pcnt[i] < 2){
            int j = seg[i].se - 1; // posicion inicial para probar
            while(pcnt[i] != 2){
                if(line[j] == true){
                    j--;
                    continue;
                }
                else{
                    ans.pb(j);
                    line[j] = true;
                    pcnt[i]++;
                    j--;
                }
            }
        }
    }
    cout<<ans.size()<<'\n';
    printv(ans);
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
