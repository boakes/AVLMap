#ifndef AVLMAP
#define AVLMAP 

#include <iostream> 
#include <stdlib.h>
#include <algorithm>
#include <list>
template<typename K,typename V>
class AVLMap{
    
private:
    struct Node{
        Node* right;
        Node* left; 
        Node* parent; 
        std::pair<K,V> nodepr; 
        int ht;
        Node(Node* r, Node* l, Node* p, K k, V v,int h){
            right = r;
            left = l;
            parent = p; 
            nodepr = std::make_pair(k,v);
            ht = h;
        }
    };

    int sz; 
    Node* root;

public:

    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        Node* loc; 
        bool itrend;
    public:
        friend class const_iterator;
        iterator(Node* l,bool b):loc(l),itrend(b){}

        Node* Successor(Node* x){
         if (x->right != nullptr){
            return AVLMap<K,V>::minNode(x->right);
         } 
          Node* y = x->parent;
          while (y != nullptr && x == y->right){
                x = y;
                y = y->parent;
            }
            return y;
        }

        Node* Predecessor(Node* x){
         if (x->left != nullptr){
            return AVLMap<K,V>::maxNode(x->left);
         } 
         Node* y = x->parent;
         while (y != nullptr && x == y->left){
                x = y;
                y = y->parent;
         }
         return y;
        }

