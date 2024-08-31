#ifndef BOOK_H
#define BOOK_H

typedef struct {
    char* title;
    int release_date;
    float price;
} book;

book* read_books(const char* filename, int* num_books);
void swap_book(book *b1, book *b2);
void bubble_sort_book(book *book_arr, int book_entries);
int book_search(book* book_arr, int book_entries, char* in_title);
int save_book(int book_entries, book* book_arr);
void free_books(book* books, int num_books);

#endif
