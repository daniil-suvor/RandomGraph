#include "Graph.h"

double Graph::Reability() {
	if (!this->Connectivity())
		return 0;
	auto copy_graph = this->Coppy();
	copy_graph->Preprocesing();
	double res = copy_graph->_Reability();
	delete copy_graph;
	return res;
}

double Graph::_ReabilityProcesing(std::list<int> proc_node, bool check_connectivity) {
	if (check_connectivity && !(this->Connectivity()))
		return 0;

	for (auto node : proc_node)
		this->Procesing(node);

	return this->_Reability();
}

double Graph::_Reability() {
	iteration++;
	switch (nodeNumbers)
	{
	case 0:
	case 1:
		return reability;
	case 2:
		return this->_ReabilityK_2();
	case 3:
		return this->_ReabilityK_3();
	case 4:
		return this->_ReabilityK_4();
	case 5:
		return this->_ReabilityK_5();
	}

	auto a = FindArticulation();
	if (!a.empty())
		return ArticulationProcesing(a);

	double res;
	int node1, node2;
	std::tie(node1, node2) = this->GetTwoNeighbors();

	/*if (this->NodeDegree(node1) == 3)
		return Procesing3d(node1);

	if (this->NodeDegree(node2) == 3)
		return Procesing3d(node2);

	if (this->NodeDegree(node1) == 4)
		return Procesing4d(node1);

	if (this->NodeDegree(node2) == 4)
		return Procesing4d(node2);*/

	double probability = this->Probability(node1, node2);
	this->RemoveEdge(node1, node2);

	if (this->Connectivity()) {
		Graph* copy_graph = this->Coppy();
		this->Procesing(node1);
		this->Procesing(node2);

		int node_contraction = copy_graph->EdgeContraction(node1, node2);
		copy_graph->reability *= probability;

		copy_graph->Procesing(node_contraction);

		this->reability *= (1 - probability);
		res = this->_Reability() + copy_graph->_Reability();
		delete copy_graph;
	}
	else {
		res = reability * probability;
		auto components = this->GetComponents();
		for (auto component : components) {
			int number = component->ContainsNode(node1) ? node1 : node2;
			component->Procesing(number);
			res *= component->_Reability();
			delete component;
		}
	}

	return res;
}

double Graph::Procesing3d(int node) {
	double res = 0;
	auto adjustment = this->GetAdjustment(node);
	auto edges = adjustment.begin();

	int node_a = (*edges).first;
	double p_a = (*edges).second;
	edges++;
	int node_b = (*edges).first;
	double p_b = (*edges).second;
	edges++;
	int node_c = (*edges).first;
	double p_c = (*edges).second;

	double q_a = 1 - p_a, q_b = 1 - p_b, q_c = 1 - p_c;

	this->RemoveNode(node);

	double RGabc = this->HelpProcesingND({ node_a, node_b, node_c }, { });

	double RGab = this->HelpProcesingND({ node_a, node_b }, { node_c });
	double RGac = this->HelpProcesingND({ node_a, node_c }, { node_b });
	double RGbc = this->HelpProcesingND({ node_b, node_c }, { node_a });

	double R0 = this->_ReabilityProcesing({ node_a, node_b, node_c }, true);

	res = (p_a * q_b * q_c + q_a * p_b * q_c + q_a * q_b * p_c) * R0 +
		q_a * p_b * p_c * RGbc +
		p_a * q_b * p_c * RGac +
		p_a * p_b * q_c * RGab +
		p_a * p_b * p_c * RGabc;
	return res;
}

