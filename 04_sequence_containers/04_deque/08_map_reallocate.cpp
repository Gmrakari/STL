

/*
 * Date:2021-06-24 16:05
 * filename:08_map_reallocate.cpp
 *
 */

/*
 * 什么时候map需要重新整治
 * 由reserve_map_at_back() 和 reverse_map_at_front()进行
 * 实际操作则由reallocate_map()执行
 *
 */

void reserve_map_at_back (size_type nodes_to_add = 1) {
	if (nodes_to_add + 1 > map_size - (finish.node - map)) 
		reallocate_map(nodes_to_add, false);
}

void reserve_map_at_front (size_type nodes_to_add = 1) {
	if (nodes_to_add > start.node - map) {
		reallocate_map(nodes_to_add, true);
	}
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::reallocate_map(size_type nodes_to_add, bool add_at_front) {
	size_type old_num_nodes = finish.node - start.node + 1;
	size_t new_num_nodes = old_num_nodes + nodes_to_add;

	map_pointer new_nstart;
	if (map_size > 2 * new_num_nodes) {
		new_nstart = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
		if (new_nstart < start.node)
			copy(start.node, finish.node + 1, new_nstart);
		else 
			copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
	}
	else {
		size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;

		map_pointer new_map = map_allocator::allocate(new_map_size);
		new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
		copy(start.node, finish.node + 1, new_nstart);
		map_allocator::deallocate(map, map_size);
		map = new_map;
		map_size = new_map_size;
	}

	start.set_node(new_nstart);
	finish.set_node(new_nstart + old_num_nodes - 1);
}
