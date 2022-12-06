#include "datahandler.h"
#include "session.h"

#include "debugmalloc.h"


Task* task_init(void) {
    Task *task;
    task = (Task*) malloc(sizeof(Task));
    if (task == NULL) {
        return NULL;
    }
    
    strcpy(task->name, "");
    task->due.y = 0;
    task->due.m = 0;
    task->due.d = 0;
    strcpy(task->cat, "");
    strcpy(task->dscr, "");
    task->done = false;
    
    return task;
}


//display

void print_tasks(void) {
    Task *pointer = session.task;
    int seq = 1;
    while (pointer != NULL && seq <= 3) {
        if (PLATFORM == 1) {
            printf(" ┌────────────────────────\n");

            printf(" │ %s\n", pointer->name);
            printf(" │ \tDue: \t%04d.%02d.%02d.\n", pointer->due.y, pointer->due.m, pointer->due.d);
            printf(" │ \tCat: \t%s\n", pointer->cat);
            printf(" │ \tInfo: \t%s\n", pointer->dscr);
            (pointer->done) ? printf(" │ \tDone\n") : printf(" │ \tNot Done\n");

            printf(" │──────────┐\n");
            printf(" │ [%d] Edit │\n", seq++);
            printf(" └────────────────────────\n");
        }
        else {
            printf(" _________________________\n");

            printf(" | %s\n", pointer->name);
            printf(" | \tDue: \t%04d.%02d.%02d.\n", pointer->due.y, pointer->due.m, pointer->due.d);
            printf(" | \tCat: \t%s\n", pointer->cat);
            printf(" | \tInfo: \t%s\n", pointer->dscr);
            (pointer->done) ? printf(" | \tDone\n") : printf(" | \tNot Done\n");

            printf(" |__________\n");
            printf(" | [%d] Edit |\n", seq++);
            printf(" |________________________\n");
        }
        
        pointer = pointer->next;
    }
}


//add task

bool valid_task(Task *task) {
    if (strcmp(task->name, "") != 0) {
        if (task->due.y !=0 && task->due.m !=0 && task->due.d !=0) {
            return true;
        }
    }
    return false;
}

Task* add_task(Task *data_start, Task *newTask) {
    Task *new = task_init();
    if (new == NULL) {
        return NULL;
    }
    
    strcpy(new->name, newTask->name);
    new->due = newTask->due;
    strcpy(new->cat, newTask->cat);
    strcpy(new->dscr, newTask->dscr);
    new->done = newTask->done;
    
    new->next = data_start;
    return new;
}


//remove task

Task* remove_task(Task *data_start, Task *rmTask) {
    Task *prev = NULL;
    Task *pointer = data_start;
    
    while (pointer != NULL && pointer != rmTask) {
        prev = pointer;
        pointer = pointer->next;
    }
    
    if (pointer == NULL) {
        strcpy(session.log, "Error while removing Task");
        return data_start;
    } else if (prev == NULL) {
        data_start = pointer->next;
        free(pointer);
        strcpy(session.log, "Task Removed");
    } else {
        prev->next = pointer->next;
        free(pointer);
        strcpy(session.log, "Task Removed");
    }
    return data_start;
}


//load

bool load_data(void) {
    FILE *savefile = open_savefile("r");
    if (savefile == NULL) {
        strcpy(session.log, "[error:can't open save file | ");
        strcat(session.log, strerror(errno));
        strcat(session.log, "]");
        return false;
    }
    
    Task *data_start = NULL;
    
    char dataLine[LEN_T_NAME+11+LEN_T_CAT+LEN_T_DSCR+1+6];
    Task loadTask;
    int numDone;
    
    while (fgets(dataLine, sizeof(dataLine), savefile) != NULL) {
        sscanf(dataLine, "%[^\t]\t%d.%d.%d.\t%[^\t]\t%[^\t]\t%d\n", loadTask.name, &loadTask.due.y, &loadTask.due.m, &loadTask.due.d, loadTask.cat, loadTask.dscr, &numDone);
        loadTask.done = (numDone == 1) ? true : false;
        
        if (strcmp(loadTask.cat, "*") == 0) {
            strcpy(loadTask.cat, "");
        }
        if (strcmp(loadTask.dscr, "*") == 0) {
            strcpy(loadTask.dscr, "");
        }
        
        data_start = add_task(data_start, &loadTask);
    }
    
    fclose(savefile);
    session.data = data_start;
    return true;
}


