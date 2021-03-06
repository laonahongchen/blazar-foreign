struct Data { double x, y; };
double sqr(double x) { return x * x; }
double dis(Data a, Data b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)); }
int n; Data p[N], q[N];
double solve(int l, int r) {
	if(l == r) return 1e18;
	if(l + 1 == r) return dis(p[l], p[r]);
	int m = (l + r) / 2;
	double d = min(solve(l, m), solve(m + 1, r));
	int qt = 0;
	for(int i = l; i <= r; i++)
		if(fabs(p[m].x - p[i].x) <= d)
			q[++qt] = p[i];
	sort(q + 1, q + qt + 1, [&](const Data &a, const Data &b) { return a.y < b.y; });
	for(int i = 1; i <= qt; i++) {
		for(int j = i + 1; j <= qt; j++) {
			if(q[j].y - q[i].y >= d) break;
			d = min(d, dis(q[i], q[j]));
		}
	}
	return d;
}
