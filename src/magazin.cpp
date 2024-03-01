#include <bits/stdc++.h>
using namespace std;

class Task {
	public:
	void solve() {
		read_input();
		print_output(get_result());
	}

	private:
	static constexpr int NMAX = (int)1e5 + 5;
	int n, q, nr = 0;
	vector<int> adj[NMAX];
	vector<int> deposits;
	vector<int> steps;

	void read_input() {
		ifstream fin("magazin.in");
		fin >> n >> q;

		for (int i = 1; i < n; ++i) {
			int parent;
			fin >> parent;
			adj[parent].push_back(i + 1);
		}

		deposits.resize(q);
		steps.resize(q);

		for (int i = 0; i < q; i++) {
			fin >> deposits[i] >> steps[i];
		}
		fin.close();
	}

	vector<int>  get_result() {
		return solve_pb();
	}

	vector<int> solve_pb() {
		vector<int> sort;
		vector<int> result;
		vector<int> visited(n + 1, 0);
		vector<int> sub_tree(n + 1, 0);
		vector<int> position(n + 1, 0);

		// algoritmul DFS pornind de la primul nod
		dfs(1, visited, sort, sub_tree, position);

		for (int i = 0; i < q; i++) {
			// pozitia depozitului de unde se va pleca
			// in vectorul sortat cu DFS
			int index = position[deposits[i]];

				// conditia pentru a se putea realiza parcurgerea
				// in mod corect, nu se poate parcurge mai mult
				// decat numarul de noduri din subgraf-ul nodului
				// curent
				if (steps[i] <= (sub_tree[deposits[i]] - 1)) {
					result.push_back(sort[index + steps[i]]);
				} else {
					result.push_back(-1);
				}
		}

		return result;
	}

	// functie pentru algoritmul DFS
	void dfs(int node, vector<int>& visited, vector<int>& sort,
			vector<int>& sub_tree, vector<int>& position) {
		// se marcheaza faptul ca nodul a fost vizitat
		visited[node] = 1;
		sort.push_back(node);

		// se retine pozitia nodului curent in vectorul sort
		position[node] = sort.size() - 1;
		sub_tree[node] = 1;

		for (auto& neigh : adj[node]) {
			if (!visited[neigh]) {
				dfs(neigh, visited, sort, sub_tree, position);
				sub_tree[node] += sub_tree[neigh];
			}
		}
	}

	void print_output(vector<int>  result) {
		ofstream fout("magazin.out");
		for (auto node : result) {
			fout << node << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main() {
	auto* task = new (nothrow) Task();
	if (!task) {
		return -1;
	}

	task->solve();
	delete task;
	return 0;
}
