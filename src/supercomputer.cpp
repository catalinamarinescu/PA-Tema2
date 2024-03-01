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
		int n, m;
		vector<int> adj[NMAX];
		vector<int> data_sets;
		vector<int> edges;
		vector<int> edges2;

		void read_input() {
			ifstream fin("supercomputer.in");
			fin >> n >> m;

			data_sets.resize(n + 1);
			for (int i = 1, y; i <= n; i++) {
				fin >> y;
				data_sets[i] = y;
			}
			edges.resize(n + 1);
			edges2.resize(n + 1);
			for (int i = 1, x, y; i <= m; i++) {
				fin >> x >> y;
				adj[x].push_back(y);
				++edges[y];
				++edges2[y];
			}
			fin.close();
		}

		int get_result() {
			return solve_bfs();
		}

		int solve_bfs() {
			// coada pentru nodurile cu setul de date 1
			queue<int> q1;

			// coada pentru nodurile cu setul de date 2
			queue<int> q2;

			// copii ale celor doua cozi pentru a putea vedea cele doua
			// posibilitati de sortare topologica
			queue<int> c1;
			queue<int> c2;

			// vectorii in care se vor realiza cele doua sortari
			vector<int> sort;
			vector<int> sort2;

			// se populeaza cozile cu nodurile care au seturile de date
			// corespunzatoare si care nu au niciun parinte
			for (int node = 1; node <= n; node++) {
				if (edges[node] == 0 && data_sets[node] == 1) {
					q1.push(node);
					c1.push(node);
				} else if (edges[node] == 0 && data_sets[node] == 2) {
					q2.push(node);
					c2.push(node);
				}
			}

			int node, node2;
			// algortimul Kahn cu BFS in cazul in care se incepe cu un nod
			// cu setul de date 1
			while (!q1.empty() || !q2.empty()) {
				while (!q1.empty()) {
					node = q1.front();
					q1.pop();
					sort.push_back(node);

					for (auto& neigh : adj[node]) {
						// se scade numarul de parinti
						edges[neigh]--;

						if (edges[neigh] == 0) {
							// se adauga vecinul in coada corespunzatoare
							// setului sau de date
							if (data_sets[neigh] == data_sets[node]) {
								q1.push(neigh);
							} else {
								q2.push(neigh);
							}
						}
					}
				}

				while (!q2.empty()) {
					node = q2.front();
					q2.pop();
					sort.push_back(node);

					for (auto& neigh : adj[node]) {
						edges[neigh]--;

						if (edges[neigh] == 0) {
							if (data_sets[neigh] == data_sets[node]) {
								q2.push(neigh);
							} else {
								q1.push(neigh);
							}
						}
					}
				}
			}

			// algortimul Kah2 cu BFS in cazul in care se incepe cu un nod
			// cu setul de date 1
			while (!c2.empty() || !c1.empty()) {
				while (!c2.empty()) {
					node2 = c2.front();
					c2.pop();
					sort2.push_back(node2);

					for (auto& neigh : adj[node2]) {
						edges2[neigh]--;

						if (edges2[neigh] == 0) {
							if (data_sets[neigh] == data_sets[node2]) {
								c2.push(neigh);
							} else {
								c1.push(neigh);
							}
						}
					}
				}

				while (!c1.empty()) {
					node2 = c1.front();
					c1.pop();
					sort2.push_back(node2);

					for (auto& neigh : adj[node2]) {
						edges2[neigh]--;

						if (edges2[neigh] == 0) {
							if (data_sets[neigh] == data_sets[node2]) {
								c1.push(neigh);
							} else {
								c2.push(neigh);
							}
						}
					}
				}
			}

			int first_cs = count_context_switches(sort);
			int second_cs = count_context_switches(sort2);

			return compare_contesxt_switches(first_cs, second_cs);
		}

		// functie care returneaza numarul mai mic de context switch-uri
		int compare_contesxt_switches(int first, int second) {
			if (first < second) {
				return first;
			}
			return second;
		}

		// functie care numara cate context switch-uri se afla
		// intr-o sortare
		int count_context_switches(vector<int> topsort) {
			int nrcs = 0;
			for (int i = 0; i <= n - 2; i++) {
				if (data_sets[topsort[i]] != data_sets[topsort[i + 1]]) {
					nrcs++;
				}
			}
			return nrcs;
		}

		void print_output(int nrcs) {
			ofstream fout("supercomputer.out");
			fout << nrcs;
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
