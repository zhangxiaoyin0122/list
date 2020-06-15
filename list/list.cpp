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
	//���캯��
	ListIterator(Node* node)
		:_node(node)
	{}
	//  ������:*iterator---->���ؽڵ��ֵ
	Ref operator*() {
		return _node->_value;
	}
	Ptr operator->() {
		return &_node->_value;
	}

	//++:�ƶ�����һ��Ԫ�ص�λ��
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
	//����ͨ��ֻ���const���η�����const������
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
		//����ѭ���ṹ
		_header->_next = _header->_prev = _header;
	}

	//β��
	void pushBack(const T& val) {
		Node* node = new Node(val);

		Node* last = _header->_prev;
		last->_next = node;
		node->_prev = last;

		node->_next = _header;
		_header->_prev = node;
		//insert(end(),val);
	}
	//ͷ��
	void pushFront(const T& val) {
		insert(begin(), val);
	}

	//����λ�õĲ���
	void insert(iterator pos, const T& val) {
		Node* node = new Node(val);

		Node* cur = pos._node; //���õ���������
		Node* prev = cur->_prev;

		prev->_next = node;
		node->_prev = prev;

		node->_next = cur;
		cur->_prev = node;
	}
	//βɾ
	void popBack() {
		earse(--end());
	}
	//ͷɾ
	void popFront() {
		earse(begin());
	}
	//����λ�õ�ɾ��
	//ɾ�����µ�����ʧЧ
	//����ֵ��һ��Ԫ�ص�λ��
	iterator earse(iterator pos) {
		//����ɾ��ͷ���
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
	//��������
	~List() {
		if (_header) {
			clear();
			delete _header;
			_header = nullptr;
		}
	}
	//���������ЧԪ��
	void clear() {
		Node* cur = _header->_next;
		while (cur != _header) {
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		//�ؽ�ѭ���ṹ
		_header->_next = _header->_prev = _header;
	}
	//��������
	List(const List<T>& l)
		:_header(new Node)
	{
		_header->_next = _header->_prev = _header;
		//���
		for (const auto& e : l) {
			pushBack(e);
		}
	}
	//��ֵ�����:�ִ�д��
	List<T> operator=(List<T> l) {
		swap(_header, l->_header);
		return *this;
	}

private:
	Node* _header;
};

//��ӡList
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
//��Χfor��ӡList
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
	