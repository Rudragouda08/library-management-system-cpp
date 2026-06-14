#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    int issued;
};

void addBook();
void displayBooks();
void searchByTitle();
void searchByAuthor();
void issueBook();
void returnBook();

int main() {
    int choice;

    do {
        cout << "\n===== Library Management System =====";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search by Title";
        cout << "\n4. Search by Author";
        cout << "\n5. Issue Book";
        cout << "\n6. Return Book";
        cout << "\n7. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchByTitle(); break;
            case 4: searchByAuthor(); break;
            case 5: issueBook(); break;
            case 6: returnBook(); break;
            case 7: cout << "\nExiting..."; break;
            default: cout << "\nInvalid Choice!";
        }

    } while(choice != 7);

    return 0;
}

void addBook() {
    Book b;
    ofstream file("books.txt", ios::app);

    cout << "\nEnter Book ID: ";
    cin >> b.id;

    cout << "Enter Title: ";
    cin >> b.title;

    cout << "Enter Author: ";
    cin >> b.author;

    b.issued = 0;

    file << b.id << " "
         << b.title << " "
         << b.author << " "
         << b.issued << endl;

    file.close();

    cout << "\nBook Added Successfully!";
}

void displayBooks() {
    ifstream file("books.txt");

    int id, issued;
    string title, author;

    cout << "\n===== Books =====";

    while(file >> id >> title >> author >> issued) {
        cout << "\nBook ID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: " << (issued == 0 ? "Available" : "Issued");
        cout << "\n-------------------";
    }

    file.close();
}

void searchByTitle() {
    ifstream file("books.txt");

    string search;
    int id, issued;
    string title, author;
    bool found = false;

    cout << "\nEnter title: ";
    cin >> search;

    while(file >> id >> title >> author >> issued) {
        if(title == search) {
            cout << "\nBook Found!";
            cout << "\nID: " << id;
            cout << "\nAuthor: " << author;
            cout << "\nStatus: " << (issued == 0 ? "Available" : "Issued");
            found = true;
        }
    }

    if(!found)
        cout << "\nBook not found!";

    file.close();
}

void searchByAuthor() {
    ifstream file("books.txt");

    string search;
    int id, issued;
    string title, author;
    bool found = false;

    cout << "\nEnter author: ";
    cin >> search;

    while(file >> id >> title >> author >> issued) {
        if(author == search) {
            cout << "\nBook ID: " << id;
            cout << "\nTitle: " << title;
            cout << "\nStatus: " << (issued == 0 ? "Available" : "Issued");
            found = true;
        }
    }

    if(!found)
        cout << "\nNo books found!";

    file.close();
}

void issueBook() {
    ifstream file("books.txt");
    ofstream temp("temp.txt");

    int searchId;
    int id, issued;
    string title, author;
    bool found = false;

    cout << "\nEnter Book ID to issue: ";
    cin >> searchId;

    while(file >> id >> title >> author >> issued) {
        if(id == searchId) {
            found = true;

            if(issued == 1) {
                cout << "\nBook already issued!";
            } else {
                issued = 1;
                cout << "\nBook Issued Successfully!";
            }
        }

        temp << id << " "
             << title << " "
             << author << " "
             << issued << endl;
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if(!found)
        cout << "\nBook not found!";
}

void returnBook() {
    ifstream file("books.txt");
    ofstream temp("temp.txt");

    int searchId;
    int id, issued;
    string title, author;
    bool found = false;

    cout << "\nEnter Book ID to return: ";
    cin >> searchId;

    while(file >> id >> title >> author >> issued) {
        if(id == searchId) {
            found = true;

            if(issued == 0) {
                cout << "\nBook is already available!";
            } else {
                issued = 0;
                cout << "\nBook Returned Successfully!";
            }
        }

        temp << id << " "
             << title << " "
             << author << " "
             << issued << endl;
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if(!found)
        cout << "\nBook not found!";
}