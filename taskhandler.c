
typedef struct Date {
    int y;
    int m;
    int d;
} Date;

typedef struct Task {
    char name[50];
    Date dueDate;
    char category[25];
    char dscr;
} Task;
