#pragma once

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <unordered_map>
#include <list>
#include <algorithm>
#include <iostream>
#include <queue>
#include <array>
#include <tuple>
#include <omp.h>
#include <stdio.h>

class Graph
{
protected:
	bool ready;
	int iteration;
	int nodeNumbers;
	double reability;

	double _Reability();
	double _ReabilityProcesing(std::list<int> proc_node, bool check_connectivity);

	double Procesing3d(int node);
	double Procesing4d(int node);
	double HelpProcesingND(std::list<int> for_contain, std::list<int> for_proc);

	virtual double _ReabilityK_2() = 0;
	virtual double _ReabilityK_3() = 0;
	virtual double _ReabilityK_4() = 0;
	virtual double _ReabilityK_5() = 0;

	virtual std::list<Graph*> GetComponents() = 0;

	virtual void Preprocesing() = 0;
	virtual int Procesing(int node) = 0;

	virtual std::list<std::pair<int, double>> GetAdjustment(int node) = 0;

	virtual double Probability(int node1, int node2) = 0;
	virtual std::pair<int, int> GetTwoNeighbors() = 0;



	virtual std::list<int> FindArticulation() = 0;
	double ArticulationProcesing(std::list<int>& articulationNodes);

	Graph* one_thread_method();
	int prepare_graph(int node_cut, int num_queue, int th_num, std::queue<Graph*>* queues);

public:
	std::list<Graph*> SplitByNode(int node);
	Graph() { iteration = 0; reability = 1; nodeNumbers = 0; ready = false; }
	virtual ~Graph() {};
	virtual Graph* Coppy() = 0;
	virtual bool Connectivity() = 0;

	virtual void Add(int node1, int node2, double probability) = 0;
	virtual void RemoveNode(int node) = 0;
	virtual void RemoveEdge(int node1, int node2) = 0;
	virtual bool ContainsNode(int node) = 0;
	virtual int NodeDegree(int node) = 0;
	virtual int EdgeContraction(int node1, int node2) = 0;

	double Reability();

	double Reability_OMP(int th_num);
	double Reability_OMP(int th_num, int node_cut);

	void GenKN(int n, double probability);
	void Grid(int n, int m, double probability);
	void LinkGrid(int n, int m, int link, double probability);
};
#endif // !_GRAPH_H_
