#pragma once
#ifndef _MATRIXGRAPH_H_
#define _MATRIXGRAPH_H_

#include "../../src/Graph.h"
#include "../iterator/src/Iterator.h"
class MatrixGraph : public Graph
{
public:
	MatrixGraph(int graphSize);
	~MatrixGraph() override;
	MatrixGraph(const MatrixGraph& graph);
	MatrixGraph* Coppy() override { return new MatrixGraph(*this); }
	bool Connectivity() override;

	void Add(int node1, int node2, double probability) override;
	void RemoveNode(int node) override;
	void RemoveEdge(int node1, int node2) override;
	bool ContainsNode(int node) override;
	int NodeDegree(int node) override;
	int EdgeContraction(int node1, int node2) override;

	NodeIterator begin() { return NodeIterator(&nodes[0], graphSize); }
	NodeIterator end() { return NodeIterator(&nodes[arraySize], graphSize); }

	AdjacentIterator begin(int node) { return AdjacentIterator(&nodes[node], graphSize, node); }
	AdjacentIterator end(int node) {
		if (node >= graphSize)
			return begin(node)++;
		return AdjacentIterator(&nodes[Index(node + 1, node + 1)]);
	}

private:
	double* nodes;
	int graphSize;
	size_t arraySize;
	double _ReabilityK_2() override;
	double _ReabilityK_3() override;
	double _ReabilityK_4() override;
	double _ReabilityK_5() override;

	void Clear_Visited();

	std::list<Graph*> GetComponents() override;

	void Preprocesing() override;
	int Procesing(int node) override;
	std::list<std::pair<int, double>> GetAdjustment(int node) override;

	int DanglingContraction(int node);
	int ChainContraction(int node);

	bool IsVisited(int node);
	void SetVisited(int node);
	int GetFirstNotVisited(int node);
	double Get(int i, int j);
	void Set(int i, int j, double p);
	void IncreaseDegree(int node);
	void ReduceDegree(int node);
	int GetFirstExistent(NodeIterator& node);
	int GetFirst(int node);
	int GetLast(int node);
	int Index(int i, int j);

	double Probability(int node1, int node2) override;
	std::pair<int, int> GetTwoNeighbors() override;

	void DFC();
	std::list<int> FindArticulation() override;

	void Write();
};



#endif // !_MATRIXGRAPH
