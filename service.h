#pragma once

#include "observer.h"
#include "entities.h"
#include "repository.h"
#include <string>
#include "undo.h"
using std::string;

class Service: public Observable{
private:
    Repo& rep;
    vector<ActiuneUndo*> list_undo;
public:
    explicit Service(Repo& rep) :rep{ rep } {}


    void add(int apt, string nume, int sup, string tip);

    vector<Bloc> get_All();

    void generate();

    void del_serv(int ap, const string& nume);

    void modify_serv(int ap, string nume, int sup, string tip);

    bool get_serv(int ap, string& nume);

    Bloc get(int ap, string nume);

    vector<Bloc> filtru(string nume);

    void empty_all();

    vector<Bloc> sort_a();

    vector<Bloc> sort_n();

    void random(int nr);

    vector<Bloc> filtru_supr(int sup);

    void undo();
};

