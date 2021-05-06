
/*
 * Date:2021-05-06 14:16
 * filename:2_01_standard_interface.cpp
 *
 */

allocator::value_type
allocator::pointer
allocator::const_pointer
allocator::reference
allocator::const_reference
allocator::size_type
allocator::difference_type

allocator::rebind

allocator::allocator()
	default constructor

allocator::allocator(const allocator&)
	copy constructor

template <class U>allocator::allocator(const allocator<U>&)

allocator::~allocator()
	destructor

pointer allocator::address(reference x) const

const_pointer allocator::address(const_reference x) const

pointer allocator::allocate(size_type n,const void* = 0)

void allocator::deallocate(pointer p,size_type n)

size_type allocator::max_size() const

void allocator::construct(pointer p,const T& x)
	==> new((void*) p) T(x)

void allocator::destroy(pointer p)
	==> p->~T()
