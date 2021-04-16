
#include <iostream>
#include <vector>
using namespace std;

int main(){

	vector< vector<int> > b(10,vector<int>(5,0));

	cin >> b[1][1];
	cin >> b[2][2];
	cin >> b[3][3];


	int m,n;
	for(m = 0; m < b.size();m++){
		for(n = 0;n < b[m].size();n++)
				cout << b[m][n] << " ";
		cout << endl;
	}

	return 0;
}

