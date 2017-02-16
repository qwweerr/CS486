#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <math.h>
using namespace std;

struct example{
	vector<double> attribute;
	int healthy;
};

struct node{
	double threshold;
	int attribute;
	int healthy;
	int colic;
	node *left;
	node *right;
};

vector<example> list;

bool com1(pair<double,double> i, pair<double,double> j){
	return i.second < j.second;
}

bool com2(pair<int, pair<double,double> > i, pair<int, pair<double,double> > j){
	return i.second.second < j.second.second;
}

//caculate the information gain of the choose attribute.
double IG(double threshold, vector<pair<double,int> > l){
	double positive = 0;
	double negative = 0;
	double I = 0;
	double LEFT = 0;
	double RIGHT = 0;
	double lp = 0;
	double ln = 0;
	double rp = 0;
	double rn = 0;
	for(int i = 0; i < l.size(); ++i){
		if(l[i].second == 1 && l[i].first <= threshold){
			lp++;
		}
		if(l[i].second == 0 && l[i].first <= threshold){
			ln++;
		}
		if(l[i].second == 1 && l[i].first > threshold){
			rp++;
		}
		if(l[i].second == 0 && l[i].first > threshold){
			rn++;
		}
	}
	double sum1 = lp+ln;
	if(lp != 0 && ln != 0){
		LEFT = (-(lp/(sum1))) * log2 (lp/sum1) +
			(-(ln/sum1)) * log2 (ln/sum1);
	}

	double sum2 = rp+rn;
	if(rp != 0 && rn != 0){
		RIGHT = (-(rp/sum2)) * log2(rp/sum2) +
			(-(rn/sum2)) * log2(rn/sum2);
	}

	positive = lp + rp;
	negative = ln + rn;

	if(positive != 0 && negative != 0){
		I = (-(positive/(positive+negative))) * log2 (positive/(positive+negative)) +
			(-(negative/(positive+negative))) * log2 (negative/(positive+negative));
	}

	double x = lp+ln;
	double y = rn+rp;
	double z = l.size();
	double result = (I - (x/z)*LEFT + -(y/z)*RIGHT);
	return result;
}

//find out under current example which attributes can get the hightest IG.
pair<int, pair<double,double> > max_IG(vector<example> le){
	vector<pair<int, pair<double,double> > > m;
	int count = 0; 
	while(count < 16){
		vector<pair<double,int> > value;
		int attribute = count;
		for(int i = 0; i < le.size(); ++i){
			double v = le[i].attribute[count];
			int check = le[i].healthy;
			value.push_back(make_pair(v,check));
		}
		vector<pair<double,double> > v1;
		for(int i = 0; i < value.size(); ++i){
			double threshold = value[i].first;
			double ig = IG(threshold,value);
			v1.push_back(make_pair(threshold,ig));
		}

		pair<double,double> f;
		
		int s = v1.size();

		f = *(max_element(v1.begin(),v1.begin()+s,com1));
		count++;
		m.push_back(make_pair(attribute,f));
	}
	
	pair<int, pair<double,double> > p;
	int size = m.size();
	p = *(max_element(m.begin(),m.begin()+size,com2));
	return p;
}

//bulid tree, using train data.
node* create(vector<example> data){
	int dlen = data.size();
	int t = 0;
	int f = 0;
	for(int i = 0; i < dlen; ++i){
		if(data[i].healthy == 1){
			t++;
		}
		if(data[i].healthy == 0){
			f++;
		}
	}
	if(t == dlen || f == dlen){
		node *n = new node;
		n->threshold = -1;
		n->attribute = -1;
		if(t == dlen){
			n->healthy = 1;
		}else{
			n->healthy = -1;
		}
		if(f == dlen){
			n->colic = 0;
		}else{
			n->colic = -1;
		}
		n->left = NULL;
		n->right = NULL;
		return n;

	}
	node *root = new node;
	pair<int, pair<double,double> >  check;
	check = max_IG(data);
	int attri = check.first;
	double thre = check.second.first;
	root->threshold = thre;
	root->attribute = attri;
	root->healthy = -1;
	root->colic = -1;

	vector<example> left;
	vector<example> right;
	for(int i = 0; i < data.size(); ++i){
		if(data[i].attribute[attri] <= thre){
			left.push_back(data[i]);
		}
		if(data[i].attribute[attri] > thre){
			right.push_back(data[i]);
		}
	}

	
	root->left = create(left);
	root->right = create(right);
	return root;
}

