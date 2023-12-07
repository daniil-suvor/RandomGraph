#include "Graph.h"

double Graph::Reability_OMP(int th_num) {

	auto q = std::queue<Graph*>();
	const size_t size = th_num;
	auto first_graph = this->Coppy();
	first_graph->Preprocesing();

	q.push(first_graph);
	double* res = new double[th_num] {0};
	int number_wait = 0;
	bool wait = false;
	bool work = true;
	Graph* graph = NULL;
	Graph* copy_graph = NULL;
#pragma omp parallel num_threads(size) shared(q, res, size, number_wait) firstprivate(wait, work, graph, copy_graph)
	{
		while (work) {
#pragma omp critical
			{
				if (!q.empty()) {
					graph = q.front();
					q.pop();
					if (wait) {
						wait = false;
						number_wait--;
					}
				}
				else {
					if (!wait) {
						wait = true;
						number_wait++;
					}
					work = (th_num != number_wait);
				}
			}
			if (!wait) {
				while (!graph->ready) {
					copy_graph = graph->one_thread_method();
					if (copy_graph != NULL) {
#pragma omp critical
						{
							q.push(copy_graph);
						}
					}
				}
				res[omp_get_thread_num()] += graph->reability;
				delete graph;
			}
		}

	}

	double result = 0;
	for (int i = 0; i < th_num; i++) {
		result += res[i];
	}
	delete[] res;
	return result;
}

Graph* Graph::one_thread_method() {

	iteration++;
	switch (nodeNumbers)
	{
	case 0:
	case 1:
		ready = true;
		return NULL;
	case 2:
		reability = this->_ReabilityK_2();
		ready = true;
		return NULL;
	case 3:
		reability = this->_ReabilityK_3();
		ready = true;
		return NULL;
	case 4:
		reability = this->_ReabilityK_4();
		ready = true;
		return NULL;
	case 5:
		reability = this->_ReabilityK_5();
		ready = true;
		return NULL;
	}

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

	Graph* copy_graph = this->Coppy();
	double probability = this->Probability(node1, node2);

	copy_graph->RemoveEdge(node1, node2);

	if (copy_graph->Connectivity()) {

		copy_graph->Procesing(node1);
		copy_graph->Procesing(node2);
		copy_graph->reability *= (1 - probability);
	}
	else {
		delete copy_graph;
		copy_graph = NULL;
	}

	int node_contraction = this->EdgeContraction(node1, node2);
	this->reability *= probability;
	this->Procesing(node_contraction);

	return copy_graph;
}

int Graph::prepare_graph(int node_cut, int num_queue, int th_num, std::queue<Graph*>* queues) {
	iteration++;
	if (this->nodeNumbers <= node_cut) {
		queues[num_queue].push(this);
		num_queue = (num_queue + 1) % th_num;
		return num_queue;
	}

	int node1, node2;
	std::tie(node1, node2) = this->GetTwoNeighbors();
	double probability = this->Probability(node1, node2);
	Graph* copy_graph = this->Coppy();
	copy_graph->RemoveEdge(node1, node2);

	if (copy_graph->Connectivity()) {
		copy_graph->Procesing(node1);
		copy_graph->Procesing(node2);
		copy_graph->reability *= (1 - probability);
		num_queue = copy_graph->prepare_graph(node_cut, num_queue, th_num, queues);
	}
	else
		delete copy_graph;

	int node_contraction = this->EdgeContraction(node1, node2);
	this->reability *= probability;
	this->Procesing(node_contraction);
	return this->prepare_graph(node_cut, num_queue, th_num, queues);
}

double Graph::Reability_OMP(int th_num, int node_cut) {
	if (!this->Connectivity())
		return 0;

	const size_t size = th_num;
	auto first_graph = this->Coppy();
	first_graph->Preprocesing();
	double* res = new double[th_num] {0};

	auto queues = new std::queue<Graph*>[th_num] {std::queue<Graph*> {}};
	first_graph->prepare_graph(node_cut, 0, th_num, queues);
	Graph* graph = NULL;
#pragma omp parallel num_threads(size) shared(queues, res) firstprivate(graph)
	{
		int thread_num = omp_get_thread_num();
		auto queue = queues[thread_num];
		while (!queue.empty()) {
			graph = queue.front();
			queue.pop();
			res[thread_num] += graph->_Reability();
			delete graph;
		}

	}

	double result = 0;
	for (int i = 0; i < th_num; i++) {
		result += res[i];
	}
	delete[] res;
	delete[] queues;
	//delete first_graph;
	return result;
}