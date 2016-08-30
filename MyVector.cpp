/*
File name: vector
Author: leifeifei
Date: 2016-3-30
update: 2016.8.23
Description: 实现一个向量容器
*/

#include <iostream>
#define CHILD(i) ( 2 * ( i ) + 1)    //用于堆排序
using namespace std;

//定义向量容器
template <class T>
class MyVector
{
template <class T1>
friend ostream & operator << (ostream &out,MyVector<T1> & t);
template <class T1>
friend istream & operator >> (istream &in,MyVector<T1> & t);
public:
typedef T * iterator;         //定义一个输入迭代器
typedef T * const_iterator;   //定义一个只读迭代器
typedef bool (*sortfunp)(T a,T b);  //申明一个排序谓词函数指针，返回值是bool类型

	 //以类中类的形式，定义一个逆向迭代器
   class reverse_iterator
   {  
    public:

      //初始化反向迭代器
   reverse_iterator(T * _ptr = NULL)
    {
         rev = _ptr;
    }

    //将后置++重写成后置--，这是实现逆向迭代器最重要的
    reverse_iterator operator ++ (int i)
    {
        reverse_iterator it = *this;
        this->rev = this->rev-1;
        return it.rev;
    }
      bool operator != (reverse_iterator it)
      {
          return this->rev != it.rev;
      }
      T operator * ()
      {
          return *rev;
      }
      reverse_iterator operator - (int i)
      {
         return this->rev-i;
      }
    private:
        T *rev;
   };

   //无参数 - 构造一个空的vector, 
   MyVector(T * _ptr = NULL)
   {
      v_size = 0;
      v_capacity = 0;
      ptr = _ptr;
   }

   //数量(num)和值(val) - 构造一个初始放入num个值为val的元素的Vector 
  MyVector( int num, const T &val )
   {
   	   resize(num);
   	   int i;
   	   for (i = 0; i < num; i++)
   	   {
   	   	 ptr[i] = val;
   	   }
   }

   //vector(from) - 构造一个与vector from 相同的vector 
   MyVector( const MyVector &from )
   {
   	 resize(from.v_size);
   	 int i;
   	 for (i = 0; i < from.v_size; i++)
   	 {
   	 	ptr[i] = from.ptr[i];
   	 }
   }

   //迭代器(start)和迭代器(end) - 构造一个初始值为[start,end)区间元素的Vector(注:半开区间). 
   MyVector( iterator start, iterator end )
   {
   	   iterator it;
   	   int i = 0;
   	   for (it = start; it != end; it++) //找到start的入口位置
   	   {
            i++;
   	   }
       resize(i);
       i = 0;
       for (it = start; it != end; it++) //将start 到end的元素插入本链表
   	   {
            ptr[i] = *it;
            i++;
   	   }
   }

   ~MyVector()
   {
   	  if(ptr != NULL)
   	  {
   	  	delete ptr;
   	  	ptr = NULL;
   	  }
   }

    void resize( int size)
    {
   	  v_size = size;
   	  v_capacity = 2 * v_size;
   	  ptr = new T[v_capacity];
    }

   //begin()函数返回一个指向当前vector起始元素的迭代器
   iterator begin()
   {
   	   return ptr;
   }

   //end() 函数返回一个指向当前vector末尾元素的下一位置的迭代器.
   iterator end()
   {
   	   return ptr+v_size;
   }

   //返回指向当前vector起始位置的逆迭代器.
    reverse_iterator rend()
    {
      return reverse_iterator(ptr);
    }
    
    //返回指向当前vector末尾的逆迭代器
    reverse_iterator rbegin()
    {
      return reverse_iterator(ptr+v_size);
    }

    //push_back()添加值为val的元素到当前vector末尾
    void push_back( const T &val )
    {
       if(ptr == NULL)  //当ptr为空时
       {
          ptr = new T[1];
       }
        if(v_size + 1 > v_capacity) //判断当前size大小是否超过容量
    	{
    		T * tmp = ptr;
    		iterator it = begin();
    		iterator itend = end(); 
    		resize(v_size);
    		int i = 0;
    		while (it < itend)
    		{
                ptr[i] = *it;
                it++;
                i++;
    		}
    		delete tmp;
    		tmp = NULL;
    	}
      ptr[this->v_size] = val;
      v_size = v_size+1;      
    }

    //删除当前vector最末的一个元素  
    void pop_back()
    {
    	if(v_size == 0)
    	{
    		return;
    	}
    	v_size--;
    }

    //返回当前vector在重新进行内存分配以前所能容纳的元素数量. 
    int capacity()
    {
    	return v_capacity;
    }

    //返回当前vector所容纳元素的数目 
    int size()
    {
    	return v_size;
    }

