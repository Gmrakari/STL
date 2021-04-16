
#include <iostream>
#include <vector>
using namespace std;

int main(){

		vector<int> a;

		vector<int> b(10);
	
		vector<int> c(10,1);

		vector<int> e(c);

		vector<int> f(c.begin(),c.end() + 3);

		int n[] = {1, 2, 3, 4, 5};

		vector<int> g(n,n+5);

		vector<int> h(&n[1],&n[4]);

		/*
		 *
		cin >> c[2];
		cin >> c[3];
		cin >> c[4];
	
		*/

		int i = 0;
	


		for(i = 0;i < g.size();i++){
			cout << "g[" << i << "] = "  <<  g[i] << "  " ;
		}
		cout<<endl;
	
		vector<int>::iterator t;
		for(t = g.begin(); t != g.end();t++)
				cout<<*t<<" ";


		/*

		for(i = 0;i < b.size();i++){
			cout << b[i] << endl;
		}
		
		*/
}
