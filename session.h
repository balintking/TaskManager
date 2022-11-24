#ifndef SESSION_H
#define SESSION_H

#include <stdbool.h>

typedef struct Session {
    char user[10];
    char password[10];
} Session;

extern bool activeSession;
extern Session session;

void start_session(void);
void end_session(void);

#endif
