/*
File name: My_List
Author: leifeifei
Date: 2016-3-30
UpDate: 2016-8-22
Description: 实现一个双链表容器
*/

#include <iostream>
using namespace std;

//申明链表容器类
template<class T>
class MyList;

//定义链表结点类
template<class T>
class Node
{
friend class MyList<T>;
public:
    Node()
    {
        next = NULL;
        pre_next = NULL;
    }
    Node(T _data, Node<T> * _pre_next = NULL, Node<T> * _next = NULL)
    {
    	data = _data;
    	pre_next = _pre_next;
    	next = _next;
    	
    }
private:
	T data;
	Node<T> * next;     //指向链表下一结点
	Node<T> * pre_next; //指向链表前一结点
};

//定义链表容器类
template<class T>
class MyList
{
typedef bool (*sortfunp)(T a,T b);   //申明一个排序谓词函数指针，返回值是bool类型
typedef bool (*removenode)(T data);  //申明一个条件删除结点函数指针，返回值是bool类型
typedef bool (*is_unique)(T a,T b);  //申明一个判定数据是否无重复函数指针，返回值是bool类型
public:
    
    //类中建迭代器
	class iterator
	{
	friend class MyList;
	public:
		iterator(Node<T> * _ptr = NULL)
		{
			ptr = _ptr;
		}
		bool operator != (iterator it)
		{
			 return it.ptr != ptr;
		}
		bool operator == (iterator it)
		{
			return this->ptr->data = it.ptr->data;
		}
        
        T& operator * ()
        {
            return this->ptr->data;
        }
        void operator = (iterator it)
        {
            this->ptr = it.ptr;
        }
        iterator operator ++ (int i)
        {
        	iterator it = *this;
        	this->ptr = this->ptr->next;
        	return it;
        }

        iterator operator + (int num)
        {
        	while (ptr != NULL && num--)
        	{
                ptr = ptr->next;
        	}
        	return ptr;
        }

        iterator operator - (int num)
        {
        	if (ptr == NULL)
        	{
        		return ptr;
        	}
        	while (ptr != NULL & num--)
        	{
        		return ptr = ptr->pre_next;
        	}
        	return ptr;
        }
	private:
		Node<T> * ptr;

	};
	MyList()
	{
		head = NULL;
		curr = NULL;
	}
    
    ////带结点数初始化链表
	MyList(int num)
	{
		head = NULL;
		curr = NULL;
		Node<T> * newnode = NULL;
		while (num--)
		{
			newnode = new Node<T>;
			if (head == NULL)
			{
				head = newnode;
				curr = newnode;
			}
			else
			{
				curr = head;
	            while(curr->next != NULL)
	            {
	        	   curr = curr->next;
	            }
		        curr->next = newnode;
		        newnode->pre_next = curr;
			}
		    newnode = NULL;
		}
	}

    //带值，带结点数初始化链表
	MyList(int num,T data)
	{
       head = NULL;
       curr = NULL;
       while (num--)
       {
       	  push_back(data);
       }
	}

    //以其他链表作为副本初始化
	MyList(MyList & from)
	{
       head = NULL;
       curr = NULL;
       Node<T> * tmp = from.head;
       while (tmp != NULL)
       {
       	  push_back(tmp->data);
       	  tmp = tmp->next;
       }
	}
    
    //将另一链表[start,end)元素，初始化链表
	MyList(iterator start,iterator end)
	{
       head = NULL;
       curr = NULL;
       while (start != end)
       {
       	  push_back(*start);
       	  start++;
       }
       if (start.ptr != NULL)
       {
       	push_back(*start);
       }
	}
    
    //析构链表
	~MyList()
	{
		if(head != NULL)
		{
			delete head;
			head = NULL;
		}
		if(curr != NULL)
		{
			delete curr;
			curr = NULL;
		}
	}

	 //返回头结点位置
	iterator begin()
	{
		return iterator(head);
	}

    //返回最后一个结点的后一个地址值，即NULL
	iterator end()
	{
		return iterator();
	}

    //返回一个逆向迭代器，指向链表的末尾。
	iterator rbegin()
	{
        curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        return iterator(curr);
	}

    //返回一个逆向迭代器，指向链表的末尾。
    iterator rend()
    {
    	return iterator(head);
    }
    
