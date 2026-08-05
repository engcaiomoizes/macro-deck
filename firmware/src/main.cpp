#include "app/application.h"

int main() {
    Application app;
    
    app.initialize();

    while (true) {
        app.update();
    }
}