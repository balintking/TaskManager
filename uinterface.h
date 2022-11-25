#ifndef UINTERFACE_H
#define UINTERFACE_H

#include <stdio.h>

typedef enum Page{
    login,
    dashboard,
    tasks,
    single,
    newTask,
    logout
} Page;

void display(Page screen);

#endif
