#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;

struct factor{
	vector<string> var;
	vector<pair<string, double> > problist;
};

factor restrict(factor f, string variable, char value){
	factor newfactor;
	int index;
	for(int i = 0; i < f.var.size(); ++i){
		
		if(f.var[i] == variable){
			index = i;
			break;
		}
	}
	
	f.var.erase(f.var.begin()+index+1);
	
	newfactor.var = f.var;
	for(int i = 0; i < f.problist.size(); ++i){
		
		if(f.problist[i].first[index] == value){
			
			double prob = f.problist[i].second;
			string s = f.problist[i].first;
			newfactor.problist.push_back(make_pair(s,prob));
		}	
	}
	return newfactor;
}


factor multiply(factor f1, factor f2){
	vector<int> index1;
	vector<int> index2;
	factor newfactor;
	for(int i = 0; i < f1.var.size(); ++i){
		for(int j = 0; j < f2.var.size(); ++j){
			if(f1.var[i] == f2.var[j]){
				
				index1.push_back(i);
				index2.push_back(j);
				break;
			}
		}
	}
	vector<string> n1 = f1.var;
	for(int i = 0; i < index1.size(); ++i){
		n1.erase(n1.begin()+index1[i]+1);
	}
	
	n1.insert(n1.end(), f2.var.begin(), f2.var.end());
	
	newfactor.var = n1;
	for(int i = 0; i < f1.problist.size(); ++i){
		for(int j = 0; j < f2.problist.size(); ++j){
			
			bool check = true;
			for(int x = 0; x < index1.size(); ++x){
				if(f1.problist[i].first[(index1[x])] != f2.problist[j].first[(index2[x])]){
					check = false;
					break;
				}
				
			}
			
			if(check){
				double mult = f1.problist[i].second * f2.problist[j].second;
				string str1 = f1.problist[i].first;
				string str2 = f2.problist[j].first;
				for(int i = 0; i < index1.size(); ++i){
					str1.erase(str1.begin()+index1[i]);
				}
				string str = str1+str2;
				newfactor.problist.push_back(make_pair(str, mult));
			}
			
		}
	}
	return newfactor;
}


factor sumout(factor f, string variable){
	vector<int> index;
	factor newfactor;
	int out;
	for(int i = 0; i < f.var.size(); ++i){
		if(f.var[i] != variable){
			index.push_back(i);
		}
		if(f.var[i] == variable){
			out = i;
		}
	}
	vector<string> v = f.var;
	v.erase(v.begin()+out);
	newfactor.var = v;
	for(int i = 0; i < f.problist.size()-1; ++i){
		//cout << "check6" << endl;
		double sum = 0;
		for(int j = i+1; j < f.problist.size(); ++j){
			//cout << "check7" << endl;
			bool check = false;
			for(int x = 0; x < index.size(); ++x){
				if(f.problist[i].first[index[x]] == f.problist[j].first[index[x]]){
					check = true;
				}
			}
			if(check){
				sum += f.problist[i].second + f.problist[j].second;
				string str1 = f.problist[i].first;
				
				str1.erase(str1.begin()+out);
				
				
				newfactor.problist.push_back(make_pair(str1,sum));
			}
		}
	}
	
	return newfactor;

}

factor normalize(factor f){
	double pro0;
	double pro1;
	for(int i = 0; i < f.problist.size(); ++i){
		if(f.problist[i].first == "0"){
			pro0 += f.problist[i].second;
		}else if(f.problist[i].first == "1"){
			pro1 += f.problist[i].second;
		}
	}
	double newpro1 = pro1/(pro1+pro0);
	double newpro0 = pro0/(pro1+pro0);

	factor newfactor;
	newfactor.var = f.var;
	vector<pair<string, double> > newpro;
	newpro.push_back(make_pair("0",newpro0));
	newpro.push_back(make_pair("1",newpro1));

	newfactor.problist = newpro;
	return newfactor;
}

factor inference(vector<factor> factors, vector<string> vars, vector<string> HiddenVariables, vector<pair<string, char> > evidences){
	vector<factor> newfactors;
	if(evidences.empty()){
		newfactors = factors;
	}else{
		for(int x = 0; x < factors.size(); ++x){
			for(int i = 0; i < evidences.size(); ++i){
				factor nf;
				nf = restrict(factors[x],evidences[i].first,evidences[i].second);
				newfactors.push_back(nf);
			}
		}
	}
	
	factor newfactor;
	if(newfactors.size() == 1){
		newfactor = newfactors[0];
	}else{
		//cout << "check2" << endl;
		newfactor = newfactors[0];
		for(int j = 1; j < newfactors.size(); ++j){
			factor f = newfactor;
			newfactor = multiply(f,newfactors[j]);	
		}
	}
	//cout << "check3" << endl;
	factor newfactor2;
	newfactor2 = newfactor;
	for(int i = 0; i < HiddenVariables.size(); ++i){
		//cout << "check4" << endl;
		newfactor2 = sumout(newfactor2, HiddenVariables[i]);
	}
	//cout << "check5" << endl;
	return normalize(newfactor2);
}

