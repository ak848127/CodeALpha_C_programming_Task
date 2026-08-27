#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "accounts.dat"

struct Account {
    int accountNo;
    char name[50];
    float balance;
};

void createAccount() {
    struct Account acc;
    FILE *fp;

    fp = fopen(FILE_NAME, "ab");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accountNo);

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    if (acc.balance < 0) {
        printf("Invalid balance!\n");
        fclose(fp);
        return;
    }

    fwrite(&acc, sizeof(struct Account), 1, fp);

    fclose(fp);

    printf("\nAccount created successfully!\n");
}

void deposit() {
    struct Account acc;
    FILE *fp;
    int accountNo;
    float amount;
    int found = 0;

    fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        printf("\nNo accounts found.\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accountNo);

    printf("Enter Deposit Amount: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
        fclose(fp);
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp)) {

        if (acc.accountNo == accountNo) {

            acc.balance += amount;

            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);

            printf("\nAmount deposited successfully!\n");
            printf("New Balance: %.2f\n", acc.balance);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nAccount not found.\n");
    }

    fclose(fp);
}

void withdraw() {
    struct Account acc;
    FILE *fp;
    int accountNo;
    float amount;
    int found = 0;

    fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        printf("\nNo accounts found.\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accountNo);

    printf("Enter Withdrawal Amount: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
        fclose(fp);
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp)) {

        if (acc.accountNo == accountNo) {

            found = 1;

            if (amount > acc.balance) {
                printf("\nInsufficient balance!\n");
            } else {

                acc.balance -= amount;

                fseek(fp, -sizeof(struct Account), SEEK_CUR);
                fwrite(&acc, sizeof(struct Account), 1, fp);

                printf("\nWithdrawal successful!\n");
                printf("Remaining Balance: %.2f\n", acc.balance);
            }

            break;
        }
    }

    if (!found) {
        printf("\nAccount not found.\n");
    }

    fclose(fp);
}

void balanceEnquiry() {
    struct Account acc;
    FILE *fp;
    int accountNo;
    int found = 0;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo accounts found.\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accountNo);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {

        if (acc.accountNo == accountNo) {

            printf("\n===== ACCOUNT DETAILS =====\n");
            printf("Account Number : %d\n", acc.accountNo);
            printf("Account Holder : %s\n", acc.name);
            printf("Balance        : %.2f\n", acc.balance);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nAccount not found.\n");
    }

    fclose(fp);
}

void editAccount() {
    struct Account acc;
    FILE *fp;
    int accountNo;
    int found = 0;

    fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        printf("\nNo accounts found.\n");
        return;
    }

    printf("\nEnter Account Number to edit: ");
    scanf("%d", &accountNo);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {

        if (acc.accountNo == accountNo) {

            printf("Enter New Account Holder Name: ");
            scanf(" %[^\n]", acc.name);

            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);

            printf("\nAccount updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nAccount not found.\n");
    }

    fclose(fp);
}

void displayAccounts() {
    struct Account acc;
    FILE *fp;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo accounts found.\n");
        return;
    }

    printf("\n===== ALL BANK ACCOUNTS =====\n");

    while (fread(&acc, sizeof(struct Account), 1, fp)) {

        printf("\nAccount Number : %d", acc.accountNo);
        printf("\nAccount Holder : %s", acc.name);
        printf("\nBalance        : %.2f\n", acc.balance);
    }

    fclose(fp);
}

int main() {

    int choice;

    while (1) {

        printf("\n\n================================\n");
        printf("       BANKING SYSTEM\n");
        printf("================================\n");

        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Edit Account\n");
        printf("6. Display All Accounts\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                createAccount();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdraw();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                editAccount();
                break;

            case 6:
                displayAccounts();
                break;

            case 7:
                printf("\nThank you for using Banking System!\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}