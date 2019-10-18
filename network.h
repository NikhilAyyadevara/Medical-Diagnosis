#include "Graph_Node.h"

class network
{
	public:
		vector<Graph_Node> Pres_Graph;

	public:
		int addNode(Graph_Node);
		int netSize();
		int get_index(string);
		vector<Graph_Node>::iterator get_nth_node(int);
		vector<Graph_Node>::iterator search_node(string);
		void updateCPTs();
};