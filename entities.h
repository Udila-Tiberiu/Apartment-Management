#pragma once

#include <string>
#include <utility>

using std::string;

class Bloc {
private:
    int apartament;
    string nume_prop;
    int suprafata;
    string tip;
public:
    [[nodiscard]] int getAp() const;

    [[nodiscard]] string getNume() const;

    [[nodiscard]] int getSup() const;

    [[nodiscard]] string getTip() const;

    void setAp(Bloc& ot);

    void setNume(Bloc& ot);

    void setSup(Bloc& ot);

    void setTip(Bloc& ot);

    Bloc(int ap, string nume, int sup, string tip) : apartament{ ap }, nume_prop{ std::move(nume) }, suprafata{ sup }, tip{ std::move(tip) } {}

    Bloc() = default;



    bool operator==(Bloc& ot);
};


