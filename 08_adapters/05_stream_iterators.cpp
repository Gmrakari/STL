

/*
 * Date:2021-09-11 10:42
 * filename:05_stream_iterators.cpp
 *
 */

/*
 * stream iterators 可以将迭代器绑定到一个stream(数据流)对象身上。
 * 绑定到istream对象(例如 std::cin)者，称为istream_iterator
 * std::cout 称为ostream_iterator
 *
 * 所谓绑定一个istream object，其实就是在istream iterator内部维护一个istream member
 * 客户端对于迭代器所做的operator++操作，会被引导调用迭代器内部所含的那个istream member的输入操作
 * (operator>>)。
 * 这个迭代器Input Iterator,不具备operator--
 *
 */

//这是一个input iterator,能够为"来自某一basic_istream"的对象执行格式化输入操作
//istream_iterator<T, charT, traits, Distance>
//然而一般使用input iterators时都只使用第一个template参数，此时以下仍适用
template <class T, class Distance = ptrdiff_t>
class istream_iterator {
	friend bool
	operator== __STL_NULL_TMPL_ARGS(const istream_iterator<T, Distance>& x, 
			const istream_iterator<T, Distance>& y);
protected:
	istream* stream;
	T value;
	bool end_marker;
	void read() {
		end_marker = (*stream) ? true : false;
		if (end_marker) *stream >> value; //关键
		//以上，输入之后，stream的状态可能改变，所以下面再判断一次以决定end_marker
		//当读到eof或读到型别不符的资料,stream即处于false状态
		end_marker = (*stream) ? true : false;
	}
public:
	typedef input_iterator_tag iterator_category;
	typedef T value_type;
	typedef Distance difference_type;
	typedef const T* pointer;
	typedef const T& reference;
	
	//以上，因身为input iterator,所以采用const比较保险
	
	istream_iterator() : stream(&cin), end_marker(false) {}
	istream_iterator(istream& s) : stream(&s) { read(); }

	//以上两行的用法:
	//istream_iterator<int> eos;					//造成end_marker为false;
	//istream_iterator<int> initer(cin);	//引发read()。程序至此会等待输入
	//因此，下面这两行客户端程序
	//istream_iterator<int> initer(cin); (A)
	//cout << "please input..." << endl; (B)
	//会停留在(A)等待一个输入，然后才执行(B)出现提示信息。这是不合理的现象
	//规避之道:永远在最必要的时候，才定义一个istream_iterator
	
	reference operator*() const { return value; }
	pointer operator->() const { return &(operator*()); }

	//迭代器前进一个位置,就代表要读取一笔资料
	istream_iterator<T, Distance>& operator++() {
		read();
		return *this;
	}

	istream_iterator<T, Distance> operator++(int) {
		istream_iterator<T, Distance> tmp = *this;
		read();
		return tmp;
	}
};

//这是一个output iterator,能够将对象格式化输出到某个basic_ostream上
//ostream_iterator<T, charT, traits>
//然而一般使用onput iterators时都只使用第一个template参数，此时以下仍适用
template <class T>
class ostream_iterator {
protected:
	ostream* stream;
	const char* string; //每次输出后的间隔符号  变量名称为string也可以!

public:
	typedef output_iterator_tag iterator_category;
	typedef void								value_type;
	typedef void								difference_type;
	typedef void								pointer;
	typedef void								reference;

	ostream_iterator(ostream& s) : stream(&s), string(0) {}
	ostream_iterator(ostream& s, const char* c) : stream(&s), string(c) {}
	//以上ctors用法
	//ostream_iterator<int> outiter(cout, ' '); //输出至cout,每次间隔一空格
	
	//对迭代器做赋值(assign)操作，就代表要输出一笔资料
	ostream_iterator<T>& operator=(const T& value) {
		*stream << value;					//关键：输出数字
		if (string) 
			*stream << string;			//如果间隔符号不为空，输出间隔符号
		return *this;
	}

	//注意以下三个操作
	ostream_iterator<T>& operator*() { return *this; }
	ostream_iterator<T>& operator++() { return *this; }
	ostream_iterator<T>& operator++(int) { return *this; }
};

/*
 * ostream_iterator<int> outite(cout, " ");
 * copy(id.begin(), id.end(), outite);
 *
 * template <class RandomAccessIterator, class OutputIterator, class Distance>
 * inline OutputIterator
 * __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance *) {
 *   for (Distance n = last - fist; n > 0; --n, ++result, ++first) {
 *			*result = *first;	//result是一个ostream_iterator object
 *   }
 *   return result;
 * }
 *
	ostream_iterator<T>& operator=(const T& value) {
		*stream << value;					//关键：输出数字
		if (string) 
			*stream << string;			//如果间隔符号不为空，输出间隔符号
		return *this;
	}
	ostream_iterator<T>& operator*() { return *this; }
	ostream_iterator<T>& operator++() { return *this; }
	ostream_iterator<T>& operator++(int) { return *this; }
 */

/*
 * 根据ostream_iterator的定义,对result取值，返回的是自己。对result执行赋值(assign)操作，
 * 则是将operator=右手边的东西输出到cout去。
 * 当copy()算法进入for循环的下一次迭代时，会引发++result,而根据ostream_iterator的定义，对result累加
 * 会返回自己。
 * 如此持续下去，直到资料来源结束(first == last)为止
 *
 */

