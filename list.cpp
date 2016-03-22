 //模板单链表
#include <iostream>
using namespace std;

template<class T>
class list;

template<class T>
class listnode
{
	friend class list<T>;
public:
	listnode ()
	{
		next=NULL;
	}

	listnode (T _data)
	{
		data=_data;
		next=NULL;
	}
	listnode<T> * creatnode(T _data,listnode<T> *next=NULL)
	{
		listnode<T> * newnode=new listnode<T>(_data);
        newnode->next=next;
        return newnode;
	}

private:
	T  data;
    listnode<T> *next; 
};

template<class T>
class list
{
public:
	list ()
	{
		head=new listnode<T>(100);
	}

    ~list ()
    {
        deletenodes();
    }

    //释放节点
    void deletenodes()
    {
        listnode<T> *curr=head->next;
        listnode<T> *tmp;
        while(curr->next != NULL)
        {
        	tmp=curr;
        	curr=curr->next;
        	delete tmp;
        }
        delete curr;
        delete head;
        //head=NULL;
    }

     //创建链表
    bool creatlist(int num)
    {
    	listnode<T> *curr=head;
    	T data_in;
    	int j;
    	for(j=1;j<=num;j++)
    	{
    		cout<<"请输入第"<<j<<"个节点的数据"<<endl;
    	    cin>>data_in;    
    		listnode<T> * newnode=curr->creatnode(data_in,curr->next);
    		curr->next=newnode;
    		curr=curr->next;
    	}
    	return true;
    }

    //显示链表数据
	void display()
	{
		listnode<T> *curr=head->next;
		int j=1;
		while(curr != NULL)
		{
			cout<<j<<'\t'<<curr->data<<'\t';
			curr=curr->next;	
			j++;
		}
		cout<<endl;

	}

	//找到某个节点位置
	listnode<T> * locate(int i)
	{
        listnode<T> *curr=head->next;
        if (i==0)
        {
        	return head;
        }
		int k=1;
		if(i == k)
		{
			return curr;
		}

		while(k <= i)
		{
			curr=curr->next;
			if(curr->next == NULL)
			{
				return curr;
				break;
			}
			k++;
		}
		return curr;

	}
     
	//插入第几个节点之后  
    bool insert (int i)
    {
    	listnode<T> *curr=locate(i);
    	if (curr==NULL)
    	{
    		return false;
    	}
    	cout<<"请输入你想加入节点的数据值"<<endl;
	    cin>>curr->data;
    	listnode<T> *newnode=new listnode<T>(curr->data);
    	listnode<T> *tmp;
    	tmp=curr->next;
    	curr->next=newnode;
    	newnode->next=tmp; 
    	return true;
    }  

    //计算链表的长度  
    int Length()
    {
    	if(isempty())
    	{
    		return 0;
    	}
    	listnode<T> *curr=head;
    	int i=0;
    	while(curr->next!=NULL)
    	{
    		curr=curr->next;
    		i++;
    	}
    	return i;
    }

    //删除第i个节点  删除 成功 返回真  
    bool remove(int i)
    {
    	if(i<0)
		{
			return false;
		}
    	if(isempty())
    	{
    		return false;
    	}
    	listnode<T> *curr=locate(i-1);
    	listnode<T> *del;
    	if(curr == NULL )
    	{
    		return false;
    	}
    	if(curr->next != NULL)
    	{
           del=curr->next;
    	   curr->next=del->next;
    	   delete del;
    	   return true;
    	}
    	delete curr;
    	
    }

    //是否为空 空 返回 真
    bool isempty()
    {
       if(head->next==NULL)
       {
       	  return true;
       }
       return false;
    }
private:
	listnode<T> *head;
};

int main(int argc, char const *argv[])
{
	listnode<int> _listnode;
	list<int> _list;
	int number;
	int  i;
	char user_choice='9';
	char yes_no;
	while(1)
	{
		if(user_choice == '9')
		{
			cout<<"************************************************"<<endl;
			cout<<"***** 1 创建链表 "<<endl;
			cout<<"***** 2 释放所有节点"<<endl;
			cout<<"***** 3 显示所有节点值"<<endl;
			cout<<"***** 4 删除第几个节点"<<endl;
			cout<<"***** 6 在第几个节点后插入一个新节点"<<endl;
			cout<<"***** 7 链表是否为空"<<endl;
			cout<<"***** 8 链表有多长"<<endl;
			cout<<"***** 9 显示主菜单"<<endl;
			cout<<"***** 0 退出"<<endl;
			cout<<"************************************************"<<endl;
		}
        cout<<"请输入你的选择: "<<endl;
        cin>>user_choice;
	    switch(user_choice)
	    {
		   case'1':    //创建链表
		   {
			  cout<<"开始创建链表，输入要创建多少个节点"<<endl;
			  cin>>number;
			  if(_list.creatlist(number))
			  {
			   	   cout<<"创建成功"<<endl;
			  } 
              else
              {
            	   cout<<"创建失败"<<endl;
              }
            break;
		}
		case'2':    //释放所有节点
		{
			cout<<"确认要释放所有节点？确认输入 y 否则 输入 n"<<endl;
			cin>>yes_no;
			if(yes_no == 'Y' || yes_no == 'y')
			{
				_list.deletenodes();
				cout<<"销毁成功"<<endl;
			}
			break;	
		}
		case'3':    //显示所有节点值
		{
			_list.display();
            break;
		}
		case'4':    //删除第几个节点
		{
			cout<<"请输入，你想删除第几个节点"<<endl;
            cin>>i;
            if(_list.remove(i))
            {
            	cout<<"删除成功"<<endl;
            }
            else
            {
            	cout<<"删除失败 或该节点是最后一个节点"<<endl;
            }
			break;
		}
		case'6':    //在第几个节点后插入一个新节点
		{
			cout<<"输入你想在第几个节点后插入节点"<<endl;
			cin>>i;
            if(_list.insert(i))
            {
               cout<<"插入成功"<<endl;
               _list.display();
            }
            else
            {
            	cout<<"插入失败"<<endl;
            }
			break;
		}
		case'7':    //链表是否为空
		{
			if(!_list.isempty())
			{
				cout<<"链表不是空的"<<endl;
			}
			else
			{
				cout<<"链表是空的"<<endl;
			}
			break;
		}
		case'8':    //链表有多长
		{
			int len=_list.Length();
			if (len)
			{
				cout<<"目前总共有"<<len<<"个节点"<<endl;
			}
			else
			{
				cout<<"链表为空 "<<endl;
			}
			break;
		}
		case'9':    //退出程序
		{
			break;
		}
		default:
		{
			cout<<"输入数据有误!"<<endl;
            break;
		}       
	}
	if(user_choice=='0' || user_choice== '2')
	{
		cout<<"程序已经退出，感谢你的使用!"<<endl;
		break;
	}
	
	}
	return 0;
}