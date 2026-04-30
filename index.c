#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    int roll;
    char name[50];
    int attended;
};

struct Student s[MAX];
int n = 0;
int total_classes = 0;

// MODULE 1: Add Student
void addStudent() {
    if(n >= MAX) {
        printf("Student limit reached!\n");
        return;
    }

    printf("\nEnter Roll No: ");
    scanf("%d", &s[n].roll);

    printf("Enter Name: ");
    scanf("%s", s[n].name);

    s[n].attended = 0;
    n++;

    printf("Student Added Successfully!\n");
}

// MODULE 2: Mark Attendance
void markAttendance() {
    int i, mark;

    if(n == 0) {
        printf("No students available!\n");
        return;
    }

    total_classes++;

    for(i = 0; i < n; i++) {
        printf("Is %s present? (1=Yes 0=No): ", s[i].name);
        scanf("%d", &mark);

        if(mark == 1) {
            s[i].attended++;
        }
    }
}

// MODULE 3: View Attendance
void viewAttendance() {
    int i;

    if(n == 0) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Attendance Record ---\n");

    for(i = 0; i < n; i++) {
        printf("Roll: %d | Name: %s | Attended: %d\n",
               s[i].roll, s[i].name, s[i].attended);
    }
}

// MODULE 4: Calculate Percentage
void calculatePercentage() {
    int i;

    if(n == 0) {
        printf("No students available!\n");
        return;
    }

    printf("\n--- Attendance Percentage ---\n");

    for(i = 0; i < n; i++) {
        float percent = 0;

        if(total_classes > 0) {
            percent = (s[i].attended * 100.0) / total_classes;
        }

        printf("Roll: %d | Name: %s | Percentage: %.2f%%\n",
               s[i].roll, s[i].name, percent);
    }
}

// BONUS MODULE: Save to File
void saveToFile() {
    FILE *fp = fopen("attendance.txt", "w");

    if(fp == NULL) {
        printf("Error saving file!\n");
        return;
    }

    fprintf(fp, "%d %d\n", n, total_classes);

    for(int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %d\n",
                s[i].roll, s[i].name, s[i].attended);
    }

    fclose(fp);
    printf("Data saved successfully!\n");
}

// BONUS MODULE: Load from File
void loadFromFile() {
    FILE *fp = fopen("attendance.txt", "r");

    if(fp == NULL) {
        printf("No previous data found!\n");
        return;
    }

    fscanf(fp, "%d %d", &n, &total_classes);

    for(int i = 0; i < n; i++) {
        fscanf(fp, "%d %s %d",
               &s[i].roll, s[i].name, &s[i].attended);
    }

    fclose(fp);
    printf("Data loaded successfully!\n");
}

// MAIN FUNCTION
int main() {
    int choice;

    loadFromFile(); // load existing data

    do {
        printf("\n===== Student Attendance System =====\n");
        printf("1. Add Student\n");
        printf("2. Mark Attendance\n");
        printf("3. View Attendance\n");
        printf("4. Calculate Percentage\n");
        printf("5. Save Data\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: markAttendance(); break;
            case 3: viewAttendance(); break;
            case 4: calculatePercentage(); break;
            case 5: saveToFile(); break;
            case 6: 
                saveToFile();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 6);

    return 0;
}