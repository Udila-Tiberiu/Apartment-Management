#include "entities.h"

int Bloc::getAp() const {
    return apartament;
}

string Bloc::getNume() const {
    return nume_prop;
}

int Bloc::getSup() const {
    return suprafata;
}

string Bloc::getTip() const {
    return tip;
}

bool Bloc::operator==(Bloc& ot) {
    if (ot.getAp() == apartament && ot.getNume() == nume_prop) {
        return true;
    }
    return false;
}

void Bloc::setAp(Bloc& ot) {
    apartament = ot.getAp();
}

void Bloc::setNume(Bloc& ot) {
    nume_prop = ot.getNume();
}

void Bloc::setSup(Bloc& ot) {
    suprafata = ot.getSup();
}

void Bloc::setTip(Bloc& ot) {
    tip = ot.getTip();
}
