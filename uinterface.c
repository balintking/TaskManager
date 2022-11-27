
#include "uinterface.h"
#include "session.h"
#include "navigation.h"

void display_log(void) {
    printf("%s\n", session.log);
    session.log[0] = '\0';
}

static void display_login(void){
    printf("\n");
    printf("LOGIN");
    printf("\n\n");
    
    printf("[1] username: %s\n", session.user);
    printf("[2] password: %s\n", session.password);
    printf("\n");
    
    printf("[3] Login\n");
    printf("\n");

}

static void display_dashboard(void){
    printf("\n");
    printf("HELLO, ");
    for (int i = 0; i < strlen(session.user); i++) {
        printf("%c", toupper(session.user[i]));
    }
    printf("!\n");
    printf("\n\n");
    
    printf("Your Tasks for today [progress_bar] 100%% Done\n");
    printf("\n");
    printf("Next Task: [3] [next_task]\n");
    printf("\n\n\n\n");
    
    printf("[1] Create New Task\t[2] See All Tasks\t\t\t[9] Log Out\n");
    printf("\n");
    
    if (session.data != NULL) {
        printf("%s %d.%d.%d. %s %s", session.data->name, session.data->due.y, session.data->due.m, session.data->due.d, session.data->cat, session.data->dscr);
    }
    
}

static void display_tasks(void){
    printf("\n");
    printf("YOUR TASKS");
    printf("\n\n");
    
    print_tasks();
    
    printf("[0] Back\t[8] Next Page\t[9] Previous Page\n");
    printf("\n");
}

static void display_newTask(void){
    printf("\n");
    printf("CREATE NEW TASK");
    printf("\n\n");
    
    printf("[1] Title: %s\n", session.task->name);
    printf("[2] Due Date: %d.%d.%d.\n", session.task->due.y, session.task->due.m, session.task->due.d);
    printf("[3] Category: %s\n", session.task->cat);
    printf("[4] Description: %s\n", session.task->dscr);
    printf("[5] Done: ");
    if (session.task->done) {
        printf("Yes");
    }
    else {
        printf("No");
    }
    printf("\n");
    printf("\n");
    
    printf("[0] Save\t[9] Cancel\n");
    printf("\n");

}

static void display_logout(void) {
    printf("\n");
    printf("LOG OUT");
    printf("\n\n");
    
    printf("[1] Log out\n");
    printf("[2] Close application\n");
    printf("\n");
    printf("[9] Cancel\n");
    printf("\n");
}

/*displays the contents of the current page*/
void display(Page screen) {
    
    if (PLATFORM == 1) {
        system("clear");
    }
    else {
        system("cls");
    }
    
    switch(screen){
        case login:
            display_login();
            break;
        case dashboard:
            display_dashboard();
            break;
        case tasks:
            display_tasks();
            break;
        case single:
            break;
        case newTask:
            display_newTask();
            break;
        case logout:
            display_logout();
            break;
        default:
            break;
    }
    
    display_log();
    
    printf("OPTION: ");
}


