#include <bits/stdc++.h>
using namespace std;

const int maxBooks = 1000;

struct Holders {
    string name;
    int phoneNo;
};

struct Book {
    int id;
    string name;
    string authorName;
    int copies;
    float price;
    vector<Holders> holders;
};

Book books[maxBooks];
int bookCount = 0;
int bookId = 100;

int partition(Book arr[], int start, int end, string sortField) {
    Book pivot = arr[start];
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (sortField == "id") {
            if (arr[i].id <= pivot.id)
                count++;
        } else if (sortField == "name") {
            if (arr[i].name <= pivot.name)
                count++;
        }
    }
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {
        if (sortField == "id") {
            while (arr[i].id <= pivot.id) {
                i++;
            }

            while (arr[j].id > pivot.id) {
                j--;
            }
        } else if (sortField == "name") {
            while (arr[i].name <= pivot.name) {
                i++;
            }

            while (arr[j].name > pivot.name) {
                j--;
            }
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(Book arr[], int start, int end, string sortField) {
    if (start >= end)
        return;
    int p = partition(arr, start, end, sortField);
    quickSort(arr, start, p - 1, sortField);
    quickSort(arr, p + 1, end, sortField);
}

void printBooks(Book arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "Book ID: " << arr[i].id << "\nName: " << arr[i].name << "\nAuthor Name: " << arr[i].authorName <<"\nCopies: " << arr[i].copies << "\nPrice: " << arr[i].price << "\nNumber of Holders: " << arr[i].holders.size() << "\n---------------------------------------------------\n";
    }
}

void printBook(Book book) {
    cout << "Book Details: \nName: " << book.name << "\nAuthor Name: " << book.authorName << "\nCopies: " << book.copies << "\nPrice: " << book.price;
    if (!book.holders.empty()) {
        cout << "\nHolders: ";
        for (const auto& holder : book.holders) {
            cout << "\nName: " << holder.name << ", Phone No: " << holder.phoneNo;
        }
    }
    cout << endl;
}

void addBook(Book arr[]) {
    if (bookCount < maxBooks) {
        string name;
        string authorName;
        int copies;
        float price;
        cout << "Enter details of book: \nBook Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Author Name: ";
        getline(cin, authorName);
        cout << "Number of Copies: ";
        cin >> copies;
        cout << "Price: ";
        cin >> price;
        books[bookCount] = {bookId, name, authorName, copies, price};
        bookCount++;
        bookId++;
    } else {
        cout << "LIBRARY IS FULL!!\n";
    }
}

void issueBook(Book &book){
    if(book.copies > 0){
        string name;
        int phoneNo;
        cout<<"Enter your details \nName: ";
        cin.ignore();
        getline(cin, name);
        cout<<"Phone Number: ";
        cin>>phoneNo;
        Holders holder;
        holder.name = name;
        holder.phoneNo = phoneNo;
        book.holders.push_back(holder);
        book.copies--;
        cout<<"Book issued.\nNumber of copies left: "<<books->copies<<"\n";
    }
    else{
        cout<<"Book out of Stock\n";
    }
}

void deleteBook(Book arr[], int ind){
    swap(arr[ind], arr[bookCount-1]);
    cout<<"Book with id "<<arr[bookCount-1].id<<" is deleted successfully!\n";
    bookCount--;
}

void returnBook(Book arr[], int ind){
    int phone;
    cout<<"Enter your phone number: ";
    cin>>phone;
    auto &holders = arr[ind].holders;
    for (auto it = holders.begin(); it != holders.end(); ++it) {
        if (it->phoneNo == phone) {
            holders.erase(it);
            cout << "Holder with phone number '" << phone << "' removed from book with id '" << arr[ind].id << "'\n";
            arr[ind].copies++;
            return;
        }
    }
    cout << "Holder not found.\n";
    return;
}

int searchBook(Book arr[], int bookCount) {
    int choice;
    cout << "Search book by \n1. Title\n2. Id\nEnter your choice: ";
    cin >> choice;
    if (choice == 1) {
        string title;
        cout << "Enter book title: ";
        cin.ignore();
        getline(cin, title);
        quickSort(books, 0, bookCount - 1, "name");
        int low = 0, high = bookCount - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid].name == title) {
                printBook(arr[mid]);
                return mid;
            } else if (arr[mid].name < title) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        cout << "Book not found.\n";
    } else if (choice == 2) {
        int id;
        cout << "Enter book id: ";
        cin >> id;
        quickSort(books, 0, bookCount - 1, "id");
        int low = 0, high = bookCount - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid].id == id) {
                printBook(arr[mid]);
                return mid;
            } else if (arr[mid].id < id) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        cout << "Book not found.\n";
    } else {
        cout << "WRONG INPUT!!\n";
    }
    return -1;
}

int main() {
    bool f = true;
    cout << "\nLibrary Management System\n";
    while (f) {
        int choice;
        cout << "1. Add New Book\n";
        cout << "2. Search for a Book\n";
        cout << "3. Issue a Book\n";
        cout << "4. Return a Book\n";
        cout << "5. List All Books\n";
        cout << "6. Delete a Book\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        int ind;
        int ch;

        switch (choice) {
            case 1:
                addBook(books);
                break;
            case 2:
                ind = searchBook(books, bookCount);
                break;
            case 3:
                cout << "Search Book that you need!\n";
                ind = searchBook(books, bookCount);
                if(ind != -1){
                    issueBook(books[ind]);
                }
                break;
            case 4:
                cout << "Search Book that is to be returned!\n";
                ind = searchBook(books, bookCount);
                if(ind != -1){
                    returnBook(books, ind);
                }
                break;
            case 5:
                ch;
                cout << "How would you like to sort books to display?\n1. by ID\n2. by title\n";
                cin>>ch;
                if(ch == 1){
                    quickSort(books, 0, bookCount-1, "id");
                    printBooks(books, bookCount);
                }
                else if(ch == 2){
                    quickSort(books, 0, bookCount-1, "name");
                    printBooks(books, bookCount);
                }
                else{
                    cout<<"WRONG INPUT!!\n";
                }
                break;
            case 6:
                cout<<"Search for book to be deleted!\n";
                ind = searchBook(books, bookCount);
                if(ind != -1){
                    deleteBook(books, ind);
                }
                break;
            case 7:
                ch;
                cout<<"Do you sure want to exit?\nPress 1 to exit\nPress any other key to continue\n";
                cin>>ch;
                if(ch == 1){
                    f = false;
                }
                break;
            default:
                cout<<"Please input a correct option!!\n";
        }
    }
}