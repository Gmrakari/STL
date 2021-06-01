

/*
 * Date:2021-06-01 17:28
 * filename:05_list-merge_reverse_sort.cpp
 *
 */

//merge() 将x合并到*this身上。两个lists的内容都必须先经过递增排序
template <class T, class Alloc>
void list<T, Alloc>::merge(list<T, Alloc>& x) {
	iterator first1 = begin();
	iterator last1=  end();
	iterator first2 = x.begin();
	iterator last2 = x.end();

	//注意，前提是，两个lists都已经递增排序
	while (first1 != last1 && first2 != last2) {
		if (*first2 < *first1) {
			iterator next= first2;
			transfer(first1, first2, ++next);
			first2 = next;
		}
		else
			++first1;
		if (first2 != last2) {
			transfer(last1, first2, last2);
		}
	}
}

//多看transfer的实现，具体是怎么transfer的。模拟出来

//reverse() 将*this的内容逆向重置
template <class T, class Alloc>
void list<T, Alloc>::reverse() {
	//以下判断，如果是空表，或仅有一个元素，就不进行任何操作
	// 使用size() == 0 || size() == 1来判断 慢
	if (node->next == node || link_type(node->next)->next == node) 
		return ;
	iterator first = begin();
	++first;
	while (first != end() ) {
		iterator old = first;
		++first;
		transfer(begin(), old, first);
	}
}

// list 不能使用STL算法sort()，必须使用自己的sort() member function
// 因为STL算法sort() 只介绍RamdonAccessIterator
// 本函数使用quick sort
template <class T, class Alloc>
void list<T, Alloc>::sort() {
	//以下判断，如果是空表，或仅有一个元素，就不进行任何操作
	// 使用size() == 0 || size() == 1来判断 慢
	if (node->next == node || link_type(node->next)->next == node) 
		return ;

	//一些新的lists，作为中介数据存放区
	list<T, Alloc> carry;
	list<T, Alloc> counter[64];
	int fill = 0;
	while (!empty()) {
		carry.splice(carry.begin(), *this, begin());
		int i = 0;
		while( i < fill && !counter[i].empty() ) {
			counter[i].merge(carry);
			carry.swap(counter[i++]);
		}
		carry.swap(counter[i]);
		if (i == fill) ++fill;
	}
	for (int i = 1; i < fill;++i) {
		counter[i].merge(counter[i - 1]);
	}
	swap(counter[fill - 1]);
		
}


