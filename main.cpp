#include <iostream>

using namespace std;

// class Person {
//     public:
//         Person(string firstName, string lastName, int number){
//             firstName = firstName;
//             lastName = lastName;
//             number = number;
//         };
//     private:
        // string firstName;
        // string lastName;
        // int number;
// };

struct Person {
    string firstName;
    string lastName;
    int number;
};

struct BinarySearchTree {
    Person person;
    BinarySearchTree *left, *right;
    public:
        BinarySearchTree();
        BinarySearchTree(Person);
};

class Book {
    public:
        void Add(Person *person) {

        };
        void Delete(Person *person){

        };
        Person Find(Person person){

        };
        Person Change(Person *person, int newNumber){

        };
        Person Display(){

        };
        void Quit(){

        };
    private:
        Person personData;

};

class UserInterface {
    
};

int main()
{

    return 0;
}