double Graph::Procesing4d(int node) {
	double res = 0;

	auto adjustment = this->GetAdjustment(node);
	auto edges = adjustment.begin();

	int node_a = (*edges).first;
	double p_a = (*edges).second;
	edges++;
	int node_b = (*edges).first;
	double p_b = (*edges).second;
	edges++;
	int node_c = (*edges).first;
	double p_c = (*edges).second;
	edges++;
	int node_d = (*edges).first;
	double p_d = (*edges).second;

	double q_a = 1 - p_a, q_b = 1 - p_b, q_c = 1 - p_c, q_d = 1 - p_d;

	this->RemoveNode(node);

	double RGabcd = this->HelpProcesingND({ node_a, node_b, node_c, node_d }, { });

	double RGab = this->HelpProcesingND({ node_a, node_b }, { node_c, node_d });
	double RGac = this->HelpProcesingND({ node_a, node_c }, { node_b, node_d });
	double RGad = this->HelpProcesingND({ node_a, node_d }, { node_c, node_b });
	double RGbc = this->HelpProcesingND({ node_b, node_c }, { node_a, node_d });
	double RGbd = this->HelpProcesingND({ node_b, node_d }, { node_a, node_c });
	double RGcd = this->HelpProcesingND({ node_c, node_d }, { node_a, node_b });

	double RGabc = this->HelpProcesingND({ node_a, node_b, node_c }, { node_d });
	double RGabd = this->HelpProcesingND({ node_a, node_b, node_d }, { node_c });
	double RGacd = this->HelpProcesingND({ node_a, node_c, node_d }, { node_b });
	double RGbcd = this->HelpProcesingND({ node_b, node_c, node_d }, { node_a });

	double R0 = this->_ReabilityProcesing({ node_a, node_b, node_c, node_d }, true);

	res = (p_a * q_b * q_c * q_d + q_a * p_b * q_c * q_d + q_a * q_b * p_c * q_d + q_a * q_b * q_c * p_d) * R0 +
		q_a * p_b * p_c * q_d * RGbc +
		p_a * q_b * p_c * q_d * RGac +
		p_a * p_b * q_c * q_d * RGab +
		p_a * q_b * q_c * p_d * RGad +
		q_a * p_b * q_c * p_d * RGbd +
		q_a * q_b * p_c * p_d * RGcd +
		p_a * p_b * p_c * q_d * RGabc +
		p_a * p_b * q_c * p_d * RGabd +
		p_a * q_b * p_c * p_d * RGacd +
		q_a * p_b * p_c * p_d * RGbcd +
		p_a * p_b * p_c * p_d * RGabcd;
	return res;
}

double Graph::HelpProcesingND(std::list<int> for_contain, std::list<int> for_proc) {
	Graph* G = this->Coppy();
	auto iter = for_contain.begin();
	int node = *iter;
	iter++;
	for (; iter != for_contain.end(); iter++)
		node = G->EdgeContraction(node, *iter);
	for_proc.push_back(node);
	double res = G->_ReabilityProcesing(for_proc, true);
	delete G;
	return res;
}

std::list<Graph*> Graph::SplitByNode(int node) {
	auto adjacentNodes = this->GetAdjustment(node);
	this->RemoveNode(node);
	auto graphs = this->GetComponents();

	for (auto [adjacentNode, probability] : adjacentNodes) {
		for (auto graph : graphs)
			if (graph->ContainsNode(adjacentNode)) {
				graph->Add(node, adjacentNode, probability);
				break;
			}
	}
	return graphs;
}

double Graph::ArticulationProcesing(std::list<int>& articulationNodes) {
	double res = this->reability;
	std::list<Graph*> stack = { this->Coppy() };
	auto articulationIter = articulationNodes.begin();
	while (!stack.empty())
	{
		auto graph = stack.back();
		auto iter = articulationIter;
		stack.pop_back();
		for (; iter != articulationNodes.end(); iter++) {
			if (graph->ContainsNode(*iter)) {
				auto graphs = graph->SplitByNode(*iter);
				stack.splice(stack.end(), graphs);
				articulationIter++;
				break;
			}
		}
		if (iter == articulationNodes.end()) {
			res *= graph->_Reability();
			delete graph;
		}

	}
	return res;
}
