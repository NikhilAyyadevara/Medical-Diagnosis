#include "network.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

// Format checker just assumes you have Alarm.bif and Solved_Alarm.bif (your file) in current directory
using namespace std;

network read_network(string s)
{
	network Alarm;
	string line;
	int find=0;
	ifstream myfile(s); 
	string temp;
	string name;
	vector<string> values;
	
	if (myfile.is_open())
	{
		while (! myfile.eof() )
		{
			stringstream ss;
			getline (myfile,line);
			
			
			ss.str(line);
			ss>>temp;
			
			
			if(temp.compare("variable")==0)
			{
					
					ss>>name;
					getline (myfile,line);

					stringstream ss2;
					ss2.str(line);
					for(int i=0;i<4;i++)
					{
						ss2>>temp;
					}
					values.clear();
					while(temp.compare("};")!=0)
					{
						values.push_back(temp);
						
						ss2>>temp;
					}
					Graph_Node new_node(name,values.size(),values);
					int pos=Alarm.addNode(new_node);

					
			}
			else if(temp.compare("probability")==0)
			{
					
					ss>>temp;
					ss>>temp;
					
					vector<Graph_Node>::iterator listIt;
					vector<Graph_Node>::iterator listIt1;
					listIt=Alarm.search_node(temp);
					int index=Alarm.get_index(temp);
					ss>>temp;
					values.clear();
					while(temp.compare(")")!=0)
					{
						listIt1=Alarm.search_node(temp);
						listIt1->add_child(index);
						values.push_back(temp);
						
						ss>>temp;

					}
					listIt->set_Parents(values);
					getline (myfile,line);
					stringstream ss2;
					
					ss2.str(line);
					ss2>> temp;
					
					ss2>> temp;
					
					vector<float> curr_CPT;
					string::size_type sz;
					while(temp.compare(";")!=0)
					{	
						curr_CPT.push_back(atof(temp.c_str()));
						
						ss2>>temp;
					}
					
					listIt->set_CPT(curr_CPT);


			}
			else
			{
				
			}
			
		}
		
		if(find==1)
		myfile.close();
	}
	
	return Alarm;
}