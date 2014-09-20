/**
 * @file    app/main.cpp
 *
 * @brief   Main function implementation
 *
 * @author  ymoch
 */

#include "application.h"

int main(int argc, char *argv[])
{
    Qta::App::Application app(argc, argv);
    return app.exec();
}
