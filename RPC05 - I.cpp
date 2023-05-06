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
#define mod 998244353 // cambiar sg el problema
#define LINE deb1("=====================")
using namespace std;
//====== EN CASO DE EMERGENCIA SACAR EL COMENTARIO =======//
#define int long long
//========================================================//
vi di = {0, 1, 0, 1};
vi dj = {0, 0, 1, 1};
void solve(){
    vi pow2 = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    vb used(1e8, 0);
    int n;
    cin>>n;
    int x = pow2[n];
    vvi grid(x, vi(x, 0));
    vvb vis(x, vb(x, 0));
    for(int i = 0; i<x; i++){
        for(int j = 0; j<x; j++){
            cin>>grid[i][j];
        }
    }
    for(int i = 0; i<x-1; i++){
        for(int j = 0; j<x-1; j++){
            //printm(vis);
            map<int,int> m;
            // 
            for(int k = 0; k<4; k++){
                // saltarse casillas usadas
                if(!vis[i+di[k]][j+dj[k]]){
                    // si el color esta usado y la casilla esta libre, printear -1
                    if(used[grid[i+di[k]][j+dj[k]]]){
                        cout<<0<<'\n';
                        return;
                    }
                    // de lo contrario, añadirlo a la cuenta
                    m[grid[i+di[k]][j+dj[k]]]++;
                }
            }
            // contar colores y marcar (solo se cuentan casillas libres)
            int color = 0;
            for(auto p: m){
                if(p.se == 3){
                    int color = p.fi;
                    for(int k = 0; k<4; k++){
                        if(grid[i+di[k]][j+dj[k]] == color){
                            vis[i+di[k]][j+dj[k]] = 1;
                        }
                    }
                    used[p.fi] = 1;
                }
                if(p.se == 4){
                    cout<<0<<'\n';
                    return;
                }
            }
        }
    }
    // ultima vuelta
    if(used[0]){
        cout<<0<<'\n';
        return;
    }
    bool ok = false;
    for(int i = 0; i<x; i++){
        for(int j = 0; j<x; j++){
            if(!vis[i][j]){
                if(ok){
                    cout<<0<<'\n';
                    return;
                }
                if(grid[i][j] != 0){
                    cout<<0<<'\n';
                    return;
                }
                if(grid[i][j] == 0){
                    ok = true;
                }
            }
        }
    }
    cout<<1<<'\n';
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
