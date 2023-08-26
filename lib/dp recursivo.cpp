int solve(int x){
	if(ready[x]) return value[x];
	int ans = 0;
	// for...
	
	value[x] = ans;
	ready[x] = true;
	return ans;
}
