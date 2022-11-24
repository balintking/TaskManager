
#include "uinterface.h"
#include "session.h"
#include "navigation.h"

/*displays the contents of the current page*/
void display() {
    switch(page){
        case login:
            printf("[1] username: ");
            printf("[2] password: ");
            break;
        case dashboard:
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
}

void page_login(void){
    
}
