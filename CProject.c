#include <stdio.h>
#include <string.h>

typedef struct {
    int rollno;
    char name[30];
    int age;
    char gender[10];
    char department[20];
    int semester;
    int marks[5];
    float attendance;
} student;

int rollnoExists(int rollno) {
    FILE *fp = fopen("students.dat", "rb");
    student stu;
    if (fp == NULL) {
        return 0;
    }
        while (fread(&stu, sizeof(student), 1, fp) == 1) {
            if (stu.rollno == rollno){
                fclose(fp);
                return 1;
            }
        }
        fclose(fp);
        return 0;
    }
void addStudent() {
        student stu;
        FILE *fp;
        do {
            printf("Enter Roll no: ");
            scanf("%d", &stu.rollno);
            if (stu.rollno <= 0) {
                printf("Roll number must be positive. Enter again.\n");
            }
            else if (rollnoExists(stu.rollno)) {
                printf("Roll no. already exists. Enter a unique roll no.\n");
            }
        }
        while (stu.rollno <= 0 || rollnoExists(stu.rollno));
        printf("Enter name: ");
        scanf("%s", stu.name);
        do {
            printf("Enter age: ");
            scanf("%d", &stu.age);
            if (stu.age < 1 || stu.age > 100) {
                printf("Age must be between 1 and 100. Enter again.\n");
            }
        }
        while (stu.age < 1 || stu.age > 100);
        do {
            printf("Enter gender (M/F): ");
            scanf("%s", stu.gender);
            if (strcmp(stu.gender, "M") != 0 && strcmp(stu.gender, "F") != 0) {
                printf("Invalid gender. Enter M or F.\n");
            }
        }
        while (strcmp(stu.gender, "M") != 0 && strcmp(stu.gender, "F") != 0);
        printf("Enter department: ");
        scanf("%s", stu.department);
        do {
            printf("Enter semester: ");
            scanf("%d", &stu.semester);
            if (stu.semester <= 0 || stu.semester > 8) {
                printf("Semester must be between 1 and 8. Enter again.\n");
            }
        }
        while (stu.semester <= 0 || stu.semester > 8);
        for (int i = 0; i < 5; i++) {
            do {
                printf("Enter marks for sub %d: ", i + 1);
                scanf("%d", &stu.marks[i]);
                if (stu.marks[i] < 0 || stu.marks[i] > 100) {
                    printf("Invalid marks entered. Range must be between 0 and 100. Enter again.\n");
                }
            }
            while (stu.marks[i] < 0 || stu.marks[i] > 100);
        }
        do {
            printf("Enter addendance percentage: ");
            scanf("%f", &stu.attendance);
            if (stu.attendance < 0 || stu.attendance > 100) {
                printf("Invalid attendance percentage entered. Enter again.\n");
            }
        }
        while (stu.attendance < 0 || stu.attendance > 100);
        fp = fopen("students.dat", "ab");
        if (fp == NULL) {
            printf("Unable to open students data file.\n");
            return;
        }
        fwrite(&stu, sizeof(student), 1, fp);
        fclose(fp);
        printf("Successfully added student record.\n");
    }
    void viewStudents() {
        FILE *fp = fopen("students.dat", "rb");
        student stu;
        int found = 0;
        if (fp == NULL) {
            printf("Unable to open students data file.\n");
            return;
        }
        printf(" ================ STUDENT RECORDS ================\n");
        while (fread(&stu, sizeof(student), 1, fp) == 1) {
            found = 1;
            printf("\n Roll No.            : %d", stu.rollno);
            printf("\n Name                : %s", stu.name);
            printf("\n Age                 : %d", stu.age);
            printf("\n Gender              : %s", stu.gender);
            printf("\n Department          : %s", stu.department);
            printf("\n Semester            : %d", stu.semester);
            for (int i = 0; i < 5; i++) {
                printf("\n Marks in subject %d  : %d", i + 1, stu.marks[i]);
            }
            printf("\n Attendance          : %.2f", stu.attendance);
            printf("\n ================================================\n");
        }
        fclose(fp);
        if (found == 0) {
            printf("No Students Found...\n");
        }
    }
    void searchStudent() {
        FILE *fp;
        student stu;
        int rollno;
        char name[30];
        int found;  
        while (1) {
            printf("Enter roll no. to search: ");
            scanf("%d", &rollno);
            printf("Enter name to search: ");
            scanf("%s", name);
            fp = fopen("students.dat", "rb");
            if (fp == NULL) {
                printf("Unable to open students data file.\n");
                return;
            }
            found = 0;
            while (fread(&stu, sizeof(student), 1, fp) == 1) {
                if (stu.rollno == rollno && strcmp(stu.name, name) == 0) {
                    printf(" ================ STUDENT RECORD FOUND ================\n");
                    printf("\n Roll No.            : %d", stu.rollno);
                    printf("\n Name                : %s", stu.name);
                    printf("\n Age                 : %d", stu.age);
                    printf("\n Gender              : %s", stu.gender);
                    printf("\n Department          : %s", stu.department);
                    printf("\n Semester            : %d", stu.semester);
                    for (int i = 0; i < 5; i++) {
                        printf("\n Marks in subject %d : %d", i + 1, stu.marks[i]);
                    }
                    printf("\n Attendance          : %.2f", stu.attendance);
                    printf("\n ======================================================\n");
                    found = 1;
                    break;
                }
            }
            fclose(fp);
            if (found == 0) {
                printf("Student record not found. Please enter correct details.\n");
            }
            else {
                break;
            }
        }
    }
    void updateStudent() {
        FILE *fp;
        FILE *temp;
        student stu;
        int rollno;
        char name[30];
        int found = 0;

        fp = fopen("students.dat", "rb");
        if (fp == NULL) {
            printf("No student records found. Cannot update.");
            return;
        }
        if (fread(&stu, sizeof(student), 1, fp) != 1) {
            printf("No student records found. Cannot update.");
            fclose(fp);
            return;
        }
        fclose(fp);

        while (1) {
            printf("Enter student's roll no. to updatde: ");
            scanf("%d", &rollno);
            printf("Enter student's name to update: "); 
            scanf("%s", name);
    
            found = 0;
            fp = fopen("students.dat", "rb");
            if (fp == NULL) {
                printf("Unable to open students data file.\n");
                return;
            }
            temp = fopen("temp.dat", "wb");
            if (temp == NULL) {
                printf("Unable to create a temporary file.\n");
                fclose(fp);
                return;
            }
            found = 0;
            while (fread(&stu, sizeof(student), 1, fp) == 1) {
                if (stu.rollno == rollno && strcmp(stu.name, name) == 0) {
                    found = 1;
                    
                    printf("Student record found. Enter new details:\n");
                    printf("Enter new name: ");
                    scanf("%s", stu.name);
                    do {
                        printf("Enter new age: ");
                        scanf("%d", &stu.age);                 
                        if (stu.age < 1 || stu.age > 100) {
                            printf("Age must be between 1 and 100. Enter again.\n");
                        }
                    } 
                    while (stu.age < 1 || stu.age > 100);
                    do {
                        printf("Enter new gender (M/F): ");
                        scanf("%s", stu.gender);               
                        if (strcmp(stu.gender, "M") != 0 && strcmp(stu.gender, "F") != 0) {
                            printf("Invalid gender. Enter M or F.\n");
                        }
                    } 
                    while (strcmp(stu.gender, "M") != 0 && strcmp(stu.gender, "F") != 0);
                    printf("Enter new department: ");
                    scanf("%s", stu.department);
                    do {
                        printf("Enter new semester: ");
                        scanf("%d", &stu.semester);
                    
                        if (stu.semester <= 0 || stu.semester > 8) {
                            printf("Semester must be between 1 and 8. Enter again.\n");
                        }
                    }
                    while (stu.semester <= 0 || stu.semester > 8);
                    for (int i = 0; i < 5; i++) {
                        do {
                            printf("Enter new marks for sub %d: ", i + 1);
                            scanf("%d", &stu.marks[i]);
                            if (stu.marks[i] < 0 || stu.marks[i] > 100) {
                                printf("Invalid marks entered. Range must be between 0 and 100. Enter again.\n");
                            }
                        }
                        while (stu.marks[i] < 0 || stu.marks[i] > 100);
                    }
                    do {
                        printf("Enter addendance percentage: ");
                        scanf("%f", &stu.attendance);
                        if (stu.attendance < 0 || stu.attendance > 100) {
                            printf("Invalid attendance percentage entered. Enter again.\n");
                        }
                    }
                    while (stu.attendance < 0 || stu.attendance > 100);
                }
                fwrite(&stu, sizeof(student), 1, temp);
            }
            fclose(fp);
            fclose(temp);
            if (found == 1) {
                remove("students.dat");
                rename("temp.dat", "students.dat");
                printf("Successfully updated student's record.\n");
                break;
            }
            else {
                remove("temp.dat");
                printf("Student record not found. Please enter correct details.\n");
            }
        }
    }
    void deleteStudent() {
        FILE *fp; 
        FILE *temp;
        student stu;
        int rollno;

        fp = fopen("students.dat", "rb");
        if (fp == NULL) {
            printf("No student records found. Cannot delete.\n");
            return;
        }
        if (fread(&stu, sizeof(student), 1, fp) != 1) {
            printf("No student records found. Cannot delete.\n");
            fclose(fp);
            return;
        }
        fclose(fp);
        while (1) {
            printf("Enter student's roll no. to delete: ");
            scanf("%d", &rollno);
            fp = fopen("students.dat", "rb");
            if (fp == NULL) {
                printf("Unable to open students data file.\n");
                return;
            }
            temp = fopen("temp.dat", "wb");
            if (temp == NULL) {
                printf("Unable to create a temporary file.\n");
                fclose(fp);
                return;
            }
            int found = 0;
            while(fread(&stu, sizeof(student), 1, fp) == 1) {
                if (stu.rollno == rollno) {
                    found = 1;
                    continue;
                }
                fwrite(&stu, sizeof(student), 1, temp);
            } 
            fclose(fp);
            fclose(temp);
            if (found == 1) {
                remove("students.dat");
                rename("temp.dat", "students.dat");
                printf("Successfully deleted student's record.\n");
                break;
            }
            else{
                remove("temp.dat");
                printf("Student record not found. Please enter correct details.\n");
            }
        }
    }
    void studentStatistics() {
        FILE *fp;
        student stu;
        int totalStudents = 0;
        int totalMarks;
        int passCount = 0;
        float average;
        float highestAvg = 0;
        float lowestAvg = 100;
        float totalAvg = 0; 
        float classAvg;
        float passPercentage;
        int passMark = 200;
        fp = fopen("students.dat", "rb");
        if (fp == NULL) {
            printf("nable to open students data file.\n");
            return;
        }
        while (fread(&stu, sizeof(student), 1, fp) == 1) {
            totalStudents += 1;
            totalMarks = 0;
            for (int i = 0; i < 5; i++) {
                totalMarks += stu.marks[i];
            }
            average = totalMarks / 5.0;
            totalAvg = totalAvg + average;
            if (average > highestAvg) {
                highestAvg = average;
            }
            if (average < lowestAvg) {
                lowestAvg = average;
            }
            if (totalMarks >= passMark) {
                passCount += 1;
            }
        }
        fclose(fp);
        if (totalStudents == 0) {
            printf("No records found.\n");
            return;
        }
        classAvg = totalAvg / totalStudents;
        passPercentage = ((float)passCount / totalStudents) * 100;
        printf("\n ================ STUDENT STATISTICS ================\n");
        printf("\n 1. Total Number of Students: %d", totalStudents);
        printf("\n 2. Highest Average Marks: %.2f", highestAvg);
        printf("\n 3. Lowest Average Marks: %.2f", lowestAvg);
        printf("\n 4. Class Average Marks: %.2f", classAvg);
        printf("\n 5. Pass Percentage: %.2f", passPercentage);
        printf("\n ======================================================\n");
    }

int main() {
    int choice;
    while (1) {
        printf("\n ======================= STUDENT MANAGEMENT SYSTEM =======================\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Students' Statistics\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                studentStatistics();
                break;
            case 7:
                printf("\n =================== EXITING STUDENT MANAGEMENT SYSTEM =================== ");
                return 0;
            default:
                printf("Invalid choice...Try again\n");
        }
    }
    return 0;
}
