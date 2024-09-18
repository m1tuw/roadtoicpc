// binomial_coefficients bc(maxn, mod)
struct binomial_coefficients{
    int MAXN, mod;
    vi fact;
    vi invfact;
    binomial_coefficients(int MAXN, int mod): MAXN(MAXN), mod(mod) {
        fact.resize(MAXN+1);
        invfact.resize(MAXN+1);
        fact[0] = 1;
        rep(i,1,MAXN+1) fact[i] = (i*fact[i-1])%mod;
        int ans = 1;
        int a = fact[MAXN];
        int b = mod-2;
        while(b>0){
            if(b&1) ans=ans*a%mod;
            a=a*a%mod;
            b>>=1;
        }
        invfact[MAXN]=ans;
        repr(i,MAXN-1,0) invfact[i]=(invfact[i+1]*(i+1))%mod;
        invfact[0] = 1;
    }
    int c(int n, int k){
        if(n<k) return 0;
        int dw = (invfact[n-k]*invfact[k])%mod;
        int up = fact[n];
        return (dw*up)%mod;
    }
};