//save

bool save_data(void) {
    FILE *savefile = open_savefile("w");
    if (savefile == NULL) {
        strcpy(session.log, "[error:can't open save file | ");
        strcat(session.log, strerror(errno));
        strcat(session.log, "]");
        return false;
    }
    
    Task *pointer = session.data;
    while (pointer != NULL) {
        fprintf(savefile, "%s\t", pointer->name);
        fprintf(savefile, "%d.%d.%d.\t", pointer->due.y, pointer->due.m, pointer->due.d);
        if ((pointer->cat)[0] == '\0') {
            fprintf(savefile, "*\t");
        } else {
            fprintf(savefile, "%s\t", pointer->cat);
        }
        if (pointer->dscr[0] == '\0') {
            fprintf(savefile, "*\t");
        } else {
            fprintf(savefile, "%s\t", pointer->dscr);
        }
        if (pointer->done) {
            fprintf(savefile, "1\n");
        } else {
            fprintf(savefile, "0\n");
        }
        
        Task *next = pointer->next;
        free(pointer);
        pointer = next;
    }
    
    fclose(savefile);
    return true;
}

//others

int compare_dates(Date d1, Date d2) {
    if (d1.y < d2.y)
        return -1;
    else if (d1.y > d2.y)
        return 1;
    else {
         if (d1.m<d2.m)
              return -1;
         else if (d1.m>d2.m)
              return 1;
         else {
             if (d1.d<d2.d)
                 return -1;
             else if(d1.d>d2.d)
                 return 1;
             else
                 return 0;
         }
    }
}

double percent_today(int *count_today, int *count_today_done) {
    *count_today = 0;
    *count_today_done = 0;
    
    //src:https://www.techiedelight.com/print-current-date-and-time-in-c/
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    for (Task *pointer = session.data; pointer != NULL; pointer = pointer->next) {
        if (pointer->due.y == tm.tm_year+1900 && pointer->due.m == tm.tm_mon+1 && pointer->due.d == tm.tm_mday) {
            (*count_today)++;
            if (pointer->done == true) {
                (*count_today_done)++;
            }
        }
    }
    
    if (*count_today == 0) {
        return -1;
    } else {
        return round((double) *count_today_done / *count_today * 100);
    }
}

bool find_next_task(void) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    Date date_now = {tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday};
    Task *next = NULL;
    
    for (Task *pointer = session.data; pointer != NULL; pointer = pointer->next) {
        Date task_date = pointer->due;
        
        if (compare_dates(task_date, date_now) != -1) {
            if (next == NULL) {
                next = pointer;
            } else {
                int cmp = compare_dates(task_date, next->due);
                if (cmp == 0) {
                    if (strcmp(pointer->name, next->name) < 0) {
                        next = pointer;
                    }
                } else if (cmp == -1) {
                    next = pointer;
                }
            }
        }
    }
    if (next == NULL) {
        return false;
    }
    session.task = next;
    return true;
}

bool jump_seq(void) {
    Task *pointer = session.task;
    if (pointer == NULL) {
        return false;
    }
    int jumps = 0;
    
    for (int i = 0; i < 3; i++) {
        if (pointer->next != NULL) {
            pointer = pointer->next;
            jumps++;
        }
    }
    
    if (jumps == 3) {
        session.task = pointer;
        return true;
    }
    return false;
}
