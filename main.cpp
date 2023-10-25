#include <iostream>
#include "graph/oop_graph/src/OOPGraph.h"
#include "graph/src/Graph.h"
#include "graph/matrix_graph/src/MatrixGraph.h"
#include <chrono>

Graph* CreateGraph(int n, bool oop = true) {
    if (oop)
        return new OOPGraph();
    else
        return new MatrixGraph(n);
}

Graph* test(int n, bool oop = true) {
    Graph* graph;
    switch (n)
    {
    case 0:
        graph = CreateGraph(16, oop);
        graph->Grid(4, 4, 0.7); // 0.41643
        break;
    case 1:
        graph = CreateGraph(25, oop);
        graph->Grid(5, 5, 0.7); // 0.340888
        break;
    case 2:
        graph = CreateGraph(10, oop);
        graph->GenKN(10, 0.45); // 0.954152
        break;
    case 3:
        graph = CreateGraph(32, oop);
        graph->LinkGrid(4, 4, 1, 0.7); // 0.12139
        break;
    case 4:
        graph = CreateGraph(50, oop);
        graph->LinkGrid(5, 5, 1, 0.7); // 0.0813434
        break;
    case 5:
        graph = CreateGraph(12, oop);
        graph->GenKN(12, 0.7); // 0.999979
        break;
    default:
        graph = new OOPGraph();
        break;
    }

    return graph;
}
void speed_test(int n, Graph* graph) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
        graph->Reability();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << duration.count() << std::endl;
}

void test_reability(Graph* graph) {
    std::cout << "Connectivity " << graph->Connectivity() << std::endl;

    std::cout << "Reability " << graph->Reability() << std::endl;
}

int main()
{
    auto graph = test(0, false);
    test_reability(graph);
    //speed_test(10, graph);
    delete graph;
}

