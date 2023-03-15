// se necesita declarar un parametro n y un vector sieve
for (int x = 2; x <= n; x++) {
  if (sieve[x]) continue;
    for (int u = 2*x; u <= n; u += x) {
      sieve[u] = x;
  }
}
