# Expense Tracker

A simple CLI expense tracker application to manage personal finances. The application allows users to add, delete, and view their expenses, along with a summary of expenses. 

---

## Description

Expense Tracker is a command-line application designed to help users efficiently track and manage their daily expenses. Users can view all expenses, add new ones, delete entries, and view monthly or total expense summaries. 

[Learn more](https://link.com)

---

## Features

- Add an expense with a description and amount.
- Update an existing expense.
- Delete an expense by ID.
- View all recorded expenses in a tabular format.
- Generate a total expense summary.
    - Filter expense summaries by a specific month.

### Additional Features

- Add categories for expenses and filter by category.
- Set a monthly budget with warnings for overspending.
- Export expense records to a CSV file for external use.

---

## How to Run

The Expense Tracker runs from the command line interface.

### Requirements

- A C++ compiler (e.g., `g++`).
- Standard C++ library support for `vector`, `fstream`, and `sstream`.
- Basic understanding of terminal commands.

### Instructions

1. Clone or download the repository.
2. Navigate to the project directory.
3. Compile the application using `g++`:
   ```bash
   g++ -o expense-tracker main.cpp
   ```
4. Run the compiled application:
   ```bash
   ./expense-tracker <command> [options]
   ```

---

## Usage

Below are some examples of commands and their outputs:

```bash
$ ./expense-tracker add --description "Lunch" --amount 20
# Expense added successfully (ID: 1)

$ ./expense-tracker add --description "Dinner" --amount 10
# Expense added successfully (ID: 2)

$ ./expense-tracker list
# ID  Date       Description  Amount
# 1   2024-08-06  Lunch        $20
# 2   2024-08-06  Dinner       $10

$ ./expense-tracker summary
# Total expenses: $30

$ ./expense-tracker delete --id 2
# Expense deleted successfully

$ ./expense-tracker summary
# Total expenses: $20

$ ./expense-tracker summary --month 8
# Total expenses for August: $20
```

This tool is ideal for practicing command-line interface development, filesystem interaction, and data management through a user-friendly CLI application.

