#include "MainWindow.hpp"

//TODO: Fix the vertex fix for shininess

int main(int argc, char* argv[])
{
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication app(argc, argv);

    MainWindow window;
    return app.exec();
};
