/*
File name: RbTree
Author: leifeifei
Date: 2016.8.18~2016.8.20
Description: 实现简单的红黑树
红黑树：红黑树本质上就是一棵二叉查找树，也就是在二叉查找树的基础上，增加了着色等性质，
        使红黑树保存相对平衡，从而保证“红黑树的查找，插入，删除的时间复杂度最坏为O(logn)
        的性质。
二叉查找树的性质：
        1.若任意结点的左子树不为空，则左子树上所有结点的值均小于它的父结点的值。
        2.若任意结点的右子树不为空，则右子树上所有结点的值均大一它的父结点的值。
        3.任意结点的左子树和右子树，也分别是二叉查找树。
        4.二叉查找树中，没有重复的结点。
红黑树的性质：
        1.每个结点要么是红的，要么是黑的。
        2.根结点是黑的。
        3.每个叶子结点时黑的。
        4.如果一个结点是红的那么它的两个孩子都是黑的。
        5.对于任意结点而言，其到叶结点也即树尾端NIL指针，的每条路径都包括相同数目的黑结点。
程序思路：
        1.采用模板类实现。
        2.采用枚举对红黑树颜色进行定义，定义一个模板红黑树结点类，一个模板红黑树。
        3.主要分为两块，红黑树结点的插入与删除。
          1.插入部分 默认插入的结点均为红色
            1.先调用Find_Rbtree函数，判读所插入结点是否存在，然后，从根结点开始，根据要插入
              值data，至上而下，依次遍历找到比data较大一点的值，遍历途中，若遇到某个结点有两
              个红色结点的黑色，则调用Fix_Up函数，去调整，这可一定程度上有效避免，当插入时，
              出现两个连续的红色结点。
            2.若插入时，其父结点是红色，则也调用Fix_up函数进行修复，使其满足性质。
          2.删除部分
            1.我们先找到要删除结点del的位置，如果del没有左右孩子，又是红色，则直接删除。
            2.若del无左右孩子，是黑色，此时调用Delete_Fix_up函数进行修复性质。
            3.若del有右孩子，则找到其右子树中最小结点与之替换。则问题又回到1,2步。
            4.若del无右孩子，但是有左孩子，则找到左子树最大结点与之替换，问题也回到1,2步。
            5.在3,4步中，若找到替换结点有左孩子或者右孩子，则与之替换。在进行相应操作。
            6.在破坏性质时，调用Delete_fix_up时，del已经和其父母断开，即可视为已删除。
          3.删除，破坏性质，需修复情况可分为。
            1.当del为黑色，兄弟结点为红色时。也即父结点为黑色时。
            2.当del为黑色，兄弟结点为黑色时，父结点也为黑色时。这种情况有点复杂。
            3.当del为黑色，当父结点为红色时，以兄弟结点为修补点，调用Fix_up即可修复。
*/

#include <iostream>
using namespace std;

//申明模板RbTree
template<class T>
class RbTree;


//利用枚举来对红黑树的颜色进行定义
typedef enum RbNodeColor
{
	RED,
	BLACK
}RbNodeColor;

//定义结点类
template<class T>
class RbNode
{
friend class RbTree<T>;
public:
    RbNode()
    {
    	parent = NULL;
    	left = NULL;
    	right = NULL;
    	color = BLACK;
    }

	RbNode(T _data, RbNode<T> * p, RbNode<T> * l, RbNode<T> * r, RbNodeColor _color = BLACK)
	{
       data = _data;
       parent = p;
       left = l;
       right = r;
       color = _color;
	}
private:
	T data;                 //结点数据域
	RbNode<T> * parent;     //父结点指针
	RbNode<T> * left; //左孩子
	RbNode<T> * right;//右孩子
	RbNodeColor color;      //结点颜色
};

//定义RbTree
template<class T>
class RbTree
{
public:

	//内建一个内部类，
    class iterator
    {
    friend class RbTree;
    public:
    	iterator(RbNode<T> * _rn = NIL,RbTree<T> * _rt = NULL)
    	{
             rn = _rn;
             rt = _rt;
    	}
        