int pass(example data, node *tree){
	int sum = 0;
	if(tree == NULL){
		return sum;
	}
	if(tree->threshold == -1){
		if(tree->healthy == data.healthy){
			sum = 1;
		}
		if(tree->colic == data.healthy){
			sum = 1;
		}
	}else{
		//cout << "here" << endl;
		int attri = tree->attribute;
		//cout << "attribute: " << attri << endl;
		double thre = tree->threshold;
		//cout << "threshold: " << thre << endl;
		//cout << "data attribute: " << data.attribute[attri] << endl;
		if(data.attribute[attri] <= thre){
			//cout << "c3" << endl;
			sum = pass(data, tree->left);
		}
		if(data.attribute[attri] > thre){
			//cout << "c4" << endl;
			sum = pass(data,tree->right);
		}
	}
	return sum;
}

int print(node* tree){
	if(tree == NULL){
		return 0;
	}
	cout << "attri: " << tree->attribute << endl;
	cout << "threshold: " << tree->threshold << endl;
	cout << "healthy: " << tree->healthy << endl;
	cout << "colic: " << tree->colic << endl;
	if(tree->left == NULL){
		cout << "right1" << endl;
		print(tree->right);
		return 0;
	}
	if(tree->right == NULL){
		cout << "left1" << endl;
		print(tree->left);
		return 0;
	}
	if(tree->left != NULL && tree->right != NULL){
		cout << "left" << endl;
		print(tree->left);
		cout << "right" << endl;
		print(tree->right);
	}
}

int main(){
	
	fstream file;
	file.open("horseTrain.txt");
	string fline;
	while(getline(file,fline)){
		example e;
		double num;
		string situation;
		istringstream fs(fline);
		string line;
		int count = 0;
		while(getline(fs,line,',')){
			istringstream ss(line);
			if(count < 16){
				ss >> num;
				e.attribute.push_back(num);
				count++;
			}else{
				count = 0;
				ss >> situation;
				//cout << situation << endl;	
				if(situation == "healthy."){
					e.healthy = 1;
				}
				if(situation == "colic."){
					e.healthy = 0;
				}
			}
		}
		list.push_back(e);
	}
	// for(int i = 0; i < list.size(); ++i){
	// 	cout << "size: "<< list[i].attribute.size() << endl;
	// 	for(int j = 0; j < (list[i]).attribute.size(); ++j){
	// 		cout << list[i].attribute[j] << " ";
	// 	}
	// 	cout << "healthy: "<< list[i].healthy;
	// 	cout << endl;
	// }
	// cout << list.size() << endl;
	node *tree;
	cout << "start" << endl;
	tree = create(list);
	cout << "build" << endl;
	
	int f = print(tree);
	
vector<example> test;
	fstream file1;
	file1.open("horseTest.txt");
	string fline1;
	while(getline(file1,fline1)){
		example e;
		double num;
		string situation;
		istringstream fs(fline1);
		string line;
		int count = 0;
		while(getline(fs,line,',')){
			istringstream ss(line);
			if(count < 16){
				ss >> num;
				e.attribute.push_back(num);
				count++;
			}else{
				count = 0;
				ss >> situation;
				//cout << situation << endl;	
				if(situation == "healthy."){
					e.healthy = 1;
				}
				if(situation == "colic."){
					e.healthy = 0;
				}
			}
		}
		test.push_back(e);
	}
	// for(int i = 0; i < test.size(); ++i){
	// 	cout << "size: "<< test[i].attribute.size() << endl;
	// 	for(int j = 0; j < (test[i]).attribute.size(); ++j){
	// 		cout << test[i].attribute[j] << " ";
	// 	}
	// 	cout << "healthy: "<< list[i].healthy;
	// 	cout << endl;
	// }
	double right1 = 0;
	for(int i = 0; i < list.size(); ++i){
		//cout << "check" << endl;
		right1 += pass(list[i], tree);
		//cout << "check1" << endl;
	}
	double total1 = list.size();
	cout << "train right answer: " << right1 << endl;
	cout << "train total instance: " << total1 << endl;
	cout << "train accuracy: " << right1/total1 << endl;

	double right = 0;
	for(int i = 0; i < test.size(); ++i){
		//cout << "check" << endl;
		right += pass(test[i], tree);
		//cout << "check1" << endl;
	}
	double total = test.size();

	cout << "right answer: " << right << endl;
	cout << "total instance: " << total << endl;
	cout << "accuracy: " << right/total << endl;
}
