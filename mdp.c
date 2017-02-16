#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct cell{
	string location;
	int initial;
	double current;
};


void value_iteration(vector<cell> list){
	for(int i = 0; i < 25; ++i){
		for(vector<cell>::iterator it = list.begin(); it != list.end(); ++it){
			if(it->location == "LT"){
				//cout << "LT" << endl;
				double sum1 = 0;
				sum1 = it->initial + 0.9*(0.8*(list[1].current)+0.1*(list[3].current)+0.1*(it->current));
				double sum2 = 0;
				sum2 = it->initial + 0.9*(0.1*(list[1].current)+0.8*(list[3].current)+0.1*(it->current));
				double sum3 = 0;
				sum3 = it->initial + 0.9*(0.8*(it->current)+0.1*(list[1].current)+0.1*(it->current));
				double sum4 = 0;
				sum4 = it->initial + 0.9*(0.8*(it->current)+0.1*(list[3].current)+0.1*(it->current));
				it->current = max(max(sum1,sum2),max(sum3,sum4));

			}
			if(it->location == "MT"){
				//cout << "MT" << endl;
				double sum1 = 0;
				sum1 = it->initial + 0.9*(0.8*(list[2].current)+0.1*(list[4].current)+0.1*(it->current));
				double sum2 = 0;
				sum2 = it->initial + 0.9*(0.8*(list[0].current)+0.1*(list[4].current)+0.1*(it->current));
				double sum3 = 0;
				sum3 = it->initial + 0.9*(0.8*(list[4].current)+0.1*(list[0].current)+0.1*(list[2].current));
				it->current = max(max(sum1,sum2),max(sum2,sum3));
			}
			if(it->location == "RT"){
				continue;
			}
			if(it->location == "LC"){
				//cout << "LC" << endl;
				double sum1 = 0;
				sum1 = it->initial + 0.9*(0.8*(list[0].current)+0.1*(list[4].current)+0.1*(it->current));
				double sum2 = 0;
				sum2 = it->initial + 0.9*(0.8*(list[6].current)+0.1*(list[4].current)+0.1*(it->current));
				double sum3 = 0;
				sum3 = it->initial + 0.9*(0.8*(list[4].current)+0.1*(list[0].current)+0.1*(list[6].current));
				double sum4 = 0;
				sum4 = it->initial + 0.9*(0.8*(it->current)+0.1*(list[0].current)+0.1*(list[6].current));
				it->current = max(max(sum1,sum2),max(sum4,sum3));
			}
			if(it->location == "MC"){
				//cout << "MC" << endl;
				double sum1 = 0;
				sum1 = it->initial + 0.9*(0.8*(list[1].current)+0.1*(list[3].current)+0.1*(list[5].current));
				double sum2 = 0;
				sum2 = it->initial + 0.9*(0.8*(list[3].current)+0.1*(list[1].current)+0.1*(list[7].current));
				double sum3 = 0;
				sum3 = it->initial + 0.9*(0.8*(list[7].current)+0.1*(list[3].current)+0.1*(list[5].current));
				double sum4 = 0;
				sum4 = it->initial + 0.9*(0.8*(list[5].current)+0.1*(list[1].current)+0.1*(list[7].current));
				it->current = max(max(sum1,sum2),max(sum3,sum4));

			}
			if(it->location == "RC"){
				//cout << "RC" << endl;
				double sum1 = 0;
				sum1 = it->initial + 0.9*(0.8*(list[4].current)+0.1*(list[2].current)+0.1*(list[8].current));
				double sum2 = 0;
				sum2 = it->initial + 0.9*(0.8*(list[2].current)+0.1*(list[4].current)+0.1*(it->current));
				double sum3 = 0;
				sum3 = it->initial + 0.9*(0.8*(list[8].current)+0.1*(list[4].current)+0.1*(it->current));
				it->current = max(max(sum1,sum2),max(sum2,sum3));
			}
			if(it->location == "LB"){
				//cout << "LB" << endl;
				double sum1 = 0;
				sum1 = it->initial + 0.9*(0.8*(list[3].current)+0.1*(it->current)+0.1*(list[7].current));
				double sum2 = 0;
				sum2 = it->initial + 0.9*(0.8*(list[7].current)+0.1*(it->current)+0.1*(list[3].current));
				double sum3 = 0;
				sum3 = it->initial + 0.9*(0.1*(list[7].current)+0.8*(it->current)+0.1*(it->current));
				double sum4 = 0;
				sum4 = it->initial + 0.9*(0.1*(list[3].current)+0.8*(it->current)+0.1*(it->current));
				it->current = max(max(sum1,sum2),max(sum3,sum4));
				//cout << it->current << endl;
			}
			if(it->location == "MB"){
				//cout << "MB" << endl;
				double sum1 = 0;
				sum1 = it->initial + 0.9*(0.8*(list[4].current)+0.1*(list[6].current)+0.1*(list[8].current));
				double sum2 = 0;
				sum2 = it->initial + 0.9*(0.8*(list[6].current)+0.1*(list[4].current)+0.1*(it->current));
				double sum3 = 0;
				sum3 = it->initial + 0.9*(0.8*(list[8].current)+0.1*(list[4].current)+0.1*(it->current));
				double sum4 = 0;
				sum4 = it->initial + 0.9*(0.1*(list[8].current)+0.1*(list[6].current)+0.8*(it->current));
				it->current = max(max(sum1,sum2),max(sum4,sum3));
			}
			if(it->location == "RB"){
				//cout << "RB" << endl;
				double sum1 = 0;
				sum1 = it->initial + 0.9*(0.8*(list[5].current)+0.1*(it->current)+0.1*(list[7].current));
				double sum2 = 0;
				sum2 = it->initial + 0.9*(0.8*(list[7].current)+0.1*(it->current)+0.1*(list[5].current));
				double sum3 = 0;
				sum3 = it->initial + 0.9*(0.1*(it->current)+0.8*(it->current)+0.1*(list[5].current));
				double sum4 = 0;
				sum4 = it->initial + 0.9*(0.1*(it->current)+0.8*(it->current)+0.1*(list[7].current));
				it->current = max(max(sum1,sum2),max(sum3,sum4));
			}
		}
	}
	int f = 0;
	for(vector<cell>::iterator it = list.begin(); it != list.end(); ++it){
		cout << it->current << " ";
		f++;
		if(f == 3){
			cout << endl;
			f = 0;
		} 
	}
}


int main(){
	vector<cell> list;
	cell c1;
	c1.location = "LT";
	c1.initial = 3;
	c1.current = 3;
	cell c2;
	c2.location = "MT";
	c2.initial = -1;
	c2.current = -1;
	cell c3;
	c3.location = "RT";
	c3.initial = 10;
	c3.current = 10;
	cell c4;
	c4.location = "LC";
	c4.initial = -1;
	c4.current = -1;
	cell c5;
	c5.location = "MC";
	c5.initial = -1;
	c5.current = -1;
	cell c6;
	c6.location = "RC";
	c6.initial = -1;
	c6.current = -1;
	cell c7;
	c7.location = "LB";
	c7.initial = -1;
	c7.current = -1;
	cell c8;
	c8.location = "MB";
	c8.initial = -1;
	c8.current = -1;
	cell c9;
	c9.location = "RB";
	c9.initial = -1;
	c9.current = -1;
	

	list.push_back(c1);
	list.push_back(c2);
	list.push_back(c3);
	list.push_back(c4);
	list.push_back(c5);
	list.push_back(c6);
	list.push_back(c7);
	list.push_back(c8);
	list.push_back(c9);
	
	
	value_iteration(list);
	
	
	
}
