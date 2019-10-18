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
				// cout << "hi" << endl;
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
					else
					{
						nvals.clear();
						vals.clear();
						break;
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
			if(vals.size()>0)
				Alarm.get_nth_node(j)->observations.at(x)++;
		}
	}

	cout << "initialization done!" <<"\n";
	Alarm.updateCPTs();

	int count = 0;
	while(count<500)
	{
		for(int i=0;i<data.size();++i)
		{
			for(int j=0;j<Alarm.netSize();++j)
			{
				vector<int> parents = Alarm.get_nth_node(j)->indexParents;
				int val = Alarm.get_nth_node(j)->get_value_index(data.at(i).at(j));
				vector<int> vals;
				vector<int> nvals;
				vector<int> nvalss;
				int qmark = -1;
				bool q = false;
					// cout << "hi" << endl;
				if(val==-1)
				{
					qmark = 0;
					q = true;
				}
				vals.push_back(val);
				nvals.push_back(Alarm.get_nth_node(j)->get_nvalues());
				for(int k=0;k<parents.size();++k)
				{
					nvals.push_back(Alarm.get_nth_node(parents.at(k))->get_nvalues());
					vals.push_back(Alarm.get_nth_node(parents.at(k))->get_value_index(data.at(i).at(parents.at(k))));
					if(Alarm.get_nth_node(parents.at(k))->get_value_index(data.at(i).at(parents.at(k)))==-1)
					{
						qmark = (k+1);
						q = true;
					}
				}
				nvalss = nvals;
				nvals.push_back(1);

				for(int k=nvals.size()-2;k>0;--k)
				{
					nvals.at(k) = nvals.at(k)*nvals.at(k+1);
				}
				if(nvals.size()>0)
					nvals.erase(nvals.begin());

				int x = 0;

				for(int k=0;k<nvals.size();++k)
				{
					if(vals.at(k)>=0)
						x += (nvals.at(k))*vals.at(k);
				}
				if(qmark==-1)
				{
					Alarm.get_nth_node(j)->observations.at(x)++;
					// cout<<"abdbdjfjfj"<<endl;
				}
				else
				{
					int abc = 0;
					while(abc<nvalss.at(qmark))
					{
						// cout<<"hi"<<endl;
						Alarm.get_nth_node(j)->observations.at(x) += Alarm.get_nth_node(j)->get_CPT().at(x);
						x+=nvals.at(qmark);
						abc++;
					}
				}
			}
		}
		Alarm.updateCPTs();
		count++;
	}

	vector<pair<string, vector<float> > > cpt;
	for(int i=0;i<Alarm.netSize();++i)
	{
		// cout<<Alarm.get_nth_node(i)->get_name()<<" ";
		// Alarm.get_nth_node(i)->printCPT();
		cpt.push_back(make_pair(Alarm.get_nth_node(i)->get_name(), Alarm.get_nth_node(i)->get_CPT()));
	}

	out(argv[1], cpt);

	return 0;
}