#include <bits/stdc++.h>

using namespace std;

vector<vector<string> > readData(int nodes, string file)
{
	ifstream fin;
	fin.open(file);

	vector<vector<string> > data;
	string s;
	int line=0;
	while(fin>>s)
	{
		vector<string> v;
		data.push_back(v);
		for(int i=0;i<nodes;++i)
		{
			data.at(line).push_back(s.substr(1,s.length()-2));
			if(i<nodes-1)
				fin>>s;
		}
		line++;
	}

	return data;
}