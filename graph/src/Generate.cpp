#include "Graph.h"

void Graph::GenKN(int n, double probability) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++)
			this->Add(i, j, probability);
	}
}

void Graph::Grid(int n, int m, double probability) {
	for (int i = 1; i < n; i++)
		this->Add(i - 1, i, probability);

	for (int j = 1; j < m; j++) {
		this->Add((j - 1) * n, j * n, probability);
		for (int i = 1; i < n; i++) {
			this->Add(j * n + i, (j - 1) * n + i, probability);
			this->Add(j * n + i, j * n + i - 1, probability);
		}
	}
}

void Graph::LinkGrid(int n, int m, int link, double probability) {
	this->Grid(n, 2 * m, probability);
	for (int i = 0; i < n - link; i++)
		this->RemoveEdge(n * (m - 1) + i, n * m + i);
}
