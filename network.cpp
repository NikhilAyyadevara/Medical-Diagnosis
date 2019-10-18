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
	vector<Graph_Node>::iterator listIt;
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
vector<Graph_Node>::iterator network::get_nth_node(int n)
{
	return Pres_Graph.begin()+n;
	// int count=0;
	// for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
	// {
	// 	if(count==n)
	// 		return listIt;
	// 	count++;
	// }
	// return listIt; 
}

//get the iterator of a node with a given name
vector<Graph_Node>::iterator network::search_node(string val_name)
{
	vector<Graph_Node>::iterator listIt;
	for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
	{
		if(listIt->get_name().compare(val_name)==0)
			return listIt;
	}

		cout<<"node not found\n";
	return listIt;
}

void network::updateCPTs()
{
	int n = 0;
	for(int i=0;i<Pres_Graph.size();++i)
	{
		n = 1;
		for(int j=0;j<Pres_Graph.at(i).indexParents.size();++j)
		{
			n = n*Pres_Graph.at(Pres_Graph.at(i).indexParents.at(j)).get_nvalues();
		}
		Pres_Graph.at(i).updateCPT(n);
	}
}