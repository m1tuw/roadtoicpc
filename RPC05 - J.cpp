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
    int n;
    int totalsum = 0;
    cin >> n;
    vi v(n);
    for(int i = 0; i<n; i++){
        cin >> v[i];
        totalsum += v[i];
    }
    vi ans;
    vi v2 = v;
    reverse(v2.begin(), v2.end());
    
    int sum = totalsum;

    vvb dp(n+1, vb(totalsum+1, 0));
    vvb dp2(n+1, vb(totalsum+1, 0));
    // dp[i][j] = 1 si es posible armar j usando los primeros i
    for(int i = 0; i<n+1; i++){
        dp[i][0] = 1;
        dp2[i][0] = 1;
    }
    dp[0][v[0]] = 1;
    dp2[0][v2[0]] = 1;
    for(int i = 1; i<n+1; i++){
        for(int j = 1; j<=totalsum; j++){
            dp[i][j] = dp[i-1][j] || (j-v[i]>=0 ? dp[i-1][j-v[i]]: 0);
            dp2[i][j] = dp2[i-1][j] || (j-v2[i]>=0 ? dp2[i-1][j-v2[i]]: 0);
        }
    }
    sum = totalsum - v[0];
    if(sum%2 == 0){
        if(dp2[n-2][sum/2]){
            ans.pb(1);
        }
    }

    sum = totalsum - v[n-1];
    if(sum%2 == 0){
        if(dp[n-2][sum/2]){
            ans.pb(n);
        }
    }
    for(int k = 1; k<n-1; k++){
        sum = totalsum - v[k];
        if(sum%2 == 1){
            continue;
        }
        for(int i = 0; i<totalsum; i++){
            if(sum/2 - i < 0){
                break;
            }
                if(dp[k-1][sum/2 - i] && dp2[n-k-2][i]){
                    ans.pb(k+1);
                    break;
                }       
        }
    }

    cout<<ans.size()<<'\n';
    sort(ans.begin(), ans.end());
    for(int i = 0; i<ans.size()-1; i++){
        cout<<ans[i]<<" ";
    }
    cout<<ans[ans.size()-1]<<'\n';
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
