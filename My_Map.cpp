/*
File name: My_Map
Author: leifeifei
Date:2016.8.21-2016.8.22
Description: 实现STL的一个关联容器————Map
Map容器：
       1.map是c++的一个标准容器，它提供了很好的一对一的关系。
       2.map容器的元素是一些关键字——值（key-value）对，key和value可以是你想要的任意类型，
         关键字起到了索引的作用，值则表示与索引相关的联的数据。换句话说，就是通过key可以
         找到相应的value。
       3.这里说下map内部数据的组织，map内部自建一颗红黑树（一种非严格意义上的平衡二叉树），
         这颗树具有对数据自动排序的功能，所以在map内部所有的数据都是有序的。
       4.它是一个相关联的容器，它的大小可以改变，它能根据关键字来提高读取数据能力
       5.它提供一个双向的定位器来读写取数据。
       6.它的每一个元素的关键字key都是惟一的。
       7.它是一个模板，它能提供一个一般且独立的数据类型
*/

#include <iostream>
#include <string>
using namespace std;

//申明Map容器
template<class T1,class T2>
class MyMap;

//定义类建红黑树结点颜色类
typedef enum Color_Rb
{
    RED,
    BLACK
}Color_Rb;

//定义pair类
template<class T1,class T2>
class m_pair
{
friend class MyMap<T1,T2>;
public:
    T1 first;
    T2 second;
    m_pair():first(T1()),second(T2())
    {}
    m_pair(const T1 & f,const T2 & s):first(f),second(s)
    {}

};

//定义map容器结点类
template<class T1,class T2>
class Map_Node
{
friend class MyMap<T1,T2>;
public:
    Map_Node()
    {
        parent = NULL;
        left = NULL;
        right = NULL;
        color = BLACK;
    }
    Map_Node(T1 _key,T2 _value,Map_Node<T1,T2> * p,Map_Node<T1,T2> * l,Map_Node<T1,T2> * r,Color_Rb _color)
    {
        key = _key;
        valve = _value;
        parent = p;
        left = l;
        right = r; 
        color = _color;
    }

private:
    T1 key;    //map关键字
    T2 valve;  //map数据域
    Map_Node<T1,T2> * parent;
    Map_Node<T1,T2> * left;
    Map_Node<T1,T2> * right;
    Color_Rb color;
};

//定义map容器类
template<class T1,class T2>
class MyMap
{
public:
     class RbTree;
     class iterator
        {
        friend class RbTree;
        friend class MyMap;
        public:
            iterator(Map_Node<T1,T2> * _node_ptr = NIL,RbTree * _rbtree = NULL)
            {
                 node_ptr = _node_ptr;
                 rbtree = _rbtree;
            }
            
            bool operator == (iterator from)
            {
                return node_ptr == from.node_ptr;
            }
            
            bool operator != (iterator from)
            {
                return node_ptr != from.node_ptr;
            }
            
            iterator operator ++(int i)
            {
                iterator it = *this;
                Map_Node<T1,T2> * tmp = NULL;
                Map_Node<T1,T2> * p = NIL;
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
            Map_Node<T1,T2> * node_ptr;  //当前红黑树结点
            RbTree * rbtree;  //当前结点所在子树
        };
    class RbTree
    {
    friend class MyMap;
    public:
        
        RbTree(Map_Node<T1,T2> * _root = NIL)
        {
            root = _root;
            size = 0;
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
            Map_Node<T1,T2> * tmp = root;
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
        bool Insert_RbTree(T1 key,T2 value)
        {
          Map_Node<T1,T2> * newnode = NULL;
          if (root == NIL)    //当根结点为空时
          {
            newnode = new Map_Node<T1,T2>(key,value,NIL,NIL,NIL,BLACK);
            root = newnode;
            size = 1;
            return true;
          }
          Map_Node<T1,T2> * tmp = root;
          Map_Node<T1,T2> * p = NIL;
          Map_Node<T1,T2> * gp = NIL;
      
          iterator it  = Find_RbTree(root,key);   //查找该值在红黑树内是否已存在
          if ( it.node_ptr->key == key )
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
            if (key < tmp->key)
            {
                tmp = tmp->left;
            }
            else
            {
                tmp = tmp->right;
            }
          }
         
          newnode = new Map_Node<T1,T2>(key,value,p,NIL,NIL,RED);
         
          if (key < p->key)
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
           size += 1;
           //cout << "over" << endl;
           return true;
        }
        
