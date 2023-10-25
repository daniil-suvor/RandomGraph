#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int graphSize) : Graph() {
	this->graphSize = graphSize;
	this->arraySize = graphSize * (graphSize + 1) / 2;
	nodes = new double[arraySize]();
}

MatrixGraph::~MatrixGraph() {
	delete [] nodes;
}

MatrixGraph::MatrixGraph(const MatrixGraph& graph) {
	this->iteration = graph.iteration;
	this->graphSize = graph.graphSize;
	this->reability = graph.reability;
	this->nodeNumbers = graph.nodeNumbers;
	this->arraySize = graph.arraySize;
	this->nodes = new double[arraySize]();
	std::memcpy(nodes, graph.nodes, sizeof(double) * arraySize);
}

bool MatrixGraph::ContainsNode(int node) {
	return Get(node, node) != 0;
}

double MatrixGraph::Probability(int node1, int node2) {
	return Get(node1, node2);
}

int MatrixGraph::Index(int i, int j) {
	if (j > i)
		return (graphSize * i - (i * (i + 1)) / 2 + j);
	else
		return (graphSize * j - (j * (j + 1)) / 2 + i);
}
double MatrixGraph::Get(int i, int j) {
	if (i >= graphSize || j >= graphSize)
		return 0.0;
	return nodes[Index(i, j)];
}

void MatrixGraph::Set(int i, int j, double p) {
	if (i >= graphSize || j >= graphSize)
		return;
	nodes[Index(i, j)] = p;
}

int MatrixGraph::NodeDegree(int node) {
	int degree = static_cast<int>(Get(node, node));
	if (degree != 0) {
		if (degree > 0)
			degree--;
		else
			degree++;
	}
	return degree;
}

void MatrixGraph::IncreaseDegree(int node) {
	int index = Index(node, node);
	if (nodes[index] == 0.0) {
		nodeNumbers++;
		nodes[index] = 1;
	}
	if (nodes[index] < 0)
		nodes[index] -= 1;
	else
		nodes[index] += 1;
}

void MatrixGraph::ReduceDegree(int node) {
	int index = Index(node, node);
	if (nodes[index] > 0)
		nodes[index] -= 1;
	else
		nodes[index] += 1;
}

int MatrixGraph::GetFirstExistent(NodeIterator& node) {
	for (; node != this->end(); node++) {
		if (*node != 0)
			return node.node;
	}
	return -1;
}

void MatrixGraph::Add(int node1, int node2, double probability) {
	if (node1 >= graphSize || node2 >= graphSize || node1 == node2)
		return;
	double probabilityOld = Get(node1, node2);
	if (probabilityOld != 0.0)
		Set(node1, node2, 1 - (1 - probability) * (1 - probabilityOld));
	else {
		Set(node1, node2, probability);
		IncreaseDegree(node1);
		IncreaseDegree(node2);
	}
}

void MatrixGraph::RemoveEdge(int node1, int node2) {
	if (node1 >= graphSize || node2 >= graphSize || node1 == node2)
		return;
	if (Get(node1, node2) > 0) {
		Set(node1, node2, 0.0);
		ReduceDegree(node1);
		ReduceDegree(node2);
	}
}

void MatrixGraph::RemoveNode(int node) {
	if (node >= graphSize)
		return;
	for (auto iter = this->begin(node); iter != this->end(node); iter++) {
		if (*iter != 0.0) {
			*iter = 0.0;
			ReduceDegree(iter.adjNode);
		}
	}
	Set(node, node, 0.0);
	nodeNumbers--;
}

int MatrixGraph::EdgeContraction(int node1, int node2) {
	if (node1 >= graphSize || node2 >= graphSize || node1 == node2)
		return -1;
	for (auto iter = this->begin(node2); iter != this->end(node2); iter++) {
		if (*iter != 0)
			Add(iter.adjNode, node1, *iter);
	}

	RemoveNode(node2);
	return node1;
}

