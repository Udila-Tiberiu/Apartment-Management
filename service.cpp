
#include "service.h"

void Service::add(int apt, string nume, int sup, string tip) {
    Bloc b{ apt,nume,sup,tip };
    rep.store(b);
    list_undo.push_back(new AddUndo{ rep, b });
    notify();
}

vector<Bloc> Service::get_All() {
    return rep.getAll();
}

void Service::generate()
{
    rep.generate();
}

void Service::del_serv(int ap, const string& nume) {
    Bloc sters;
    int i = 0;
    Bloc b{ ap,nume,0,"A" };
    for (auto& bl : rep.getAll()) {
        if (bl == b) {
            sters = bl;
            break;
        }
        else {
            i++;
        }
    }
    rep.del_repo(sters);
    list_undo.push_back(new DeleteUndo{ rep, sters, i });
    notify();
}

void Service::modify_serv(int ap, string nume, int sup, string tip) {
    Bloc b{ ap,nume,sup,tip };
    Bloc mod = rep.modify_repo(b);
    list_undo.push_back(new ModifyUndo{ rep, mod });
    notify();
}

bool Service::get_serv(int ap, string& nume) {
    Bloc b{ ap, nume, 0, "A" };
    return rep.get_repo(b);
}

Bloc Service::get(int ap, string nume)
{
    return rep.get(ap, nume);
}

vector<Bloc> Service::filtru(string nume) {
    return rep.fil_nume(nume);
}

void Service::empty_all() {
    rep.empty_list();
}

vector<Bloc> Service::sort_a() {
    return rep.sort_ap();
}

vector<Bloc> Service::sort_n()
{
    return rep.sort_nume();
}

void Service::random(int nr) {
    rep.random_gen(nr);
}

vector<Bloc> Service::filtru_supr(int sup) {
    return rep.filtru_sup(sup);
}

void Service::undo() {
    if (list_undo.empty()) {
        throw RepoException("Nu se mai poate efectua undo.");
    }
    ActiuneUndo* act = list_undo.back();
    act->doUndo();
    list_undo.pop_back();
    delete act;
}
