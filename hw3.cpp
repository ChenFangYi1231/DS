/*
 * 1. This Program is Developed Solely by Myself: Yes
 * 2. Student ID: 107061207
 * 3. OJ ID: DS2107061207
 * 4. OJ SID: 2223836
 * 5. OJ Score: 10
 */

#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class Tree;
class TreeNode { 
    friend class Tree; private: 
    char data; 
    TreeNode *leftChild; 
    TreeNode *rightChild; 
};

class Tree{ 
    public:
        // return 1 if ch[] is the same as level order of the tree, else return 0
        int checkLevel(char *ch, int index);
        // return 1 if ch[] is the same as inorder of the tree, else return 0
        int checkInorder(char *ch, int index);
        // build a tree according to given level order and inorder string
        TreeNode *buildTree(char *chl, char* chi, int len); 
        TreeNode *root; 
};


int main(void)
{
    int i, j, k, done;
    int num, len, per[26];
    char chl[26], c, chi[26];
    Tree *t = new Tree;

    scanf("%d\n", &num);            // number of sequence pairs
    for(i = 0; i < num; i++){
        done = 0;
        j = 0;
        while(!done){               // scan level order string
            scanf("%c", &c);
            if(c == '\n'){
                done = 1;
            }
            else{
                chl[j] = c;
                j++;
            }
        }
        len = j;                    // length of the string
        for(j = 0; j < len; j++){   // scan inorder string
            scanf("%c", &chi[j]);
        }
        for(j = 0; j < len; j++){   // calculate permutaion
            for(k = 0; k < len; k++){
                if(chl[j] == chi[k]){
                    per[j] = k;
                    k = len;
                }
            }
        }
        scanf("%c", &c);
        t->root = t->buildTree(chl, chi, len);  // build a tree according to strings
        if(i == 0){                     // print number of pairs
            printf("%d\n", num);
        }
        for(j = 0; j < len; j++){       // print level order string
            printf("%c", chl[j]);
        }
        printf("\n");
        for(j = 0; j < len; j++){       // print inorder string
            printf("%c", chi[j]);
        }
        printf(" ");
        for(j = 0; j < len; j++){       // print permutation and the result
            printf("%d", per[j]);
            if(j != len - 1){
                printf("-");
            }
            else if(t->checkLevel(chl, 0) && t->checkInorder(chi, 0)){
                printf(" Yes\n");
            }
            else{
                printf(" No\n");
            }
        }
    }
}

TreeNode * Tree::buildTree(char *chl, char* chi, int len)
{
    TreeNode *root = new TreeNode;
    int i, j, index, countl = 0, countr = 0;
    char *Rlevel, *Rinorder, *Llevel, *Linorder;

    
    root->data = chl[0];            // first term of level order is root
    if(len == 1){                   // root is the last term
        root->rightChild = 0;
        root->leftChild = 0;
    }
    else{
        for(i = 0; i < len; i++){   // find the index of inorder string which data is root
            if(root->data == chi[i]){
                index = i;
                i = len;
            }
        }
        if(index != len - 1){                   // right tree exists
            Rinorder = new char[len - 1];       // new inorder string for right tree
            Rlevel = new char[len - 1];         // new level order string for right tree
            for(i = 0, countr = 0; i < len; i++){
                if(i > index){
                    Rinorder[countr] = chi[i];
                    countr++;
                }
            }
            for(i = 1, countr = 0; i < len; i++){
                for(j = 0; j < len; j++){
                    if(chl[i] == chi[j]){
                        if(j > index){
                            Rlevel[countr] = chl[i];
                            countr++;
                        }
                        j = len;
                    }
                }
            }
            // build right tree of root
            root->rightChild = buildTree(Rlevel, Rinorder, len - index - 1);
            delete [] Rinorder;
            delete [] Rlevel;
        }
        else{       // right tree DNE, so rightChild of root is NULL
            root->rightChild = 0;
        }
        if(index != 0){                     // left tree exists
            Linorder = new char[index];     // new inorder string for left tree
            Llevel = new char[index];       // new level order string for left tree
            for(i = 0, countr = 0, countl = 0; i < len; i++){
                if(i < index){
                    Linorder[countl] = chi[i];
                    countl++;
                }
            }
            for(i = 1, countr = 0, countl = 0; i < len; i++){
                for(j = 0; j < len; j++){
                    if(chl[i] == chi[j]){
                        if(j < index){
                            Llevel[countl] = chl[i];
                            countl++;
                        }
                        j = len;
                    }
                }
            }
            // left tree DNE, so leftChild of root is NULL
            root->leftChild = buildTree(Llevel, Linorder, index);
            delete [] Llevel;
            delete [] Linorder;
        }
        else{   
            root->leftChild = 0;
        }
    }
    return root;
}

int Tree::checkLevel(char* ch, int index)
{
    queue <TreeNode *> q;
    TreeNode *currentNode = root;

    while (currentNode)
    { 
        if(currentNode->data != ch[index]){
            return 0;       // data is different, return 0
        }
        else{
            index++;
        }
        if (currentNode->leftChild) 
            q.push(currentNode->leftChild);
        if (currentNode->rightChild) 
            q.push(currentNode->rightChild);
        if (q.empty())
            return 1;       // all the element is tested, return 1
        currentNode = q.front(); q.pop();
    }
}

int Tree::checkInorder(char *ch, int index)
{
    stack <TreeNode*> s;
    TreeNode *currentNode = root;
    while(1){
        while(currentNode){
            s.push(currentNode);
            currentNode = currentNode->leftChild;
            currentNode = s.top();
            s.pop();
            if(s.empty())
                return 1;   // all the element is tested, return 1
            if(currentNode->data != ch[index]){
                return 0;   // data is different, return 0
            }
            else{
                index++;
            }
            currentNode = currentNode->rightChild;
        }
    }

}