        bool operator == (iterator from)
        {
        	return rn == from.rn;
        }
        
        bool operator != (iterator from)
        {
        	return rn != from.rn;
        }
        iterator operator ++(int i)
        {
        	iterator it = *this;
        	RbNode<T> * tmp = NULL;
        	RbNode<T> * p = NIL;
        	if (it.node_ptr == NIL)  //当前结点为空时
        	{
        		it.node_ptr = rbtree->root;
        		if (it.node_ptr == NIL)      //当前为空树时
        		{
        			return iterator(it.node_ptr,rbtree);
        		}
        		else                         //不为空树时
        		{
        			if (it.node_ptr->left != NIL)
        			{
        				it.node_ptr = Find_Min(it.ptr->left);
        			}
        		}
        	}
        	else                       //当前结点不为空时
        	{
        		if (it.node_ptr->right != NIL)    //若当前结点的右子树不为空时
        		{
        			it.node_ptr = Find_Min(it.node_ptr->right);
        		}
        		else                              //当前结点右子树为空时，则找到gp
        		{
        			p = it.node_ptr->parent;
        			it.node_ptr = p;
        			while (p != NIL && it.node_ptr == p->right)
        			{
        				it.node_ptr = p;
        				p = p->parent;
        			}
        		}
        	}
        	return *this;
        }
    private:
    	RbNode<T> * rn;
    	RbTree<T> * rt;
    };

	RbTree()
	{
		if (NIL == NULL)
		{
			NIL = new RbNode<T>;
		}
		root = NIL;
		RbTree_Size = 0;
	}
    
    ~RbTree()
    {
    	if (root != NULL)
    	{
    		delete root;
    		root = NULL;
    	}
    }

    //返回一个指向红黑树的最左子树，最小的结点
    iterator begin()
    {
    	RbNode<T> * tmp = root;
    	while (tmp->left != NIL)
    	{
    		tmp = tmp->left;
    	}
    	return iterator(tmp,this);
    }

    iterator end()
    {
      return iterator(NIL,this);
    }

    //插入结点
	bool Insert_RbTree(T data)
	{
	  RbNode<T> * newnode = NULL;
	  if (root == NIL)    //当根结点为空时
      {
      	newnode = new RbNode<T>(data,NIL,NIL,NIL,BLACK);
      	root = newnode;
      	return true;
      }
      RbNode<T> * tmp = root;
      RbNode<T> * p = NIL;
      RbNode<T> * gp = NIL;
  
      iterator it  = Find_RbTree(root,data);   //查找该值在红黑树内是否已存在
      if ( it.rn->data == data )
      {
      	return false;
      }
      while(tmp != NIL)
      {
      	//当结点的左右孩子为红色结点时，这一步，避免了当父结点和叔父结点
      	//都为红结点时的问题。
      	if (tmp->left->color == RED && tmp->right->color == RED)
      	{
      		Fix_up(tmp);
      	}
      	p = tmp;
      	if (data < tmp->data)
      	{
      		tmp = tmp->left;
      	}
      	else
      	{
      		tmp = tmp->right;
      	}
      }
      newnode = new RbNode<T>(data,p,NIL,NIL,RED);
      if (data < p->data)
      {
      	p->left = newnode;
      } 
      else
      {
      	p->right = newnode;
      }
       if (p->color == RED)    //当其父结点为红色时
       {
       	  Fix_up(newnode);
       }
       root->color = BLACK;    //保证根结点始终为黑色
       return true;
	}
    
