#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
  char name[50];
  int id, rank;
  int marks[3], total;
} st;

st s[51];

void display(int count); // Function Prototype
void add(int c);
int delet(int c);
void alphabetical_order(int c);
void find_rank(int c);
bool t = false;
int main() {

  int choice, count = 0;
  bool exit = false;
  for (; 1;) {
    t = false;
    printf("Enter your choice\n");
    printf("1. Display Students details\n");
    printf("2. Add Student\n");
    printf("3. Delete Student\n");
    printf("4. Exit\n");
    int choice;

    scanf("%d", &choice);
    switch (choice) {
    case 1:
      display(count);
      break;
    case 2:
      count++;
      add(count);
      break;
    case 3:
      count = delet(count);
      break;
    case 4:
      exit = true;
      break;
    default:
      printf("Invalid Choice Entered\n");
    }
    if (exit)
      break;
  }
  return 0;
}

void display(int count) {
  if (count != 0) {
    printf("Enter your choice\n1.Display Students in Alphabetical "
           "Oredr.\n2.Display Students in Ascending Order of their rank\n");
    int display_choice;
    scanf("%d", &display_choice);
    switch (display_choice) {
    case 1:
      t = true;
      find_rank(count);
      alphabetical_order(count);
      for (int i = 1; i <= count; i++) {
        printf("Student Name: %s\n", s[i].name);
        printf("Student ID: %d\n", s[i].id);
        printf("Student Total Marks: %d\n", s[i].total);
        printf("Student Rank: %d\n", s[i].rank);
        printf("\n");
      }
      break;
    case 2:
      find_rank(count);
      for (int i = 1; i <= count; i++) {
        printf("Student Name: %s\n", s[i].name);
        printf("Student ID: %d\n", s[i].id);
        printf("Student Total Marks: %d\n", s[i].total);
        printf("Student Rank: %d\n", s[i].rank);
        printf("\n");
      }
      break;
    default:
      printf("Invalid Choice");
    }
  } else {
    printf("No student added\n");
  }
}
void add(int c) {
  FILE *fp;
  fp = fopen("data.txt", "a");
  printf("Enter name\n");
  scanf("%s", s[c].name);
  printf("Enter id\n");
  scanf("%d", &s[c].id);
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    printf("Enter marks\n");
    scanf("%d", &s[c].marks[i]);
    sum += s[c].marks[i];
  }
  s[c].total = sum;
  fprintf(fp, "Name: %s\n", s[c].name);
  fprintf(fp, "ID: %d\n", s[c].id);
  fprintf(fp, "Total Marks: %d\n", s[c].total);
  fprintf(fp, "\n");
  fclose(fp);
}
void find_rank(int c) {

  for (int i = c; i > 1; i--) {
    for (int j = 1; j < i; j++) {
      if (s[j].total < s[j + 1].total) {
        char copy[50];
        strcpy(copy, s[j].name);
        strcpy(s[j].name, s[j + 1].name);
        strcpy(s[j + 1].name, copy);
        int restore = s[j].id;
        s[j].id = s[j + 1].id;
        s[j + 1].id = restore;
        int temp = s[j].total;
        s[j].total = s[j + 1].total;
        s[j + 1].total = temp;
      }
    }
  }

  FILE *fp;
  fp = fopen("data.txt", "w");
  for (int i = 1; i <= c; i++) {
    s[i].rank = i;
    if (!t) {
      fprintf(fp, "Name: %s\n", s[i].name);
      fprintf(fp, "ID: %d\n", s[i].id);
      fprintf(fp, "Total Marks: %d\n", s[i].total);
      fprintf(fp, "Rank: %d\n", s[i].rank);
      fprintf(fp, "\n");
    }
  }
  fclose(fp);
}
void alphabetical_order(int c) {
  for (int i = 1; i <= c; i++) {
    for (int j = i + 1; j <= c; j++) {
      if (strcmp(s[i].name, s[j].name) > 0) {
        char copy[50];
        strcpy(copy, s[i].name);
        strcpy(s[i].name, s[j].name);
        strcpy(s[j].name, copy);
        int restore = s[i].id;
        s[i].id = s[j].id;
        s[j].id = restore;
        int temp = s[i].total;
        s[i].total = s[j].total;
        s[j].total = temp;
        int restore_rank = s[i].rank;
        s[i].rank = s[j].rank;
        s[j].rank = restore_rank;
      }
    }
  }
}
int delet(int c) {
  if (c != 0) {
    int deletion_index;
    printf("Enter the  student you want to delete\n");
    scanf("%d", &deletion_index);
    if (deletion_index == c) {
      return c - 1;
    } else {
      for (int i = deletion_index; i < c; i++) {
        strcpy(s[i].name, s[i + 1].name);
        s[i].id = s[i + 1].id;
        s[i].total = s[i + 1].total;
        s[i].rank = s[i + 1].rank;
      }
      return c - 1;
    }
    FILE *fp;
    fp = fopen("data.txt", "w");
    for (int i = 1; i <= c; i++) {
      if (i == deletion_index)
        continue;
      fprintf(fp, "Name: %s\n", s[c].name);
      fprintf(fp, "ID: %d\n", s[c].id);
      fprintf(fp, "Total Marks: %d\n", s[c].total);
      fprintf(fp, "Rank: %d\n", s[c].rank);
      fprintf(fp, "\n");
    }
    fclose(fp);
  } else {
    printf("No student added\n");
    return 0;
  }
}