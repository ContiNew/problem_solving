#include <iostream>
#include <queue>
#include <functional>
#include <algorithm>

#define ll long long
using namespace std;

struct cmp {
	bool operator() (pair<ll, ll> j1, pair<ll, ll> j2) {
		if (j1.first == j2.first) return (j1.second < j2.second); // ���԰� ������ ��ġ�� �� ���� �־��� ����
		else return (j1.first < j2.first); // ���԰� �� ���ſ� ���� �켱�� �ȴ�.
	}
};

int main() {
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, cmp> jewels;
	priority_queue<ll, vector<ll>, less<ll>> bags;
	ll n, k; // n�� ������ ����, k�� ������ ����
	ll sum = 0;
	cin >> n >> k;

	for (ll i = 0; i < n; i++) {
			ll m, v;
			cin >> m >> v;
			jewels.push(make_pair(m, v));
	}
	for (ll i = 0; i < k; i++) {
			ll c;
			cin >> c;
			bags.push(c);
	}

	for (ll i = 0; i < n; i++) {
		ll bag = bags.top();
		ll jewel = jewels.top().first;
		/*cout << "now" << endl;
		cout << "bag: " << bag << endl;
		cout << "jewel: " << jewel << endl;
		cout << "---------------" << endl;*/
		if (bag >= jewel) {
			sum += jewels.top().second;
			bags.pop();
			k--;
			/*cout << "accepted" << endl;
			cout << "bag: " << bag << endl;
			cout << "jewel: " << jewel << endl;
			cout << "jewel val: " << jewels.top().second << endl;
			cout << "sum: " << sum << endl;
			cout << "---------------" << endl;*/
		}
		jewels.pop();
		if (k == 0) break;
	}

	cout << sum;
	return 0;
}