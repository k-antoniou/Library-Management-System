#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "author.h"
#include "writes.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    int choice, book_entries = 0, author_entries = 0, writes_entries = 0;
    int i, in_id, book_pos, author_pos, writes_pos;

    // Initialize dynamic arrays to store books, authors, and writes
    book *book_arr = NULL;
    author *author_arr = NULL;
    writes *writes_arr = NULL;

    // Allocate memory for input strings
    char *book_txt = malloc(150 * sizeof(char));
    char *author_txt = malloc(150 * sizeof(char));
    char *writes_txt = malloc(150 * sizeof(char));
    char *in_surname = malloc(150 * sizeof(char));
    char *in_name = malloc(150 * sizeof(char));
    char *in_title = malloc(150 * sizeof(char));

    // Check memory allocation
    if (!book_txt || !author_txt || !writes_txt || !in_surname || !in_name || !in_title) {
        perror("Failed to allocate memory for input strings");
        return EXIT_FAILURE;
    }

    // Prompt user for file names
    printf("Enter book, author, and writes files: ");
    if (scanf("%s %s %s", book_txt, author_txt, writes_txt) != 3) {
        perror("Invalid input format");
        goto cleanup;
    }

    // Load data from files
    book_arr = read_books(book_txt, &book_entries);
    if (!book_arr) goto cleanup;

    author_arr = read_authors(author_txt, &author_entries);
    if (!author_arr) goto cleanup;

    writes_arr = read_writes(writes_txt, &writes_entries);
    if (!writes_arr) goto cleanup;

    // Main menu loop
    while (1) {
        choice = menu();
        switch (choice) {
            case 1: // Insert new writer record
                author_arr = realloc(author_arr, sizeof(author) * (author_entries + 1));
                if (!author_arr) {
                    perror("Failed to reallocate memory for authors");
                    goto cleanup;
                }
                printf("Enter writer surname, name, and number of books: ");
                if (scanf("%s %s %d", in_surname, in_name, &author_arr[author_entries].num_of_books) != 3) {
                    perror("Invalid input format");
                    goto cleanup;
                }
                author_arr[author_entries].writer_id = author_arr[author_entries-1].writer_id + 1; // Auto-increment ID
                author_arr[author_entries].surname = strdup(in_surname);
                author_arr[author_entries].name = strdup(in_name);
                if (!author_arr[author_entries].surname || !author_arr[author_entries].name) {
                    perror("Failed to allocate memory for new author");
                    goto cleanup;
                }
                author_entries++;
                bubble_sort_author(author_arr, author_entries);
				printf("Author added\n");
                break;

            case 2: // Insert new book record
                book_arr = realloc(book_arr, sizeof(book) * (book_entries + 1));
                if (!book_arr) {
                    perror("Failed to reallocate memory for books");
                    goto cleanup;
                }
                printf("Enter book title: ");
                scanf(" %[^\n]", in_title);
                printf("Enter release date, price, and author surname: ");
                if (scanf("%d %f %s", &book_arr[book_entries].release_date, &book_arr[book_entries].price, in_surname) != 3) {
                    perror("Invalid input format");
                    goto cleanup;
                }
                book_arr[book_entries].title = strdup(in_title);
                if (!book_arr[book_entries].title) {
                    perror("Failed to allocate memory for new book");
                    goto cleanup;
                }
                book_entries++;

                // Update writes
                writes_arr = realloc(writes_arr, sizeof(writes) * (writes_entries + 1));
                if (!writes_arr) {
                    perror("Failed to reallocate memory for writes");
                    goto cleanup;
                }
                writes_arr[writes_entries].title = strdup(book_arr[book_entries - 1].title);
                writes_arr[writes_entries].writer_id = 0;
                for (i = 0; i < author_entries; i++) {
                    if (strcmp(author_arr[i].surname, in_surname) == 0) {
                        author_arr[i].num_of_books++;
                        writes_arr[writes_entries].writer_id = author_arr[i].writer_id;
                    }
                }

                // Update author if surname not found
                if (writes_arr[writes_entries].writer_id == 0) {
                    author_arr = realloc(author_arr, sizeof(author) * (author_entries + 1));
                    if (!author_arr) {
                        perror("Failed to reallocate memory for authors");
                        goto cleanup;
                    }
                    printf("Enter writer name and number of books: ");
                    if (scanf("%s %d", in_name, &author_arr[author_entries].num_of_books) != 2) {
                        perror("Invalid input format");
                        goto cleanup;
                    }
                    author_arr[author_entries].writer_id = author_arr[author_entries-1].writer_id + 1;
                    author_arr[author_entries].surname = strdup(in_surname);
                    author_arr[author_entries].name = strdup(in_name);
                    writes_arr[writes_entries].writer_id = author_arr[author_entries].writer_id;
                    if (!author_arr[author_entries].surname || !author_arr[author_entries].name) {
                        perror("Failed to allocate memory for new author");
                        goto cleanup;
                    }
                    author_entries++;
                }

                writes_entries++;
                bubble_sort_author(author_arr, author_entries);
                bubble_sort_writes(writes_arr, writes_entries);
                bubble_sort_book(book_arr, book_entries);
				printf("Book added\n");
                break;

            case 3: // Search a writer record
                printf("Enter author surname to search: ");
                if (scanf("%s", in_surname) != 1) {
                    perror("Invalid input format");
                    goto cleanup;
                }
				writes_pos=-1; //works as a flag
                for (i = 0; i < author_entries; i++) {
                    if (strcmp(author_arr[i].surname, in_surname) == 0) {
                        printf("Author Information\nID: %d, Surname: %s, Name: %s, Number of Books: %d\n",
                               author_arr[i].writer_id, author_arr[i].surname, author_arr[i].name, author_arr[i].num_of_books);
                        if ((writes_pos = writes_search_id(writes_arr, writes_entries, author_arr[i].writer_id)) >= 0) {
                            while (writes_pos < writes_entries) {
                                if (writes_arr[writes_pos].writer_id == author_arr[i].writer_id) {
                                    if ((book_pos = book_search(book_arr, book_entries, writes_arr[writes_pos].title)) >= 0) {
                                        if (strcmp(writes_arr[writes_pos].title, book_arr[book_pos].title) == 0) {
                                            printf("Books written by %s %s\n", author_arr[i].name, author_arr[i].surname);
                                            printf("Title: %s, Release Date: %d, Price: %f\n", book_arr[book_pos].title, book_arr[book_pos].release_date, book_arr[book_pos].price);
                                        }
                                    }
                                }
                                writes_pos++;
                            }
                        }
                    }else{
						if(i==author_entries-1 && writes_pos==-1) {printf("Author not found!\n");}
					}
                }
                break;

            case 4: // Search a book record
                printf("Title: ");
                scanf(" %[^\n]", in_title);
                if ((book_pos = book_search(book_arr, book_entries, in_title)) >= 0) {
                    printf("Book Information\nTitle: %s, Release Date: %d, Price: %f\n",
                           book_arr[book_pos].title, book_arr[book_pos].release_date, book_arr[book_pos].price);
                    for (i = 0; i < writes_entries; i++) {
                        if (strcmp(writes_arr[i].title, book_arr[book_pos].title) == 0) {
                            if ((author_pos = author_search(author_arr, author_entries, writes_arr[i].writer_id)) >= 0) {
                                printf("Author Information\nID: %d, Surname: %s, Name: %s, Number of books: %d\n",
                                       author_arr[author_pos].writer_id, author_arr[author_pos].surname, author_arr[author_pos].name, author_arr[author_pos].num_of_books);
                            }
                        }
                    }
                } 
                
                break;

            case 5: // Delete a writer record
                printf("ID: ");
                scanf("%d", &in_id);
                if ((author_pos = author_search(author_arr, author_entries, in_id)) >= 0) {
                    if ((writes_pos = writes_search_id(writes_arr, writes_entries, author_arr[author_pos].writer_id)) >= 0) {
                        while (writes_pos < writes_entries) {
                            if (writes_arr[writes_pos].writer_id == author_arr[author_pos].writer_id) {
                                if ((book_pos = book_search(book_arr, book_entries, writes_arr[writes_pos].title)) >= 0) {
                                    if (strcmp(writes_arr[writes_pos].title, book_arr[book_pos].title) == 0) {
                                        swap_book(&book_arr[book_pos], &book_arr[book_entries - 1]);
                                        book_entries--;
                                    }
                                }
                                swap_writes(&writes_arr[writes_pos], &writes_arr[writes_entries - 1]);
                                writes_entries--;
                            }
                            writes_pos++;
                        }
                    }
                    swap_author(&author_arr[author_pos], &author_arr[author_entries - 1]);
                    author_entries--;
                }
                bubble_sort_writes(writes_arr, writes_entries);
                bubble_sort_author(author_arr, author_entries);
                bubble_sort_book(book_arr, book_entries);
				printf("Author deleted\n");
                break;

            case 6: // Delete a book record
                printf("Title: ");
                scanf(" %[^\n]", in_title);
                if ((book_pos = book_search(book_arr, book_entries, in_title)) >= 0) {
                    for (i = 0; i < writes_entries; i++) {
                        if (strcmp(writes_arr[i].title, book_arr[book_pos].title) == 0) {
                            if ((author_pos = author_search(author_arr, author_entries, writes_arr[i].writer_id)) >= 0) {
                                author_arr[author_pos].num_of_books--;
                            }
                            swap_writes(&writes_arr[i], &writes_arr[writes_entries - 1]);
                            writes_entries--;
                        }
                    }
                    swap_book(&book_arr[book_pos], &book_arr[book_entries - 1]);
                    book_entries--;
                }
                bubble_sort_writes(writes_arr, writes_entries);
                bubble_sort_author(author_arr, author_entries);
                bubble_sort_book(book_arr, book_entries);
				printf("Book deleted\n");
                break;

            case 7: // Save records to files and exit
                save_author(author_entries, author_arr);
                save_book(book_entries, book_arr);
                save_writes(writes_entries, writes_arr);
                printf("Updated files.\n");
                goto cleanup;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

cleanup:
    free(in_surname);
    free(in_name);
    free(in_title);
    free(book_txt);
    free(author_txt);
    free(writes_txt);
    free_books(book_arr, book_entries);
    free_authors(author_arr, author_entries);
    free_writes(writes_arr, writes_entries);
    printf("Program exited.\n");

    return EXIT_SUCCESS;
}
