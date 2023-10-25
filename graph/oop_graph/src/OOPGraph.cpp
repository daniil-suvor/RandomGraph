#include "OOPGraph.h"


OOPGraph::OOPGraph() : Graph() {
	this->nodes = std::unordered_map<int, Node*>{};
}

OOPGraph::~OOPGraph() {
	if (nodes.empty())
		return;
	for (std::pair<int, Node*> node : nodes)
		delete node.second;
	nodes.clear();
}

OOPGraph::OOPGraph(const OOPGraph& graph) {
	this->nodes = std::unordered_map<int, Node*>{};
	this->iteration = graph.iteration;
	this->reability = graph.reability;
	this->nodeNumbers = graph.nodeNumbers;

	int node_number;
	double probability;
	Node* node, * adjacent_node;

	for (std::pair<int, Node*> node_pair : graph.nodes) {
		std::tie(node_number, node) = node_pair;
		this->nodes[node_number] = new Node(node_number);
	}

	for (std::pair<int, Node*> node_pair : graph.nodes) {
		std::tie(node_number, node) = node_pair;
		auto newNode = this->nodes[node_number];
		for (std::pair<Node*, double> edge : node->edges) {
			std::tie(adjacent_node, probability) = edge;
			newNode->edges[this->nodes[adjacent_node->number]] = probability;
			newNode->degre += 1;
		}
	}
}

double OOPGraph::Probability(int numberNode1, int numberNode2) {
	if (!nodes.contains(numberNode1) || !nodes.contains(numberNode2))
		return NULL;
	auto node1 = nodes[numberNode1];
	auto node2 = nodes[numberNode2];
	return node1->Probability(node2);
}

std::pair<int, int> OOPGraph::GetTwoNeighbors() {
	auto node_iter = nodes.begin();
	auto node1 = (*node_iter).second;
	auto node2 = node1->get_first();
	return std::make_pair(node1->number, node2->number);
}

std::list<Graph*> OOPGraph::GetComponents() {
	std::list<Graph*> res = {};

	this->Clear_Visited();

	while (!this->nodes.empty()) {
		auto component = new OOPGraph();
		component->iteration = this->iteration;

		(*this->nodes.begin()).second->DFC_2();

		for (auto& node : nodes) {
			if (node.second->visit)
				component->nodes[node.first] = node.second;
		}
		for (auto& node : component->nodes)
			this->nodes.erase(node.first);
		component->nodeNumbers = component->nodes.size();
		res.push_back(component);
	}
	return res;
}

void OOPGraph::Clear_Visited() {
	for (auto& node : nodes) {
		node.second->visit = false;
	}
}

void OOPGraph::Add(int numberNode1, int numberNode2, double probability) {
	Node* node1, * node2;

	if (nodes.contains(numberNode1)) {
		node1 = nodes[numberNode1];
	}
	else {
		node1 = new Node(numberNode1);
		nodes[numberNode1] = node1;
		nodeNumbers++;
	}

	if (nodes.contains(numberNode2)) {
		node2 = nodes[numberNode2];
	}
	else {
		node2 = new Node(numberNode2);
		nodes[numberNode2] = node2;
		nodeNumbers++;
	}

	node1->Add(node2, probability);
}

bool OOPGraph::Connectivity() {
	if (nodes.size() == 0)
		return true;

	this->Clear_Visited();

	(*nodes.begin()).second->DFC_2();

	for (auto& node : nodes) {
		if (!node.second->visit)
			return false;
	}

	return true;
}

void OOPGraph::RemoveNode(int nodeNumber) {
	if (nodes.contains(nodeNumber)) {
		auto node = nodes[nodeNumber];

		node->remove_node();
		nodes.erase(node->get_number());
		delete node;
		nodeNumbers--;
	}
}

void OOPGraph::RemoveEdge(int numberNode1, int numberNode2) {
	if (!nodes.contains(numberNode1) || !nodes.contains(numberNode2))
		return;
	RemoveEdge(nodes[numberNode1], nodes[numberNode2]);
}

void OOPGraph::RemoveEdge(Node* node1, Node* node2) {
	if (!node1->edges.contains(node2) || !node2->edges.contains(node1))
		return;
	node1->remove_edge(node2);
	node2->remove_edge(node1);
}

int OOPGraph::EdgeContraction(int numberNode1, int numberNode2) {
	if (!nodes.contains(numberNode1) || !nodes.contains(numberNode2))
		return NULL;
	return EdgeContraction(nodes[numberNode1], nodes[numberNode2]);
}

int OOPGraph::EdgeContraction(Node* node1, Node* node2) {
	node1->edge_contraction(node2);
	node2->remove_node();
	nodes.erase(node2->number);
	delete node2;
	nodeNumbers--;
	return node1->number;
}

bool OOPGraph::ContainsNode(int node) {
	return nodes.contains(node);
}

int OOPGraph::NodeDegree(int nodeNumber) {
	if (!nodes.contains(nodeNumber))
		return NULL;
	return nodes[nodeNumber]->degre;
}

std::list<std::pair<int, double>> OOPGraph::GetAdjustment(int nodeNumber) {
	auto result = std::list<std::pair<int, double>>{};
	if (!nodes.contains(nodeNumber))
		return result;

	auto node = nodes[nodeNumber];
	for (auto adjustment : node->edges)
		result.push_back(std::make_pair(adjustment.first->number, adjustment.second));

	return result;
}

//std::pair<std::list<std::pair<Node*, Node*>>, std::list<Node*>> Graph::Articulation() {
//	this->Clear_All();
//	(*(nodes.begin())).second->DFC_mark_articulation();
//	this->Clear_Visited();
//	return (*(nodes.begin())).second->DFC_find_articulation_and_bridge();
//}
//
//void Graph::test() {
//	for (auto node : nodes) {
//		std::cout << node.second->number << std::endl;
//		this->remove_node(node.second);
//	}
//}