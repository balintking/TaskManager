
#include "uinterface.h"
#include "session.h"
#include "navigation.h"

static void display_login(void){
    
    printf("[1] username: %s\n", session.user);
    printf("[2] password: %s\n", session.password);
    printf("\n");
    
    printf("[3] Login\n");
    printf("\n");

}

static void display_dashboard(void){
    printf("\n");
    printf("Hello, %s!\n", session.user);
    printf("\n\n");
    
    printf("Your Tasks for today [progress_bar] 100%% Done\n");
    printf("\n");
    printf("Next Task: [1] [next_task]\n");
    printf("\n\n\n\n");
    
    printf("[2] Create New Task\t[3] See All Tasks\t[4] Log Out\n");
}

void display_log(void) {
    printf("\n%s\n", session.log);
    session.log[0] = '\0';
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
            break;
        case single:
            break;
        case newTask:
            break;
        case logout:
            break;
        default:
            break;
    }
    
    display_log();
    
    printf("OPTION: ");
}


