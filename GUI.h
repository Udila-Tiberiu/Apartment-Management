#pragma once
#include "Lab10.h"
#include "service.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <qpalette.h>
#include <qbrush.h>
#include <qpainter.h>

class miniGUI : public QWidget, public Observer {
private:
    Service& serv;
    QListWidget* list = new QListWidget;
    QHBoxLayout* main_layout = new QHBoxLayout;
    
public:
    miniGUI(Service& serv) : serv{ serv } {
        serv.addObs(this);
        init();
        reload_list(serv.get_All());

    }
    
    void init() {
        setWindowTitle("Lista de blocuri");
        setLayout(main_layout);
        main_layout->addWidget(list);

    }

    void reload_list(vector<Bloc> lst) {
        list->clear();
        for (auto& bloc : lst) {
            list->addItem(QString::fromStdString(std::to_string(bloc.getAp()) + " " + bloc.getNume() + " " + std::to_string(bloc.getSup()) + " " + bloc.getTip()));
        }
    }

    void update() override {
        reload_list(serv.get_All());
    }
};


class GUI: public QWidget, public Observer
{
    friend class Paint;
public:
    GUI(Service& serv) : serv{ serv } {
        initGUI();
        loadGUI(serv.get_All());
        initConnect();
        addWindows();
    }


private:
    Service& serv;

    QLabel* listTitle = new QLabel { " Lista formata din numerele apartamentelor " };
    QListWidget* list = new QListWidget;
    QVBoxLayout* layout_paint = new QVBoxLayout;
    QPushButton* btnExit = new QPushButton{ " Exit " };
    QPushButton* btnAdd = new QPushButton{ " Add " };
    QPushButton* btnDel = new QPushButton{ " Delete " };
    QPushButton* btnMod = new QPushButton{ " Modify " };
    QPushButton* btnSrtAp = new QPushButton{ " Sort Apt. " };
    QPushButton* btnSrtNume = new QPushButton{ " Sort Nume " };
    QPushButton* btnOriginal = new QPushButton{ " Original " };
    QPushButton* btnFilSup = new QPushButton{ " Filtru - Supr. " };
    QPushButton* btnNewWindow = new QPushButton{ " New Window " };
    QPushButton* btnDesen = new QPushButton{ " Desen " };
    QPushButton* btnUndo = new QPushButton{ " Undo " };
    
    QLineEdit* txtAp = new QLineEdit;
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtSup = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QVBoxLayout* lyDyn = new QVBoxLayout;
    QWidget* btnDyn = new QWidget;

    void loadGUI(const vector<Bloc> all);

    void undoBloc();

    void initConnect();

    void initGUI();

    void addBloc();

    void delBloc();

    void modBloc();

    void filtru();

    void addWindows();

    void update() override {
        loadGUI(serv.get_All());
    }

    void addButoane(const vector<Bloc> all);
};

class Paint : public QWidget {
    friend class GUI;

private:
    Service& serv;
public:
    Paint(Service& serv) : serv{ serv } {
        this->repaint();
    }

    void paintEvent(QPaintEvent* ev) override {
        QPainter p{ this };
        int x = 10;
        int z = width() / 2;
        int y = height() / 2;
        
        for (auto b : serv.get_All()) {
            p.drawRect(x, 10, 20, b.getSup() / 10);
            x += 40;
        }
    }


}; 
//dN2sZWSwqh