// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation: 18/9/2023

#include "core/application.h"

int main(int argc, char **argv) {
    Application app = Application(800,600, "ZPG - SLA0331");
    app.init();
    Application::info();
    app.run();
}