void MatrixGraph::Clear_Visited() {
	int index = 0;
	for (auto iter = this->begin(); iter != this->end(); iter++)
		*iter = std::abs(*iter);
}

void MatrixGraph::SetVisited(int node) {
	if (node >= graphSize)
		return;
	nodes[Index(node, node)] *= -1;
}
bool MatrixGraph::IsVisited(int node) {
	return NodeDegree(node) <= 0;
}

std::list<std::pair<int, double>> MatrixGraph::GetAdjustment(int node) {
	auto res = std::list<std::pair<int, double>>{};
	if (node >= graphSize)
		return res;
	for (auto iter = this->begin(node); iter != this->end(node); iter++) {
		if (*iter != 0.0)
			res.push_back(std::make_pair(iter.adjNode, *iter));
	}
	return res;
}

std::pair<int, int> MatrixGraph::GetTwoNeighbors() {
	NodeIterator node = this->begin();
	GetFirstExistent(node);
	return std::make_pair(node.node, GetFirst(node.node));
}

int MatrixGraph::GetFirst(int node) {
	if (node >= graphSize)
		return -1;
	for (auto iter = this->begin(node); iter != this->end(node); iter++) {
		if (*iter != 0.0)
			return iter.adjNode;
	}
	return -1;
}

int MatrixGraph::GetLast(int node) {
	if (node >= graphSize)
		return -1;
	for (int adjNode = graphSize - 1; adjNode >= 0; adjNode--) {
		if (adjNode == node)
			continue;
		if (Get(adjNode, node) != 0.0)
			return adjNode;
	}
	return -1;
}

int MatrixGraph::GetFirstNotVisited(int node) {
	if (node >= graphSize)
		return -1;

	for (auto iter = this->begin(node); iter != this->end(node); iter++) {
		if (*iter != 0  && !IsVisited(iter.adjNode))
			return iter.adjNode;
	}

	return -1;
}

bool MatrixGraph::Connectivity() {
	if (nodeNumbers == 0)
		return true;
	Clear_Visited();
	NodeIterator iter = this->begin();
	int node = GetFirstExistent(iter);
	std::list<int> stack;
	SetVisited(node);
	stack.push_back(node);

	while (!stack.empty()) {
		node = stack.back();
		stack.pop_back();

		int not_vist_node = GetFirstNotVisited(node);
		if (not_vist_node == -1)
			continue;
		else {
			SetVisited(not_vist_node);
			stack.push_back(node);
			stack.push_back(not_vist_node);
		}
	}

	bool res = true;
	for (int node = 0; node < graphSize; node++) {
		if (!IsVisited(node)) {
			res = false;
			break;
		}
	}
	Clear_Visited();
	return res;
}

void MatrixGraph::DFC() {
	Clear_Visited();
	NodeIterator iter = this->begin();
	int node = GetFirstExistent(iter);
	std::list<int> stack;
	SetVisited(node);
	stack.push_back(node);

	while (!stack.empty()) {
		node = stack.back();
		stack.pop_back();

		int not_vist_node = GetFirstNotVisited(node);
		if (not_vist_node == -1)
			continue;
		else {
			SetVisited(not_vist_node);
			stack.push_back(node);
			stack.push_back(not_vist_node);
		}
	}
}

std::list<Graph*> MatrixGraph::GetComponents() {
	std::list<Graph*> res = {};

	while (nodeNumbers != 0) {
		this->Clear_Visited();
		auto component = new MatrixGraph(*this);
		component->reability = 1;

		this->DFC();

		for (auto iter = this->begin(); iter != this->end(); iter++) {
			if (*iter == 0.0)
				continue;
			if (*iter < 0)
				this->RemoveNode(iter.node);
			else
				component->RemoveNode(iter.node);
		}
		res.push_back(component);
	}
	return res;
}

void MatrixGraph::Write() {
	for (int i = 0; i < graphSize; i++) {
		for (int j = 0; j < graphSize; j++)
			std::cout << Get(i, j) << " ";
		std::cout << std::endl;
	}
}