const int N = 40005;
const int M = 100005;
const int LOGN = 17;

int n, m;, w[N];
vector<int> g[N];
int bid[N << 1];

struct Query {
	int l, r, extra, i;
	friend bool operator < (const Query &a, const Query &b) {
		if(bid[a.l] != bid[b.l])
			return bid[a.l] < bid[b.l];
		return a.r < b.r;
	}
} q[M];

int idx;
int st[N], ed[N];
int fa[N][LOGN], dep[N];
int col[N << 1], id[N << 1];

void dfs(int x, int p) {
	col[st[x] = ++idx] = w[x];
	id[st[x]] = x;
	// maintain fa[], dep[] for lca
	for(auto y: g[x])
		if(y != p)
			dfs(y, x);
	col[ed[x] = ++idx] = w[x];
	id[ed[x]] = x;
}
int lca(int x, int y); // normal lca
void prepare() {
	idx = 0;
	dfs(1, 0);
	int BS = (int)sqrt(idx + 0.5);
	for(int i = 1; i <= idx; i++)
		bid[i] = (i + BS - 1) / BS;
	for(int i = 1; i <= m; i++)
	{
		int a = q[i].l;
		int b = q[i].r;
		int c = lca(a, b);
		if(st[a] > st[b]) swap(a, b);
		if(c == a) {
			q[i].l = st[a];
			q[i].r = st[b];
			q[i].extra = 0;
		} else {
			q[i].l = ed[a];
			q[i].r = st[b];
			q[i].extra = c;
		}
	}
	sort(q + 1, q + m + 1);
}

int curans;
int ans[M];
int cnt[N];
bool state[N];

void rev(int x) {
	int &c = cnt[col[x]];
	curans -= !!c;
	c += (state[id[x]] ^= 1) ? 1 : -1;
	curans += !!c;
}
void solve() {
	prepare();
	curans = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(state, 0, sizeof(state));

	int l = 1, r = 0;
	for(int i = 1; i <= m; i++) {
		while(l < q[i].l) rev(l++);
		while(l > q[i].l) rev(--l);
		while(r < q[i].r) rev(++r);
		while(r > q[i].r) rev(r--);
		if(q[i].extra) rev(st[q[i].extra]);
		ans[q[i].i] = curans;
		if(q[i].extra) rev(st[q[i].extra]);
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}
