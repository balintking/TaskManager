
#include "navigation.h"
#include "session.h"

Page page = login;

/*gets and executes user command based on the current window*/
void get_input(){
    
    int option;
    scanf("%d", &option);
    
    switch(page){
        case login:
            switch(option) {
                case 1:
                    break;
                case 2:
                    break;
                
            }
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