        bool operator==(const iterator &i) const { 
            return (loc == i.loc && itrend == i.itrend); 
        }

        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return loc -> nodepr; }
       
        iterator &operator++() {
            Node* tmp = Successor(loc);
            if(tmp == nullptr){
                itrend = true;
            }else{
                loc = tmp;
                itrend =false;
            }
            return *this;
        }
        iterator &operator--() {
            if(itrend){
                itrend = false;
                return *this;
            }else{
                loc = Predecessor(loc);
                return *this;
            }
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }

        Node* getnode(){
            return loc;
        }
    };

    class const_iterator {
        Node* loc; 
        bool itrend;
    public:
        friend class AVLMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(Node* l,bool b):loc(l),itrend(b) {}
        // TODO: Other constructors as needed.
        const_iterator(const iterator &iter):loc(iter.loc),itrend(iter.itrend){}

        Node* Successor(Node* x){
         if (x->right != nullptr){
            return AVLMap<K,V>::minNode(x->right);
         } 
          Node* y = x->parent;
          while (y != nullptr && x == y->right){
                x = y;
                y = y->parent;
            }
            return y;
        }

        Node* Predecessor(Node* x){
         if (x->left != nullptr){
            return AVLMap<K,V>::maxNode(x->left);
         } 
         Node* y = x->parent;
         while (y != nullptr && x == y->left){
                x = y;
                y = y->parent;
            }
            return y;
        }

        bool operator==(const const_iterator &i) const { return (loc == i.loc && itrend == i.itrend);  }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const std::pair<K,V> &operator*() { return loc -> nodepr; }
        const_iterator &operator++() {
            Node* tmp = Successor(loc);
            if(tmp == nullptr){
                itrend = true;
            }else{
                loc = tmp;
                itrend=false;
            }
            return *this;
        }
        const_iterator &operator--() {
            if(itrend){
                itrend = false;
            }else{
                loc = Predecessor(loc);
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };


    int height(Node* t) {
            return (t == nullptr)?-1:t->ht;
    }
    
    void fixheight(Node* t){
        int htrgt =height(t->right);
        int htlft = height(t->left);
        t->ht = (htlft > htrgt ? htlft:htrgt) + 1;
    }

    int balance(Node* t){
        return height(t->right)-height(t->left);
    }    

    static Node* maxNode(Node* x){
        while (x->right != nullptr){
            x = x->right;
        } return x;
    }

    static Node* minNode(Node* x){
        while (x->left != nullptr){
            x = x->left;
        } return x;
    }

    AVLMap(){
       root = nullptr;
       sz = 0; 
    }
    ~AVLMap(){
       clear();
    }


    void helpCopier(Node *x){
        if(x!=nullptr){
            insert(x->nodepr);
            helpCopier(x->left);
            helpCopier(x->right);
        }
    }

    AVLMap(const AVLMap<K,V> &that){
        root = nullptr; 
        sz = 0; 
        helpCopier(that.root);
    }

    AVLMap &operator=(const AVLMap<K,V> &that) {
        clear();
        root = nullptr;
        sz = 0; 
        helpCopier(that.root);
        return *this;
    }

    void LeftRotate(Node* x){
        Node* y = x->right;
        x->right = y->left;
        if(y->left != nullptr){y->left->parent = x;}
        y->parent = x->parent;
        if(x->parent == nullptr){
            root = y;
        } else if (x == x->parent->left){
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void RightRotate(Node* x){
        Node* y = x->left;
        x->left = y->right;
        if(y->right != nullptr){y->right->parent = x;}
        y->parent = x->parent;
        if(x->parent == nullptr){
            root = y;
        } else if (x == x->parent->right){
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void DLRotate(Node* x){
        RightRotate(x->left);
        LeftRotate(x);
    }

    void DRRotate(Node* x){
        LeftRotate(x->right);
        RightRotate(x);
    }

    bool empty() const {return sz == 0;}

    unsigned size() const {return sz;}

    Node* getroot(){
        return root;
    }


    Node* fancy_find(Node* nd, const key_type& k) const{
        if(nd == nullptr || k == nd->nodepr.first){
            return nd;
        }if(k < nd->nodepr.first){
            return fancy_find(nd->left,k);
        } else if (k > nd->nodepr.first){
            return fancy_find(nd->right,k);
        } else return nd;
    }

    iterator find(const key_type& k){
        auto fndr = fancy_find(root,k);
        if(fndr == nullptr){
            return end();
        }else {
            return iterator(fndr,false);
        }
    }

    const_iterator find(const key_type& k) const{
        auto fndr = fancy_find(root,k);
        if(fndr == nullptr){
            return cend();
        }else {
            return iterator(fndr,false);
        }
    }

    unsigned int count(const key_type& k) const{
        auto fndr = fancy_find(root,k);
        if(fndr == nullptr){
            return 0;
        } else {
            return 1;
        }
    }

    std::pair<iterator,bool> insert(const value_type& val){
        iterator tmp = find(val.first);
        if(tmp != end()){
            return std::make_pair(tmp,false);
        }
        Node* z = new Node(nullptr,nullptr,nullptr,val.first,val.second,0);
        Node* y = nullptr;
        Node* x = root;
        ++sz;
        while (x != nullptr){
            y = x;
            if(val.first < x->nodepr.first){
                x = x->left;
            }else{x = x->right;}
        }
        z->parent = y;
        if(y == nullptr){
            root = z;
        } else if(val.first < y->nodepr.first){
            y->left = z;
            if(height(y->left)-height(y->right)>=2){
                if(val.first < y->left->nodepr.first){
                    LeftRotate(y);
                }
                else {
                    DLRotate(y);
                }
            }
        } else{
            y->right = z;
             if(height(y->left)-height(y->right)>=2){
                if(val.first > y->right->nodepr.first){
                    RightRotate(y);
                }
                else {
                    DRRotate(y);
                }
            }
        }
        if(y!= nullptr) fixheight(y);
        return std::make_pair(iterator(z,false),true);
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    void transplant(Node* u, Node* v){
        if(u->parent == nullptr){
            root = v;
        } else if (u == u->parent->left){
            u->parent->left = v;
        } else u->parent->right = v;
        if (v != nullptr){
            v->parent = u->parent;
        }
    }

    unsigned int erase(const key_type& k){
        Node* z = fancy_find(root,k);
        if(z == nullptr){
            return 0;
        }else{
         Node* tmp = z; 
            if(z->left == nullptr){
                transplant(z,z->right);
            }else if(z->right == nullptr){
                transplant(z,z->left);
            }else { 
                Node* y = minNode(z->right);
                if(y->parent != z){
                  transplant(y,y->right);
                  y->right = z->right;
                  y->right->parent = y;
                }
                transplant(z,y);
                y->left = z->left;
                y->left->parent = y;
            }
            delete tmp;
            --sz;
            return 1;
        }
    }

    iterator erase(const_iterator position){
        iterator tmp(position.loc,position.itrend);
        ++tmp; 
        erase((*position).first);
        return tmp;
    }

    void cleartree(Node* x){  
        if(x!=nullptr){
            if(x->left!=nullptr)cleartree(x->left);
            if(x->right!=nullptr)cleartree(x->right);
            delete x;
        }
    }

    void clear(){
        if(root!= nullptr) cleartree(root);
        sz = 0;
        root = nullptr;
    }

    mapped_type &operator[](const K &key){
        std::pair<K,V> jk;
        jk.first = key;
        auto tmp = insert(jk); 
        return (*(tmp.first)).second;
   }
   
    bool operator==(const AVLMap<K,V>& rhs) const{
       if(sz != rhs.sz){
        return false;
       }
       for(auto thsitr = begin(); thsitr != end(); ++thsitr){
         if(rhs.count((*thsitr).first) == 0){
            return false;
         }
       }
       return true;
    }

    bool operator!=(const AVLMap<K,V>& rhs) const{
        return !(*this == rhs);
    }

    iterator begin() {
        if(sz == 0){
            return end();
        }else {
            return iterator(minNode(root),false);
        }
    }
    
    const_iterator begin() const { return cbegin();}
    
    iterator end() {
        if(sz == 0){
            return iterator(root,true); 
        }else {
            return iterator(maxNode(root),true); 
        }
    }

    const_iterator end() const { return cend(); }

    const_iterator cbegin() const { 
        if(sz == 0){
            return cend();
        }else {
            return const_iterator(minNode(root),false); 
        }
    }
    const_iterator cend() const { 
        if(sz == 0){
            return const_iterator(root,true);
        } else {
            return const_iterator(maxNode(root),true);
        }
    }


};

#endif