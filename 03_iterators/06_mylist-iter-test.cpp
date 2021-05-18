

/*
 * Date:2021-05-18 20:43
 * filename:06_mylist-iter-test.cpp
 *
 */

#include "06_mylist-iter.h"
#include "06_mylist.h"
#include <bits/stdc++.h>
using namespace std;

void main()
{
	List<int> mylist;
	
	for(int i = 0;i < 5;++i)
	{
		mylist.insert_front(i);
		mylist.insert_end(i + 2);
	}
	mylist.display(); //

	ListIter<ListItem<int> > begin(mylist.front());
	ListIter<ListItem<int> > end;
	ListIter<ListItem<int> > iter;

	iter = find(begin,end,3);
	if(iter == end)
		cout << "not found" << endl;
	else
		cout << "found" << iter->val() << endl;

	iter = find(begin,end,7);
	if(iter == end)
		cout << "not found" << endl;
	else
		cout << "found" << iter->val() << endl;
	
}
