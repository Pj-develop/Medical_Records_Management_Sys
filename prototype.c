#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Medicine {
    int id;
    char name[100];
    char manufacturer[100];
    float price;
} Medicine;

int main() {
    FILE *fp;
    int i, n = 0, choice, med_id, found = 0;
    char search_name[100];
    Medicine m, med_list[100];

    // Read medicine records from file
    fp = fopen("medicine_records.txt", "r");
    if (fp) {
        while (fscanf(fp, "%d %s %s %f", &m.id, m.name, m.manufacturer, &m.price) != EOF) {
            med_list[n++] = m;
        }
        fclose(fp);
    }

    // Display menu and get user choice
    do {
        printf("\n--- Medicine Record Management System ---\n");
        printf("1. Display Medicine Details\n");
        printf("2. Add New Medicine\n");
        printf("3. Delete Medicine Details\n");
        printf("4. Search for a Medicine\n");
        printf("5. Update Medicine Details\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Display all medicine records
                printf("\n--- Available Medicine Records ---\n");
                for (i = 0; i < n; i++) {
                    printf("ID: %d\tName: %s\tManufacturer: %s\tPrice: %.2f\n", 
                            med_list[i].id, med_list[i].name, med_list[i].manufacturer, med_list[i].price);
                }
                break;

            case 2:
                // Add a new medicine record
                printf("\n--- Add New Medicine Record ---\n");
                printf("Enter the details of the new medicine:\n");
                printf("ID: ");
                scanf("%d", &m.id);
                printf("Name: ");
                scanf("%s", m.name);
                printf("Manufacturer: ");
                scanf("%s", m.manufacturer);
                printf("Price: ");
                scanf("%f", &m.price);

                med_list[n++] = m;

                // Save updated list to file
                fp = fopen("medicine_records.txt", "a");
                fprintf(fp, "%d %s %s %.2f\n", m.id, m.name, m.manufacturer, m.price);
                fclose(fp);

                printf("New record added successfully.\n");
                break;

            case 3:
                // Delete a medicine record
                printf("\n--- Delete a Medicine Record ---\n");
                printf("Enter the ID of the medicine to delete: ");
                scanf("%d", &med_id);

                for (i = 0; i < n; i++) {
                    if (med_list[i].id == med_id) {
                        found = 1;
                        printf("Are you sure you want to delete this record? (y/n)");
                        char confirm;
                        scanf(" %c", &confirm);

                        if (confirm == 'y') {
                            // Shift all records after the one to be deleted one index to the left
                            for (int j = i; j < n - 1; j++) {
                                med_list[j] = med_list[j + 1];
                            }
                            n--;

                            // Save updated list to file
                            fp = fopen("medicine_records.txt", "w");
                            for (int j = 0; j < n; j++) {
                                fprintf(fp, "%d %s %s %.2f\n", 
                                        med_list[j].id, med_list[j].name, med_list[j].manufacturer, med_list[j].price);
                            }
                            fclose(fp);

                            printf("Record deleted successfully.\n");
                        } else {
                            printf("Operation cancelled.\n");
                        }
                    }
                }

                if (!found) {
                    printf("Record not found.\n");
                }
                break;

            case 4:
                // Search for a medicine record
                printf("\n--- Search for a Medicine Record ---\n");
                printf("Enter the name of the medicine to search for: ");
                scanf("%s", search_name);

                found = 0;
                for (i = 0; i < n; i++) {
                    if (strcmp(med_list[i].name, search_name) == 0) {
                        found = 1;
                        printf("ID: %d\tName: %s\tManufacturer: %s\tPrice: %.2f\n", 
                                med_list[i].id, med_list[i].name, med_list[i].manufacturer, med_list[i].price);
                    }
                }

                if (!found) {
                    printf("No matching records found.\n");
                }
                break;

            case 5:
                // Update a medicine record
                printf("\n--- Update a Medicine Record ---\n");
                printf("Enter the ID of the medicine to update: ");
                scanf("%d", &med_id);

                found = 0;
                for (i = 0; i < n; i++) {
                    if (med_list[i].id == med_id) {
                        found = 1;
                        printf("Enter the new details of the medicine:\n");

                        printf("Name (%s): ", med_list[i].name);
                        scanf("%s", m.name);
                        if (strlen(m.name) > 0) {
                            strcpy(med_list[i].name, m.name);
                        }

                        printf("Manufacturer (%s): ", med_list[i].manufacturer);
                        scanf("%s", m.manufacturer);
                        if (strlen(m.manufacturer) > 0) {
                            strcpy(med_list[i].manufacturer, m.manufacturer);
                        }

                        printf("Price (%.2f): ", med_list[i].price);
                        scanf("%f", &m.price);
                        if (m.price > 0) {
                            med_list[i].price = m.price;
                        }

                        // Save updated list to file
                        fp = fopen("medicine_records.txt", "w");
                        for (int j = 0; j < n; j++) {
                            fprintf(fp, "%d %s %s %.2f\n", 
                                    med_list[j].id, med_list[j].name, med_list[j].manufacturer, med_list[j].price);
                        }
                        fclose(fp);

                        printf("Record updated successfully.\n");
                    }
                }

                if (!found) {
                    printf("Record not found.\n");
                }
                break;

            case 6:
                printf("\nExiting program...\n");
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 6.");

        }
    } while (choice != 6);

    return 0;
}
