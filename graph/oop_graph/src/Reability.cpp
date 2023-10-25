#include "OOPGraph.h"

double OOPGraph::_ReabilityK_2() {
	auto node_iter = nodes.begin();
	auto node1 = (*node_iter).second;
	node_iter++;
	auto node2 = (*node_iter).second;
	return reability * node1->Probability(node2);
}

double OOPGraph::_ReabilityK_3() {
	auto node_iter = nodes.begin();
	auto node1 = (*node_iter).second;
	node_iter++;
	auto node2 = (*node_iter).second;
	node_iter++;
	auto node3 = (*node_iter).second;
	double a = node1->Probability(node2);
	double b = node2->Probability(node3);
	double c = node1->Probability(node3);

	return a * b * c + a * b * (1 - c) + a * (1 - b) * c + (1 - a) * b * c;
}


double OOPGraph::_ReabilityK_4() {
	auto node_iter = nodes.begin();
	auto node1 = (*node_iter).second;
	node_iter++;
	auto node2 = (*node_iter).second;
	node_iter++;
	auto node3 = (*node_iter).second;
	node_iter++;
	auto node4 = (*node_iter).second;

	double a = node1->Probability(node2);
	double b = node2->Probability(node3);
	double c = node3->Probability(node4);
	double d = node1->Probability(node4);
	double e = node1->Probability(node3);
	double f = node2->Probability(node4);

	double res = -6 * a * b * c * d * e * f + 4 * (a * b * c * d * e + a * b * c * d * f + a * b * c * e * f + a * b * d * e * f +
		a * c * d * e * f + b * c * d * e * f) - 3 * (a * b * c * d + b * d * e * f + a * c * e * f) -
		2 * (a * b * c * e + a * b * c * f + a * b * d * e + a * b * d * f + a * b * e * f + a * c * d * e + a * c * d * f +
			a * d * e * f + b * c * d * e + b * c * d * f + b * c * e * f + c * d * e * f) +
		a * b * c + a * b * d + a * b * f + a * c * d + a * c * e + a * c * f + a * d * e + a * e * f + b * c * d +
		b * c * e + b * d * e + b * d * f + b * e * f + c * d * f + c * e * f + d * e * f;
	return res * reability;
}

double OOPGraph::_ReabilityK_5() {
	auto node_iter = nodes.begin();
	auto node1 = (*node_iter).second;
	node_iter++;
	auto node2 = (*node_iter).second;
	node_iter++;
	auto node3 = (*node_iter).second;
	node_iter++;
	auto node4 = (*node_iter).second;
	node_iter++;
	auto node5 = (*node_iter).second;

	double a = node1->Probability(node2);
	double b = node1->Probability(node3);
	double c = node1->Probability(node4);
	double d = node1->Probability(node5);

	double e = node2->Probability(node3);
	double f = node2->Probability(node4);
	double g = node2->Probability(node5);

	double h = node3->Probability(node4);
	double u = node3->Probability(node5);

	double v = node4->Probability(node5);

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

Node* OOPGraph::DanglingContraction(Node* node) {
	Node* adjacent_node;
	while (node->degre == 1) {
		adjacent_node = node->get_first();
		reability *= node->Probability(adjacent_node);
		RemoveEdge(node, adjacent_node);
		nodes.erase(node->number);
		delete node;
		nodeNumbers--;
		node = adjacent_node;
	}
	return node;
}

Node* OOPGraph::ChainContraction(Node* node) {
	Node* adjacent_node_right, * adjacent_node_left;
	double p_left, p_rigth, p_new;
	while (node->Degre() == 2) {

		adjacent_node_left = node->get_first();
		adjacent_node_right = node->get_last();

		p_left = node->Probability(adjacent_node_left);
		p_rigth = node->Probability(adjacent_node_right);
		p_new = p_left * p_rigth / (1 - (1 - p_left) * (1 - p_rigth));
		reability *= p_rigth + p_left - p_left * p_rigth;

		adjacent_node_left->Add(adjacent_node_right, p_new);
		RemoveNode(node->number);
		if (adjacent_node_left->Degre() == 2)
			node = adjacent_node_left;
		else
			node = adjacent_node_right;
	}
	return node;
}

int OOPGraph::Procesing(int nodeNumber) {
	if (!nodes.contains(nodeNumber))
		return nodeNumber;

	auto node = nodes[nodeNumber];

	while (node->degre == 1 || node->degre == 2)
	{
		if (node->Degre() == 1)
			node = DanglingContraction(node);

		if (node->Degre() == 2)
			node = ChainContraction(node);
	}

	return node->number;
}

void OOPGraph::Preprocesing() {
	auto is_dangling_node = [](std::pair<int, Node*> node) {return node.second->Degre() == 1; };

	auto dangling_node = std::find_if(nodes.begin(), nodes.end(), is_dangling_node);

	while (dangling_node != nodes.end())
	{
		this->DanglingContraction((*dangling_node).second);
		dangling_node = std::find_if(nodes.begin(), nodes.end(), is_dangling_node);
	}

	auto is_chain_node = [](std::pair<int, Node*> node) {return node.second->Degre() == 2; };

	auto chain_node = std::find_if(nodes.begin(), nodes.end(), is_chain_node);

	while (chain_node != nodes.end())
	{
		Node* node = this->ChainContraction((*chain_node).second);
		if (node->Degre() == 1)
			this->DanglingContraction(node);
		chain_node = std::find_if(nodes.begin(), nodes.end(), is_chain_node);
	}
}

std::list<int> OOPGraph::FindArticulation() {
	this->Clear_Visited();
	return (*nodes.begin()).second->DFCFindArticulation();
}
