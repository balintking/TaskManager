
#include "session.h"
#include "navigation.h"

bool activeSession = false;
Session session;

void start_session(){
    activeSession = true;
    page = login;
}

void end_session() {
    activeSession = false;
}
