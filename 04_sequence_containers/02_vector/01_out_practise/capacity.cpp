#include <iostream>
#include <vector>

using namespace std;

int main(){
	vector<int> vec;
	cout << vec.capacity() << endl;

	for(int i = 0; i < 10;++i){
		vec.push_back(i);
		cout << "size: " << vec.size() << endl;
		cout << "capacity: " << vec.capacity() << endl;
	}
	return 0;
	
}
