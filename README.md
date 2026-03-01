# FeatherDB

FeatherDB is a lightweight database project written in C.
It provides a simple interactive shell with basic commands to insert and read rows from a file-backed table.

This is being created using the guide to build a simple database for educational purpose
"https://cstack.github.io/db_tutorial/"

## Features

- File-backed table storage
- Interactive REPL prompt
- `insert` and `select` statements
- `.exit` meta command

## Project Structure

- `src/` core database source code
- `test/` test files and sample DB data
- `deps/c_std/` dependency source library used by the build
- `mate.c` / `mate.exe` build entrypoint

## Build and Run

From the project root:

```powershell
.\mate.exe
```

The program starts an interactive prompt and expects a database filename argument in normal execution flow.

## Usage

Example session:

```text
insert 1 alice alice@example.com
insert 2 bob bob@example.com
select
.exit
```

Supported commands:

- `insert <id> <username> <email>`
- `select`
- `.exit`

## Introduction to B-Tree

FeatherDB currently stores rows in a simple table layout. A B-Tree is the next step to make storage and lookups scale better as data grows.

A B-Tree is a balanced tree structure optimized for disk pages:

- Each node stores multiple keys (not just one key like a binary tree)
- Internal nodes store keys and child pointers
- Leaf nodes store actual row locations (or rows)
- All leaves stay at the same depth, so operations remain predictable

Why B-Tree for FeatherDB:

- Faster point lookups than scanning all rows
- Better insertion behavior at larger row counts
- Natural fit for page-based storage already used in database engines
- Foundation for future indexing and ordered range scans

As implementation progresses, inserts and selects can move from full-table behavior to page navigation through internal and leaf nodes.

## Notes

- The shell validates negative IDs and oversized strings.
- Data persists in the database file you open.
