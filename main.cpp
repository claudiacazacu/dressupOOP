#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <limits>
#include <string>
#include <fstream>
#include <algorithm>

class Articol {
    std::string Nume;
    std::string Tip;
    std::string Culoare;
    int Pret;

public:
    Articol(const std::string& nume, const std::string& tip, const std::string& culoare, int pret)
        : Nume(nume), Tip(tip), Culoare(culoare), Pret(pret) {}

    void GetInfo() const {
        std::cout << "Nume: " << Nume << ", Tip: " << Tip << ", Culoare: " << Culoare << ", Pret: " << Pret << "\n";
    }

    const std::string& GetNume() const { return Nume; }
    const std::string& GetTip() const { return Tip; }
    int GetPret() const { return Pret; }

    friend std::ostream& operator<<(std::ostream& os, const Articol& articol){
        os << articol.Nume << " ";
        os << articol.Tip << " ";
        os << articol.Culoare << " ";
        os << articol.Pret;
        return os;
    }
};


class Dulap{
    std::list<Articol> Articole;
    int Capacitate;
    std::string Proprietar;

    std::list<Articol> ArticoleInceput() const {
        return {
            Articol("Tricou1", "Vara","Alb", 0),
            Articol("Pantaloni1","Vara","Gri", 0),
            Articol("Adidasi1", "Vara","Alb", 0),
            Articol("Hanorac1","Iarna","Alb", 0),
            Articol("Blugi1", "Iarna","Negru", 0),
            Articol("Bocanci1","Iarna","Negru", 0) 
        };
    }

public:
    Dulap(int capacitate, const std::string& proprietar)
    :Articole(ArticoleInceput()), Capacitate(capacitate), Proprietar(proprietar){}

    int CalculeazaValoareTotala() const {
        int valoare = 0;
        for (const auto& articol : Articole) {
            valoare += articol.GetPret();
        }
        return valoare;
    }

    bool EstePlin() const {
        return (int)Articole.size() >= Capacitate;
    }

    void AdaugaArticol(const Articol& articol) {
        Articole.push_back(articol);
    }

    void GetInfo() const {
        std::cout << "Proprietar: " << Proprietar << ", Capacitate: " << Capacitate << "\n";
        std::cout << "Articole:\n";
        for ( const Articol& articol : Articole) {
            articol.GetInfo();
        }
    }

    const std::list<Articol>& GetArticole() const { return Articole; }


    friend std::ostream& operator<<(std::ostream& os, const Dulap& dulap){
        os << "Dulapul lui: " << dulap.Proprietar << "\n"
           << "Capacitatea de : " << dulap.Capacitate << "\n"
           << "Valoare totala: " << dulap.CalculeazaValoareTotala() << "\n"
           << "Articolele: \n";
        for (const auto& articol : dulap.Articole) {
            os << articol << "\n";
        }
        return os;
    }
};

class Personaj {
    std::string Nume;
    std::string Nationalitate;
    int Nivel;
    Dulap dulap;
    int Sold;

public:
    Personaj(const std::string& nume, const std::string& nationalitate, int nivel, int sold=100)
        : Nume(nume), Nationalitate(nationalitate), Nivel(nivel), dulap(15, nume), Sold(sold){}

    Personaj( const Personaj &v2)
    : Nume(v2.Nume), Nationalitate(v2.Nationalitate), Nivel(v2.Nivel), dulap(v2.dulap), Sold(v2.Sold) {}

    Personaj& operator= (const Personaj &altul){
        if( this != &altul) {
            Nume = altul.Nume;
            Nationalitate = altul.Nationalitate;
            Nivel = altul.Nivel;
            dulap = altul.dulap;
            Sold = altul.Sold;
        }
        return *this;
    }

    ~Personaj() {
        std::cout << "Personajul " << Nume << " a fost distrus.\n";
    }

    void GetInfo() const {
        std::cout << "Nume: " << Nume << ", Nationalitate: " << Nationalitate << ", Nivel: " << Nivel << ", Sold: " << Sold << "\n";
        dulap.GetInfo();
    }

    const Dulap& GetDulap() const {
        return dulap;
    }

    bool Cumparaturi(const Articol& articol){
        if (Sold < articol.GetPret()) {
            return false;
        }
        if (dulap.EstePlin()) {
            return false;
        }
        dulap.AdaugaArticol(articol);
        Sold -= articol.GetPret();
        return true;
    }

    int GetSold() const { return Sold; }

    void AfiseazaEchipamentDeSezon(const std::string& sezon) const {
        std::cout << "\nEchipament " << sezon << " al lui " << Nume << ":\n";
        bool gasit = false;
        for (const auto& articol : dulap.GetArticole()) {
            if (articol.GetTip() == sezon) {
                std::cout << "  ";
                articol.GetInfo();
                gasit = true;
            }
        }
        if (!gasit) {
            std::cout << "Nu exista articole de sezonul " << sezon << " in dulap.\n";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Personaj& personaj){
        os << "Numele: "<< personaj.Nume << "\n"
           << "Nationalitatea: "<< personaj.Nationalitate << "\n"  
           << "Nivelul: "<< personaj.Nivel << "\n"
           << "Sold: "<< personaj.Sold << "\n";
        return os;
    }
};


class Animal{
    std::string Nume;
    std::string Specie; 

public:
    Animal(const std::string& nume, const std::string& specie)
        : Nume(nume), Specie(specie) {}

