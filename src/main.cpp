#include "application.h"

int main(int argc, char **argv) {
    Application app = Application(800,600, "ZPG - SLA0331");
    app.init();
    Application::info();
    app.run();
}