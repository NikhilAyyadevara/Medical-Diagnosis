#include "network.h"

int network::addNode(Graph_Node node)
{
	Pres_Graph.push_back(node);
	return 0;
}

int network::netSize()
{
	return Pres_Graph.size();
}

// get the index of node with a given name
int network::get_index(string val_name)
{
	list<Graph_Node>::iterator listIt;
	int count=0;
	for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
	{
		if(listIt->get_name().compare(val_name)==0)
			return count;
		count++;
	}
	return -1;
}

// get the node at nth index
list<Graph_Node>::iterator network::get_nth_node(int n)
{
	list<Graph_Node>::iterator listIt;
	int count=0;
	for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
	{
		if(count==n)
			return listIt;
		count++;
	}
	return listIt; 
}

//get the iterator of a node with a given name
list<Graph_Node>::iterator network::search_node(string val_name)
{
	list<Graph_Node>::iterator listIt;
	for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
	{
		if(listIt->get_name().compare(val_name)==0)
			return listIt;
	}

		cout<<"node not found\n";
	return listIt;
}