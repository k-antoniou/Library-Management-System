# 📚 Library Management System

The Library Management System is a simple C-based command-line application designed to manage books, authors, and their relationships. The system allows users to perform operations such as adding, searching, and deleting books and authors, as well as managing the relationships between them.

## 🌟 Features

- **Add Author**: Add new authors to the system.
- **Add Book**: Add new books to the system.
- **Search Author**: Search for authors based on their ID and view their details.
- **Search Book**: Search for books based on their title and view their details.
- **Delete Author**: Remove authors from the system.
- **Delete Book**: Remove books from the system.
- **Sorting**: Books and authors are sorted by title and ID respectively.

## 📁 Files and Structure

- `main.c`: Contains the main function and user interface logic.
- `data_structures.h`: Defines the data structures used in the project.
- `file_handling.c` / `file_handling.h`: Functions for reading from and writing to files.
- `sorting.c` / `sorting.h`: Functions for sorting books and authors.
- `searching.c` / `searching.h`: Functions for searching books and authors.
- `utils.c` / `utils.h`: Utility functions including menu display and memory management.

## 🚀 Getting Started

### Compilation

To compile the project, you need to have a C compiler (e.g., gcc). You can use the following command to build the application:
```
gcc -o library_management main.c file_handling.c sorting.c searching.c utils.c
```
This command compiles all the source files and links them into an executable named `library_management`.

### Usage

The application is run from the command line and requires three arguments: the filenames for books, authors, and writes.

```
./library_management <book_file> <author_file> <writes_file>
```
For example
```
./library_management books.txt authors.txt writes.txt
```

## 👥 Authors

- [![Katerina Antoniou](https://img.shields.io/badge/GitHub-Katerina_Antoniou-purple?style=flat&logo=github)](https://github.com/k-antoniou)


## 🤝 Contributing

Contributions are welcome! Feel free to submit pull requests or open issues if you encounter any problems.

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
