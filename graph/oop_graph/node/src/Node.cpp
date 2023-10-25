#include "Node.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <list>

Node::Node(int number) {
	this->number = number;
	visit = false;
	edges = std::unordered_map<Node*, double>{};
	degre = 0;
}

int Node::Degre() {
	return degre;
}

Node::Node(const Node& node) {
	this->number = node.number;
	this->visit = false;
	edges = std::unordered_map<Node*, double>{};
	degre = 0;
}

void Node::Add(Node* node, double probability) {
	if (this == node)
		return;
	auto add_edge = edges.find(node);
	if (add_edge == edges.end()) {
		this->Fast_Add(node, probability);
	}
	else {
		double probability2 = std::get<1>(*add_edge);
		edges[node] = 1 - (1 - probability) * (1 - probability2);
		node->edges[this] = 1 - (1 - probability) * (1 - probability2);
	}
}

void Node::Fast_Add(Node* node, double probability) {
	if (this == node)
		return;
	edges[node] = probability;
	node->edges[this] = probability;
	degre += 1;
	node->degre += 1;
}

bool Node::is_conected(Node* node) {
	if (this->edges.empty())
		return false;
	return this->edges.contains(node);
}

void Node::remove_edge(Node* node) {
	if (this == node)
		return;
	degre -= 1;
	edges.erase(node);
}

void Node::remove_node() {
	Node* node;
	double probability;
	for (std::pair<Node*, double> edge : edges) {
		std::tie(node, probability) = edge;
		node->remove_edge(this);
	}
	edges.clear();
}

void Node::edge_contraction(Node* node) {
	for (std::pair<Node*, double> edge : node->edges)
		this->Add(edge.first, edge.second);
}

double Node::Probability(Node* node) {
	if (this->edges.contains(node))
		return this->edges[node];
	return 0;
}

Node* Node::get_first() {
	return (*edges.begin()).first;
}

Node* Node::get_last() {
	return (*(--edges.end())).first;
}

bool Node::operator==(int number) {
	return this->number == number;
}
void Node::DFC_2() {
	std::list<std::pair<Node*, std::unordered_map<Node*, double>::iterator>> stack;
	visit = true;
	stack.push_back(std::make_pair(this, this->edges.begin()));

	while (!stack.empty()) {
		auto [elem, not_vist_node] = stack.back();
		stack.pop_back();
		// std::find_if(elem->dfc_iter, elem->edges.end(), [](std::pair<Node*, double> edge) -> bool {return !(edge.first.); });

		//std::unordered_map<Node*, double>::iterator not_vist_node;
		for (; not_vist_node != elem->edges.end() && (*not_vist_node).first->visit; not_vist_node++) {}

		if (not_vist_node == elem->edges.end())
			continue;
		else {

			//std::cout << elem->number << " " << not_vist_node->first->number << " " << not_vist_node->second << std::endl;
			not_vist_node->first->visit = true;
			stack.push_back(std::make_pair(elem, not_vist_node));
			auto nexElem = not_vist_node->first;
			stack.push_back(std::make_pair(nexElem, nexElem->edges.begin()));
		}
	}
}



std::list<int> Node::DFCFindArticulation() {
	struct DFCStruct
	{
		std::list<Node*> children;
		std::list<Node*> adj_not_children;
		int dfc_in;
		int dfc_out;
	};

	std::list<std::pair<Node*, std::unordered_map<Node*, double>::iterator>> stack;
	std::unordered_map<Node*, DFCStruct*> tree;

	this->visit = true;
	stack.push_back(std::make_pair(this, this->edges.begin()));
	tree[this] = new DFCStruct{ {}, {}, 1, INT_MAX };
	int dfc_num = 2;
	double probability;
	auto res = std::list<int>();
	DFCStruct* tree_node;

	while (!stack.empty()) {
		auto [elem, not_vist_node] = stack.back();
		stack.pop_back();
		tree_node = tree[elem];
		for (; not_vist_node != elem->edges.end() && (*not_vist_node).first->visit; not_vist_node++)
			tree_node->adj_not_children.push_back((*not_vist_node).first);

		if (not_vist_node == elem->edges.end()) {
			int dfc_out = INT_MAX;

			for (auto adj_node : tree_node->adj_not_children)
				dfc_out = std::min(dfc_out, tree[adj_node]->dfc_in);
			for (auto adj_node : tree_node->children)
				dfc_out = std::min(dfc_out, tree[adj_node]->dfc_out);
			tree_node->dfc_out = dfc_out;
		}
		else {

			tree_node->children.push_back((*not_vist_node).first);
			tree[(*not_vist_node).first] = new DFCStruct{ {}, {}, dfc_num, INT_MAX };
			dfc_num++;
			(*not_vist_node).first->visit = true;
			stack.push_back(std::make_pair(elem, not_vist_node));
			auto nexElem = not_vist_node->first;
			stack.push_back(std::make_pair(nexElem, nexElem->edges.begin()));
		}
	}
	if (tree[this]->children.size() > 1)
		res.push_back(this->number);
	for (auto elem : tree) {
		if (elem.first == this)
			continue;
		for (auto child : elem.second->children) {
			if (tree[child]->dfc_out == elem.second->dfc_in) {
				res.push_back(elem.first->number);
				break;
			}
		}
	}

	for (auto elem : tree)
		delete elem.second;
	return res;
}
