

/*
 * Date:2021-06-21 16:18
 * filename:05_ctor.cpp
 *
 */


deque 缓冲区扩充操作相当琐碎繁杂

deque<int,alloc,8> ideq(20, 9);

其缓冲区大小为8(个元素),并令其保留20个元素空间，每个元素初值为9

为了指定deque的第三个template参数(缓冲区大小)，我们必须将前两个参数都知名出来
因此必须明确指定alloc为空间配置器。

deque自行定义了两个专属的空间配置器
protected:
//专属之空间配置器，每次配置一个元素大小
	typedef simple_alloc<value_type, Alloc> data_allocator;
//专属之空间配置器，每次配置一个指针大小
	typedef simple_alloc<pointer, Alloc> map_allocator;

	并提供有一个constructor 如下:
	deque(int n, const value_type value) 
	 : start(), finish(), map(0), map_size(0)
	{
		fill_initialize(n, value);
	}

	元素的处置设定妥当:
	template <class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::fill_initialize(size_type n, const value_type& value) {
		create_map_and_nodes(n);//把deuqe的结构都产生并安排好
		map_pointer cur;
		__STL_TRY {
			//为每个节点的缓冲区设初值
			for (cur = start.node; cur < finish.node; ++cur)
				uninitialized_fill(*cur, *cur + buffer_size(), value);
			//最后一个节点的设定稍有不同(因为尾端可能有备用空间，不必设初值)
			uninitialized_fill(finish.first, finish.cur, value);
		}
		catch(...) {
			...
		}
	}

	其中create_map_and_nodes() 负责产生并安排好deque的结构
	template<class T,class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::create_map_and_nodes(size_type num_elements) {
		//需要结点数=(元素个数 / 每个缓冲区可容纳的元素个数) + 1
		//如果刚好整除,会多配一个节点
		size_type num_nodes = num_elements / buffer_size() + 1;

		//一个map要管理几个节点，最少8个，最多是"所需节点数加2"
		//(前后各预留一个，扩充时可用)
		map_size = max(initial_map_size(), num_nodes + 2);
		map = map_allocator::allocate(map_size);

		//以上配置出一个"具有map_size个节点"的map

		//以下令nstart和nfinish指向map所拥有之全部节点的最中央区段
		//保持在最中央，可使头尾两端的扩充能量一样打。每个节点可对应一个缓冲区
		map_pointer nstart = map + (map_size - num_nodes) / 2;
		map_pointer nfinish = nstart + num_nodes - 1;

		map_pointer cur;

		__STL_TRY {
			//为map内的每个现用节点配置缓冲区。所有缓冲区加起来就是deque的
			//可用空间(最后一个缓冲区可能留有一些余裕)
			for (cur = nstart; cur <= nfinish;++cur)
				*cur = allocate_node();
		}
		catch(...) {
			...
		}
		
		//为deque内的两个迭代器start和end设定正确内容
		start.set_node(nstart);
		finish.set_node(nfinish);
		start.cur = start.first;
		finish.cur = finish.first + num_elements % buffer_size();
		// 此前说过，如果刚好整除，会多配一个节点
		// 此时即令cur指向这多配的一个节点(所对映之缓冲区)的起始处
	}


