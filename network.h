#include "Graph_Node.h"
#include <list>

class network
{
	public:
		list <Graph_Node> Pres_Graph;

	public:
		int addNode(Graph_Node);
		int netSize();
		int get_index(string);
		list<Graph_Node>::iterator get_nth_node(int);
		list<Graph_Node>::iterator search_node(string);
};