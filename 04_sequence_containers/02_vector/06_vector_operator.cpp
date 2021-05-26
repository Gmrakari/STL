

/*
 * Date:2021-05-26 16:50
 * filename:06_vector_operator.cpp
 *
 */

/*
 * pop_back,erase,clear,insert
 */

//将尾端元素拿掉，并调整大小
void pop_back() {
	--finish;
	destroy(finish);
}

//清除[first,last]中的所有元素
iterator erase(iterator first, iterator last) {
	iterator i = copy(last, finish,first);
	destroy(i, finish);
	finish = finish - (last - first);
	return first;
}

// 清除某个位置的元素
iterator erase(iterator position) {
	if (position + 1 != end()) {
		copy(position + 1, finish, position);
		--finish;
		destroy(finish);
		return position;
	}
}

void clear() { erase(begin(),end()); }

//vector::insert()

//从position开始，插入n个元素，元素初值为x
template <class T, class Alloc>
void vector<T, ALloc>::insert(iterator position, size_type n, const T& x) {
	if (n != 0 ) {
		if (size_type(end_of_storage - finish)  >= n) {
			//备用空间大于等于"新增元素个数"
			T x_copy = x;
			//以下计算插入点之后的现有元素个数
			const size_type elems_after = finish - position;
			iterator old_finish = finish;
			if (elems_after > n) {
				//"插入点之后的现有元素的个数" 大于 "新增元素个数"
				uninitialized_copy(finish - n, finish, finish);
				finish += n;//将vector元素后移
				copy_backward(position, old_finish - n, old_finish);
				fill(position, position + n, x_copy);//从插入点开始填入新值
			}
			else {
				//"插入点之后的现有元素的个数" 大于 "新增元素个数"
				uninitialized_fill_n(finish, n - elems_after, x_copy);
				finish += n - elems_after;
				uninitialized_copy(position, old_finish, finish);
				finish += elems_after;
				fill(position, old_finish, x_copy);
			}
		}
		else {
			//备用空间小于 "新增元素个数"
			//首先决定新长度:旧长度的2倍,或旧长度 + 新增元素的个数
			const size_type old_size = size();
			const size_type len = old_size() + max(old_size, n);

			//配置新的vector 空间
			iterator new_start = data_allocator::allocate(len);
			iterator new_finish = new_start;
			__STL_TRY {
				//1-首先将旧vector的插入点之前的元素复制到新空间
				new_finish = uninitialized_copy(start, position, new_start);
				//2-再将新增元素(初始值为n)填入到新空间
				new_finish = uninitialized_fill_n(new_finish, n, x);
				//3-再将旧的vector的插入点之后的元素复制到新的空间
				new_finish = uninitialized_copy(position, finish, new_finish);
			}
#ifdef __STL_USE_EXCEPTIONS
			catch(...) {
				//"commit or rollback"
				destroy(new_start, new_finish);
				data_allocator::deallocate(new_start, len);
				throw;
			}
#endif
			//清除并释放旧的vector
			destroy(start, finish);
			deallocate();
	
			//调整水位标记
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + len;
		}
	}
}
