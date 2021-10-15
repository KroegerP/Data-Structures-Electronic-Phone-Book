// Homework 3
// EECE 4040
// Group 3 - Peter Kroeger, Reagan Maddox, Michael Limberg

#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <stack>
#include <sstream>

using namespace std;

class Person {
    public:
        Person() {
            firstName = "";
            lastName = "";
            number = NULL;
        }
        Person(string firstName, string lastName, int number) : firstName(firstName), lastName(lastName), number(number) {}
        string GetLastName() {
            return lastName;
        }
        string GetFirstName() {
            return firstName;
        }
        int GetNumber() {
            return number;
        }
        void SetNumber(int value) {
            number = value;
        }
        void SetFirstName(string value) {
            firstName = value;
        }
        void SetLastName(string value) {
            lastName = value;
        }
    private:
        string firstName;
        string lastName;
        int number;
};

struct Node {
    Person person;
    Node* left;
    Node* right;
    public:
        Node(Person newPerson) : person(newPerson), left(NULL), right(NULL) {}
        // void add(Person *person){}
};

class Book {
    public:
        Book() {
            root = NULL;
        }
        void Add(Person* newPerson);

        void Delete(string lastName, string firstName);

        Node* Find(Node* root, string last, string first);
        
        void Change(string lastName, string firstName, int newNumber){   // Perform a find, and replace the phone number member of person at that node
            Node* personFind = Find(root, lastName, firstName);
            if (personFind != NULL) {
                personFind -> person.SetNumber(newNumber);
                cout << firstName << lastName << "'s number has been changed in the phone book." << endl << endl;
            }
            else{
                cout << "Cannot change number of person not in phone book." << endl << endl;
            }
        };
        Node* Display(Node* root){   // Inorder traversal
            if(root == NULL){
                return(NULL);
            }
            else{
                Display(root->left); //check left child
                cout << root->person.GetFirstName() << " " << root->person.GetLastName()<< " " << root->person.GetNumber() << endl; //print node data
                Display(root->right); //check right child
            }
            return(NULL);
        };
        void Quit(){    // Saving book to text file
            stack<Node *> treeStack;        // Use a stack instead of recursion to perform traversal through tree
            Node* curNode = root;
            ofstream bookFile;

            bookFile.open("PhoneBook.txt");

            bookFile << "First Name | Last Name | Number" << endl;
            
            while (curNode != NULL || treeStack.empty() == false) {
                while(curNode != NULL){
                    treeStack.push(curNode);
                    curNode = curNode -> left;
                }
                curNode = treeStack.top();
                bookFile << curNode -> person.GetFirstName() << " " << curNode -> person.GetLastName() << " " << curNode -> person.GetNumber() << endl;
                treeStack.pop();
                curNode = curNode -> right;
            }
            bookFile.close();
            return;
        };

        void RestoreTree(string textFile) {
            string line, firstName, lastName;
            int number;
            ifstream bookFile;
            Person* newPerson = new Person();
            bookFile.open(textFile.c_str());
            while (getline(bookFile, line)) {
                stringstream ss(line);              // String stream for each line with each value seperated by spaces
                ss >> firstName;                    // -> firstName lastName number
                ss >> lastName;
                ss >> number;
                newPerson -> SetFirstName(firstName);
                newPerson -> SetLastName(lastName);
                newPerson -> SetNumber(number);
                Add(newPerson);
            }
        }

        Node* GetRoot() {
            return root;
        }

    private:
        friend class Node;
        friend class Person;
        Node* root;
        

};

void Book :: Add(Person* newPerson)  { // Recursively find the location to add the new person based on last/first name      
    Node* newNode = new Node(*newPerson);
    newNode -> person = *newPerson;
    newNode -> left = NULL;
    newNode -> right = NULL;
    if (root == NULL) {
        root = newNode;
    }
    else {
        Node* curNode = root;
        while (curNode != NULL) {
            if(newPerson -> GetLastName() < curNode -> person.GetLastName()) { // Last name less than current node
                if(curNode -> left == NULL) {
                    curNode -> left = newNode;
                    return;
                }
                else curNode = curNode -> left;
            }
            else if(newPerson -> GetLastName() > curNode -> person.GetLastName()) { // Last name greater than current node
                if(curNode -> right == NULL) {
                    curNode -> right = newNode;
                    return;
                }
                else curNode = curNode -> right; 
            }
            else {  // Last names are equal, check the first names
                if(newPerson -> GetFirstName() < curNode -> person.GetFirstName()) { // First name less than current node
                    if(curNode -> left == NULL) {
                        curNode -> left = newNode;
                        return;
                    }
                    else curNode = curNode -> left;
                }
                else {                                                                                // First name greater than current node
                    if(curNode -> right == NULL) {
                        curNode -> right = newNode;
                        return;
                    }
                    else curNode = curNode -> right;
                }
            }
        }
    }
}

