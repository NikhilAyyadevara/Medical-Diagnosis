#include "Parser.h"
#include <chrono>

using namespace std;

int main(int argc, char* argv[])
{
	auto start = chrono::steady_clock::now();
	network Alarm;
	string file=argv[1];
	Alarm=read_network(file);
    file = argv[2];

	vector<vector<string> > data = readData(Alarm.netSize(),file);

	vector<pair<int, int> > questionMarks; //pair of line, node-index.

	for(int i=0;i<data.size();++i)
	{
		for(int j=0;j<Alarm.netSize();++j)
		{
			vector<int> parents = Alarm.get_nth_node(j)->indexParents;
			int val = Alarm.get_nth_node(j)->get_value_index(data.at(i).at(j));
			vector<int> vals;
			vector<int> nvals;

			if(val==-1)
			{
				questionMarks.push_back(make_pair(i, j));
			}
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
						questionMarks.push_back(make_pair(i, j));
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
	Alarm.setInitialObs();
	Alarm.updateCPTs();
	

	int count = 0;

	while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now()-start).count()<115000)
	{
		for(int i=0;i<questionMarks.size();++i)
		{
			int line = questionMarks.at(i).first;
			int node = questionMarks.at(i).second;
			vector<int> parents = Alarm.get_nth_node(node)->indexParents;
			int val = Alarm.get_nth_node(node)->get_value_index(data.at(line).at(node));
			vector<int> vals;
			vector<int> nvals;
			vector<int> nvalss;
			int qmark = -1;
			if(val==-1)
			{
				qmark = 0;
			}
			vals.push_back(val);
			nvals.push_back(Alarm.get_nth_node(node)->get_nvalues());
			for(int j=0;j<parents.size();++j)
			{
				nvals.push_back(Alarm.get_nth_node(parents.at(j))->get_nvalues());
				vals.push_back(Alarm.get_nth_node(parents.at(j))->get_value_index(data.at(line).at(parents.at(j))));
				if(Alarm.get_nth_node(parents.at(j))->get_value_index(data.at(line).at(parents.at(j)))==-1)
				{
					qmark = (j+1);
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
			int abc = 0;
			while(abc<nvalss.at(qmark))
			{
				Alarm.get_nth_node(node)->observations.at(x) += Alarm.get_nth_node(node)->get_CPT().at(x);
				x+=nvals.at(qmark);
				abc++;
			}
		}

		Alarm.updateCPTs();
		count++;
	}

	vector<pair<string, vector<double> > > cpt;
	for(int i=0;i<Alarm.netSize();++i)
	{
		cpt.push_back(make_pair(Alarm.get_nth_node(i)->get_name(), Alarm.get_nth_node(i)->get_CPT()));
	}

	out(argv[1], cpt);
	cout << count << endl;

	return 0;
}