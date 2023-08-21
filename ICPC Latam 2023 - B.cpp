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

// lineContainer
struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

// segment tree
template <class T>
struct SegmentTree{
  int N;
  vector <T> tree;
  SegmentTree(int _N){
    N = _N;
    tree.resize(4*N);
    build(0, 0, N-1);
  }

  SegmentTree(vector<T> &init) {
    N = init.size();
    tree.resize(4*N);
    build(0, 0, N-1, init);
  }

  T merge(T a, T b){ // Reemplazar esta funcion para determinar como juntar dos nodos para obtener el valor de su padre, en este caso es suma
    // si tenemos 2 line containers, el nuevo debera todas las lineas de los otros 2
    T ret = a; // pair<LineContainer, vector<pair<int,int>>>
    // mergear las listas
    for(auto x: b.se){
        ret.se.pb(x);
    }
    // buildeamos el lc nuevo
    LineContainer newlc;
    for(auto x: ret.se){
        newlc.add(x.fi, x.se);
    }
    ret.fi = newlc;
    return ret;
  }
  
  void build(int n, int i, int j){
    if(i == j){
      tree[n] = 0;
      return;
    }
    int mid = (i+j)/2;
    build(2*n+1, i, mid);
    build(2*n+2, mid+1, j);
    tree[n] = merge(tree[2*n+1], tree[2*n+2]);
  }

  void build(int n, int i, int j, vector<T> &init){
    if(i == j){
      tree[n] = init[i];
      return;
    }
    int mid = (i+j)/2;
    build(2*n+1, i, mid, init);
    build(2*n+2, mid+1, j, init);
    tree[n] = merge(tree[2*n+1], tree[2*n+2]);
  }

  int query(int l, int r, int x){
    return query(0, 0, N-1, l, r, x);
  }

  int query(int n, int i, int j, int l, int r, int x){
    if(l <= i && j <= r) return tree[n].fi.query(x);
    int mid = (i+j)/2;
    if(mid < l || r < i)
      return query(2*n+2, mid+1, j, l, r, x);
    if(j < l || r < mid+1)
      return query(2*n+1, i, mid, l, r, x);
    return max(
        query(2*n+1, i, mid, l, r, x),
        query(2*n+2, mid+1, j, l, r, x));
  }

  void update(int t, T val){
    update(0, 0, N-1, t, val);
  }
  
  void update(int n, int i, int j, int t, T val){
    if(t < i || j < t) return;
    if(i == j){
      tree[n] = val;
      return;
    }
    int mid = (i+j)/2;
    update(2*n+1, i, mid, t, val);
    update(2*n+2, mid+1, j, t, val);
    tree[n] = merge(tree[2*n+1], tree[2*n+2]);
  }

  int search(int from, T val){
    if(!from) return search(0, 0, N-1, val);
    return search(0, 0, N-1, val+query(0, from-1));
  }

  int search(int n, int i, int j, T val){
    if(tree[n] < val) return -1;
    if(i==j && tree[n] >= val) return i;
    int mid = (i+j)/2;
    if(tree[2*n+1] >= val) return search(2*n+1, i, mid, val);
    else return search(2*n+2, mid+1, j, val-tree[2*n+1]);
  }
};

void solve(){
    int t, p;
    cin >> t;
    vi x(t);
    vi y(t);
    for(int i = 0; i<t; i++){
        cin >> x[i];
        cin >> y[i];
    }    
    cin >> p;
    // guardar coeficientes y = ax + b
    vi a(p);
    vi b(p);

    vector<pair<LineContainer, vector<pair<int,int>>>> lcv;

    for(int i = 0; i<p; i++){
        cin >> a[i];
        cin >> b[i];

        LineContainer lc;

        pair<LineContainer, vector<pair<int,int>>> xd;

        lc.add(a[i], b[i]);

        xd.fi = lc;
        xd.se = {{a[i], b[i]}};

        lcv.pb(xd);
    }

    vector<vector<int>> ans(p);

    // armar el segment tree
    SegmentTree<pair<LineContainer, vector<pair<int,int>>>> st(lcv);

    // iteramos sobre todas las fichas
    for(int i = 0; i<t; i++){
        // revisamos primero que la ficha esté en algún subárbol
        if(st.query(0, p-1, x[i]) <= y[i]){
            continue;
        }
        int l = 0;
        int r = p-1;
        //deb2(l, r);
        while(l < r){
            int mid = (l+r)/2;
            //deb3("query: ",st.query(l, mid, x[i]), y[i]);
            if(st.query(l, mid, x[i]) > y[i]){
                r = mid;
            }
            else{
                l = mid + 1;
            }
        }
        ans[l].pb(i+1);
    }
    for(auto v: ans){
        cout << v.size() << " ";
        for(int x: v){
            cout << x << " ";
        }
        cout << '\n';
    }
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
