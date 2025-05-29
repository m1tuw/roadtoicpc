#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define vi vector<int>
#define vll vector<ll>
#define vvll vector<vector<ll>>
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
#define LINE deb1("=====================")
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define repr(i, a, b) for(int i = a; i>=b; i--)
#define erp(i, a, b) rep(i, a, b)
#define erpr(i, a, b) repr(i, a, b)
#define all(x) begin(x), end(x)
#define allr(x) (x).rbegin(), (x).rend()
#define pii pair<int,int>
using namespace std;
//====== EN CASO DE EMERGENCIA SACAR EL COMENTARIO =======//
#define int long long
//========================================================//
const int mod = 998244353;
int roots[24];
int invroots[24];

ll fastpow(ll a, ll b){
  a %= mod;
  ll ans=1;
  while(b > 0){
    if(b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}

ll modinv(ll x){
  return fastpow(x, mod-2);
}

vi fft(vi a, int d, bool inv){
    if(d == 0) return a;
    vi ans(1<<d);
    vi p, q;
    rep(i,0,1<<d){
        if(i%2 == 0) p.pb(a[i]);
        else q.pb(a[i]);
    }
    p = fft(p, d-1, inv);
    q = fft(q, d-1, inv);
    int w_n = inv?invroots[d]:roots[d];
    int curr = 1;
    rep(i,0,1<<(d-1)){
        int term = (curr * q[i])%mod;
        ans[i] = (p[i] + term) % mod;
        ans[i + (1<<(d-1))] = (p[i] - term + mod) % mod;
        curr *= w_n;
        curr %= mod;
    }
    return ans;
}

void solve(){
    roots[23] = fastpow(3, 119);
    invroots[23] = modinv(roots[23]);
    repr(i,22,0){
        roots[i] = roots[i+1]*roots[i+1];
        roots[i] %= mod;
        invroots[i] = modinv(roots[i]);
    }
    int n, m;
    cin >> n >> m;
    vi a(n);
    vi b(m);
    rep(i,0,n) cin >> a[i];
    rep(i,0,m) cin >> b[i];
    int pow2 = 1;
    int lg2 = 0;
    while(pow2 < max(n, m)){
        pow2 <<= 1LL;
        lg2++;
    }
    pow2*=2;
    lg2++;
    a.resize(pow2, 0);
    b.resize(pow2, 0);

    a = fft(a, lg2, 0);
    b = fft(b, lg2, 0);

    vi c(pow2);
    rep(i,0,pow2) c[i] = a[i] * b[i];
    rep(i,0,pow2) c[i] %= mod;

    c = fft(c, lg2, 1);
    
    int inv = modinv(pow2);
    c.resize(n+m-1);
    rep(i,0,pow2) c[i] *= inv;
    rep(i,0,pow2) c[i] %= mod;

    printv(c);
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
