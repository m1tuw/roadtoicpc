// definir mod arriba

ll fastpow(ll a, ll b){
    a %= mod;
    ll ans = 1;
    while(b>0){
        if(b & 1){
            ans = ans * a % mod;
        }
        a = a * a % mod;
        b>>=1;
    }
    return ans;
}
ll modinv(ll x){
    return fastpow(x, mod-2);
}
ll c(int n, int k){
    int up = 1;
    for(int i = n; i>k; i--){
        (up*=i)%=mod;
    }
    int down = 1;
    for(int i = n-k; i>1; i--){
        (down*=i)%=mod;
    }
    return (up*modinv(down))%mod;
}
