#ifndef AUTHOR_H
#define AUTHOR_H

typedef struct {
    int writer_id;
    char* surname;
    char* name;
    int num_of_books;
} author;

author* read_authors(const char* filename, int* num_authors);
void swap_author(author *author1, author *author2);
void bubble_sort_author(author *author_arr, int author_entries);
int author_search(author* author_arr, int author_entries, int in_id);
int save_author(int author_entries, author* author_arr);
void free_authors(author* authors, int num_authors);

#endif