        //删除结点
        //1.如果要删除的结点是叶子结点，并且是红色的，则直接删除即可
        //若是黑色可能违反了性质，需要修复，2.若要删除的结点不是叶子结点，则找到右子树的最小结点
        //与之交换，跳转到当其位置，判断是否破坏性质，若破坏，则需要修复
        //3.综上可知，要删除的结点，要么是叶子结点，要么就是含有一个红色结点
        bool Delete_RbTree(T1 key)
        {
          iterator it  = Find_RbTree(root,key);   //查找该值在红黑树内是否已存在
          if ( it.node_ptr->key != key )
          {
            return false;
          }

          Map_Node<T1,T2> * tmp = it.node_ptr;     //所需要删除的结点
          Map_Node<T1,T2> * p = tmp->parent; //其父结点
          Map_Node<T1,T2> * gp = p->parent;  //祖父结点
          Map_Node<T1,T2> * sibling = NULL;  //兄弟结点
          Map_Node<T1,T2> * del_node = NULL; //最终删除的结点

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

                T1 del_val = tmp->key;
                tmp->key = del_node->key;
                del_node->key = del_val;

                if (tmp->right != NIL)
                {
                    //当替换结点为黑色，且其右孩子不为空时，再将所删除结点替换到下一结点
                    if (del_node->color == BLACK && del_node->right != NIL)
                    {
                        del_val = del_node->right->key;
                        del_node->right->key = del_node->key;
                        del_node->key = del_val;
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
                        del_val = del_node->left->key;
                        del_node->left->key = del_node->key;
                        del_node->key = del_val;
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
            size -= 1;
            return true;       
        }
        
        //删除结点时，因破坏性质，调用此函数，可修复性质
        void Delete_Fix_up(Map_Node<T1,T2> * sibling)
        {
           Map_Node<T1,T2> * p = sibling->parent; 
           Map_Node<T1,T2> * gp = p->parent;

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
        void Fix_up_del(Map_Node<T1,T2> * x)
        {
            Map_Node<T1,T2> * p = x->parent;
            Map_Node<T1,T2> * gp = p->parent;
            Map_Node<T1,T2> * x_child = NULL;
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
        Map_Node<T1,T2> * Find_Min(Map_Node<T1,T2> * rb)
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
        Map_Node<T1,T2> * Find_Max(Map_Node<T1,T2> * rb)
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
        void Fix_up(Map_Node<T1,T2> * x)
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

            Map_Node<T1,T2> * p = x->parent;    //父结点
            Map_Node<T1,T2> * gp = p->parent;   //祖父结点
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
        void Roato_Left(Map_Node<T1,T2> * pivot)
        {
            Map_Node<T1,T2> *p = pivot->parent;
            Map_Node<T1,T2> *gp = p->parent;
           
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
        void Roato_Right(Map_Node<T1,T2> * pivot)
        {
            Map_Node<T1,T2> *p = pivot->parent;
            Map_Node<T1,T2> *gp = p->parent;

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
        
        iterator Find_RbTree(const T1 & key )
        {
            return Find_RbTree(root,key);
        }

        //定义查找函数，根据给定的结点,和所要寻找的值，找到返回结点，否则返回比这个值大一点的结点
        iterator Find_RbTree(Map_Node<T1,T2> * node,const T1 & key)
        {
            if (node == NIL)
            {
                return iterator(NIL,this);
            }
            if (key < node->key)
            {
                return Find_RbTree(node->left,key);
            }
            if (key > node->key)
            { 
                return Find_RbTree(node->right,key);
            }
            if (key == node->key)
            {
                return iterator(node,this);
            }
        }
        
        //删除红黑树中所有元素
        void clear()
        {
            if (root == NIL)
            {
                return;
            }
            iterator it;
            for (it = begin(); it != end();it++ )
            {
                Delete_RbTree(it.node_ptr->key);
            }
        }

        void empty()
        {
            if (root == NIL)
            {
                return true;
            }
            return false;
        }

        void Output_RbTree()
        {
            Output_RbTree(root);
            cout << endl;
        }

        void Output_RbTree(Map_Node<T1,T2> * rb)
        {
            if (rb == NIL)
            {
                return;
            }
            Output_RbTree(rb->left);
            cout << "[" << rb->key << "," << rb->valve << "]" <<"\t";
            Output_RbTree(rb->right);
        }
        
        private:
            Map_Node<T1,T2> * root;
            int size;
    };
    MyMap()
    {
        if (NIL == NULL)
        {
            NIL = new Map_Node<T1,T2>;
        }
        map_node = NIL;
        Rt = new RbTree(map_node);
    }

    void insert(T1 key,T2 value)
    {
       if ( !( Rt->Insert_RbTree(key,value) ) )
       {
          return;
       }
    }

    //插入val到pos的后面，然后返回一个指向这个元素的迭代器。 
    iterator insert( iterator pos, const m_pair<T1,T2> &val )
    {
        Rt->Insert_RbTree(val.first,val.second);
        return find(val.first);
    }

    //插入start到end的元素到map中。
    void insert( iterator start, iterator end )
    {
        while (start != end)
        {
            insert(start.node_ptr->key,start.node_ptr->valve);
            start++;
        }
        insert(start.node_ptr->key,start.node_ptr->valve);
    }

    //只有在val不存在时插入val。返回值是一个指向被插入元素的迭代器和一个描述是否插入的bool值。
    m_pair<iterator, bool> insert( const m_pair<T1,T2> &val )
    {
       
       bool isexists = false;
       if ( Rt->Insert_RbTree(val.first,val.second) )
       {
        
        isexists = true;
       }
       iterator it = find(val.first);
       m_pair<iterator, bool> tmp(it,isexists);
       return tmp ;
    }

    //返回一个迭代器指向map的第一个元素。
    iterator begin()
    {
        return Rt->begin();
    }

    //返回一个迭代器指向map的尾部。
    iterator end()
    {
        return Rt->end();
    }
    
    //删除map中的所有元素。
    void clear()
    {
        Rt->clear();
    }
    
    //返回map中键值等于key的元素的个数。
    int count( const T1 &key )
    {
        return 1;
    }
    
    //返回真(true)如果map为空，否则返回假(false)
    bool empty()
    {
       Rt->empty();
    }
    
    //删除在pos位置的元素
    void erase( iterator pos )
    {
        Rt->Delete_RbTree(pos.node_ptr->key);
    }

    //删除在start和end之间的元素
    void erase( iterator start, iterator end )
    {
        while (start != end)
        {
            erase(start++);
        }
    }

    //删除那些值为key的所有元素
    int erase( const T1 &key )
    {
       Rt->Delete_RbTree(key);
    }

    //返回一个迭代器指向键值为key的元素，如果没找到就返回指向map尾部的迭代器。
    iterator find( const T1 &key )
    {
        return Rt->Find_RbTree(key);
    }

    //返回一个指向map尾部的逆向迭代器。
    iterator rbegin()
    {
        return end();
    }
    
    //返回一个指向map头部的逆向迭代器。
    iterator rend()
    {
        return begin();
    }

    //返回map中保存的元素个数。
    int size()
    {
       return Rt->size;
    }
    
    //交换obj和现map中的元素。
    void swap( MyMap<T1,T2> &obj )
    {
        Map_Node<T1,T2> * tmp = Rt->root;
        Rt->root = obj.Rt->root;
        obj.Rt->root = tmp;
    }

    //函数返回一个迭代器，指向map中键值>key的第一个元素
    iterator upper_bound( const T1 &key )
    {
        iterator it = find(key);
        if (it.node_ptr->right != NIL)
        {
            it.node_ptr = it.node_ptr->right;
        }
        else
        {
            if (it.node_ptr->parent != NIL)
            {
                it.node_ptr = it.node_ptr->parent;
            }
        }
        return it;
    }

    void Output_Map()
    {
        Rt->Output_RbTree();
    }
    
    T2 &operator [](T1 key)
    {
        iterator it;
        it = find(key);
        if (it.node_ptr == NIL)
        {
            m_pair<T1,T2> tmp;
            tmp.first = key;
            it =  insert( tmp ).first;
        }
        return it.node_ptr->valve;
    }

private:
    Map_Node<T1,T2> * map_node;
    RbTree *Rt;
    static Map_Node<T1,T2> * NIL;
};

template<class T1,class T2>
Map_Node<T1,T2> * MyMap<T1,T2>::NIL = NULL;

int main(int argc, char const *argv[])
{
    //MyMap<int,string> m1;
    // m1.insert(10,"nihao");
    // m1.Output_Map();
    // m1[85] = "great";
    MyMap<string,int> m2;
    m2.insert("nihao",10);
    m2["abc"] = 85;
    m2["abc"]++;
    m2.Output_Map();
    return 0;
}
