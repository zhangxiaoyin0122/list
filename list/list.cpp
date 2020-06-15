#include <iostream>
#include <string>
using namespace std;

template <class T>
struct ListNode {

	T _value;
	ListNode<T>* _next;
	ListNode<T>* _prev;

	ListNode(const T& val = T())
		:_value(val)
		,_next(nullptr)
		,_prev(nullptr)
	{}
};

template<class T,class Ref,class Ptr>
struct ListIterator {

	typedef ListNode<T> Node;

	typedef ListIterator<T, Ref, Ptr> Self;
	//构造函数
	ListIterator(Node* node)
		:_node(node)
	{}
	//  解引用:*iterator---->返回节点的值
	Ref operator*() {
		return _node->_value;
	}
	Ptr operator->() {
		return &_node->_value;
	}

	//++:移动到下一个元素的位置
	Self& operator++() {
		_node = _node->_next;
		return *this;
	}

	Self& operator--() {
		_node = _node->_prev;
		return *this;
	}

	bool operator!=(const Self& l) {
		return _node != l->_node;
	}
	Node* _node;
};

template<class T>
class List {
public:
	typedef ListNode<T> Node;

	typedef ListIterator<T, T&, T*> iterator;
	//不能通过只添加const修饰符定义const迭代器
	typedef ListIterator<T, const T&, const T*> const_iterator;

	iterator begin() {
		return iterator(_header->_next);
	}

	iterator end() {
		return iterator(_header);
	}

	const_iterator begin()const {
		return const_iterator(_header->_next);
	}

	const_iterator end()const {
		return const_iterator(_header);
	}
	List()
		:_header(new Node)
	{
		//构建循环结构
		_header->_next = _header->_prev = _header;
	}

	//尾插
	void pushBack(const T& val) {
		Node* node = new Node(val);

		Node* last = _header->_prev;
		last->_next = node;
		node->_prev = last;

		node->_next = _header;
		_header->_prev = node;
		//insert(end(),val);
	}
	//头插
	void pushFront(const T& val) {
		insert(begin(), val);
	}

	//任意位置的插入
	void insert(iterator pos, const T& val) {
		Node* node = new Node(val);

		Node* cur = pos._node; //利用迭代器访问
		Node* prev = cur->_prev;

		prev->_next = node;
		node->_prev = prev;

		node->_next = cur;
		cur->_prev = node;
	}
	//尾删
	void popBack() {
		earse(--end());
	}
	//头删
	void popFront() {
		earse(begin());
	}
	//任意位置的删除
	//删除导致迭代器失效
	//返回值下一个元素的位置
	iterator earse(iterator pos) {
		//不能删除头结点
		if (pos != end()) {
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			delete cur;

			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}
		return pos;
	}

	size_t size()const {
		size_t conut = 0;
		for (const auto& e : *this)
			count++;
		return count;
		/*Node* cur = _header->_next;
		while (cur != _header) {
			count++;
			cur=cur->_next
		}*/
	}
	//析构函数
	~List() {
		if (_header) {
			clear();
			delete _header;
			_header = nullptr;
		}
	}
	//清除所有有效元素
	void clear() {
		Node* cur = _header->_next;
		while (cur != _header) {
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		//重建循环结构
		_header->_next = _header->_prev = _header;
	}
	//拷贝构造
	List(const List<T>& l)
		:_header(new Node)
	{
		_header->_next = _header->_prev = _header;
		//深拷贝
		for (const auto& e : l) {
			pushBack(e);
		}
	}
	//赋值运算符:现代写法
	List<T> operator=(List<T> l) {
		swap(_header, l->_header);
		return *this;
	}

private:
	Node* _header;
};

//打印List
template<class T>
void PrintList(const List<T>& l) {
	//typedef ListIterator<T, const T&, const T*> const_iterator;
	ListIterator<T, const T&, const T*>List<T>::const_iterator it = l.begin();
	while (it != l.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
}  
//范围for打印List
template<class T>
void PrintListFor(const List<T>& l) {
	for (auto& e : l) {
		cout << e << " ";
	}
	cout << endl;
}

void test() {
	List<int> lst;
	lst.pushBack(1);
	lst.pushBack(2);
	lst.pushBack(3);
	lst.pushBack(4);
	PrintList(lst);
	PrintListFor(lst);
}

int main() {
	test();
	return 0;
}
	