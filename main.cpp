#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

struct Expense {
    int id;
    std::string date;
    std::string description;
    float amount;
};

class ExpenseTracker {
private:
    std::vector<Expense> expenses;
    int nextId = 1;
    const std::string fileName = "expenses.txt";

    std::string getCurrentDate() const {
        time_t now = time(0);
        tm* localTime = localtime(&now);

        std::ostringstream oss;
        oss << (1900 + localTime->tm_year) << "-"
            << std::setw(2) << std::setfill('0') << (1 + localTime->tm_mon) << "-"
            << std::setw(2) << std::setfill('0') << localTime->tm_mday;

        return oss.str();
    }

    void loadExpenses() {
        std::ifstream file(fileName);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Expense expense;
            if (!(iss >> expense.id >> expense.date >> std::ws 
                  && std::getline(iss, expense.description, '|') 
                  && iss >> expense.amount)) {
                continue;
            }
            expenses.push_back(expense);
            if (expense.id >= nextId) {
                nextId = expense.id + 1;
            }
        }

        file.close();
    }

    void saveExpenses() const {
        std::ofstream file(fileName);
        if (!file.is_open()) return;

        for (const auto& expense : expenses) {
            file << expense.id << " " 
                 << expense.date << " " 
                 << expense.description << "|" 
                 << expense.amount << "\n";
        }

        file.close();
    }

public:
    ExpenseTracker() {
        loadExpenses();
    }

    ~ExpenseTracker() {
        saveExpenses();
    }

    void addExpense(const std::string& description, float amount) {
        Expense expense = {nextId++, getCurrentDate(), description, amount};
        expenses.push_back(expense);
        std::cout << "# Expense added successfully (ID: " << expense.id << ")" << std::endl;
    }

    void listExpenses() const {
        if (expenses.empty()) {
            std::cout << "# No expenses to display." << std::endl;
            return;
        }

        std::cout << "# " << std::setw(6) << "ID"
                  << std::setw(12) << "Date"
                  << std::setw(18) << "Description"
                  << std::setw(14) << "Amount" << std::endl;
        for (const auto& e : expenses) {
            std::cout << "# " << std::setw(6) << e.id
                      << std::setw(12) << e.date
                      << std::setw(18) << e.description
                      << std::setw(13) << "$" << std::fixed
                      << std::setprecision(2) << e.amount << std::endl;
        }
    }

    float sumExpenses(int month = 0) const {
        float total = 0;

        for (const auto& e : expenses) {
            if (month == 0 || std::stoi(e.date.substr(5, 2)) == month) {
                total += e.amount;
            }
        }

        if (month == 0) {
            std::cout << "# Total expenses: $" << std::fixed << std::setprecision(2) << total << "\n";
        } else {
            std::cout << "# Total expenses for month " << month << ": $" << std::fixed << std::setprecision(2) << total << "\n";
        }
        return total;
    }

    void deleteExpense(int id) {
        for (auto it = expenses.begin(); it != expenses.end(); ++it) {
            if (it->id == id) {
                expenses.erase(it);
                std::cout << "# Expense deleted successfully\n";
                return;
            }
        }
        std::cout << "# ERROR: Expense with ID " << id << " not found.\n";
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR 0x00: Insufficient Arguments." << std::endl;
        return 1;
    }

    ExpenseTracker tracker;

    std::string command = argv[1];

    if (command == "add") {
        std::string description;
        float amount = 0;

        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "--description" && (i + 1) < argc) {
                description = argv[++i];
            } else if (arg == "--amount" && (i + 1) < argc) {
                amount = std::stof(argv[++i]);
            }
        }

        if (description.empty() || amount <= 0) {
            std::cerr << "ERROR 0x01: Invalid arguments for adding an expense." << std::endl;
            return 1;
        }

        tracker.addExpense(description, amount);

    } else if (command == "list") {
        tracker.listExpenses();
    } else if (command == "summary") {
        int month = 0;

        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "--month" && (i + 1) < argc) {
                month = std::stoi(argv[++i]);
            }
        }

        tracker.sumExpenses(month);

    } else if (command == "delete") {
        int id = 0;
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "--id" && i + 1 < argc) {
                id = std::stoi(argv[++i]);
            }
        }

        if (id <= 0) {
            std::cerr << "ERROR 0x02: Invalid ID for deletion." << std::endl;
            return 1;
        }

        tracker.deleteExpense(id);

    } else {
        std::cerr << "ERROR 0x03: Unknown command." << std::endl;
        return 1;
    }

    return 0;
}

