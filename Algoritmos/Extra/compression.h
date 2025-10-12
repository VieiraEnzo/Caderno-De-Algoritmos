//To recover: d[arr[i]]
vector<int> d = arr;
sort(d.begin(), d.end());
d.resize(unique(d.begin(), d.end()) - d.begin());
for (int i = 0; i < n; ++i) {
    arr[i] = lower_bound(d.begin(), d.end(), arr[i]) - d.begin();
}
