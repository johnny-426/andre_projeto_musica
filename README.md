# Music Library CRUD in C

A command-line music library manager developed as an academic project in C. The application implements basic CRUD operations and persists records in a text file.

## Features

- Register songs with a unique ID, title, artist, genre and duration
- List all stored songs
- Update an existing song by ID
- Delete a song by ID
- Persist data between executions using file handling
- Validate user input through a helper library used in class

## Concepts practiced

- C structs
- Functions and modularization
- File I/O (`FILE`, `fopen`, `fscanf`, `fprintf`)
- CRUD operations
- Input validation
- Conditional logic and loops
- Basic data persistence
- CMake project configuration

## Technologies

- C (C11)
- CMake
- Git / GitHub

## Project structure

```text
.
├── main.c          # Application logic and CRUD operations
├── pss.c           # Input helper library used in class
├── pss.h           # Header for the PSS input helper library
├── CMakeLists.txt  # CMake build configuration
└── README.md
```

The program creates `musica.txt` at runtime to store the music records. This file is intentionally ignored by Git because it contains local runtime data.

## How to run

### Using CMake

```bash
cmake -S . -B build
cmake --build build
```

Then run the generated executable from the build directory.

### Using GCC

```bash
gcc -std=c11 main.c pss.c -o music-library
./music-library
```

On Windows, run the generated `music-library.exe` executable.

## Data format

Each record is stored in `musica.txt` using the following format:

```text
id;title;artist;genre;duration
```

Example:

```text
1;So What;Miles Davis;Jazz;9.22
```

## Academic context and attribution

This project was created as part of my Information Systems coursework and the CRUD application logic in `main.c` was developed by me.

`pss.c` and `pss.h` are based on the **PSS Library for C**, provided for academic use by Prof. Saulo Santos. The original copyright and BSD 3-Clause license notice are preserved in `pss.c`.

## What I learned

This project helped me practice how to structure a small C application, validate input, work with records using `struct`, and implement persistent CRUD operations using text files. It also gave me practical experience separating application logic from reusable input-handling functions.

## Possible improvements

- Split CRUD operations into separate source/header modules
- Add search by artist, title or genre
- Add sorting and filtering
- Add automated tests
- Replace text-file persistence with a database in a future version

---

Developed by **João Paulo Ramalho Fernandes de Freitas** as an academic project.
