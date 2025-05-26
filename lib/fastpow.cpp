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