    //删除结点
    //1.如果要删除的结点是叶子结点，并且是红色的，则直接删除即可
    //若是黑色可能违反了性质，需要修复，2.若要删除的结点不是叶子结点，则找到右子树的最小结点
    //与之交换，跳转到当其位置，判断是否破坏性质，若破坏，则需要修复
    //3.综上可知，要删除的结点，要么是叶子结点，要么就是含有一个红色结点
    bool Delete_RbTree(T data)
    {
      iterator it  = Find_RbTree(root,data);   //查找该值在红黑树内是否已存在
      if ( it.rn->data != data )
      {
      	return false;
      }

      RbNode<T> * tmp = it.rn;     //所需要删除的结点
      RbNode<T> * p = tmp->parent; //其父结点
      RbNode<T> * gp = p->parent;  //祖父结点
      RbNode<T> * sibling = NULL;  //兄弟结点
      RbNode<T> * del_node = NULL; //最终删除的结点

      if (tmp->left == NIL && tmp->right == NIL) //当所删除结点左右无孩子时
	  {
	        if (tmp == p->left)
		    {
		      	sibling = p->right;
		    }
		    else
		    {
		      	sibling = p->left;
		    }
		    if (tmp == p->left)
	        {
	           	p->left = NIL;
	        }
	        else
	        {
	           	p->right = NIL;
	        }
	       del_node = tmp;

           //当兄弟结点不为空时
           if (sibling != NIL)
           {
              Delete_Fix_up(sibling);          
           }
	    }
	    else//所删除结点有左孩子或者有右孩子时
	    {   
	        //当所删除结点右子树不为空时，找到右子树中最小值，与之替换
	    	if (tmp->right != NIL)
	    	{
                del_node = Find_Min(tmp->right);
            }
            else//当所删除结点右子树为空时，找到右子树中最大值，与之替换
	    	{
	    		del_node = Find_Max(tmp->left);

	    	}
            p = del_node->parent;
            gp = p->parent;
            if (del_node == p->left)
			{
			    sibling = p->right;
			}
			else
			{
			    sibling = p->left;
			}

            T del_val = tmp->data;
            tmp->data = del_node->data;
            del_node->data = del_val;

            if (tmp->right != NIL)
            {
                //当替换结点为黑色，且其右孩子不为空时，再将所删除结点替换到下一结点
                if (del_node->color == BLACK && del_node->right != NIL)
                {
                    del_val = del_node->right->data;
                    del_node->right->data = del_node->data;
                    del_node->data = del_val;
                    tmp = del_node;
                    del_node = del_node->right;
                    del_node->parent = NIL;
                    tmp->right = NIL;
                }
            }
            else
            {
            	//当替换结点为黑色，且其左孩子不为空时，再将所删除结点替换到下一结点
                if (del_node->color == BLACK && del_node->left != NIL)
                {
                    del_val = del_node->left->data;
                    del_node->left->data = del_node->data;
                    del_node->data = del_val;
                    tmp = del_node;
                    del_node = del_node->left;
                    del_node->parent = NIL;
                    tmp->left = NIL;
                }
            }
               
            //当替换结点颜色为黑色时，且其左右孩子为空时
            if (del_node->color == BLACK && del_node->right == NIL)
            {
                if (del_node == p->left)
			    {
			        p->left = NIL;
			    }
			    else
			    {
			        p->right = NIL;
			    }
                if (sibling != NIL)
                {
                    Delete_Fix_up(sibling); 
                }
            }
            if (del_node->color == RED)
            {
            	if (del_node == p->left)
			    {
			        p->left = NIL;
			    }
			    else
			    {
			        p->right = NIL;
			    }
            }

	    }
	    delete del_node;
	    del_node = NULL;    	
    }
    