void Book :: Delete(string lastName, string firstName){ // Just find the person and delete the number associated
    Node* personFind = Find(root, lastName, firstName);
    if(personFind != NULL) {
        personFind -> person.SetNumber(0);
        cout << firstName << " " <<  lastName << "'s number has been deleted from the phone book." << endl << endl;
    }
    else{
        cout << "Cannot delete number of person not in phone book." << endl << endl;
    } 
};

Node* Book :: Find(Node* root, string last, string first){ // In PSN
    if(root == NULL){
        cout << first << " " << last << " is not in the phone book." << endl << endl;
        return NULL;
    }
    else{
        // Search Left
        if(root -> person.GetLastName().compare(last) == -1){
            return Find(root->left, last, first);
        }
        // Search Right
        else if(root -> person.GetLastName().compare(last) == 1){
            return Find(root->right, last, first);
        }
        // Found
        else{
            cout << first << " " << last << " has been found in the phone book. Their phone number is: ";
            return root;
            cout << endl << endl;
        }
    }
};

class UserInterface {
    public:
        char FileRestore() {
            char ans;
            cout << "Do you want to restore a phone book from a text file? (Y/N)" << endl;
            cin >> ans;
            return ans;
        }
        void printUI(){
            cout << "-----------Please select an option from the menu below-----------" << endl;
            cout << "0 - Add a person to the phone book" << endl;
            cout << "1 - Delete a person's number in the phone book" << endl;
            cout << "2 - Find a person in the phone book (by name)" << endl;
            cout << "3 - Change a person's number" << endl;
            cout << "4 - Display the phone book in last name alphabetical order" << endl;
            cout << "5 - Quit the program" << endl;
            cout << "-----------------------------------------------------------------" << endl;
        }
};

int PhoneNumberCheck(bool newNum) {
    int phoneNumber = NULL;
    while(phoneNumber == NULL) {
        newNum ? cout << "New Phone Number: " : cout << "Phone Number: ";
        cin >> phoneNumber;
        if(phoneNumber < 999999) {  // If it is less than this, the phone number will have less than 7 digits
            cout << "ERROR: Phone number must be at least 7 digits long!" << endl;
            phoneNumber = NULL;
        }
    }
    return phoneNumber;
}

int main()
{
    // Instance of UserInterface
    UserInterface u;

    // Instance of Phone Book
    Book PhoneBook;

    // Declare variables for user input
    string first, last, textFile;
    bool newNum = false;
    int phoneNumber = NULL;
    int option = 999;

    Person* newPerson = new Person();

    char ans = u.FileRestore();

    if(toupper(ans) == 'Y') {
        cout << "Enter the name of the text file: ";
        cin >> textFile;
        PhoneBook.RestoreTree(textFile);
    }

    do{
        u.printUI();
        cin >> option;
        switch(option){
            default:
                cout << "INVALID CHOICE. PLEASE TRY AGAIN" << endl << endl;
                break;
            case 0:
                cout << "You chose option 0 - Add a person to the phone book." << endl;
                cout << "First Name: ";
                cin >> first;
                cout << "Last Name: ";
                cin >> last;
                newNum = false;
                phoneNumber = PhoneNumberCheck(newNum);
                newPerson -> SetNumber(phoneNumber);
                newPerson -> SetFirstName(first);
                newPerson -> SetLastName(last);
                PhoneBook.Add(newPerson);
                cout << first << " " << last << " has been added to the phone book." << endl << endl;
                break;
            case 1:
                cout << "You chose option 1 - Delete a person's number in the phone book." << endl;
                cout << "First name of person: ";
                cin >> first;
                cout << "Last name of person: ";
                cin >> last;
                PhoneBook.Delete(last, first);
                break;
            case 2:
                cout << "You chose option 2 - Find a person in the phone book (by name)." << endl;
                cout << "First name of person: ";
                cin >> first;
                cout << "Last name of person: ";
                cin >> last;
                PhoneBook.Find(PhoneBook.GetRoot(), last, first);
                break;
            case 3:
                cout << "You chose option 3 - Change a person's phone number." << endl;
                cout << "First name of person: ";
                cin >> first;
                cout << "Last name of person: ";
                cin >> last;
                newNum = true;
                phoneNumber = PhoneNumberCheck(newNum);
                PhoneBook.Change(last, first, phoneNumber);
                break;
            case 4:
                cout << "You chose option 4 - Display the phone book (in alphabetical order)." << endl;
                PhoneBook.Display(PhoneBook.GetRoot());
                break;
            case 5:
                cout << "You chose option 5 - Exit the program." << endl;
                cout << "The phone book will be saved as a text file." << endl << endl;
                PhoneBook.Quit();
                break;
        }
    }while(option != 5);

    return 0;
}
