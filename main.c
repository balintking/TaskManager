#include "session.h"
#include "uinterface.h"
#include "navigation.h"

int main() {

    Page next_page;
    next_page = start_session();
    
    while (activeSession) {
        display(next_page);
        next_page = navigate(next_page);
        
    }

    return 0;
}