    //删除结点时，因破坏性质，调用此函数，可修复性质
    void Delete_Fix_up(RbNode<T> * sibling)
    {
       RbNode<T> * p = sibling->parent; 
       RbNode<T> * gp = p->parent;

       if (p->color == RED) //父结点为红色结点时
       {
	       	if (gp != NIL)   //当祖父结点不为空时，调用Fix_Up函数即可
	        {
	              	Fix_up(sibling);
	        }
       }
       else   //父结点为黑色结点时
       {
            if (sibling->color == RED) //当兄弟为红色时
           	{
           	 	sibling->color = BLACK;
           	 	if (sibling == p->left)
           	 	{
           	 		sibling->right->color = RED;
           	 	    Roato_Right(sibling);
           	 	}
           	 	else
           	 	{
           	 		sibling->left->color = RED;
           	 		Roato_Left(sibling);
           	 	}
           	} 
           	else  //当兄弟为黑色
           	{
           	 	if (sibling == p->left)
           	 	{
           	 		if (sibling->left != NIL)
           	 		{
           	 			sibling->left->color = BLACK;
	                    Roato_Right(sibling);
           	 		}
           	 		 //兄弟左孩子为空，右孩子不为空时
           	 		if (sibling->left == NIL && sibling->right != NIL)
           	 		{
                        sibling->right->color = BLACK;
		                Roato_Left(sibling->right);
		                Roato_Right(sibling->right);
           	 		}	                
           	 	}
                else
           	 	{
           	 		if (sibling->right != NIL)
           	 		{
           	 			sibling->right->color = BLACK;
           	 		    Roato_Left(sibling);
           	 		}
           	 		//兄弟右孩子为空，左孩子不为空时
		           	if (sibling->right == NIL && sibling->left != NIL)
		           	{
		                sibling->left->color = BLACK;
		                Roato_Right(sibling->left);
		                Roato_Left(sibling->left);
		           	}
           	 	}

           	 	//当兄弟无左右结点时
               if (sibling->left == NIL && sibling->right == NIL)
           	   {
	           	 	if (gp != NIL && p == gp->left)
	           	 	{
	           	 		sibling->color = RED;
	                    Fix_up_del(gp->right);
	           	 	}
	           	    else if (gp != NIL && p == gp->right)
	           	    {
	           	    	sibling->color = RED;
	                    Fix_up_del(gp->left);
	           	    }
           	    }  
           	}
       } 
    }

    //当所删除结点，兄弟结点，父结点也为黑色，且左右无结点时，调用此函数修复
    //此时只能通过其祖父结点另外子树来修复性质
    void Fix_up_del(RbNode<T> * x)
    {
     	RbNode<T> * p = x->parent;
     	RbNode<T> * gp = p->parent;
     	RbNode<T> * x_child = NULL;
     	p->color = RED;

     	if (x->color == BLACK) 
     	{
     		if (x == p->right)
     		{
     			x_child = x->left;
     			Roato_Left(x);
     		}
     		else
     		{
     			x_child = x->right;
     			Roato_Right(x);
     		}
     		if (x_child != NIL && x_child->color == RED)
     		{
                Fix_up(x_child);
     		}
     	}
     	else
     	{
     		x->color = BLACK;
     		if (x == p->right)
     		{
     			Roato_Left(x);
     		}
     		else
     		{
               Roato_Right(x);
     		}
     	}	
     }

    //找到某子树里面的最小值
    RbNode<T> * Find_Min(RbNode<T> * rb)
    {
    	if (rb == NIL)
    	{
    		return rb;
    	}
    	while(rb->left != NIL)
    	{
    		rb = rb->left;
    	}
    	return rb;
    }
    
    //找到某子树里面的最大值
    RbNode<T> * Find_Max(RbNode<T> * rb)
    {
    	if (rb == NIL)
    	{
    		return rb;
    	}
    	while(rb->right != NIL)
    	{
    		rb = rb->right;
    	}
    	return rb;
    }


    //调用此函数，可以修复红黑树，使其满足性质
	void Fix_up(RbNode<T> * x)
	{
		if (x == NIL)
		{
			return;
		}
		x->color = RED;
		x->left->color = BLACK;
		x->right->color = BLACK;
		if (x == root)
		{
			return;
		}

		RbNode<T> * p = x->parent;    //父结点
		RbNode<T> * gp = p->parent;   //祖父结点
		if (gp != NULL && p->color == RED)    //当祖父结点不为空时且父结点为红色时
		{
			gp->color = RED;
			if (x == p->left && p == gp->right)  //当x时p的左孩子，p是gp的右孩子时
			{
				x->color = BLACK;
				Roato_Right(x);
				p = x;
			}
			else if (x == p->right && p == gp->left) //当x是p的右孩子，p是gp左孩子时
			{
				x->color == BLACK;
				Roato_Left(x);
				p = x;
			}
			else
			{
				p->color = BLACK;
			}
			if (p == gp->left)    //当x是p的左孩子，p是gp的左孩子
			{
				Roato_Right(p);
			}
			else                  //当x是p的右孩子，p是gp的右孩子
			{
				Roato_Left(p);
			}
		}
	}
    
