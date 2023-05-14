#include <iostream>

class DblList;
class DblListNode {
    friend class DblList;
    private:
        int data;
        DblListNode *left, *right;
};

class DblList {
    public:
        //리스트 조작연산
        void Delete(DblListNode*);

    
    private:
        DblListNode * first; //헤더노드를 가리킴
    
};


void DblList::Delete(DblListNode *x)
{
    if (x==first) throw "Deletion of header node not permitted";
    else {
        x->left->right = x->right;
        x->right->left = x->left;
        delete x;
    }
}

void DblList::Insert(DblListNode *p, DblListNode *x)
{//노드 x의 오른편에 노드 p 삽입
    p->left = x; p->right = x->right;
    x->right->left = p; x->right = p;
}