    //函数删除当前vector中的所有元素.
    void clear()
    {
         v_size = 0;
    }

    //如果当前vector没有容纳任何元素,则empty()函数返回true,否则返回false
    bool empty()
    {
    	if(this->v_size == 0)
    	{
    		return true;
    	}
    	else
    	{
    		return false;
    	}
    }

    //删作指定位置loc的元素,
    iterator erase(iterator loc)
    {
      if (loc == NULL)
      {
      	return NULL;
      }
      int len = this->v_size-1;
      iterator it;
      int i = 0;
      for (it = begin(); it < end(); it++) //找到loc的后一个位置
      {
        if(it == loc)
        {
          it++;
          break;
        }
        i++;
      }
      while ( it != end() )  //将loc的位置后的元素往前移动
      {
        this->ptr[i] = *it;
        it++;
        i++;
      }
      this->v_size = len;
    }

    //删除区间[start, end)的所有元素.返回值是指向删除的最后一个元素的下一位置的迭代器
    iterator erase( iterator start, iterator end )
    {
      while(start != end)
      {
        erase(start);
        start++;
      }
    }

    //front()函数返回当前vector起始元素的引用
    T& front()
    {
    	return *(this->ptr);
    }

    //该函数，主要是为了定位 所删除数据，或者插入数据位置而写的，返回所删除或者插入的位置
    iterator find(iterator start,iterator end,T &val)
    {
    	iterator it;
    	for (it = start; it < end; it++)
    	{
    		if (*it == val)
    		{
    			return it;
    		}
    	}
    	return it;
    } 

    iterator find(const T & val)
    {
    	iterator it;
    	for (it = begin(); it < end(); it++)
    	{
    		if (*it == val)
    		{
    			return it;
    		}
    	}
    	return it;
    }
    
    //在指定位置loc前插入值为val的元素,返回指向这个元素的迭代器,
    iterator insert( iterator loc, const T &val )
    {
     	int len = v_size + 1;
     	iterator it = begin();
        iterator itend = end();
     	if(v_size + 1 > v_capacity)  //当当前size+1大于当前容量时
    	{
    	   T * tmp = ptr;
    	   resize(len - 1);

         //将当前容量的后面元素，往后移动，若移到loc位置，即插入该元素
    	   while( (itend > it) && (len != 0) )  
    	   {
    		    if(itend == loc)
    		    {
    		       this->ptr[len--] = *itend;
    			   this->ptr[len] = val;
    		    }
    		    ptr[--len] = *itend--;   
    	    }
    	    delete tmp;
    	    tmp = NULL;	
    	}
    	else
    	{

            //将当前容量的后面元素，往后移动，若移到loc位置，即插入该元素
    		while(itend != begin() )
    	    {
    		  if(itend == loc)
    		  {
    		    this->ptr[len--] = *itend;
    			this->ptr[len] = val;
    			break;
    		  }
    		  ptr[--len] = *--itend;   
    	    }
    	    v_size += 1;
    	}
    	return loc;	
    }
    
    //在指定位置loc前插入num个值为val的元素 
    void insert( iterator loc, int num, const T &val )
    {
    	while(num--)
    	{
    		insert(loc,val);
    	}
    }

    //在指定位置loc前插入区间[start, end)的所有元素 . 
    void insert( iterator loc, iterator start, iterator end )
    {
    	iterator it;
    	while(start != end)
    	{
    		insert(loc,*--end);
    	} 	 	
    }
    
    //swap()函数交换当前vector与vector from的元素
    void swap( MyVector &from )
    {
    	T * tmp = ptr;
    	ptr = from.ptr;
    	from.ptr = tmp;
    	int t_size = v_size;
    	v_size = from.v_size;
    	from.v_size = t_size;
    	int t_capacity = v_capacity;
    	v_capacity = from.v_capacity;
    	from.v_capacity = t_capacity;
    } 
    
    //堆排序的建堆函数
    void build_heap(T * arr,int i,int len)
    {
    	T tmp;
    	int child;
    	for (tmp = arr[i]; CHILD(i) < len && i < len; i = child)
    	{
    		child = CHILD(i);
    		if (child < len-1 && arr[child] < arr[child+1])
    		{
    			child++;
    		}
    		if (tmp < arr[child])
    		{
    			arr[i] = arr[child];
    		}
    		else
    		{
    			break;
    		}
    	}
        arr[i] = tmp;
    }

    void build_heap(T * arr,int i,int len,sortfunp fp)
    {
    	T tmp;
    	int child;
    	for (tmp = arr[i]; CHILD(i) < len && i < len; i = child)
    	{
    		child = CHILD(i);
    		if (child < len-1 && fp(arr[child] , arr[child+1]) )
    		{
    			child++;
    		}
    		if ( fp(tmp , arr[child]) )
    		{
    			arr[i] = arr[child];
    		}
    		else
    		{
    			break;
    		}
    	}
        arr[i] = tmp;
    }
    
