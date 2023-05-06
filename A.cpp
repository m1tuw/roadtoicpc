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
    int n, k;
    cin >> n >> k;
    vector<double> v(n);
    for(int i = 0; i<n; i++){
        cin>>v[i];
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    vector<vector<double>> dp(2*n + 1, vector<double>(n + 1, 0));
    int id = n;
    // base cases
    dp[id-1][1] = v[0];
    dp[id+1][1] = 1 - v[0];
    for(int j = 2; j<=n; j++){
        for(int i = 0; i<2*n + 1; i++){ // dp[i][id] = 0 points
            dp[i][j] += (i+1 < 2*n + 1 ? dp[i+1][j-1]*v[j-1] : 0) + (i-1 >= 0 ? dp[i-1][j-1]*(1-v[j-1]) : 0); // check for out of bounds
        }
    }
    //printm(dp);
    //LINE;
    double ans = 0;
    double sum;
    for(int j = 1; j<=n; j++){
        sum = 0;
        for(int i = 0; i<=n-k; i++){
            sum+=dp[i][j];
        }
        //deb1(sum);
        ans = max(ans, sum);
    }
    cout<<setprecision(8);
    cout<<ans<<'\n';
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