#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <stdio.h>

typedef enum Page{
    login,
    dashboard,
    tasks,
    single,
    newTask,
    logout
} Page;

extern Page page;

void get_input(void);

#endif
