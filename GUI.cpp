#include "GUI.h"

void GUI::loadGUI(const vector<Bloc> all)
{
    list->clear();
    for (auto& bloc : all) {
        string ap = std::to_string(bloc.getAp());
        QListWidgetItem* apt = new QListWidgetItem(QString::fromStdString(ap));
        apt->setData(Qt::UserRole, QString::fromStdString(bloc.getNume()));
        apt->setData(Qt::BackgroundRole, QBrush{ Qt::lightGray, Qt::SolidPattern });
        list->addItem(apt);
    }
}

void GUI::initConnect()
{
    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        QMessageBox::information(nullptr, "info", "Aplicatia s-a finalizat");
        close();
        });

    QObject::connect(btnSrtAp, &QPushButton::clicked, [&]() {
        loadGUI(serv.sort_a());
        
        });

    QObject::connect(btnSrtNume, &QPushButton::clicked, [&]() {
        loadGUI(serv.sort_n());
        
        });

    QObject::connect(btnOriginal, &QPushButton::clicked, [&]() {
        loadGUI(serv.get_All());
        
        });

    QObject::connect(btnFilSup, &QPushButton::clicked, [&]() {
        filtru();
        });

    QObject::connect(btnNewWindow, &QPushButton::clicked, [&]() {
        auto c = new GUI{ serv };
        c->move(10, 10);
        c->show();  
        });

    QObject::connect(btnDesen, &QPushButton::clicked, [&]() {
        auto pGUI = new Paint{ serv };
        pGUI->move(900, 100);
        pGUI->show();
        });

    QObject::connect(btnAdd, &QPushButton::clicked, this, &GUI::addBloc);

    QObject::connect(btnUndo, &QPushButton::clicked, this, &GUI::undoBloc);

    QObject::connect(btnDel, &QPushButton::clicked, this, &GUI::delBloc);

    QObject::connect(btnMod, &QPushButton::clicked, this, &GUI::modBloc);

    QObject::connect(list, &QListWidget::itemSelectionChanged, [&]() {
        auto sel = list->selectedItems();
        if (sel.isEmpty()) {
            txtAp->setText("");
            txtNume->setText("");
            txtSup->setText("");
            txtTip->setText("");
        }
        else {
            auto sellItem = sel.at(0);
            auto ap = sellItem->text();
            auto nume = sellItem->data(Qt::UserRole).toString();
            txtAp->setText(ap);
            txtNume->setText(nume);
            auto b = serv.get(ap.toInt(), nume.toStdString());
            txtSup->setText(QString::number(b.getSup()));
            txtTip->setText(QString::fromStdString(b.getTip()));

        }
        });
}

void GUI::initGUI()
{
    setWindowTitle("Aplicatia");
    serv.addObs(this);
    Paint* pain = new Paint{ serv };
    pain->setLayout(layout_paint);
    QHBoxLayout* lyMain = new QHBoxLayout{};
    setLayout(lyMain);

    auto drp = new QVBoxLayout;
    auto stg = new QVBoxLayout;
    stg->addWidget(listTitle);
    stg->addWidget(list);

    auto srtBtns = new QHBoxLayout;
    srtBtns->addWidget(btnSrtAp);
    srtBtns->addWidget(btnSrtNume);
    srtBtns->addWidget(btnOriginal);
    stg->addLayout(srtBtns);

    lyMain->addLayout(stg);

    auto frm = new QFormLayout{};
    frm->addRow("Apartament", txtAp);
    frm->addRow("Nume propreitar", txtNume);
    frm->addRow("Suprafata", txtSup);
    frm->addRow("Tipul", txtTip);
    drp->addLayout(frm);

    auto lyBtns = new QHBoxLayout{};
    auto btStg = new QVBoxLayout;
    auto btDrp = new QVBoxLayout;
    auto btMij = new QVBoxLayout;
    btStg->addWidget(btnAdd);
    btDrp->addWidget(btnDel);
    btStg->addWidget(btnMod);
    btDrp->addWidget(btnFilSup);
    btStg->addWidget(btnExit);
    btDrp->addWidget(btnNewWindow);
    lyBtns->addLayout(btStg);
    lyBtns->addLayout(btDrp);
    btMij->addWidget(btnUndo);
    btMij->addWidget(btnDesen);
    lyBtns->addLayout(btMij);
    
    
    drp->addLayout(lyBtns);
    drp->addWidget(pain);

    lyMain->addLayout(drp);
 

}

void GUI::undoBloc()
{
    try {
        serv.undo();
        loadGUI(serv.get_All());
        this->repaint();
        serv.notify();
    }
    catch (RepoException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
    }
}

void GUI::addBloc()
{
    try {
        if (txtAp->text() == "" || txtNume->text() == "" || txtTip->text() == "" || txtSup->text() == "") {
            QMessageBox::warning(this, "Warning", "Nu au fost introduse toate datele");
        }
        else {
            serv.add(txtAp->text().toInt(), txtNume->text().toStdString(), txtSup->text().toInt(), txtTip->text().toStdString());
            loadGUI(serv.get_All());
            this->repaint();
            serv.notify();
        }
    }
    catch (RepoException& e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMsg()));
    }
}

void GUI::delBloc()
{
    try {
        serv.del_serv(txtAp->text().toInt(), txtNume->text().toStdString());
        loadGUI(serv.get_All());
        this->repaint();
        serv.notify();
    }
    catch (RepoException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
    }
}

void GUI::modBloc()
{
    try {
        serv.modify_serv(txtAp->text().toInt(), txtNume->text().toStdString(), txtSup->text().toInt(), txtTip->text().toStdString());
        loadGUI(serv.get_All());
        this->repaint();
        serv.notify();
    }
    catch (RepoException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
    }
}

void GUI::filtru()
{
    list->clear();
    auto sup = txtSup->text().toInt();
    for (auto& bloc : serv.get_All()) {
        string ap = std::to_string(bloc.getAp());
        QListWidgetItem* apt = new QListWidgetItem(QString::fromStdString(ap));
        apt->setData(Qt::UserRole, QString::fromStdString(bloc.getNume()));
        if (bloc.getSup() > sup) {
            apt->setData(Qt::BackgroundRole, QBrush{ Qt::red, Qt::SolidPattern });
        }
        else {
            apt->setData(Qt::BackgroundRole, QBrush{ Qt::lightGray, Qt::SolidPattern });
        }
        list->addItem(apt);
    }
}

void GUI::addWindows()
{
    miniGUI* wind = new miniGUI(serv);
    wind->show();
}

void GUI::addButoane(const vector<Bloc> all)
{
    for (const auto& bloc : all) {
        if (bloc.getSup() > 400) {
            lyDyn->addWidget(new QPushButton{QString::fromStdString(bloc.getNume())});
        }
    }
    
}



