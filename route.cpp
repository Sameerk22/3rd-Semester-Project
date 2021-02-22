#include "avl.cpp"
template<typename T>
struct Node {
    Tree<T> data;
    long nodeId;
    Node<T>* next;

};


template<typename T>
struct routeNode {
    int data;
    int* data1;
    routeNode<T>* next;
    routeNode<T>* prev;
    Node<T>* link;
};


template<typename T>
class Route_Table {
public:
    routeNode<T>* head;
    routeNode<T>* tail;
    routeNode<T>* spare;


    void tabulate(int space, int* machineArr, int msize, int nodes) {
        routeNode<T>* tempNode = head;

        for (int k = 0; k < msize; k++) {
            int first = machineArr[k];
            tempNode->data1 = new int[space];
            int temp = 0, temp1 = 0;
            for (int i = 0; i < space; i++) {
                temp1 = pow(2, i);
                temp = (first + temp1) % nodes;
                cout << "t" << temp << endl;
                for (int j = 0; j < msize; j++) {

                    if (temp > machineArr[j]) {
                        if (temp > machineArr[msize - 1]) {
                            for (int z = 0; z < msize; z++) {
                                if (temp < nodes) {
                                    tempNode->data1[i] = machineArr[0];
                                }
                                if (temp <= machineArr[z]) {
                                    tempNode->data1[i] = machineArr[z];
                                    z = msize;
                                    j = msize;
                                }
                            }
                        }
                    }
                    else
                        if (temp <= machineArr[j]) {
                            tempNode->data1[i] = machineArr[j];
                            j = msize;
                        }

                }
            }
            tempNode = tempNode->next;
        }
    }

    void drawTable(int space, int msize) {
        routeNode<T>* b = head;
        for (int k = 0; k < msize; k++) {
            cout << "FTP " << k + 1 << endl;
            for (int i = 0; i < space; i++) {

                cout << b->data1[i] << endl;
            }
            cout << "----------------" << endl;
            b = b->next;
        }
    }

    int search(int nodeid, int key, int space, int* machineArr, int msize) {

        routeNode<T>* tempNode = head;
        int id = 0;
        for (int i = 0; i < msize; i++) {
            if (machineArr[i] == nodeid)
                id = i;
        }

        for (int i = 0; i < id; i++) {
            tempNode = tempNode->next;
        }
        id = nodeid;
        int temp1 = 0;
        cout << "Start from node " << nodeid << endl;
        for (int j = 0; j < msize; j++) {
            if (id == key) {
                cout << "True" << endl;
                temp1 = id;
                return temp1;
            }
            else
                if (id < key && key <= tempNode->data1[0]) {
                    temp1 = tempNode->data1[0];
                    cout << "Jump to Node 1 " << temp1 << endl;
                    j = msize;
                    id = temp1;
                }
                else
                    for (int i = 0; i < space; i++) {
                        if (tempNode->data1[i] < key && key <= tempNode->data1[i + 1]) {
                            temp1 = tempNode->data1[i];
                            cout << "Jump to Node 2 " << temp1 << endl;
                            i = space;
                            id = temp1;
                        }
                    }
            if (tempNode->next == NULL) {
                tempNode = head;
            }
            tempNode = tempNode->next;
        }
        return temp1;
    }

    Route_Table() {
        head = NULL;
        tail = NULL;
        spare = NULL;
    }
    routeNode<T>* gethead() {
        return head;
    }
    routeNode<T>* gettail() {
        return tail;
    }

    void createtwoWayrouteNode(int value, Node<T>* link1) {
        routeNode<T>* n = new routeNode<T>;
        n->data = value;
        n->link = link1;
        n->prev = NULL;
        n->next = NULL;
        if (head == NULL) {

            head = n;
            tail = n;
        }
        else {
            n->prev = tail;
            tail->next = n;
            tail = n;
        }
    }

    void deleterouteNode(int deldata) {
        tail = head;
        routeNode* delptr = NULL;
        while (tail != NULL) {
            if (tail->data == deldata) {

                delptr = tail;
                tail->prev->next = tail->next;
                tail->next->prev = tail->prev;
            }
            tail = tail->next;
        }
        delete delptr;
    }
    void removeAt(int index) {
        routeNode* delptr = NULL;
        int count = 0;
        tail = head;
        while (tail != NULL) {
            count++;
            if (count == index) {
                delptr = tail;
                tail->prev->next = tail->next;
                tail->next->prev = tail->prev;

            }
            tail = tail->next;
        }
        delete delptr;
    }
    void sortlist() {
        int temp = 0;
        tail = head;
        while (tail != NULL) {
            spare = tail->next;
            while (spare != NULL) {
                if (tail->data > spare->data) {
                    temp = tail->data;
                    tail->data = spare->data;
                    spare->data = temp;
                }
                spare = spare->next;
            }
            tail = tail->next;
        }

    }

    void printforward(routeNode<T>* headd) {
        routeNode* save = headd;
        while (save != NULL) {
            cout << "The data in the routeNode is:" << save->data << endl;
            save = save->next;
        }
        cout << endl;
    }
    void printreverse(routeNode<T>* taill) {
        routeNode* temp = taill;
        while (temp != NULL) {
            cout << "The data in the routeNode is:" << temp->data << endl;
            temp = temp->prev;
        }
    }

};
