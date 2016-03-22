
//实现模板栈
#include <iostream>
using namespace std;

template<class T>
class stack
{
public:
	stack ()    //无参创建空栈
	{
		stackspace=NULL;
	    stacksize=0;
	    top=-1;
	}

	stack (int _stacksize)    //创建一个可以容纳size个元素的栈
	{
		stackspace=NULL;
	    stacksize=0;
	    top=-1;
	    creatstack(_stacksize);
	}

	bool creatstack(int _stacksize)    //实际创建一个可以容纳size个元素的栈
	{
		if(stackspace)    //判断是否已创建,已创建则返回 false
		{
			return false;
		}
		stacksize=_stacksize;   
		if(stacksize<=0)    //判断是否小于 或等于 0
		{
			return false;
		}
		stackspace=new T[stacksize];
		if(stackspace==NULL)    //判断是否创建成功
		{
			return false;
		}
		return true;
	}

    //入栈 成功 返回 真 
	bool push(T &data)
	{
		if(!stackspace)    //判断栈是否创建成功
		{
			return false;
		}
		if(isfull())    //判断是否已满
		{
			return false;
		}
		stackspace[++top]=data;
		return true;
	}

    //显示所有数据元素
	void display_stack()
	{
		int i;
		if(stacksize)
        {
         cout<<"目前栈的所有的数据元素为: ";
		 for(i=0;i<=top;i++)
		 {
			cout<<stackspace[i]<<'\t';
		 }
		 cout<<endl;
	    }
        else
        {
          cout<<"栈尚未建立!"<<endl;
        }
	}

	//出栈 成功 返回 真
	bool pop()
	{
		if(isempty())    //判断是否为空
		{
			return false;
		}
		cout<<"出栈数据： "<<stackspace[top]<<endl;
		top--;
		return true;
	}
	//判断栈是否满 满 返回true 
	bool isfull()
	{
		if(!stackspace)    //判断栈是否已创建
		{
			return false;
		}
		if(top == (stacksize-1))    //判断栈顶位置是否等于栈的大小
		{
			return true;
		}
		return false;

	}

	//判断栈是否空  空 返回true 
	bool isempty()
	{
		if(!stackspace)
		{
			return false;
		}
		if(top<0)
		{
			return true;  
		}
		return false;
	}

	//返回栈顶元素值 成功 返回 真
	bool gettopvalue()
	{
		if(isempty())    //判断是否为空
		{
			return false;
		}
		cout<<"栈顶值是："<<stackspace[top]<<endl;
		return true;
	}
    
    //销毁栈的函数
	void distroy()
	{
		if(stackspace)
		{
         delete []stackspace;
		}
        stackspace=NULL;
        top=-1;
        stacksize=0;
	}

    //析构函数
	~stack()
	{
		distroy();
	}
    T data;          //需要输入的数据	
private:
	T *stackspace;   //指向栈的指针
    int stacksize;   //栈的大小，当为0时，表示栈没有创建空间
    int top;         //top栈顶位置，当为-1时，栈为空
    
};

int main(int argc, char const *argv[])
{
	stack<int> _stack;
	int size=0;
	int data_out;
	char yes_no;
	char user_choice='9';
	while(1)
	{
		if(user_choice=='9')
	{
		cout<<"*********************************"<<endl;
		cout<<"*******创建栈的基本操作**********"<<endl;
		cout<<"*********************************"<<endl;
		cout<<"***** 1：创建一个栈"<<endl;
		cout<<"***** 2: 销毁栈"<<endl;
		cout<<"***** 3: 数据进栈"<<endl;
		cout<<"***** 4: 数据出栈"<<endl;
		cout<<"***** 5: 显示所有数据元素"<<endl;
		cout<<"***** 6: 读取栈底元素"<<endl;
		cout<<"***** 7: 判断栈是否为空"<<endl;
		cout<<"***** 8: 判断栈是否已满"<<endl;
		cout<<"***** 9: 显示菜单"<<endl;
		cout<<"***** 0: 退出程序"<<endl;
		cout<<"*********************************"<<endl;
	}
	cout<<"请输入你的选择: "<<endl;
    cin>>user_choice;
	switch(user_choice)
	{
		case'1':    //创建一个栈
		{
			cout<<"开始创建栈，输入要创建的空间大小"<<endl;
			cin>>size;
			if(_stack.creatstack(size))
			{
			   	   cout<<"创建成功"<<endl;
			} 
            else
            {
            	cout<<"已经创建 或者 创建失败"<<endl;
            }
            break;
		}
		case'2':    //销毁栈
		{
			cout<<"确认要销毁栈？确认输入 y 否则 输入 n"<<endl;
			cin>>yes_no;
			if(yes_no == 'Y' || yes_no == 'y')
			{
				_stack.distroy();
				cout<<"销毁成功"<<endl;
			}
			break;	
		}
		case'3':    //数据进栈
		{
			cout<<"输入数据"<<endl;
			cin>>_stack.data;
			if (_stack.push(_stack.data))
			{
               _stack.display_stack();
			}
			else
			{
				cout<<"已满 或者 进栈失败!"<<endl;
			}
            break;
		}
		case'4':    //数据出栈
		{
			if (!_stack.pop())
			{
				cout<<"空栈 或者 出栈失败！"<<endl;
			}
			break;
		}
		case'5':    //显示所有数据元素
		{
			_stack.display_stack();
			break;
		}
		case'6':    //读取栈底元素
		{
			if(!_stack.gettopvalue())
			{
               cout<<"空栈 或者 获取栈顶元素失败!"<<endl;
			}
			break;
		}
		case'7':    //判断栈是否为空
		{
			if(!_stack.isempty())
			{
				cout<<"栈不是空的"<<endl;
			}
			else
			{
				cout<<"栈是空的"<<endl;
			}
			break;
		}
		case'8':    //判断栈是否为满
		{
			if (!_stack.isfull())
			{
				cout<<"栈不是满的"<<endl;
			}
			else
			{
				cout<<"栈是满的"<<endl;
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
	if(user_choice=='0')
	{
		cout<<"程序已经退出，感谢你的使用!"<<endl;
		break;
	}
	
 }
	
	return 0;
}