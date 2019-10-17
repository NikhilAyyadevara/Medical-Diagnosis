#include "Parser.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[])
{
	network Alarm;
	string file=argv[1];
	Alarm=read_network(file);
    file = argv[2];
// Example: to do something
	vector<vector<string> > v = readData(Alarm.netSize(),file);
	// cout<<v.size()<<"\n";
	vector<int> b;
	for(int i=0;i<Alarm.netSize();++i)
	{
		b.push_back(0);
	}
	int l=0;
	for(int i=0;i<v.size();++i)
	{
		// cout<<v[i].size()<<"\n";
		for(int j=0;j<v.at(i).size();++j)
		{
			if(v[i][j]=="?")
				b.at(j) += 1;
		}
	}

	for(int i=0;i<Alarm.netSize();++i)
	{
		cout<<Alarm.get_nth_node(i)->get_name()<<" ";
	}
	cout<<"\n";
	for(int i=0;i<Alarm.netSize();++i)
	{
		for(int j=0;j<Alarm.get_nth_node(i)->indexParents.size();++j)
		{
			cout<<Alarm.get_nth_node(i)->indexParents.at(j)<<" ";
		}
		cout<<"\n";
	}
	return 0;
}