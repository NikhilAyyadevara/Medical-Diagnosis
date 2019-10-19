#include <bits/stdc++.h>
using namespace std;

void out(string ino, vector<pair<string, vector<double> > > cpt){
	ifstream f;
	f.open(ino);
	fstream outfile;
	outfile.open("solved_alarm.bif",ios::out);

	string line;
	string temp;
	string name_bif;
	if (f.is_open()) {
		while (! f.eof() ) {
			stringstream ss;
			getline (f,line);
			ss.str(line);
			if(line!="")
				outfile << line << "\n";
			ss>>temp;
			if(temp.compare("probability")==0){
				ss>>temp;
				ss>>temp;
				vector<double> p;
				for (int i = 0; i < cpt.size(); ++i){
					if(cpt[i].first==temp){
						p = cpt[i].second;
						// for(int k=0;k<p.size();k++){
						// 	outfile  << p[k] << " ";
						// }
						// outfile << ";" <<"\n";
					}
				}
				while(line!="}"){
					getline(f,line);
					stringstream ss2;
					ss2.str(line);
					string temp2;
					ss2 >> temp2;
					if(temp2=="table"){
						outfile << "\t"<<"table" << " ";
						for(int k=0;k<p.size();k++){
							outfile  << p[k] << " ";
						}
						outfile << ";" <<"\n";
					}
				}
				outfile << line <<"\n";
			}
		}

	}

}


