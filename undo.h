#pragma once

#include "entities.h"
#include "repository.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class AddUndo : public ActiuneUndo {
private:
    Bloc b_adaugat;
    Repo& rep;

public:
    AddUndo(Repo& rep, const Bloc& b) : rep{ rep }, b_adaugat{ b } {}

    void doUndo() override {
        rep.del_repo(b_adaugat);
    }
};

class DeleteUndo : public ActiuneUndo {
private:
    Bloc b_sters;
    Repo& rep;
    int i;

public:
    DeleteUndo(Repo& rep, const Bloc& b, int i) : rep{ rep }, b_sters{ b }, i{ i } {}

    void doUndo() override {
        rep.store_in(b_sters, i);
    }
};

class ModifyUndo : public ActiuneUndo {
private:
    Bloc b_mod;
    Repo& rep;

public:
    ModifyUndo(Repo& rep, const Bloc& b) : rep{ rep }, b_mod{ b } {}

    void doUndo() override {
        Bloc bl = rep.modify_repo(b_mod);
    }
};
