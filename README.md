# ATM-Machine-Simulator
# 🏧 Advanced ATM Machine Simulator in C

A feature-rich, terminal-based ATM Machine Simulator written in C. This project simulates core banking operations including secure PIN authentication, multi-account management, cash withdrawals with denomination breakdowns, fund transfers, and transaction history tracking.

---

## 🚀 Features

* **🔒 Secure PIN Verification:** Limits users to 3 attempts before locking/blocking the card for security.
* **💳 Multi-Account Management:** Supports both **Savings** and **Current** accounts with independent balances.
* **💵 Smart Cash Withdrawals:** 
  * Validates against insufficient funds and non-zero/negative inputs.
  * Restricts withdrawals to multiples of ₹100.
  * **Denomination Breakdown:** Automatically calculates and displays the exact count of ₹500, ₹200, and ₹100 notes dispensed.
* **💸 Fund Transfers:** Seamlessly transfer money between Savings and Current accounts.
* **🔑 PIN Modification:** Allows users to update their 4-digit PIN securely by verifying their current PIN.
* **📜 Mini Statement:** Keeps track of and displays the last 5 transactions performed during the session.

---

## 🛠️ Syllabus Focus & Concepts Covered

This project is designed to reinforce fundamental C programming concepts:
* `switch-case` statements for menu navigation
* `while` loops for continuous execution and attempt limits
* Logical operators (`&&`) for authentication checks
* Variable scope and memory handling
* Arrays and strings for transaction logging

---

## 📋 Getting Started

### Prerequisites
You need a C compiler installed on your system (such as **GCC**, **Clang**, or **MinGW**).

### Compilation & Execution
1. Clone or download the repository/source file.
2. Open your terminal or command prompt in the project directory.
3. Compile the code using GCC:
   ```bash
   gcc atm_simulator.c -o atm_simulator
