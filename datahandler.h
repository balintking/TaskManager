#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <stdlib.h>
#include <stdbool.h>

#define LEN_T_NAME 50
#define LEN_T_CAT 25
#define LEN_T_DSCR 200

typedef struct Date {
    int y;
    int m;
    int d;
} Date;

typedef struct Task {
    char name[LEN_T_NAME+1];
    Date due;
    char cat[LEN_T_CAT+1];
    char dscr[LEN_T_NAME+1];
    bool done;
    struct Task *next;
} Task;

Task* init_task(void);
bool valid_task(Task *task);

Task* insert_task(Task *data_start, Task *loadTask);
bool append_task(Task *data_start, Task *newTask);
void print_tasks(void);

bool load_data(void);
bool save_data(void);

#endif

/*test1
 2022.2022.2022.
 cat1
 d1
 0
 test2
 2022.2022.2022.
 cat2
 d4
 0
*/