    bool empty()
	{
		if (head == NULL && curr == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//将val连接到链表的头部。
    void push_front( const T &val )
    {
    	Node<T> *newnode = NULL;
        newnode = new Node<T>(val);
        if( empty() )  //当链表头结点即当前结点为空时
    	{
             head = newnode;
             curr = newnode;
    	}
    	else
    	{
    		newnode->next = head;
    		head->pre_next = newnode;
    		head = newnode;
    	}
    }
    
    //将val连接到链表的最后
    void push_back( const T &val )
    {
    	Node<T> *newnode = NULL;
        newnode = new Node<T>(val);
    	if(head == NULL)
    	{
             head = newnode;
             curr = newnode;
    	}
    	else
    	{
    		curr = head;
            while(curr->next != NULL)
            {
        	   curr = curr->next;
            }
            curr->next = newnode;
            newnode->pre_next = curr;
    	} 	
    }

     //删除链表的第一个元素。
    void pop_front()
    {
    	if( !empty() )
    	{
    		Node<T> * tmp = head;
    		head = head->next;
    		head->pre_next = NULL;
    		delete tmp;
    		tmp = NULL;
    	}
    	else
    	{
    		cout<<"the list is empty!"<<endl;
    	}
    }

    //删除链表的最后一个元素。
    void pop_back()
    {
    	if( !empty() )
    	{
    		curr = head;
    		Node<T> * tmp = curr;
    		while(tmp->next != NULL)
            {
               curr = tmp;
               tmp = tmp->next;
            }
            curr->next = NULL;
            tmp->pre_next = NULL;
            delete tmp;
            tmp = NULL;
    	}
    	else
    	{
    		cout<<"the list is empty!"<<endl;
    	}
    }

     //该函数，主要是为了定位 所删除数据，或者插入数据位置而写的，返回所删除或者插入的位置
    iterator find(iterator start,iterator end,T data)
    {
        while(start != end)
        {
        	if(*start == data)
        	{
        		return start;
        		break;
        	}
        	start++;
        }
        return start;
    }

    iterator find(const T &val )
    {
    	iterator it;
    	for (it = begin(); it != end(); it++)
    	{
    		if (*it == val)
    		{
    			return it;
    			break;
    		}
    	}
    	return it;
    }

     //插入元素val到位置pos，
    iterator insert( iterator pos, const T &val )
    {
        if (pos.ptr == NULL)
        {
        	cout << "wrong address" << endl;
        	return iterator();
        }
    	Node<T> *tmp = NULL;
    	
    	tmp = pos.ptr;
    	if (tmp == head)
    	{
    		push_front(val);
    	}
    	else if (tmp->next == NULL)
    	{
    		push_back(val);
    	}
    	else
    	{
    		curr = tmp->pre_next;
    		Node<T> * newnode = new Node<T>(val,curr,tmp);
    		curr->next = newnode;
    		tmp->pre_next = newnode;
    	}
    	return iterator(newnode);
    }

    //插入num个元素val到pos之前
    void insert( iterator pos, int num, const T &val )
    {
    	while(num--)
    	{
    		insert(pos,val);
    	}
    }

    //插入start到end之间的元素到pos的位置
    void insert( iterator pos, iterator start, iterator end )
    {
    	while(start != end)
    	{ 
    		insert(pos,*start);
    		start++;
    	}
    	if (start.ptr != NULL)
    	{
    		insert(pos,*start);
    	}
    }

    void erase(const T & val)
    {
    	if (head->data == val)
    	{
    		pop_front();
    		return;
    	}

    	Node<T> * tmp = head->next;
    	Node<T> * q = NULL;
    	while (tmp != NULL)
    	{
    		if (tmp->data == val)
    		{
    			break;
    		}
    		tmp = tmp->next;
    	}
    	if (tmp != NULL && tmp->next == NULL)
    	{
    		pop_back();
    	}
    	else if (tmp != NULL && tmp->next != NULL)
    	{
    		q = tmp->pre_next;
    		curr = tmp->next;
    		q->next =curr;
    		curr->pre_next = q;
    		delete tmp;
    		tmp = NULL;
    	}    	
    }

    //删除以pos指示位置的元素, 
    iterator erase( iterator pos )
    {
    	if ( pos.ptr == NULL )
    	{
            cout << "wrong address" << endl;
            return pos;
    	}    	
    	Node<T> * tmp = NULL;
    	Node<T> * q = NULL;
    	tmp = pos.ptr;
    	if (tmp == head)
    	{    		
    		pop_front();
    		return iterator(head);
    		
    	}
    	else if (tmp->next == NULL)
    	{
    		pop_back();
    		return iterator(tmp->pre_next);
    		
    	}
    	else
    	{
           curr = tmp->pre_next;
           q = tmp->next;
           curr->next = q;
           q->pre_next = curr;
           delete tmp;
           tmp = NULL;
           return iterator(q);
    	}

    }

     //或者删除start和end之间的元素。
    iterator erase( iterator start, iterator end )
    {
          while(start != end)
          {
          	erase(start);
          	start++;
          }
          if (start.ptr != NULL)
          {
          	erase(start);
          }
    }

    //把自己和lst链表连接在一起，产生一个整齐排列的组合链表
    void merge( MyList &from )
    {
    	from.curr = from.head;
    	while(from.curr->next != NULL)
    	{
    		from.curr = from.curr->next;
    	}
    	from.curr->next = head;
    	head->pre_next = from.curr;
    	head = from.head;
        sort(head,NULL);     
    }

    //如果指定compfunction，则将指定函数作为比较的依据。
    void merge( MyList &from, sortfunp fp  )
    {
        from.curr = from.head;
        while(from.curr->next != NULL)
        {
            from.curr = from.curr->next;
        }
        from.curr->next = head;
        head->pre_next = from.curr;
        head = from.head;
        sort(head,NULL,fp);     
    }
    
    //删除链表中所有值为val的元素
    void remove(const T &val)
    {
        if(head->data == val)  //若删除结点为头结点时
        {
            pop_front();
        }
        Node<T> * tmp = head->next;
        curr = head;
        while(tmp != NULL)
        {
            //所删除结点下一结点不为空时
            if( tmp->data == val && tmp->next != NULL )
            {
                curr->next = tmp->next;
                tmp->next->pre_next = curr;    
                delete tmp;
                tmp = NULL;
                break;
            }

            //所删除结点下一结点为空时
            if( tmp->data == val && tmp->next == NULL )
            {
                pop_back();
                break;
            }
            curr = tmp;
            tmp = tmp->next;
        }
    }

    //以一元谓词pr为判断元素的依据，遍历整个链表。如果pr返回true则删除该元素。
    void remove_if(removenode pr)
    {
        if(pr(head->data))
        {
            pop_front();
        }

        Node<T> *tmp = head->next;
        curr = head;

        while(tmp != NULL)
        {
            //所删除结点下一结点不为空时
            if ( pr(tmp->data) && tmp->next != NULL )
            {
               curr->next = tmp->next;
               tmp->next->pre_next = curr; 
                delete tmp;
                tmp = NULL;
                break;
            }

            //所删除结点下一结点为空时
            if ( pr(tmp->data) && tmp->next == NULL )
            {
                pop_back();
                break;
            }
            curr = tmp;
            tmp = tmp->next;  
        }
    }
   
    //返回一个引用，指向链表的第一个元素。
    iterator& front()
    {
        return iterator(head);
    }

    //返回list中元素的数量
    int size()
    {
    	curr = head;
    	int i = 0;
    	while (curr != NULL)
    	{
    		curr = curr->next;
    		i++;
    	}
    	return i;
    }

    void swap_sort(Node<T> * left,Node<T> * right)
    {
    	if (left == right)
    	{
    		return;
    	}
    	T val = left->data;
    	left->data = right->data;
    	right->data = val;

    }

    void sort()
    {
    	sort(head,NULL);
    }

    //为链表排序，默认是升序
    void sort(Node<T> * left,Node<T> * right)
    {
    	if (left == right)
    	{
    		return;
    	}
    	Node<T> * base = left;
    	Node<T> * slow = base;
    	Node<T> * fast = base->next;
    	while (fast != right)
    	{
            if (base->data > fast->data)
            {
            	slow = slow->next;
            	swap_sort(slow,fast);
            }
            fast = fast->next;
    	}
    	swap_sort(base,slow);
    	sort(base,slow);
    	sort(base->next,NULL);
    }
    
    //如果指定compfunction的话，就采用指定函数来判定两个元素的大小。
    void sort(Node<T> * left,Node<T> * right,sortfunp fp )
    {
    	Node<T> * base = left;
    	Node<T> * slow = base;
    	Node<T> * fast = base->next;
    	while ( fp(fast < right) )
    	{
            if (base->data > fast->data)
            {
            	slow = slow->next;
            	swap_sort(&slow,&fast);
            }
            fast = fast->next;
    	}
    	swap_sort(&base,&slow);
    	sort(base,slow,fp);
    	sort(base->next,NULL,fp);
    }

     //把lst连接到pos的位置。
    void splice( iterator pos, MyList &from )
    {
    	if (pos.ptr == NULL)
    	{
            cout << "wrong address" << endl;
            return;
    	}
    	Node<T> * tmp = NULL;

        if (pos.ptr == head)
        {
           tmp = from.head;
           while (tmp->next != NULL)
           {
           	 tmp = tmp->next;
           }
           tmp->next = head;
           head->pre_next = tmp;
           head = from.head;
        }
        if (pos.ptr->next == NULL)
        {
        	tmp = head;
        	while (tmp->next != NULL)
            {
           	 tmp = tmp->next;
            }
            tmp->next = from.head;
            from.head->pre_next = tmp;
        }
        else
        {
        	curr = pos.ptr->pre_next;
        	tmp = from.head;
            while (tmp->next != NULL)
            {
           	   tmp = tmp->next;
            }
            tmp->next = curr->next;
            curr->next->pre_next = tmp;
            curr->next = from.head;
            from.head->pre_next = curr;
        }
    	
    }

    //如果指定其他参数，则插入lst中del所指元素到现链表的pos上
    void splice( iterator pos, MyList &from, iterator del )
    {  
    	insert(pos,*del);
    }

    //或者用start和end指定范围。
    void splice( iterator pos, MyList &lst, iterator start, iterator end )
    {
    	while (start != end)
    	{
    		insert(pos,*start);
    		start++;
    	}
    	if (start.ptr != NULL)
    	{
    		insert(pos,*start);
    	}
    	
    }

    //交换lst和现链表中的元素。
    void swap(MyList &lst)
    {
    	Node<T> *tmp = NULL;
    	tmp = lst.head;
    	lst.head = head;
    	head = tmp;
    }

    //删除链表中所有重复的元素
    void unique()
    {
    	sort(head,NULL);
    	curr = head;
    	Node<T> * tmp = head->next;

    	while (tmp != NULL)
    	{
    		if (curr->data == tmp->data)
    		{
    			curr = tmp;
    			tmp = tmp->next;
    			erase(curr->data);
     		}
    		else
    		{
    			curr = tmp;
    			tmp = tmp->next;
    		}
    	}
    }

    //如果指定pr，则使用pr来判定是否删除
    void unique(is_unique pr )
    {
       sort(head,NULL);
        curr = head;
    	Node<T> * tmp = head->next;

    	while (tmp != NULL)
    	{
    		if ( pr(curr->data == tmp->data) )
    		{
    			curr = tmp;
    			tmp = tmp->next;
    			erase(curr->data);
     		}
    		else
    		{
    			curr = tmp;
    			tmp = tmp->next;
    		}
    	}
    }

    //删除list的所有元素
    void clear()
    {
    	if( !empty() )
    	{
            Node<T> * tmp;
    	    curr = head->next;
    	    while(curr->next != NULL)
    	    {
    	    	tmp = curr;
    	    	curr->pre_next = NULL;
    	    	curr = curr->next;
                head->next = curr;
                curr->pre_next = head;
    		    delete tmp;
    		    tmp = NULL;
    	   }
    	   delete head;
    	   delete curr;
    	   head = NULL;
    	   curr = NULL;
    	}
    	else
    	{
    		cout<<"the list is empty!"<<endl;
    	}
    	
    }

	 //输出链表
	void output_mylist()
	{
		if( !empty() )   //判断该链表是否为空
		{
			iterator it;
		    for(it = begin(); it != end(); it++)
		    {
			   cout << *it << '\t';
		    }
		    cout << endl;
		}
		else
    	{
    		cout << "the list is empty!" << endl;
    	}	
	}

private:
	Node<T> * head;
	Node<T> * curr;
};

//定义排序谓词
template <class T>
bool sortdirection (T a,T b)
{
	return a > b;
}

//定义一种默认删除结点
template <class T>
bool isremove(T data)
{
	if(data == 88)
	{
        return true;
    }
    else
    {
        return false;
    }
}

//根据此函数判断数据是否唯一
template<class T>
bool isunique(T a,T b)
{
    if(a == b)
    {
        return true;
    }
    else
    {
        return false;
    }
}


int main(int argc, char const *argv[])
{
	MyList<int> a;
	MyList<int> a1;
	a.push_back(73);
    a.push_back(28);
    a.push_back(88);
    a.push_back(72);
    a.push_back(73);
    a.push_back(28);
    a.push_back(88);
    a.push_front(100);
    a.output_mylist();
    a1.push_back(3);
    a1.push_back(8);
    a1.push_back(18);
    a1.push_back(20);
    a1.push_back(68);
    //a1.output_mylist();
    //a.pop_back();
    //a.unique();
    //a.sort();
    MyList<int>::iterator itret=a.find(88);
    // MyList<int>::iterator itret2=a1.find(20);
    //a.splice(itret,a1,a1.begin()+2,a1.end());
    //a.erase(itret);
    //a.splice(itret,a1,itret2);
    //a.swap(a1);
    // a.erase(a.begin()+2,a.end());
    //a.insert(itret,3,222);
    //a.splice(itret,a1);
    //a.remove_if(isremove);
    //a.splice(itret,a1,itret2);
    //a.merge(a1);
    //a.insert(itret,528);
    //a.insert(itret,a1.begin()+1, a1.end());
    a.output_mylist();  
    //MyList<int> a2(a1.begin(), a1.end() ); 
    //a2.output_mylist();
	return 0;
}

