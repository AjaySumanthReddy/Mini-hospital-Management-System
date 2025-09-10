#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store patient info
struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    char phone[15];
};

// Function to add a new patient
void addPatient() {
    struct Patient p;
    FILE *fp = fopen("patients.txt", "a");

    if (fp == NULL) {
        printf("❌ Error opening file!\n");
        return;
    }

    printf("\n--- Add New Patient ---\n");
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    getchar();

    printf("Enter Name: ");
    fgets(p.name, 50, stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar();

    printf("Enter Disease: ");
    fgets(p.disease, 50, stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    printf("Enter Phone: ");
    fgets(p.phone, 15, stdin);
    p.phone[strcspn(p.phone, "\n")] = 0;

    fprintf(fp, "%d|%s|%d|%s|%s\n", p.id, p.name, p.age, p.disease, p.phone);
    fclose(fp);
    printf("✅ Patient record added successfully!\n");
}

// Function to view all patients
void viewPatients() {
    struct Patient p;
    FILE *fp = fopen("patients.txt", "r");

    if (fp == NULL) {
        printf("📭 No patient records found. Add one first!\n");
        return;
    }

    printf("\n--- All Patient Records ---\n");
    printf("%-5s %-20s %-5s %-20s %-15s\n", "ID", "Name", "Age", "Disease", "Phone");
    printf("--------------------------------------------------------------------\n");

    while (fscanf(fp, "%d|%49[^|]|%d|%49[^|]|%14[^\n]\n",
                  &p.id, p.name, &p.age, p.disease, p.phone) == 5) {
        printf("%-5d %-20s %-5d %-20s %-15s\n", p.id, p.name, p.age, p.disease, p.phone);
    }

    fclose(fp);
    printf("\n");
}

// Function to search patient by ID
void searchPatient() {
    int id, found = 0;
    struct Patient p;
    FILE *fp = fopen("patients.txt", "r");

    if (fp == NULL) {
        printf("📭 No records to search.\n");
        return;
    }

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d|%49[^|]|%d|%49[^|]|%14[^\n]\n",
                  &p.id, p.name, &p.age, p.disease, p.phone) == 5) {
        if (p.id == id) {
            printf("\n✅ Found Patient:\n");
            printf("ID: %d\nName: %s\nAge: %d\nDisease: %s\nPhone: %s\n",
                   p.id, p.name, p.age, p.disease, p.phone);
            found = 1;
            break;
        }
    }

    if (!found) printf("❌ Patient with ID %d not found.\n", id);
    fclose(fp);
}

// Function to delete a patient by ID
void deletePatient() {
    int id, found = 0;
    struct Patient p;
    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("❌ Error handling files!\n");
        return;
    }

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d|%49[^|]|%d|%49[^|]|%14[^\n]\n",
                  &p.id, p.name, &p.age, p.disease, p.phone) == 5) {
        if (p.id != id) {
            fprintf(temp, "%d|%s|%d|%s|%s\n", p.id, p.name, p.age, p.disease, p.phone);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found) printf("✅ Patient record deleted successfully.\n");
    else printf("❌ Patient with ID %d not found.\n", id);
}

// Main function
int main() {
    int choice;
    printf("🏥 Welcome to Mini Hospital Management System 🏥\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1. Add Patient\n2. View All Patients\n3. Search by ID\n4. Delete by ID\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: printf("👋 Goodbye!\n"); break;
            default: printf("⚠ Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