    void GetInfo() const {
        std::cout << "Nume: " << Nume << ", Specie: " << Specie << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Animal& animal){
        os << "Animalutul este "<< animal.Specie
           << " cu numele "<< animal.Nume << "\n";
        return os;
    }
};


class Magazin{
    std::list<Articol> Articole;
    std::string Nume;

    std::list<Articol> Articolele() const {
        return{
            Articol("Tricou1_mag", "Vara", "Negru", 10),
            Articol("Tricou2_mag", "Vara", "Gri", 10),
            Articol("Pantaloni1_mag", "Vara", "Negru", 20),
            Articol("Hanorac1_mag", "Iarna", "Negru", 25),
            Articol("Pantaloni5_mag", "Iarna", "Alb", 30),
            Articol("Adidasi2_mag", "Vara", "Gri", 40),
            Articol("Ochelari de soare", "Vara", "Negru", 15)
        };
    }

public:
    explicit Magazin(const std::string& nume)
    : Articole(Articolele()), Nume(nume) {}

    void GetInfo() const {
        std::cout << "Magazin: " << Nume << "\n";
        std::cout << "Articole disponibile:\n";
        for ( const Articol& articol : Articole) {
            articol.GetInfo();
        }
    }

    const std::list<Articol>& GetArticole() const { return Articole; }

    const Articol* CautaArticol(const std::string& numeArticol) const {
        for (const Articol& articol : Articole) {
            if (articol.GetNume() == numeArticol) {
                return &articol;
            }
        }
        return nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const Magazin& magazin){
        os << "Magazinul: " << magazin.Nume << "\n"
           << "Articolele disponibile: \n";
        for (const auto& articol : magazin.Articole) {
            os << articol << "\n"; 
        }
        return os;
    }
};

int main() {
    std::ifstream fin("tastatura.txt"); 
    if (!fin){
        std::cerr << "N-am putut deschide tastatura.txt\n";
        return 1;
    }

    std::string nume;
    std::vector<std::string> nationalitati = {"Romanian", "French", "Spanish", "Italian"};

    std::cout << "Care vrei sa fie numele personajului?\n";
    std::getline(fin, nume);

    std::cout << "Nationalitatile:\n";
    for(size_t i=0; i < nationalitati.size(); i++){
        std::cout << i+1 << "; " << nationalitati[i] << "\n";
    }

    int optiune;
    while(true){
        std::cout << "Alege nationalitatea: ";
        if (!(fin >> optiune)) { 
            std::cerr << "Eroare la citire sau EOF.\n";
            return 1;
        }
        if (optiune > 0 && optiune <= (int)nationalitati.size()) break;
        std:: cout << "Alegere invalida. Haide sa intelegem din nou!\n";
    }

    Personaj player(nume, nationalitati[optiune - 1], 1, 100);
    Personaj player_default = player;

    std::cout << "\nStarea initiala a Personajului:\n" << player;
    std::cout << "Dulapul initial:\n" << player.GetDulap() << "\n";
    
    std::cout << "Detalii Personaj:\n";
    player.GetInfo();

    player.AfiseazaEchipamentDeSezon("Vara");
    
    std::string rasp2;
    fin >> rasp2;
    if (rasp2 == "Y" || rasp2 == "y") {
        Magazin magazin("Magazinul Jocului");

        std::cout << "\nInformatii Magazin:\n";
        magazin.GetInfo();

        std::cout << "\nArticole Magazin:\n" << magazin << "\n";

        std::cout << "Ai " << player.GetSold() << " bani \n";
        std::cout << "Ce vrei sa cumperi? *introduci numele aici\n";
        
        std::string raspArticol;
        fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(fin, raspArticol);

        const Articol* articolGasit = magazin.CautaArticol(raspArticol);
        
        if (articolGasit) {
            std::cout << "Valoarea dulapului inainte de cumparaturi: " << player.GetDulap().CalculeazaValoareTotala() << "\n";
            
            if (player.Cumparaturi(*articolGasit)){
                std::cout << "Ai cumparat: " << articolGasit->GetNume() << ".\n";
                std::cout << "Soldul tau este acum: " << player.GetSold() << "\n";
            } else {
                std::cout << "Nu s-a putut cumpara. Nu ai suficienti bani sau dulapul este plin.\n";
            }
        } else {
            std::cout << "Articolul **" << raspArticol << "** nu a fost gasit in magazin.\n";
        }
        std::cout << "\nDulapul dupa cumparaturi:\n" << player.GetDulap() << "\n";
    }

    std::cout << "\nTestare Constructor de Copiere:\n";
    Personaj player_iarna(player);
    std::cout << "Noul personaj (copie): " << player_iarna;
    
    std::cout << "\nTestare Operator= de Copiere (Reset):\n";
    player = player_default;
    std::cout << "Personajul principal a fost resetat:\n" << player.GetDulap() << "\n";

    std::cout << "\nTestare Clasa Animal:\n";
    Animal caine("Rex", "Caine");
    Animal pisica("Miau", "Pisica");
    caine.GetInfo(); 
    std::cout << pisica; 

    return 0;
}