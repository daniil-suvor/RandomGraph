#include "MatrixGraph.h"

double MatrixGraph::_ReabilityK_2() {
	auto [node1, node2] = GetTwoNeighbors();
	return Probability(node1, node2);
}

double MatrixGraph::_ReabilityK_3() {
	int node1 = GetFirstExistent(0);
	int node2 = GetFirstExistent(node1 + 1);
	int node3 = GetFirstExistent(node2 + 1);

	double a = Probability(node1, node2);
	double b = Probability(node2, node3);
	double c = Probability(node1, node3);

	return a * b * c + a * b * (1 - c) + a * (1 - b) * c + (1 - a) * b * c;
}


double MatrixGraph::_ReabilityK_4() {
	int node1 = GetFirstExistent(0);
	int node2 = GetFirstExistent(node1 + 1);
	int node3 = GetFirstExistent(node2 + 1);
	int node4 = GetFirstExistent(node3 + 1);

	double a = Probability(node1, node2);
	double b = Probability(node2, node3);
	double c = Probability(node3, node4);
	double d = Probability(node1, node4);
	double e = Probability(node1, node3);
	double f = Probability(node2, node4);

	double res = -6 * a * b * c * d * e * f + 4 * (a * b * c * d * e + a * b * c * d * f + a * b * c * e * f + a * b * d * e * f +
		a * c * d * e * f + b * c * d * e * f) - 3 * (a * b * c * d + b * d * e * f + a * c * e * f) -
		2 * (a * b * c * e + a * b * c * f + a * b * d * e + a * b * d * f + a * b * e * f + a * c * d * e + a * c * d * f +
			a * d * e * f + b * c * d * e + b * c * d * f + b * c * e * f + c * d * e * f) +
		a * b * c + a * b * d + a * b * f + a * c * d + a * c * e + a * c * f + a * d * e + a * e * f + b * c * d +
		b * c * e + b * d * e + b * d * f + b * e * f + c * d * f + c * e * f + d * e * f;
	return res * reability;
}

double MatrixGraph::_ReabilityK_5() {
	int node1 = GetFirstExistent(0);
	int node2 = GetFirstExistent(node1 + 1);
	int node3 = GetFirstExistent(node2 + 1);
	int node4 = GetFirstExistent(node3 + 1);
	int node5 = GetFirstExistent(node4 + 1);


	double a = Probability(node1, node2);
	double b = Probability(node1, node3);
	double c = Probability(node1, node4);
	double d = Probability(node1, node5);

	double e = Probability(node2, node3);
	double f = Probability(node2, node4);
	double g = Probability(node2, node5);

	double h = Probability(node3, node4);
	double u = Probability(node3, node5);

	double v = Probability(node4, node5);

	double k1 = 1 - (1 - e) * ((1 - f) * (1 - g) + (1 - h) * (1 - u));
	double k2 = 1 - (1 - h) * ((1 - b) * (1 - u) + (1 - c) * (1 - v));
	double k3 = 1 - (1 - v) * ((1 - f) * (1 - c) + (1 - d) * (1 - g));
	double k4 = 1 - (1 - d) * ((1 - a) * (1 - b) + (1 - g) * (1 - u));
	double k5 = 1 - (1 - a) * ((1 - b) * (1 - c) + (1 - e) * (1 - f));

	double k6 = a * h * u + a * v * (h * (1 - u) + (1 - h) * u) + (1 - a) * (1 - h) * (1 - u) * (1 - 4 * (1 - v));

	double k7 = c * d * e + e * v * (c * (1 - d) + (1 - c) * d) + (1 - d) * (1 - e) * (1 - v);

	double k8 = a * d * h + g * h * (a * (1 - d) + (1 - a) * d) + (1 - a) * (1 - h) * (1 - g);
	double k9 = a * b * v + e * v * (a * (1 - b) + (1 - a) * b) + (1 - a) * (1 - e) * (1 - v);
	double k10 = e * d * f + d * h * (e * (1 - f) + (1 - e) * f) + (1 - d) * (1 - f) * (1 - h);
	double k11 = b * f * g + b * v * (f * (1 - g) + (1 - f) * g) + (1 - b) * (1 - g) * (1 - v);
	double k12 = c * e * g + c * u * (e * (1 - g) + (1 - e) * g) + (1 - c) * (1 - e) * (1 - u);
	double k13 = b * d * f + f * u * (b * (1 - d) + (1 - b) * d) + (1 - b) * (1 - d) * (1 - f);
	double k14 = b * c * g + g * h * (c * (1 - b) + (1 - c) * b) + (1 - b) * (1 - c) * (1 - g);
	double k15 = a * c * u + f * u * (c * (1 - a) + (1 - c) * a) + (1 - c) * (1 - f) * (1 - u);

	double res = 1 -
		((1 - b) * (1 - c) * ((1 - a) * (1 - d) * k1 + (1 - f) * (1 - e) * ((1 - d) * (1 - g) * k6 + (1 - u) * (1 - v) * k8)) +
			(1 - f) * (1 - g) * ((1 - a) * (1 - e) * k2 + (1 - h) * (1 - u) * ((1 - a) * (1 - b) * k7 + (1 - c) * (1 - d) * k9)) +
			(1 - b) * (1 - h) * ((1 - e) * (1 - u) * k3 + (1 - d) * (1 - v) * ((1 - a) * (1 - f) * k12 + (1 - e) * (1 - g) * k15)) +
			(1 - c) * (1 - v) * ((1 - f) * (1 - h) * k4 + (1 - a) * (1 - g) * ((1 - b) * (1 - u) * k10 + (1 - e) * (1 - h) * k13)) +
			(1 - d) * (1 - u) * ((1 - g) * (1 - v) * k5 + (1 - a) * (1 - e) * ((1 - c) * (1 - h) * k11 + (1 - f) * (1 - v) * k14)));

	return res * reability;
}

