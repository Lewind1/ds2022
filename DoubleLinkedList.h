#include<iostream>
#include<initializer_list>
#include<cstdlib>
template <typename Ob>
/**
储存数据类型为Ob的双向列表
*/
class List
{
    private:
  	  struct Node
 	   {
 	   	Object data;
 	   	Node *prev;
 	   	Node *next;
 	   	
 	   	Node(const Object & d = Object{},Node * p = nullptr,Node * n = nullptr)
 	   	 :data{d},prev{p},next{n}{}
 	   	/**
 	        创建并赋值一个新节点（元素），仅使用其他数据的值，且确保不改变其他数据
 	   	*/
 	   	Node(Object && d,Node * p = nullptr,Node *n =nullptr)
 	   	 :data{std::move(d)},prev{p},next{n}{}
 	   	/**
 	   	创建并赋值一个新节点（元素）
 	   	*/				 
 	   };
 	   /**
 	   定义了一个双向链表的节点（元素）
 	   */
    public:
	  class const_iterator
	   {
	   	public:
	   		const_iterator() : current{nullptr}
	   		 {}
	   		
	   		const Object & operator*() const
	   		 {return retrieve（）;}
	   		/**
 	   		定义const_iterator的*操作
 	   		*/
	   		const_iterator & operator++()
	   		 {current =current->next;
	   		  return *this;}
	   		 }
	   		/**
 	   		定义const_iterator的++操作
 	   		*/
	   		const_iterator operator++(int)
	   		 {
	   		 const_iterator old = *this;
	   		 ++(*this);
	   		 return old;
	   		 }
	   		/**
 	   		使用const_iterator的下一个位置但不改变本身位置？？？
 	   		*/
	   		bool operator==(const const_iterator & rhs)const
	   		 {return current == rhs.current;}
	   		/**
 	   		定义const_iterator的比较为current的比较，比较仅为当时的值比较
 	   		*/
	   		bool operator!=(const const_iterator & rhs)const
	   		 {return !(*this == rhs);}
	   		/**
 	   		定义const_iterator的比较为current的比较，比较仅为当时的值比较???
 	   		*/
	   	protected:
	   		Node *current;
	   		/**
 	   		iterator的current指向节点（元素）
 	   		*/
	   		Object & retrieve() const
	   		 {return current->data;}
	   		/**
 	   		获取迭代器当前所处位置的值
 	   		*/
	   		const_iterator(Node *p) : current{p}
	   		 {}
	   		/**
 	   		将迭代器移动到 p 上？？？
 	   		*/
	   		friend class List<Object>;
	   		/**
 	   		友好类 列表？？？
 	   		*/
	   };
	   /**
	   定义了一个迭代器类：const_iterator
	   */
	  class iterater: public const_iterator
	   {
	   	public:
	   	 	iterator()
	   	 	{}
	   	 	
	   	 	Object & operator* ()
	   	 	{return const_iterator::retrieve():}
	   	 	
	   	 	const Object & operator* ()const
	   	 	{return const_iterator::operator*();}
	   	 	
	   	 	iterator & operator++()
	   	 	{
	   	 		this->current = this->current->next;
	   	 		return *this;
	   	 	}
	   	 	
	   	 	iterator operator++(int)
	   	 	{
	   	 		iterator old = *this;
	   	 		++(*this);
	   	 		return old;
	   	 	}
	   	 
	   	 protected:
	   	 	iterator(Node *p) : const_iterator{p}
	   	 	{}
	   	 	
	   	 	friend class List<Object>;
	   };
	   /**
	   定义了另一个迭代器类:iterator？？？
	   */
    public:
	  List()
	   {init();}
	   /**
	   开始一个新的双向链表
	   */
	   
	  ~List()
	   {clear();
	   delete head;
	   delete tail;}
	   /**
	   析构链表，防止数据泄漏
	   */
	    
	  List(const List & rhs)
	   {
	   	init();
	   	for(auto & x : rhs)
	   		push_back(x);
	   }
	   /**
	   开始一个新的双向链表，并按顺序把rhs填入链表？
	   */
	  
	  List & operator = (const List & rhs)
	   {
	   	List copy = rhs;
	   	std::swap(*this,copy);
	   	return *this;
	   }
	   /**
	  复制链表？？？
	  */
	  
	  List(List && rhs)
	   : theSize{rhs.theSize},head{rhs.head},tail{rhs.tail}
	   {
	   	rhs.theSize = 0;
	   	rhs.head = nullptr;
	   	rhs.tail = nullptr;
	   }
	  /**
	  剪切链表？？？
	  */
	  
	  List & operator= (List && rhs)
	   {
	   	std::swap(theSize,rhs.theSize);
	   	std::swap(head,rhs.head);
	   	std::swap(tail,rhs.tail);
	   	return *this;
	   }
	   /**
	  交换链表？？？
	  */
	  
	  iterator begin()
	   {return {head->next};}
	   /**
	  返回链表中的第一个元素的位置
	  */
	  
	  const_iterator begin() const
	   {return {head->next};}
	   /**
	  返回链表中第一个元素的位置，为确定数值，并确保不改变任何数据
	  */
	  
	  iterator end()
	   {return {tail};}
	   /**
	  返回链表末尾元素的下一个位置
	  */
	
	  const_iterator end() const
	   {return {tail};}
	  /**
	  返回链表末尾元素的下一个位置，为确定数值，并确保不改变任何数据
	  */
	  
	  int size() const
	   {return theSize;}
	  /**
	  返回链表长度
	  */
	  
	  bool empty() const
	   {return size() == 0;}
	   /**
	  判断链表是否为空链表
	  */
	  
	  void clear()
	  {
	   while(!empty())
	     pop_front();
	  }
	  /**
	  清楚链表中的所有元素
	  */
	  
	  Object & front()
	   {return *begin();}
	   /**
	  返回链表中的第一个元素
	  */
	  
	  const Object & front() const
	   {return *begin();}
	   /**
	  返回链表中的第一个元素，为确定数值，并确保不改变任何数据
	  */
	  
	  Object & back()
	   {return *--end();}
	   /**
	  返回链表中的最后一个元素
	  */
	  
	  const Object & back() const
	   {return *--end();}
	   /**
	  返回链表的最后一个元素，为确定数值，并确保不改版任何数据
	  */
	  
	  void push_front(const Object & x)
	   {insert(begin(),x);}
	  /**
	  在链表开头加上一个元素x，仅采用x的值
	  */
	  
	  void push_front(Object && x)
	   {insert(begin(),std::move(x));}
	  /**
	  在链表开头加上一个元素x，把x移动到链表
	  */
	  
	  void push_back(const Object & x)
	   {insert(end(),x);}
	  /**
	  在链表末尾加上一个元素x，仅采用x的值
	  */
	  
	  void push_back(Object && x)
	   {insert(end(),std::move(x));}
	  /**
	  在链表末尾加上一个元素x，把x移动到链表
	  */
	  
	  void pop_front()
	   {erase(begin());}
	  /**
	  从链表开头弹出（删除）一个元素
	  */
	  
	  void pop_back()
	   {erase(--end());}
	  /**
	  从链表末尾弹出（删除）一个元素
	  */
	  
	  iterator insert(iterator itr,const Object & x)
	   {
	   	Node *p = itr.current;
	   	theSize++;
	   	return{p->prev = p->prev-next = new Node{x,p->prev,p}};
	   }
	  /**
	  在itr前插入一个元素x，并只采用x的值
	  */
	  
	  itarator insert(iterator itr,Object && x)
	   {
	   	Node *p = itr.current;
	   	theSize++;
	   	return{p->prev = p->prev-next = new Node{std::move(x),p->prev,p}};
	   }
	  /**
	  在itr前插入一个元素x，将x移动到链表中
	  */
	  
	  iterator erase(iterator itr)
	   {
	   	Node *p = itr.current;
	   	iterator retVal{p->next};
	   	p->prev->next = p->next;
	   	p->next->prev = p->prev;
	   	delete p;
	   	theSize--;
	   	return retVal;
	   }
	  /**
	  删除迭代器所在位置的元素
	  */
	  iterator erase(iterator from,iterator to)
	   {
	   	for(iterator itr = from; itr != to;)
	   		itr=erase(itr);
	   	return to;
	   }
    	 /**
    	 清除从from到to前的所有元素，并将迭代器放置在to位置
    	 */
    private:
	  int theSize;
	  Node *head;
	  Node *tail;
	  
	  void init()
	   {
	   	theSize = 0;
	   	head = new Node;
	   	tail = new Node;
	   	head->next = tail;
	   	tail->prev = head;
	   }
	   /**
	   开始一个新双向链表
	   */
};
    
