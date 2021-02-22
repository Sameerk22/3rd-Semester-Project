#include "DHT.cpp"
int hashkey(string key) {
    int result = 0;
    int power = 1;
    char arr = 'a';
    char arr1 = 'A';
    for (int j = 0; j < key.length(); j++) {
        for (int i = 0; i < 26; i++) {
            if (key[j] == arr) {
                result += pow(10, j);
                result += i;
            }
            arr = arr + 1;

        }
        arr = 'a';
    }
    return result;
}

void displayMenu()
{
    cout << "Please choose an option:\n";
    cout << "1. Specify Number of Machines\n";
    cout << "2. Specify Number of Bits\n";
    cout << "3. Option to manually assign Id to each machine.\n";
    cout << "4. Automatically assign ID to each machine\n";
    cout << "5. Insert data in the form of key, value pairs from any machine.\n";
    cout << "6. Remove data by specifying the key from any machine.\n";
    cout << "7. Print the routing table of any machine.\n";
    cout << "8. Print the AVL tree maintain on any machine.\n";


}


int main() {

    Circle<int> a;
    int choice = 1;
    int num = 0;
    int node = 0;
    string key = "", value = "";
    
    while (choice != 0) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Please choose number of Machines" << endl;
            cin >> num;
            a.setMachines(num);
            break;
        case 2:
            cout << "Please choose number of Bits" << endl;
            cin >> num;
            a.setspace(num);
            break;
        case 3:
            a.createMachineNetwork(1);
            break;
        case 4:
            a.createMachineNetwork(0);
            break;
        case 5:
            cout << "Please enter your node" << endl;
            cin >> node;
            cout << "Please enter your key" << endl;
            cin >> key;
            a.addpair(node, hashkey(key));
            break;
        case 6:
            cout << "Please enter your node" << endl;
            cin >> node;
            cout << "Please enter your key" << endl;
            cin >> key;
            a.removepair(node, hashkey(key));
            break;
        case 7:
            a.displaynetwork();
            break;
        case 8:
            a.display();
            break;
        default:
            break;
        }
    }
    
/*
    Circle<int> a;
    a.setspace(5);
    a.setMachines(9);
    a.createMachineNetwork(1);
    //a.setactiveNodes(20);

   // a.genRand();
    cout << "The circular linked list is: " << endl;
    //a.display();
   // long int b = hashkey("Sameer",a.space);
   // cout << b;
    a.displaynetwork();
    int b = hashkey("l");
    cout << b<<endl;
    a.addpair(28,b);

    a.display();

    // a.addMachine(7);
     //a.display();
     //a.removepair(28, 12);
     //a.display();
     */

    return 0;
}