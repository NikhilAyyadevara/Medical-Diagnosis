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
	vector<vector<string> > data = readData(Alarm.netSize(),file);
	// cout<<v.size()<<"\n";

	for(int i=0;i<data.size();++i)
	{
		for(int j=0;j<Alarm.netSize();++j)
		{
			vector<int> parents = Alarm.get_nth_node(j)->indexParents;
			int val = Alarm.get_nth_node(j)->get_value_index(data.at(i).at(j));
			vector<int> vals;
			vector<int> nvals;
			if(val!=-1)
			{
				vals.push_back(val);
				nvals.push_back(Alarm.get_nth_node(j)->get_nvalues());
				for(int k=0;k<parents.size();++k)
				{
					if(Alarm.get_nth_node(parents.at(k))->get_value_index(data.at(i).at(parents.at(k)))!=-1)
					{
						vals.push_back(Alarm.get_nth_node(parents.at(k))->get_value_index(data.at(i).at(parents.at(k))));
						nvals.push_back(Alarm.get_nth_node(parents.at(k))->get_nvalues());
					}
				}
				nvals.push_back(1);
			}

			for(int k=nvals.size()-2;k>0;--k)
			{
				nvals.at(k) = nvals.at(k)*nvals.at(k+1);
			}
			if(nvals.size()>0)
				nvals.erase(nvals.begin());

			int x = 0;

			for(int k=0;k<nvals.size();++k)
			{
				x += (nvals.at(k))*vals.at(k);
			}

			Alarm.get_nth_node(j)->observations.at(x)++;
		}
	}

	for(int i=0;i<Alarm.netSize();++i)
	{
		Alarm.get_nth_node(i)->updateCPT();
		Alarm.get_nth_node(i)->printCPT();
	}



	return 0;
}