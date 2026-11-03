#include <stdio.h>
#include <string.h>

int main() {
    int pin = 1234, enteredPin, choice, attempts = 3;
    float savingsBalance = 5000.0, currentBalance = 10000.0;
    float amount;
    int accType; // 1 for Savings, 2 for Current

    // Transaction history array to store up to the last 5 transactions
    char history[5][100];
    int historyCount = 0;

    // 1. PIN Verification with 3 attempts limit
    while (attempts > 0) {
        printf("Enter 4-digit PIN (%d attempts remaining): ", attempts);
        scanf("%d", &enteredPin);

        if (enteredPin == pin) {
            printf("Access Granted!\n\n");
            break;
        } else {
            attempts--;
            if (attempts > 0) {
                printf("Incorrect PIN! Please try again.\n");
            }
        }
    }

    if (attempts == 0) {
        printf("Card Blocked! Too many incorrect PIN attempts.\n");
        return 0;
    }

    // Main ATM Menu Loop
    while (1) {
        printf("\n--- ADVANCED ATM MENU ---\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Fund Transfer (Savings <-> Current)\n");
        printf("5. Change PIN\n");
        printf("6. Mini Statement\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Check Balance
                printf("Select Account Type:\n1. Savings Account\n2. Current Account\nChoice: ");
                scanf("%d", &accType);
                if (accType == 1)
                    printf("Savings Account Balance: ₹%.2f\n", savingsBalance);
                else if (accType == 2)
                    printf("Current Account Balance: ₹%.2f\n", currentBalance);
                else
                    printf("Invalid Account Type!\n");
                break;

            case 2: // Deposit Money
                printf("Select Account Type:\n1. Savings Account\n2. Current Account\nChoice: ");
                scanf("%d", &accType);
                printf("Enter deposit amount: ₹");
                scanf("%f", &amount);

                if (amount <= 0) {
                    printf("Error: Deposit amount must be greater than zero!\n");
                } else {
                    if (accType == 1) {
                        savingsBalance += amount;
                        printf("Successfully deposited ₹%.2f to Savings Account.\n", amount);
                    } else if (accType == 2) {
                        currentBalance += amount;
                        printf("Successfully deposited ₹%.2f to Current Account.\n", amount);
                    } else {
                        printf("Invalid Account Type!\n");
                        break;
                    }

                    // Record transaction in history
                    char transactionStr[100];
                    snprintf(transactionStr, sizeof(transactionStr), "Deposited: ₹%.2f", amount);
                    
                    if (historyCount < 5) {
                        strcpy(history[historyCount], transactionStr);
                        historyCount++;
                    } else {
                        for (int i = 0; i < 4; i++) {
                            strcpy(history[i], history[i + 1]);
                        }
                        strcpy(history[4], transactionStr);
                    }
                }
                break;

            case 3: // Withdraw Money
                printf("Select Account Type:\n1. Savings Account\n2. Current Account\nChoice: ");
                scanf("%d", &accType);
                printf("Enter withdrawal amount (multiples of ₹100): ₹");
                scanf("%f", &amount);

                if (amount <= 0) {
                    printf("Error: Withdrawal amount must be greater than zero!\n");
                } else if ((int)amount % 100 != 0) {
                    printf("Error: Amount must be in multiples of ₹100!\n");
                } else {
                    float *targetBalance = (accType == 1) ? &savingsBalance : (accType == 2) ? &currentBalance : NULL;

                    if (targetBalance == NULL) {
                        printf("Invalid Account Type!\n");
                        break;
                    }

                    if (amount > *targetBalance) {
                        printf("Insufficient balance!\n");
                    } else {
                        *targetBalance -= amount;
                        printf("Please collect cash: ₹%.2f\n", amount);

                        // Cash Denomination Breakdown calculation
                        int amtInt = (int)amount;
                        int n500 = amtInt / 500;
                        amtInt %= 500;
                        int n200 = amtInt / 200;
                        amtInt %= 200;
                        int n100 = amtInt / 100;

                        printf("Denomination Breakdown:\n");
                        if (n500 > 0) printf("  - ₹500 x %d\n", n500);
                        if (n200 > 0) printf("  - ₹200 x %d\n", n200);
                        if (n100 > 0) printf("  - ₹100 x %d\n", n100);

                        // Record transaction in history
                        char transactionStr[100];
                        snprintf(transactionStr, sizeof(transactionStr), "Withdrew: ₹%.2f", amount);
                        
                        if (historyCount < 5) {
                            strcpy(history[historyCount], transactionStr);
                            historyCount++;
                        } else {
                            for (int i = 0; i < 4; i++) {
                                strcpy(history[i], history[i + 1]);
                            }
                            strcpy(history[4], transactionStr);
                        }
                    }
                }
                break;

            case 4: { // Fund Transfer Between Accounts
                int transferType;
                printf("Fund Transfer Direction:\n");
                printf("1. Savings Account -> Current Account\n");
                printf("2. Current Account -> Savings Account\n");
                printf("Choice: ");
                scanf("%d", &transferType);

                printf("Enter transfer amount: ₹");
                scanf("%f", &amount);

                if (amount <= 0) {
                    printf("Error: Transfer amount must be greater than zero!\n");
                } else if (transferType == 1) {
                    if (amount > savingsBalance) {
                        printf("Insufficient balance in Savings Account!\n");
                    } else {
                        savingsBalance -= amount;
                        currentBalance += amount;
                        printf("Successfully transferred ₹%.2f from Savings to Current Account.\n", amount);

                        char transactionStr[100];
                        snprintf(transactionStr, sizeof(transactionStr), "Transfer: ₹%.2f (Sav->Cur)", amount);
                        if (historyCount < 5) {
                            strcpy(history[historyCount], transactionStr);
                            historyCount++;
                        } else {
                            for (int i = 0; i < 4; i++) strcpy(history[i], history[i + 1]);
                            strcpy(history[4], transactionStr);
                        }
                    }
                } else if (transferType == 2) {
                    if (amount > currentBalance) {
                        printf("Insufficient balance in Current Account!\n");
                    } else {
                        currentBalance -= amount;
                        savingsBalance += amount;
                        printf("Successfully transferred ₹%.2f from Current to Savings Account.\n", amount);

                        char transactionStr[100];
                        snprintf(transactionStr, sizeof(transactionStr), "Transfer: ₹%.2f (Cur->Sav)", amount);
                        if (historyCount < 5) {
                            strcpy(history[historyCount], transactionStr);
                            historyCount++;
                        } else {
                            for (int i = 0; i < 4; i++) strcpy(history[i], history[i + 1]);
                            strcpy(history[4], transactionStr);
                        }
                    }
                } else {
                    printf("Invalid transfer option selected!\n");
                }
                break;
            }

            case 5: { // PIN Change
                int oldPin, newPin;
                printf("Enter current 4-digit PIN: ");
                scanf("%d", &oldPin);
                if (oldPin == pin) {
                    printf("Enter new 4-digit PIN: ");
                    scanf("%d", &newPin);
                    pin = newPin;
                    printf("PIN changed successfully!\n");
                } else {
                    printf("Incorrect current PIN! Action aborted.\n");
                }
                break;
            }

            case 6: // Mini Statement
                printf("\n--- MINI STATEMENT (Last %d Transactions) ---\n", historyCount);
                if (historyCount == 0) {
                    printf("No recent transactions found.\n");
                } else {
                    for (int i = 0; i < historyCount; i++) {
                        printf("%d. %s\n", i + 1, history[i]);
                    }
                }
                break;

            case 7: // Exit
                printf("Thank you for using our ATM! Have a wonderful day.\n");
                return 0;

            default:
                printf("Invalid choice! Please select an option between 1 and 7.\n");
        }
    }
}