    //左旋函数
    void Roato_Left(RbNode<T> * pivot)
    {
    	RbNode<T> *p = pivot->parent;
    	RbNode<T> *gp = p->parent;
       
        p->right =  pivot->left;    //piovt的原右孩子改变为p的左孩子
        pivot->left = p;            //将p作为pivot的右孩子
        
        if (gp != NIL)              
        {
        	if (p == gp->left)
        	{
        	   gp->left = pivot;
        	}
        	else
        	{
        		gp->right = pivot;
        	}
        }
        p->parent = pivot;           //改变p的parent
        pivot->parent = gp;          //改变pivot的parent
        if (p->right != NIL)
        {
        	p->right->parent = p;
        }
        if (p == root)
        {
        	root = pivot;
        }
    }

    //右旋函数
    void Roato_Right(RbNode<T> * pivot)
    {
    	RbNode<T> *p = pivot->parent;
    	RbNode<T> *gp = p->parent;

        p->left = pivot->right;     //piovt的原左孩子改变为p的右孩子
        pivot->right = p;            //将p作为pivot的左孩子
       
        if (gp != NIL)              
        {
        	if (p == gp->left)
        	{
        	   gp->left = pivot;
        	}
        	else
        	{
        		gp->right = pivot;
        	}
        }
        p->parent = pivot;           //改变p的parent
        pivot->parent = gp;          //改变pivot的parent
        if (p->left != NIL)
        {
        	p->left->parent = p;
        }
        if (p == root)
        {
        	root = pivot;
        }
    }
    
	//定义查找函数，根据给定的结点,和所要寻找的值，找到返回结点，否则返回比这个值大一点的结点
	iterator Find_RbTree(RbNode<T> * node,T data)
	{
		if (node == NIL)
		{
			return iterator(NIL,this);
		}
		if (data < node->data)
		{
			return Find_RbTree(node->left,data);
		}
		if (data > node->data)
		{ 
			return Find_RbTree(node->right,data);
		}
		if (data == node->data)
		{
			return iterator(node,this);
		}
	}
    
    void Output_RbTree()
    {
    	//cout << root->data << "root";
    	Output_RbTree(root);
    	cout << endl;
    }

    void Output_RbTree(RbNode<T> * rb)
    {
        if (rb == NIL)
        {
        	return;
        }
        Output_RbTree(rb->left);
        cout << rb->data << "\t";
        Output_RbTree(rb->right);
    }

private:
	RbNode<T> * root;
	int RbTree_Size;
	static RbNode<T> * NIL;
};

template<class T>
RbNode<T> * RbTree<T>::NIL = NULL;

int main(int argc, char const *argv[])
{
	RbTree<int> a1;
	a1.Insert_RbTree(10);
	a1.Insert_RbTree(85);
	a1.Insert_RbTree(15);
	a1.Insert_RbTree(70);
	a1.Insert_RbTree(20);
	a1.Insert_RbTree(60);
	a1.Insert_RbTree(30);
	a1.Insert_RbTree(50);
	a1.Insert_RbTree(65);
	a1.Insert_RbTree(80);
	a1.Insert_RbTree(90);
	a1.Insert_RbTree(40);
	a1.Insert_RbTree(5);
	a1.Insert_RbTree(55);
	a1.Insert_RbTree(60);
	a1.Output_RbTree();
	cout << "##############after delete###############" << endl;
	a1.Delete_RbTree(5);
	a1.Delete_RbTree(20);
	a1.Delete_RbTree(80);
	a1.Delete_RbTree(90);
	a1.Delete_RbTree(85);
	//a1.Delete_RbTree(20);
	a1.Output_RbTree();
	return 0;
}
