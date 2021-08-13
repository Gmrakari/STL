

/*
 * Date:2021-08-13 11:40
 * filename:03_multimap.cpp
 *
 */

/*
 * multimap的特性以及用法与map完全相同，唯一的差别在于它允许键值重复
 * 因此它的插入操作采用的是底层机制RB-tree的insert_equal()而非insert_unique()
 */

template <class Key, class T, class Compare = less<Key>, class Alloc = alloc>
class multimap {
public:
	//typedefs
	// 与map相同
	
	//allocation/deallocation
	//maptimap一定使用insert_equal()而不使用insert_unique()
	//map才使用inert_unique()
	
	template <class InputIterator>
		multimap(InputIterator first, InputIterator last)
		: t(Compare()) { t.insert_equal(first, last); }

	template <class InputIterator>
		multimap(InputIterator first, InputIterator last, const Compare& comp)
		:t(comp) { t.insert_equal(first, last); }

	//其他与map相同
	
	//insert/erase
	iterator insert(const value_type& x) { return t.insert_equal(x); }
	iterator insert(iterator position, const value_type& x) {
		return t.insert_equal(position, x);
	}

	template <class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			t.insert_equal(first, last);
		}
	//其他与map相同
}
