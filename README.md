# 📚 Library Management System

The Library Management System is a simple C-based command-line application designed to manage books, authors, and their relationships. The system allows users to perform operations such as adding, searching, and deleting books and authors, as well as managing the relationships between them.

## 🌟 Features

- **Add Author**: Add new authors to the system.
- **Add Book**: Add new books to the system.
- **Search Author**: Search for authors based on their surnames and view their details.
- **Search Book**: Search for books based on their title and view their details.
- **Delete Author**: Remove authors from the system.
- **Delete Book**: Remove books from the system.
- **Sorting**: Books and authors are sorted by title and ID respectively.

## 📁 Files and Structure

- `main.c`: Contains the main function and user interface logic.
- `book.c` / `book.h`: Functions for managing book records, including searching, sorting and saving books.
- `author.c` / `author.h`: Functions for managing author records, including searching, sorting, and saving authors.
- `writes.c` / `writes.h`: Functions for handling the relationships between authors and their books, such as reading, searching, and saving these relationships.
- `utils.c` / `utils.h`: Utility functions.

## 🚀 Getting Started

### Compilation

To compile the project, you must have a C compiler (e.g., GCC). 

You can build the project by navigating to the directory containing the source files and running the following command:

```
gcc -o library_management main.c book.c author.c writes.c utils.c
```
This command compiles all the source files and links them into an executable named `library_management`.

### Usage

The application is run from the command line with the command:

```
./library_management
```
Follow the on-screen prompts to add, search, delete, or update book and author records.

### Notes

- The application requires three files as input. These files should contain existing records of books, authors, and their relationships, respectively.
    - books.txt
      ```
      <total_number_of_books>
      <book_title>
      <release_date>
      <price>
      ...
      ```
    - authors.txt
      ```
      <total_number_of_authors>
      <writer_id>
      <surname>
      <name>
      <num_of_books>
      ...
      ```
    - writes.txt
      ```
      <total_number_of_writes>
      <book_title>
      <writer_id>
      ...
      ```
  
- The file paths will be prompted when the program starts. Ensure these files are available in the same directory or provide absolute paths.
- Examples of input files (books.txt, authors.txt, writes.txt) are provided in the **example files** directory of the repository.

## 👥 Authors

- [![Katerina Antoniou](https://img.shields.io/badge/GitHub-Katerina_Antoniou-purple?style=flat&logo=github)](https://github.com/k-antoniou)


## 🤝 Contributing

Contributions are welcome! Feel free to submit pull requests or open issues if you encounter any problems.

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
