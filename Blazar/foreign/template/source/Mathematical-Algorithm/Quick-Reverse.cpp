long long inverse(const long long &x, const long long &mod) {
	if (x == 1) {
		return 1;
	} else {
		return (mod - mod / x) * inverse(mod % x, mod) % mod;
	}
}
