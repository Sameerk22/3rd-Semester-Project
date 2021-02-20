#include "route.cpp"
template<typename T>
Route_Table<T> RouteTable;


template<typename T>
class Circle {
public:
    Node<T>* head = NULL;
    int Nodes = 0;
    int space = 0;
    int currentNode = 0;
    int numMachines = 0;
    int* machineArr;


    void createMachineNetwork(int op) {
        if (op == 0) {
            srand(time(NULL));
            machineArr = new int[numMachines];
            for (int i = 0; i < numMachines; i++) {
                machineArr[i] = rand() % Nodes;
            }
        }
        else
            if (op == 1) {
                int a = 0;
                machineArr = new int[numMachines];
                for (int i = 0; i < numMachines; i++) {
                    cout << "Enter MACHINE ID" << endl;
                    cin >> a;
                    machineArr[i] = a;
                }
            }

        sortNetwork();
        genRand();
        RouteTable<T>.tabulate(space, machineArr, numMachines, Nodes);

    }

    void displaynetwork() {
        for (int i = 0; i < numMachines; i++) {
            cout << machineArr[i] << endl;
        }
        RouteTable<T>.drawTable(space, numMachines);

    }

    void sortNetwork() {
        int temp = 0;
        int compleft = 0;
        for (int i = 1; i < numMachines; i++) {
            temp = machineArr[i];
            compleft = i - 1;
            while (temp < machineArr[compleft] && compleft != -1) {
                machineArr[compleft + 1] = machineArr[compleft];
                compleft--;
            }
            machineArr[compleft + 1] = temp;
        }

        return;

    }

    void insert(int com, int newdata) {
        if (com == 1) {
            Node<T>* newnode = new Node<T>;
            Node<T>* ptr = head;
            newnode->data.callinsert(newdata);
            newnode->next = head;
            if (head != NULL) {
                while (ptr->next != head)
                    ptr = ptr->next;
                ptr->next = newnode;
            }
            else
                newnode->next = newnode;
            head = newnode;
            head->nodeId = machineArr[currentNode];
            RouteTable<T>.createtwoWayrouteNode(1, head);

            currentNode++;
        }
        else
            if (com == 0) {
                head->data.callinsert(newdata);
            }
    }
    void display() {
        Node<T>* ptr;
        ptr = head;
        do {
            cout << "Node " << ptr->nodeId << endl;
            ptr->data.display();
            cout << endl;
            cout << endl;
            cout << endl;
            ptr = ptr->next;
        } while (ptr != head);
    }

    void setNodes(int a) {
        int b = pow(2, a);
        Nodes = b;
    }
    void setspace(int a) {
        space = a;
        setNodes(a);
    }

    void setMachines(int a) {
        numMachines = a;
    }

    void genRand() {
        srand(time(NULL));
        int randspace = 0;
        for (int i = 0; i < numMachines; i++) {
            insert(1, rand() % Nodes);
            for (int j = 0; j < space; j++) {
                insert(0, rand() % Nodes);
            }

        }
    }
    void addpair(int node, int key) {
        int a = RouteTable<T>.search(node, key, space, machineArr, numMachines);
        cout << endl << a << endl;
        Node<T>* b = head;
        for (int i = 0; i < numMachines; i++) {
            if (a == b->nodeId) {
                b->data.callinsert(key);
            }
            b = b->next;
        }

    }

    void removepair(int node, int key) {
        int a = RouteTable<T>.search(node, key, space, machineArr, numMachines);
        cout << endl << a << endl;
        Node<T>* b = head;
        for (int i = 0; i < numMachines; i++) {
            if (a == b->nodeId) {
                b->data.calldelete(key);
            }
            b = b->next;
        }

    }
    void addMachine(int data) {

        int a = data;
        int* b = new int[numMachines];
        for (int i = 0; i < numMachines; i++) {
            b[i] = machineArr[i];
        }
        numMachines += 1;
        machineArr = new int[numMachines];
        machineArr[numMachines - 1] = a;
        sortNetwork();
        insert(1, rand() % Nodes);
        for (int i = 0; i < space; i++) {
            insert(0, rand() % Nodes);

        }

        RouteTable.tabulate(space, machineArr, numMachines, Nodes);
        return;

    }

};