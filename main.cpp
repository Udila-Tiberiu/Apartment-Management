#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo;

    Service serv{ repo };
    serv.generate();

    GUI gui{ serv };

    gui.show();

    return a.exec();
}
