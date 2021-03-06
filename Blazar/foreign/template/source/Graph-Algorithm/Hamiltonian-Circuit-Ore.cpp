int left[N], right[N], next[N], last[N];
void cover(int x) {
	left[right[x]] = left[x];
	right[left[x]] = right[x];
}
int adjacent(int x) {
	for (int i = right[0]; i <= n; i = right[i]) {
		if (graph[x][i]) {
			return i;
		}
	}
	return 0;
}
std::vector<int> solve() {
	for (int i = 1; i <= n; ++i) {
		left[i] = i - 1;
		right[i] = i + 1;
	}
	int head, tail;
	for (int i = 2; i <= n; ++i) {
		if (graph[1][i]) {
			head = 1;
			tail = i;
			cover(head);
			cover(tail);
			next[head] = tail;
			break;
		}
	}
	while (true) {
		int x;
		while (x = adjacent(head)) {
			next[x] = head;
			head = x;
			cover(head);
		}
		while (x = adjacent(tail)) {
			next[tail] = x;
			tail = x;
			cover(tail);
		}
		if (!graph[head][tail]) {
			for (int i = head, j; i != tail; i = next[i]) {
				if (graph[head][next[i]] && graph[tail][i]) {
					for (j = head; j != i; j = next[j]) {
						last[next[j]] = j;
					}
					j = next[head];
					next[head] = next[i];
					next[tail] = i;
					tail = j;
					for (j = i; j != head; j = last[j]) {
						next[j] = last[j];
					}
					break;
				}
			}
		}
		next[tail] = head;
		if (right[0] > n) {
			break;
		}
		for (int i = head; i != tail; i = next[i]) {
			if (adjacent(i)) {
				head = next[i];
				tail = i;
				next[tail] = 0;
				break;
			}
		}
	}
	std::vector<int> answer;
	for (int i = head; ; i = next[i]) {
		if (i == 1) {
			answer.push_back(i);
			for (int j = next[i]; j != i; j = next[j]) {
				answer.push_back(j);
			}
			answer.push_back(i);
			break;
		}
		if (i == tail) {
			break;
		}
	}
	return answer;
}
