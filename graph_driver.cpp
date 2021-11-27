#include "graph.cpp"

int main() {
	
	/*
	Graph g(false);
	g.addVertex('A');
	g.addVertex('B');
	g.addVertex('C');
	g.addVertex('D');
	g.addVertex('E');
	g.addVertex('F');

	g.addEdge('A', 'C');
	g.addEdge('A', 'E');
	g.addEdge('B', 'C');
	g.addEdge('B', 'F');
	g.addEdge('C', 'D');
	g.addEdge('C', 'F');
	g.addEdge('D', 'F');
	g.addEdge('E', 'F');

	g.dfs();
	cout << endl;
	g.bfs();
	*/

	/*
	Graph g2(true);
	g2.addVertex('1');
	g2.addVertex('2');
	g2.addVertex('3');
	g2.addVertex('4');
	g2.addVertex('5');
	g2.addVertex('6');
	g2.addVertex('7');

	g2.addEdge('1', '2');
	g2.addEdge('1', '3');
	g2.addEdge('2', '5');
	g2.addEdge('2', '6');
	g2.addEdge('2', '4');
	g2.addEdge('3', '4');
	g2.addEdge('4', '5');
	g2.addEdge('5', '7');

	g2.topologicalSort('1');
	*/

	/*
	Graph g3(true);
	g3.addVertex('A');
	g3.addVertex('B');
	g3.addVertex('C');
	g3.addVertex('D');
	g3.addVertex('E');

	g3.addEdge('A', 'B', 10);
	g3.addEdge('A', 'C', 3);
	g3.addEdge('A', 'D', 20);
	g3.addEdge('B', 'D', 5);
	g3.addEdge('C', 'B', 2);
	g3.addEdge('C', 'E', 15);
	g3.addEdge('D', 'E', 11);

	g3.dijkstrasAlg('A');
	*/

	/*Graph g4(true);
	g4.addVertex('A');
	g4.addVertex('B');
	g4.addVertex('C');
	g4.addVertex('D');
	g4.addVertex('E');
	g4.addVertex('F');

	g4.addEdge('A', 'C', 7);
	g4.addEdge('A', 'E', 9);
	g4.addEdge('B', 'C', 5);
	g4.addEdge('B', 'F', 6);
	g4.addEdge('C', 'D', 1);
	g4.addEdge('C', 'F', 2);
	g4.addEdge('D', 'F', 2);
	g4.addEdge('E', 'F', 1);*/

	Graph g4("mine.graph", true); 

	cout << "Out Degree A:" <<  g4.getOutDegree('A') << endl;
	int maxOut;
	g4.getMaxOutDegree(maxOut);
	cout << "Max out: " << maxOut << endl;
	cout << "In Degree E:" << g4.getInDegree('A') << endl;
	int maxIn;
	g4.getMaxInDegree(maxIn);
	cout << "Max in: " << maxIn << endl;
	cout << "BREADTH FIRST" << endl;
	g4.bfs();
	cout << "DEPTH FIRST" << endl;
	g4.dfs();
	g4.topologicalSort('A');
	g4.dijkstrasAlg('A');


	g4.prim();
}
