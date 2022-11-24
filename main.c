#include "session.h"
#include "uinterface.h"
#include "navigation.h"

int main() {

    start_session();

    while(activeSession) {
        display();
        get_input();
    }

    return 0;
}
