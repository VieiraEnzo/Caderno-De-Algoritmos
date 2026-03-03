//BIT - Range Update

vector<int> bit1, bit2;
void init(int n){
	bit1.assign(n+1, 0);
	bit2.assign(n+1, 0);
}

int rsq(vector<int> &bit, int i){
	int ans = 0;
	for(; i; i-=i&-i)
		ans += bit[i];
	return ans;
}

void update(vector<int> &bit, int i, int v){
	for(; i < bit.size(); i+=i&-i)
		bit[i] += v;
}

void update(int i, int j, int v){
	update(bit1, i, v);
	update(bit1, j+1, -v);
	update(bit2, i, v*(i-1));
	update(bit2, j+1, -v*j);	
}

int rsq(int i){
	return rsq(bit1, i)*i - rsq(bit2, i);
}

int rsq(int i, int j){
	return rsq(j) - rsq(i-1);
}
