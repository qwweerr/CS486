#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <sstream>
using namespace std;

vector<pair<char,pair<int,int> > > city;
vector<char> unvisit;
vector<char> visit;
vector<pair<char,vector<int> > > distancelist;
vector<pair<pair<char,char>, int> > MST;
vector<char> path;
int node = 0;

// compute the distance from one city to all other city
void createGraph(vector<pair<char,pair<int,int> > > city){
	char c;
	vector<int> d;
	int x1, y1, x2, y2;
	int dis;
	pair<char, vector<int> > distance;
	for(int i = 0; i < city.size(); ++i){
		c = (city[i]).first;
		x1 = (city[i].second).first;
		y1 = (city[i].second).second;
		for(int j = 0; j < city.size(); ++j){
			x2 = (city[j].second).first;
			y2 = (city[j].second).first;
			dis = sqrt((pow((x1-x2),2)+ pow((y1-y2),2)));
			d.push_back(dis);
		}
		distance = make_pair(c,d);
		distancelist.push_back(distance);
	}
	//cout << "print2" << endl;
}

// find the minimun spanning tree
void findMST(vector<pair<char,vector<int> > > distancelist, char s){
	int low = 0;
	int n = 0;
	char des;
	for(int i = 0; i < distancelist.size(); ++i){
		if(distancelist[i].first == s){
			for(int j = 0; j < distancelist[i].second.size(); ++j){
				if((distancelist[i].second)[j] == 0){
					continue;
				}
				if(low == 0){
					low = (distancelist[i].second)[j];
					n = j;
				}else{
					if((distancelist[i].second)[j] <= low){
						low = (distancelist[i].second)[j];
						n = j;
					}
				}
			}	
		}
		des = s+n;
		pair<char,char> e = make_pair(s,des);
		pair<pair<char,char>, int> f = make_pair(e,low);
		MST.push_back(f);
		s = des;
	}
	//cout << "print3" << endl;
}

//heuristic function
int function(vector<pair<pair<char,char>, int> > MST, char s){
	int n = unvisit.size();
	//cout << MST.size() << endl;
	int cost = 0;
	while(n > 0){
		//cout << "print6" << endl;
		for(int i = 0; i < MST.size(); ++i){
			if(MST[i].first.first == s && MST[i].second != 0){
				//cout << s << endl;
				cost += MST[i].second;
				//node++;
				break;
			}
		}
		n--;
	}
	// find the nearst unvisit city to start city A
	int num;
	for(int i = 0; i < MST.size(); ++i){
		if(MST[i].first.first == s && MST[i].first.second == 'A'){
			num = MST[i].second;
		}
	}
	cost += num;
	//cout << "print4" << endl;
	return cost;
}


//A* search
void A_star(vector<char> unvisit, char s){
	path.push_back(s);
	char des;
	int h = 0;
	for(int i = 0; i < unvisit.size(); ++i){
		//cout << "print5" << endl;
		if(h == 0){
			h = function(MST,unvisit[i]);
			//des = unvisit[i];
			//path.push_back(des);
		} 
		if(h < function(MST,unvisit[i])){
			h = function(MST,unvisit[i]);
			des = unvisit[i];
			path.push_back(des);
		}
		node++;
	}
	visit.push_back(s);
	unvisit.erase(unvisit.begin());
	// for(int i = 0; i < unvisit.size(); ++i){
	// 	cout << unvisit[i] << ' ';
	// }
	// cout << endl;
	if(!unvisit.empty()){
		A_star(unvisit,des);
		//cout << "print" << endl;
	}
}





int main(){
	int numOfCity = 0;
	bool first = true;
	char name;
	int x,y;
	string line;
	//read in data from file
	//cout << "print" << endl;
	ifstream myfile("instance_3.txt");
		while(getline(myfile,line)){
			if(first){
				first = false;
			}else{
				istringstream ss(line);
				ss >> name;
				ss >> x;
				ss >> y;
				unvisit.push_back(name);
				pair<int,int> coordinate;
				coordinate = make_pair(x,y);
				pair<char, pair<int,int> > citydata;
				citydata= make_pair(name,coordinate);
				city.push_back(citydata);
			}
		}
		//cout << "print1" << endl;
	createGraph(city);
	findMST(distancelist,'A');
	A_star(unvisit,'A');
	// path.push_back('A');
	// for(vector<char>::iterator it = path.begin(); it != path.end(); ++it){
	// 	cout << *it << ' ';
	// }
	// cout << endl;
	cout << node << endl;
	return 0;
}