    void sort()
   {
   	 sort(ptr,v_size);
   }

     //默认升序
    void sort(T * arr,int v_size)
    {
    	int i;
    	int val;
    	for (i = v_size/2; i >= 0; i--)
    	{
    		build_heap(arr,i,v_size);
    	}
    	for (i = v_size-1; i >0; i--)
    	{
            val = arr[i];
            arr[i] = arr[0];
            arr[0] = val;
            build_heap(arr,0,i);
    	}
    }


    //根据排序位置决定排序方式
    void sort(sortfunp fp)
    {
    	sort(ptr,v_size,fp);
    }

     //默认升序
    void sort(T * arr,int v_size,sortfunp fp)
    {
    	int i;
    	int val;
    	for (i = v_size/2; i >= 0; i--)
    	{
    		build_heap(arr,i,v_size,fp);
    	}
    	for (i = v_size-1; i >0; i--)
    	{
            val = arr[i];
            arr[i] = arr[0];
            arr[0] = val;
            build_heap(arr,0,i,fp);
    	}
    }

    //该函数，主要为了重写 == != < > <= >= 符号所写
    int compare(const T * left,const T * right)
    {
    	while(left != NULL && right != NULL)
       {
        	if(*left > *right)
        	{
        		return 1;
        		break;
        	}
        	if(*left < *right)
        	{
        		return -1;
        		break;
        	}
        	if(*left == *right)
        	{
        		left++;
        	    right++;
        	}
        }
        return 0;
    }

    //重写下标符号，为了可以像下标一样访问数据
    T & operator[](unsigned index)const
    {
    	return ptr[index];
    }

     bool operator == (MyVector & from)
    {
	     if ( compare(ptr,from.ptr) )
	     {
		     return false;
	     }
	     else
	     {
		     return true;
	     }
	 }

    bool operator != ( MyVector & from)
    {
	    if ( compare(ptr,from.ptr) )
	    {
		    return true;
	    }
	    else
	    {
		    return false;
	    }
    }

    bool operator >= ( MyVector & from)
    {
	    if ( compare(ptr,from.ptr) == -1)
	    {
		    return false;
	    }
	    else
	    {
		    return true;
	    }
    }

    bool operator <= ( MyVector & from)
    {
	    if ( compare(ptr,from.ptr) == 1)
	    {
		      return false;
	    }
	    else
	    {
		    return true;
	    }
    }

    bool operator > ( MyVector & from)
    {
	    if ( compare(ptr,from.ptr) == 1)
	    {
		    return true;
	    }
	    else
	    {
		    return false;
	    }
    }

    bool operator < ( MyVector & from)
    {
	    if( compare(ptr,from.ptr) == -1)
	    {
		    return true;
	    }
	    else
	    {
		    return false;
	    }
    }


   //正序输出
   void output_vector()
   {
  	   iterator it;
  	   for ( it = begin(); it < end(); it++ )
  	   {
  		  cout << *it << '\t';
  	   }
  	   cout << endl;
   }

    //反序输出
    void output_vector_re()
    {
   	   reverse_iterator it;
  	   for (it = rbegin()-1; it != rend(); it++)
  	   {
  		  cout << *it << '\t';
  	   }
  	   cout << *it << endl;
    }

private:
   int v_size;
   int v_capacity;
   T * ptr;
};

//重写输入符号
template<class T>
istream & operator >> (istream &in,MyVector<T> & t)
{
	int i;
	for (i = 0; i < t.capacity(); i++)
	{
		in >> t.ptr[i];
	}
	return in;
}

//重写输出符号
template<class T>
ostream & operator << (ostream &out,MyVector<T> & t)
{
	int i;
	for (i = 0; i < t.capacity(); i++)
	{
		out << t.ptr[i] << "\t";
	}
	return out;
}

int main(int argc, char const *argv[])
{
	MyVector<int> v1(2,88);
	MyVector<int> v2;
	v1.push_back(90);
	v1.push_back(70);
	v1.push_back(39);
	v1.output_vector();
	//v2.output_vector();
    //v1.swap(v2);
	//MyVector<int>::iterator it = v1.find(90);
	//v1.insert(it,55);
	//v1.sort();
	//v1.output_vector();
	// int i;
	// for (i = 0; i< 5; i++)
	// {
	// 	cout << v1[i] << "\t";
	// }
	// cout << endl;
	
	cin >> v2;
	
	v2.output_vector();
	return 0;
}