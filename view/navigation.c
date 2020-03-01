#include "./navigation.h"

int currentMainWindow = 0;

int getCurrentMainWindow() {
    return currentMainWindow;
}

void setCurrentMainWindow(int newId) {
    currentMainWindow = newId;
}