int MatrixGraph::DanglingContraction(int node) {
	int adjacent_node;
	while (NodeDegree(node) == 1) {
		adjacent_node = GetFirst(node);
		reability *= Probability(node, adjacent_node);
		RemoveNode(node);
		node = adjacent_node;
	}
	return node;
}
int MatrixGraph::ChainContraction(int node) {
	int adjacent_node_right, adjacent_node_left;
	double p_left, p_rigth, p_new;
	while (NodeDegree(node) == 2) {
		adjacent_node_left = GetFirst(node);
		adjacent_node_right = GetLast(node);

		p_left = Probability(node, adjacent_node_left);
		p_rigth = Probability(node, adjacent_node_right);
		p_new = p_left * p_rigth / (1 - (1 - p_left) * (1 - p_rigth));
		reability *= p_rigth + p_left - p_left * p_rigth;

		Add(adjacent_node_left, adjacent_node_right, p_new);
		RemoveNode(node);
		if (NodeDegree(adjacent_node_left) == 2)
			node = adjacent_node_left;
		else
			node = adjacent_node_right;
	}
	return node;
}

int MatrixGraph::Procesing(int node) {
	if (node >= graphSize)
		return node;

	int nodeDegree = NodeDegree(node);
	while (nodeDegree == 1 || nodeDegree == 2)
	{
		if (nodeDegree == 1)
			node = DanglingContraction(node);

		if (nodeDegree == 2)
			node = ChainContraction(node);
		nodeDegree = NodeDegree(node);
	}

	return node;
}

void MatrixGraph::Preprocesing() {
	int node = 0;
	int nodeDegree = NodeDegree(node);
	while (node < graphSize)
	{
		nodeDegree = NodeDegree(node);
		if (nodeDegree == 1 || nodeDegree == 2) {
			Procesing(node);
			node = 0;
		}
		else
			node++;
	}
}

std::list<int> MatrixGraph::FindArticulation() {
	struct DFCStruct
	{
		std::list<int> children;
		std::list<int> adj_not_children;
		int dfc_in;
		int dfc_out;
	};

	std::list<int> stack;
	std::unordered_map<int, DFCStruct*> tree;

	Clear_Visited();
	int node = GetFirstExistent(0);
	int startNode = node;
	SetVisited(node);
	stack.push_back(node);
	tree[node] = new DFCStruct{ {}, {}, 1, INT_MAX };
	int dfc_num = 2;
	double probability;
	auto res = std::list<int>();
	DFCStruct* tree_node;
	int not_vist_node;
	while (!stack.empty()) {
		node = stack.back();
		stack.pop_back();
		tree_node = tree[node];
		not_vist_node = -1;
		for (auto iter = this->begin(node); iter != this->end(node); iter++) {
			if (*iter != 0) {
				if (IsVisited(iter.adjNode))
					tree_node->adj_not_children.push_back(iter.adjNode);
				else {
					not_vist_node = iter.adjNode;
					break;
				}
			}
		}

		if (not_vist_node == -1) {
			int dfc_out = INT_MAX;

			for (auto adj_node : tree_node->adj_not_children)
				dfc_out = std::min(dfc_out, tree[adj_node]->dfc_in);
			for (auto adj_node : tree_node->children)
				dfc_out = std::min(dfc_out, tree[adj_node]->dfc_out);
			tree_node->dfc_out = dfc_out;
		}
		else {
			tree_node->children.push_back(not_vist_node);
			tree[not_vist_node] = new DFCStruct{ {}, {}, dfc_num, INT_MAX };
			dfc_num++;
			this->SetVisited(not_vist_node);
			stack.push_back(node);
			stack.push_back(not_vist_node);
		}
	}
	if (tree[startNode]->children.size() > 1)
		res.push_back(startNode);
	for (auto elem : tree) {
		if (elem.first == startNode)
			continue;
		for (auto child : elem.second->children) {
			if (tree[child]->dfc_out == elem.second->dfc_in) {
				res.push_back(elem.first);
				break;
			}
		}
	}

	for (auto elem : tree)
		delete elem.second;
	Clear_Visited();
	return res;
}