int main(){
	//use data of the Bayes Nets slide 17
	factor f;   //f = f2
	vector<string> v;
	v.push_back("A");
	v.push_back("B");
	f.var = v;
	vector<pair<string, double> > v1;
	v1.push_back(make_pair("00",0.6));
	v1.push_back(make_pair("01",0.4));
	v1.push_back(make_pair("10",0.1));
	v1.push_back(make_pair("11",0.9));
	f.problist = v1; 

	factor newf;
	newf = restrict(f,"A",'0');

	cout << newf.var[0] << endl;
	cout << newf.problist[0].first << " " << newf.problist[0].second << endl;
	cout << newf.problist[1].first << " " << newf.problist[1].second << endl;


	factor g;   // g = f3
	vector<string> s;
	s.push_back("B");
	s.push_back("C");
	g.var = s;

	vector<pair<string, double> > s1;
	s1.push_back(make_pair("00",0.2));
	s1.push_back(make_pair("01",0.8));
	s1.push_back(make_pair("10",0.3));
	s1.push_back(make_pair("11",0.7));

	g.problist = s1;

	factor newf1;

	newf1 = multiply(f,g);

	for(int i = 0; i < newf1.var.size(); ++i){
		cout << newf1.var[i] << " ";
	}
	cout << endl;

	for(int i = 0; i < newf1.problist.size(); ++i){
		cout << newf1.problist[i].first << " " << newf1.problist[i].second << endl;
	}


	factor newf2;
	newf2 = sumout(f,"A");

	for(int i = 0; i < newf2.var.size(); ++i){
		cout << newf2.var[i] << " ";
	}
	cout << endl;

	for(int i = 0; i < newf2.problist.size(); ++i){
		cout << newf2.problist[i].first << " " << newf2.problist[i].second << endl;
	}


	factor a; // a=f1
	vector<string> m;
	m.push_back("A");
	a.var = m;

	vector<pair<string, double> > m1;
	m1.push_back(make_pair("1",0.9));
	m1.push_back(make_pair("0",0.1));

	a.problist = m1;

	
	vector<factor> vf;
	vf.push_back(f);
	vf.push_back(g);
	vf.push_back(a);

	vector<string> vs;
	vs.push_back("C");

	vector<string> hv;
	hv.push_back("B");
	hv.push_back("A");
	cout << "hv[0] " << hv[0] << endl;
	cout << "hv[1] " << hv[1] << endl;
	
	factor newf3;
	vector<pair<string, char> > k;
	newf3 = inference(vf, vs, hv, k);
	
	for(int i = 0; i < newf3.var.size(); ++i){
		cout << newf3.var[i] << " ";
	}
	cout << endl;

	for(int i = 0; i < newf3.problist.size(); ++i){
		cout << newf3.problist[i].first << " " << newf3.problist[i].second << endl;
	}
	

	//FH = h NDG = D fs = S fm = M NA = a FB = B
	factor FH;
	vector<string> q;
	q.push_back("D");
	q.push_back("M");
	q.push_back("S");
	q.push_back("H");

	vector<pair<string, double> > q1;
	q1.push_back(make_pair("1111", 0.99));
	q1.push_back(make_pair("1110", 0.01));
	q1.push_back(make_pair("1101", 0.65));
	q1.push_back(make_pair("1100", 0.35));
	q1.push_back(make_pair("1011", 0.75));
	q1.push_back(make_pair("1010", 0.25));
	q1.push_back(make_pair("1001", 0.2));
	q1.push_back(make_pair("1000", 0.8));
	q1.push_back(make_pair("0111", 0.9));
	q1.push_back(make_pair("0110", 0.1));
	q1.push_back(make_pair("0011", 0.5));
	q1.push_back(make_pair("0010", 0.5));
	q1.push_back(make_pair("0101", 0.4));
	q1.push_back(make_pair("0100", 0.6));
	q1.push_back(make_pair("0001", 0));
	q1.push_back(make_pair("0000", 1));

	FH.var = q;
	FH.problist = q1;

	factor NA;
	vector<string> w;
	w.push_back("A");

	vector<pair<string, double> > w1;
	w1.push_back(make_pair("0",0.7));
	w1.push_back(make_pair("1",0.3));
	NA.var = w;
	NA.problist = w1;

	factor FS;
	vector<string> e;
	e.push_back("S");

	vector<pair<string, double> > e1;
	e1.push_back(make_pair("0",0.95));
	e1.push_back(make_pair("1",0.05));

	NA.var = e;
	NA.problist = e1;

	factor FM;
	vector<string> r;
	r.push_back("M");

	vector<pair<string, double> > r1;
	r1.push_back(make_pair("0", 0.965));
	r1.push_back(make_pair("1", 0.035));
	FM.var = r;
	FM.problist = r1;

	factor NDG;
	vector<string> t;
	t.push_back("A");
	t.push_back("M");
	t.push_back("D");

	vector<pair<string, double> > t1;
	t1.push_back(make_pair("111",0.8));
	t1.push_back(make_pair("110",0.2));
	t1.push_back(make_pair("001", 0));
	t1.push_back(make_pair("000", 1));
	t1.push_back(make_pair("101",0.5));
	t1.push_back(make_pair("100",0.5));
	t1.push_back(make_pair("011", 0.4));
	t1.push_back(make_pair("010", 0.6));

	NDG.var = t;
	NDG.problist = t1;

}
