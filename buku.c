#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BOOKS 100
#define MAX_TITLE 50
#define MAX_AUTHOR 50
#define MAX_PUBLISHER 50

// Struktur data untuk buku
struct Book {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    char publisher[MAX_PUBLISHER];
    int year;
    float price;
    int stock;
    int isActive; // 1 = active, 0 = deleted
};

// Array untuk menyimpan buku
struct Book books[MAX_BOOKS];
int bookCount = 0;

// Function prototypes
void addBook();
void editBook();
void deleteBook();
void searchBook();
void displayBook(struct Book book);
void displayAllBooks();
int findBookById(int id);
void clearScreen();

int main() {
    int choice;
    
    do {
        printf("\n=== Buku ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Edit Buku\n");
        printf("3. Hapus Buku\n");
        printf("4. Cari Buku\n");
        printf("5. Tampilkan Semua Buku\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        clearScreen();
        
        switch(choice) {
            case 1:
                addBook();
                break;
            case 2:
                editBook();
                break;
            case 3:
                deleteBook();
                break;
            case 4:
                searchBook();
                break;
            case 5:
                displayAllBooks();
                break;
        }
    } while(choice != 0);
    
    return 0;
}

void addBook() {
    if(bookCount >= MAX_BOOKS) {
        printf("Database penuh!\n");
        return;
    }
    
    struct Book newBook;
    newBook.id = bookCount + 1;
    newBook.isActive = 1;
    
    printf("=== Tambah Buku Baru ===\n");
    printf("Judul: ");
    getchar();
    fgets(newBook.title, MAX_TITLE, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;
    
    printf("Pengarang: ");
    fgets(newBook.author, MAX_AUTHOR, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;
    
    printf("Penerbit: ");
    fgets(newBook.publisher, MAX_PUBLISHER, stdin);
    newBook.publisher[strcspn(newBook.publisher, "\n")] = 0;
    
    printf("Tahun Terbit: ");
    scanf("%d", &newBook.year);
    
    printf("Harga: ");
    scanf("%f", &newBook.price);
    
    printf("Stok: ");
    scanf("%d", &newBook.stock);
    
    books[bookCount] = newBook;
    bookCount++;
    
    printf("\nBuku berhasil ditambahkan!\n");
}

void editBook() {
    int id;
    printf("Masukkan ID buku yang akan diedit: ");
    scanf("%d", &id);
    
    int index = findBookById(id);
    if(index == -1) {
        printf("Buku tidak ditemukan!\n");
        return;
    }
    
    printf("=== Edit Buku ===\n");
    printf("Judul [%s]: ", books[index].title);
    getchar();
    fgets(books[index].title, MAX_TITLE, stdin);
    books[index].title[strcspn(books[index].title, "\n")] = 0;
    
    printf("Pengarang [%s]: ", books[index].author);
    fgets(books[index].author, MAX_AUTHOR, stdin);
    books[index].author[strcspn(books[index].author, "\n")] = 0;
    
    printf("Penerbit [%s]: ", books[index].publisher);
    fgets(books[index].publisher, MAX_PUBLISHER, stdin);
    books[index].publisher[strcspn(books[index].publisher, "\n")] = 0;
    
    printf("Tahun Terbit [%d]: ", books[index].year);
    scanf("%d", &books[index].year);
    
    printf("Harga [%.2f]: ", books[index].price);
    scanf("%f", &books[index].price);
    
    printf("Stok [%d]: ", books[index].stock);
    scanf("%d", &books[index].stock);
    
    printf("\nBuku berhasil diupdate!\n");
}

void deleteBook() {
    int id;
    printf("Masukkan ID buku yang akan dihapus: ");
    scanf("%d", &id);
    
    int index = findBookById(id);
    if(index == -1) {
        printf("Buku tidak ditemukan!\n");
        return;
    }
    
    books[index].isActive = 0;
    printf("\nBuku berhasil dihapus!\n");
}

void searchBook() {
    char keyword[MAX_TITLE];
    int found = 0;
    
    printf("Masukkan kata kunci pencarian: ");
    getchar();
    fgets(keyword, MAX_TITLE, stdin);
    keyword[strcspn(keyword, "\n")] = 0;
    
    printf("\n=== Hasil Pencarian ===\n");
    for(int i = 0; i < bookCount; i++) {
        if(books[i].isActive && (strstr(books[i].title, keyword) || 
           strstr(books[i].author, keyword) || 
           strstr(books[i].publisher, keyword))) {
            displayBook(books[i]);
            found = 1;
        }
    }
    
    if(!found) {
        printf("Tidak ada buku yang ditemukan!\n");
    }
}

void displayBook(struct Book book) {
    if(book.isActive) {
        printf("\nID: %d\n", book.id);
        printf("Judul: %s\n", book.title);
        printf("Pengarang: %s\n", book.author);
        printf("Penerbit: %s\n", book.publisher);
        printf("Tahun: %d\n", book.year);
        printf("Harga: Rp%.2f\n", book.price);
        printf("Stok: %d\n", book.stock);
        printf("------------------------\n");
    }
}

void displayAllBooks() {
    printf("\n=== Daftar Semua Buku ===\n");
    int found = 0;
    
    for(int i = 0; i < bookCount; i++) {
        if(books[i].isActive) {
            displayBook(books[i]);
            found = 1;
        }
    }
    
    if(!found) {
        printf("Tidak ada buku dalam database!\n");
    }
}

int findBookById(int id) {
    for(int i = 0; i < bookCount; i++) {
        if(books[i].id == id && books[i].isActive) {
            return i;
        }
    }
    return -1;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}