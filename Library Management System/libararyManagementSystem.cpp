#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Library {
    string id, name, author;
    fstream file;

public:
    void addBook();
    void showAllBooks();
    void extractBook();
    void deleteBook();
    void updateBook();
};

void Library::addBook() {
    cin.ignore();
    cout << "\nEnter Book ID: ";
    getline(cin, id);
    cout << "Enter Book Name: ";
    getline(cin, name);
    cout << "Enter Author Name: ";
    getline(cin, author);

    file.open("bookData.txt", ios::out | ios::app);
    if (file.is_open()) {
        file << id << "*" << name << "*" << author << "\n";
        cout << "Book added successfully!\n";
        file.close();
    } else {
        cout << "Error opening file.\n";
    }
}

void Library::showAllBooks() {
    file.open("bookData.txt", ios::in);
    if (!file.is_open() || file.peek() == EOF) {
        cout << "\nNo books available.\n";
        return;
    }

    cout << "\n\n\tBook ID\t\tBook Name\t\tAuthor Name\n";
    cout << "-------------------------------------------------------------\n";

    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author);
        cout << "\t" << id << "\t\t" << name << "\t\t" << author << "\n";
    }

    file.close();
}

void Library::extractBook() {
    cin.ignore();
    cout << "\nEnter Book ID to Search: ";
    getline(cin, id);

    bool found = false;
    file.open("bookData.txt", ios::in);
    while (getline(file, name, '*')) {
        string tempName, tempAuthor;
        getline(file, tempName, '*');
        getline(file, tempAuthor);

        if (name == id) {
            cout << "\nBook Found:\n";
            cout << "Book ID: " << name << "\n";
            cout << "Book Name: " << tempName << "\n";
            cout << "Author: " << tempAuthor << "\n";
            found = true;
            break;
        }
    }

    if (!found) cout << "Book not found!\n";

    file.close();
}

void Library::deleteBook() {
    cin.ignore();
    cout << "\nEnter Book ID to Delete: ";
    getline(cin, id);

    fstream tempFile("temp.txt", ios::out);
    file.open("bookData.txt", ios::in);

    bool found = false;
    while (getline(file, name, '*')) {
        string tempName, tempAuthor;
        getline(file, tempName, '*');
        getline(file, tempAuthor);

        if (name != id) {
            tempFile << name << "*" << tempName << "*" << tempAuthor << "\n";
        } else {
            found = true;
        }
    }

    file.close();
    tempFile.close();
    remove("bookData.txt");
    rename("temp.txt", "bookData.txt");

    if (found)
        cout << "Book deleted successfully!\n";
    else
        cout << "Book not found.\n";
}

void Library::updateBook() {
    cin.ignore();
    cout << "\nEnter Book ID to Update: ";
    getline(cin, id);

    fstream tempFile("temp.txt", ios::out);
    file.open("bookData.txt", ios::in);

    bool found = false;
    while (getline(file, name, '*')) {
        string tempName, tempAuthor;
        getline(file, tempName, '*');
        getline(file, tempAuthor);

        if (name == id) {
            found = true;
            cout << "\nEnter New Book Name: ";
            getline(cin, tempName);
            cout << "Enter New Author Name: ";
            getline(cin, tempAuthor);
        }

        tempFile << name << "*" << tempName << "*" << tempAuthor << "\n";
    }

    file.close();
    tempFile.close();
    remove("bookData.txt");
    rename("temp.txt", "bookData.txt");

    if (found)
        cout << "Book updated successfully!\n";
    else
        cout << "Book not found.\n";
}

int main() {
    Library obj;
    char choice;

    do {
        cout << "\n\n========== Library Management ==========\n";
        cout << "1. Show All Books\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Add Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Update Book\n";
        cout << "6. Exit\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            obj.showAllBooks();
            break;
        case '2':
            obj.extractBook();
            break;
        case '3':
            obj.addBook();
            break;
        case '4':
            obj.deleteBook();
            break;
        case '5':
            obj.updateBook();
            break;
        case '6':
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != '6');

    return 0;
}
