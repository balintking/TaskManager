
#include "uinterface.h"
#include "session.h"
#include "navigation.h"

static void display_login(void){
    
    printf("[1] username: ");
    printf("%s", session.user);
    printf("\n");
    
    printf("[2] password: ");
    printf("%s", session.password);
    printf("\n");
    printf("\n");
    
    printf("[3] Login");
    printf("\n");

}

static void display_dashboard(void){
    
}

void display_log(void) {
    printf("\n%s\n", session.log);
    session.log[0] = '\0';
}

/*displays the contents of the current page*/
void display(Page screen) {
    
    system("clear");
    
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


