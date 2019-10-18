#include "Graph_Node.h"

Graph_Node::Graph_Node(string name,int n,vector<string> vals)
{
	Node_Name=name;

	nvalues=n;
	values=vals;
	

}


string Graph_Node::get_name()
{
	return Node_Name;
}

vector<int> Graph_Node::get_children()
{
	return Children;
}

vector<string> Graph_Node::get_Parents()
{
	return Parents;
}

vector<float> Graph_Node::get_CPT()
{
	return CPT;
}

int Graph_Node::get_nvalues()
{
	return nvalues;
}

vector<string> Graph_Node::get_values()
{
	return values;
}

void Graph_Node::set_CPT(vector<float> new_CPT)
{
	CPT.clear();
	CPT=new_CPT;
	for(int i=0;i<new_CPT.size();++i)
	{
		observations.push_back(0.1);
	}
}

void Graph_Node::updateCPT(int n)
{
	CPT.clear();
	vector<float> total;
	for(int i=0;i<n;++i)
	{
		float x = 0;
		for(int j=i;j<observations.size();j+=n)
		{
			x += observations.at(j);
		}
		total.push_back(x);
	}

	for(int i=0;i<observations.size();++i)
	{
		CPT.push_back(observations.at(i)/total.at(i%n));
		observations.at(i)=0.01;
	}
}

void Graph_Node::set_Parents(vector<string> Parent_Nodes)
{
	Parents.clear();
	Parents=Parent_Nodes;
}

// add another node in a graph as a child of this node
int Graph_Node::add_child(int new_child_index )
{
	for(int i=0;i<Children.size();i++)
	{
		if(Children[i]==new_child_index)
			return 0;
	}
	Children.push_back(new_child_index);
	return 1;
}

int Graph_Node::get_value_index(string val)
{
	for(int i=0;i<nvalues;++i)
	{
		if(val==values.at(i))
			return i;
	}
	return -1;
}

void Graph_Node::printCPT()
{
	for(int i=0;i<CPT.size();++i)
	{
		cout<<CPT.at(i)<<" ";
	}
	cout<<"\n";
}

void Graph_Node::printObservations()
{
	for(int i=0;i<observations.size();++i)
	{
		cout<<observations.at(i)<<" ";
	}
	cout<<"\n";
}