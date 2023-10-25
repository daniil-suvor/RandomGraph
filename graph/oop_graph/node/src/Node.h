#pragma once
#ifndef _NODE_H_
#define _NODE_H_

#include <unordered_map>
#include <tuple>

class OOPGraph;
class Node
{
	friend class OOPGraph;
private:
	std::unordered_map<Node*, double> edges;
	bool visit;
	int number;
	size_t degre;
public:
	Node(int number);
	Node(const Node& node);

	bool is_conected(Node* node);

	void Add(Node* node, double probability);
	void Fast_Add(Node* node, double probability);

	void DFC_2();
	std::list<int> DFCFindArticulation();

	void remove_node();
	void remove_edge(Node* node);

	void edge_contraction(Node* node);

	double Probability(Node* node);

	bool operator==(int number);

	int Degre();
	int get_number() { return number; }

	Node* get_last();
	Node* get_first();
};
#endif  // _NODE_H_
