#pragma once
#ifndef _OOPGRAPH_H_
#define _OOPGRAPH_H_
#include "../../src/Graph.h"
#include "../node/src/Node.h"

class OOPGraph : public Graph
{
private:
	std::unordered_map<int, Node*> nodes;
	double _ReabilityK_2() override;
	double _ReabilityK_3() override;
	double _ReabilityK_4() override;
	double _ReabilityK_5() override;

	void Clear_Visited();

	std::list<Graph*> GetComponents() override;

	void Preprocesing() override;
	int Procesing(int node) override;
	std::list<std::pair<int, double>> GetAdjustment(int node) override;

	Node* DanglingContraction(Node* node);
	Node* ChainContraction(Node* node);

	double Probability(int node1, int node2) override;
	std::pair<int, int> GetTwoNeighbors() override;

	void RemoveEdge(Node* node1, Node* node2);
	int EdgeContraction(Node* node1, Node* node2);

	std::list<int> FindArticulation() override;
public:
	OOPGraph();
	~OOPGraph() override;
	OOPGraph(const OOPGraph& graph);
	OOPGraph* Coppy() override { return new OOPGraph(*this); }
	bool Connectivity() override;

	void Add(int node1, int node2, double probability) override;
	void RemoveNode(int node) override;
	void RemoveEdge(int node1, int node2) override;
	bool ContainsNode(int node) override;
	int NodeDegree(int nodeNumber) override;

	int EdgeContraction(int node1, int node2) override;
};

#endif // !_OOPGRAPH_H_
