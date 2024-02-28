#pragma once

#include "entities.h"
#include <vector>
#include <cassert>
#include <fstream>
#include <iomanip>

using std::vector;
class RepoException {
    string msg;
public:
    RepoException(string m) :msg{ m } {}
    string getMsg() {
        return msg;
    }
};


class Repo {
private:
    vector<Bloc> list;
public:

    Repo() = default;

    virtual ~Repo() = default;

    virtual void store(Bloc& bloc);

    void store_in(Bloc& bloc, int i);

    void generate();

    vector<Bloc> getAll();

    virtual void del_repo(Bloc& b);

    virtual Bloc modify_repo(Bloc& b);

    bool get_repo(Bloc& b);

    Bloc get(int ap, string nume);

    vector<Bloc> fil_nume(string& nume);

    void empty_list();

    vector<Bloc> sort_ap();

    vector<Bloc> sort_nume();

    void random_gen(int nr);

    vector<Bloc> filtru_sup(int sup);
};

class RepoFile : public Repo {
private:
    string fname;
    void loadFromFile();
    void saveToFile();
public:
    RepoFile(string filename) : Repo(), fname{ filename } {
        loadFromFile();
    }
    void store(Bloc& b) override {
        Repo::store(b);
        saveToFile();
    }

    void del_repo(Bloc& b) override {
        Repo::del_repo(b);
        saveToFile();
    }

    Bloc modify_repo(Bloc& b) override {
        Bloc bl = Repo::modify_repo(b);
        saveToFile();
    }
};

void test_repo();

string randomStrGen(int length);

int randomInt(int n);


