#include "repository.h"
#include <algorithm>
#include <fstream>

void Repo::store(Bloc& bloc) {
    for (const auto& b : list) {
        if (b.getAp() == bloc.getAp() && b.getNume() == bloc.getNume()) {
            throw RepoException("Apartamentul exista deja");
        }
    }
    list.push_back(bloc);
}

void Repo::store_in(Bloc& bloc, int i) {
    list.insert(list.begin() + i, bloc);
}

void Repo::generate()
{
    Bloc b1{ 10, "Ana", 400, "mare" };
    Bloc b2{ 12, "Ion", 500, "mic" };
    Bloc b3{ 20, "Ioana", 1000, "mediu" };
    Bloc b4{ 5, "Ana", 700, "mare" };
    Bloc b5{ 8, "Marcel", 900, "mic" };
    Repo::store(b1);
    Repo::store(b2);
    Repo::store(b3);
    Repo::store(b4);
    Repo::store(b5);
}

void Repo::del_repo(Bloc& bloc) {
    int OK = 0, I = 0;
    for (auto& b : list) {
        if (b == bloc) {
            list.erase(list.begin() + I);
            OK = 1;
        }
        I++;
    }
    if (OK == 0) {
        throw RepoException("Apartamentul nu exista.");
    }
}

vector<Bloc>Repo::getAll() {
    return list;
}

Bloc Repo::modify_repo(Bloc& b) {
    int OK = 0;
    Bloc mod;
    for (Bloc& bloc : list) {
        if (bloc == b) {
            mod = bloc;
            bloc.setSup(b);
            bloc.setTip(b);
            OK = 1;
            break;
        }
    }
    if (OK == 0) {
        throw RepoException("Apartamentul nu exista.");
    }
    return mod;
}

bool Repo::get_repo(Bloc& b) {
    auto rez = std::find_if(list.begin(), list.end(), [=](Bloc& bloc) {
        return static_cast<Bloc>(b) == bloc;
        });
    if (rez != list.end()) {
        return true;
    }
    return false;
}

Bloc Repo::get(int ap, string nume)
{
    Bloc b;
    for (Bloc& bloc : list) {
        if (bloc.getAp() == ap && bloc.getNume() == nume) {
            b = bloc;
            break;
        }
    }
    return b;
}

vector<Bloc> Repo::fil_nume(string& nume) {
    vector<Bloc> d;
    std::copy_if(list.begin(), list.end(), std::back_inserter(d), [nume](Bloc& b) {
        return b.getNume() == nume;
        });
    return d;
}

vector<Bloc> Repo::filtru_sup(int sup) {
    vector<Bloc> d;
    std::copy_if(list.begin(), list.end(), std::back_inserter(d), [sup](Bloc& b) {
        return b.getSup() < sup;
        });
    return d;
}

void Repo::empty_list() {
    list.clear();
}

vector<Bloc> Repo::sort_ap() {
    vector<Bloc> v;
    v = list;
    std::sort(v.begin(), v.end(), [](const Bloc& b1, const Bloc& b2) {
        return b1.getAp() < b2.getAp();
        });
    return v;
}

vector<Bloc> Repo::sort_nume()
{
    vector<Bloc> v;
    v = list;
    std::sort(v.begin(), v.end(), [](const Bloc& b1, const Bloc& b2) {
        return b1.getNume() < b2.getNume();
        });
    return v;
}

void Repo::random_gen(int nr) {
    int i = 0;
    while (i < nr) {
        Bloc b{ randomInt(2), randomStrGen(7), randomInt(5), randomStrGen(7) };
        store(b);
        i++;
    }
}


void test_repo() {
    Repo rep;
    Bloc b{ 1,"A",2,"B" };
    rep.store(b);
    auto list = rep.getAll();
    assert(list.size() == 1);
    try {
        rep.store(b);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}

int randomInt(int n) {
    // This program will create some sequence of random
    // numbers on every program run within range 0 to N-1
    int x = rand() % n;
    return x;
}

string randomStrGen(int length) {
    static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string result;
    result.resize(length);

    srand(time(NULL));
    for (int i = 0; i < length; i++)
        result[i] = charset[rand() % charset.length()];

    return result;
}

void RepoFile::loadFromFile() {
    std::ifstream in(fname);
    if (!in.is_open()) {
        throw RepoException("Fisier nu s-a putut deschide:" + fname);
    }
    int ap, sup;
    string nume, tip;
    while (in >> ap >> nume >> sup >> tip) {
        Bloc b{ ap,nume,sup,tip };
        Repo::store(b);
    }
    in.close();
}

void RepoFile::saveToFile() {
    std::ofstream out(fname);
    if (!out.is_open()) {
        throw std::runtime_error("Eroare in deschiderea fisierului.");
    }
    for (auto& b : getAll()) {
        out << b.getAp() << ' ' << b.getNume() << ' ' << b.getSup() << ' ' << b.getTip();
        out << std::endl;
    }
    out.close();
}

