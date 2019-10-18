#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Graph_Node
{

	private:
		string Node_Name;  // Variable name 
		vector<int> Children; // Children of a particular node - these are index of nodes in graph.
		vector<string> Parents; // Parents of a particular node- note these are names of parents
		int nvalues;  // Number of categories a variable represented by this node can take
		vector<string> values; // Categories of possible values
		vector<float> CPT; // conditional probability table as a 1-d array . Look for BIF format to understand its meaning

	public:
		vector<int> indexParents;
		vector<float> observations;
		vector<float> CPT_temp;
		Graph_Node(string, int, vector<string>);
		string get_name();
		vector<int> get_children();
		vector<string> get_Parents();
		vector<float> get_CPT();
		int get_nvalues();
		vector<string> get_values();
		void set_CPT(vector<float>);
		void set_Parents(vector<string>);
		int add_child(int);
		void updateCPT();
		int get_value_index(string);
		void printCPT();
		void printObservations();
};