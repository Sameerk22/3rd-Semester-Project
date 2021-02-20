#include <iostream>
#include <algorithm>
#include <time.h>
#include <cmath>
using namespace std;
static int totalFiles = 0;

template<typename T>
struct Avl_tree_Node {
    int hashval;
    Avl_tree_Node* left_Child;
    Avl_tree_Node* right_Child;
};


template<typename T>
class Tree {
public:
    Avl_tree_Node<T>* root;
    int file = 0;
    int line = 0;


    Tree() {
        root = NULL;
    }


    Avl_tree_Node<T>* full_Right(Avl_tree_Node<T>* temp) {
        Avl_tree_Node<T>* spare;
        spare = temp->right_Child;
        temp->right_Child = spare->left_Child;
        spare->left_Child = temp;

        return spare;
    }


    Avl_tree_Node<T>* right_Left_ROT(Avl_tree_Node<T>* temp) {
        Avl_tree_Node<T>* spare;
        spare = temp->right_Child;
        temp->right_Child = full_Left(spare);

        return full_Right(temp);
    }


    Avl_tree_Node<T>* full_Left(Avl_tree_Node<T>* temp) {
        Avl_tree_Node<T>* spare;
        spare = temp->left_Child;
        temp->left_Child = spare->right_Child;
        spare->right_Child = temp;

        return spare;
    }


    Avl_tree_Node<T>* left_Right_ROT(Avl_tree_Node<T>* temp) {
        Avl_tree_Node<T>* spare;
        spare = temp->left_Child;
        temp->left_Child = full_Right(spare);

        return full_Left(temp);
    }


    int diff_Factor(Avl_tree_Node<T>* spare) {
        int left_child_height = find_Depth(spare->left_Child);
        int right_child_height = find_Depth(spare->right_Child);
        int b_factor = left_child_height - right_child_height;
        return b_factor;
    }


    Avl_tree_Node<T>* b_Factor(Avl_tree_Node<T>* spare) {
        int bal_factor = diff_Factor(spare);
        if (bal_factor > 1) {
            if (diff_Factor(spare->left_Child) > 0)
                spare = full_Left(spare);
            else
                spare = left_Right_ROT(spare);
        }
        else if (bal_factor < -1) {
            if (diff_Factor(spare->right_Child) > 0)
                spare = right_Left_ROT(spare);
            else
                spare = full_Right(spare);
        }
        return spare;
    }

    int find_Depth(Avl_tree_Node<T>* spare) {
        int height = 0;
        if (spare != NULL) {
            int left_child_height = find_Depth(spare->left_Child);
            int right_child_height = find_Depth(spare->right_Child);
            int max_height = max(left_child_height, right_child_height);
            height = max_height + 1;
        }
        return height;
    }


    void  callinsert(int data) {
        root = insert(root, data);
        return;
    }


    Avl_tree_Node<T>* insert(Avl_tree_Node<T>* temp, int v) {
        if (temp == NULL) {
            temp = new Avl_tree_Node<T>;
            temp->hashval = v;
            line++;
            if (line == 100) {
                file++;
                totalFiles++;
                line = 0;
            }
            temp->left_Child = NULL;
            temp->right_Child = NULL;
            return temp;
        }
        else if (v < temp->hashval) {
            temp->left_Child = insert(temp->left_Child, v);
            temp = b_Factor(temp);
        }
        else if (v >= temp->hashval) {
            temp->right_Child = insert(temp->right_Child, v);
            temp = b_Factor(temp);
        } return temp;
    }


    Avl_tree_Node<T>* leftest_Node(Avl_tree_Node<T>* node)
    {
        Avl_tree_Node<T>* current = node;
        while (current->left_Child != NULL)
            current = current->left_Child;

        return current;
    }


    void  calldelete(int data) {
        root = deleteNode(root, data);
        return;
    }


    Avl_tree_Node<T>* deleteNode(Avl_tree_Node<T>* root1, int hashval) {

        if (root1 == NULL)
            return root1;
        else if (hashval > root1->hashval)
            root1->right_Child = deleteNode(root1->right_Child, hashval);



        else if (hashval > root1->hashval)
            root1->right_Child = deleteNode(root1->right_Child, hashval);
        else
        {

            if ((root1->left_Child == NULL) ||
                (root1->right_Child == NULL))
            {
                Avl_tree_Node<T>* temp = root1->left_Child ? root1->left_Child : root1->right_Child;


                if (temp == NULL)
                {
                    temp = root1;
                    root1 = NULL;
                }
                else
                    *root1 = *temp;

                free(temp);
            }
            else {
                Avl_tree_Node<T>* temp = leftest_Node(root1->right_Child);
                root1->hashval = temp->hashval;
                root1->right_Child = deleteNode(root1->right_Child, temp->hashval);
            }

        }

        root1 = b_Factor(root1);
        return root1;


    }


    void  display() {
        print_Tree(root, 1);
        return;
    }


    void  print_Tree(Avl_tree_Node<T>* temp, int left_Child) {
        int i;
        if (temp != NULL) {
            print_Tree(temp->right_Child, left_Child + 1);
            cout << " ";
            if (temp == root)
                cout << "Root is ";
            for (i = 0; i < left_Child && temp != root; i++)
                cout << " ";
            cout << temp->hashval;
            print_Tree(temp->left_Child, left_Child + 1);
        }
    }
};