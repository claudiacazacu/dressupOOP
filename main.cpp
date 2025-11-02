#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <limits>
#include <string>
#include <fstream>
//#include <Helper.h>

class Articol {
    std::string Nume;
    std::string Tip;
    std::string Culoare;
    int Pret;


    public:
    Articol(const std::string& nume, const std::string& tip, const std::string& culoare,int pret)
        : Nume(nume), Tip(tip), Culoare(culoare), Pret(pret) {}

    void GetInfo() const {
        std::cout << "Nume: " << Nume << ", Tip: " << Tip << ", Culoare: " << Culoare << ", Pret: " << Pret << "\n";
    }

    const std::string& GetNume() const { return Nume; }
    int GetPret() const { return Pret; }


    friend std::ostream& operator<<(std::ostream& os, const Articol& articol){
        os<<articol.Nume<<" ";
        os<<articol.Tip<<" ";
        os<<articol.Culoare<<" ";
        os<<articol.Pret<<"\n";
        return os;

    }
};


class Dulap{
    std::list<Articol> Articole;
    int Capacitate;
    std::string Proprietar;

    std::list<Articol> ArticoleInceput(){
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
    friend std::ostream& operator<<(std::ostream& os, const Dulap& dulap){
        os<<"Dulapul lui: " << dulap.Proprietar << "\n"
            << "Capacitatea de : " << dulap.Capacitate << "\n"
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

    void GetInfo() const {
        std::cout << "Nume: " << Nume << ", Nationalitate: " << Nationalitate << ", Nivel: " << Nivel << "\n";
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


    //constructorul meu de copiere
    //in contextul jocului meu, vreau ca personajul sa aiba versiunea
    //cu outfit de vara si outfit de iarna
    Personaj( const Personaj &v2)
    : Nume(v2.Nume), Nationalitate(v2.Nationalitate), Nivel(v2.Nivel), dulap(v2.dulap), Sold(v2.Sold) {}

    //operatorul de copiere
    //vreau sa pot da reset la outfitul default
    Personaj& operator= (const Personaj &altul){
        if( this != &altul) {
            Nume = altul.Nume;
            Nationalitate = altul.Nationalitate;
            Nivel = altul.Nivel;
            dulap=altul.dulap;
            Sold = altul.Sold;
            //nu stiu inca ce adaug aici 
        }
        return *this;
    };

    ~Personaj() {
        std::cout << "Personajul " << Nume << " a fost distrus.\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Personaj& personaj){
        os<<"Numele: "<<personaj.Nume <<"\n"
            <<"Nationalitatea: "<<personaj.Nationalitate<<"\n"  
            <<"Nivelul: "<<personaj.Nivel<<"\n";
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
        os<<"Animalutul este "<<animal.Specie
            <<" cu numele "<<animal.Nume<<"\n";
        return os;
    }
};


class Magazin{
    std::list<Articol> Articole;
    std::string Nume;

    std::list<Articol> Articolele(){
        return{
            //top vara
            Articol("Tricou1", "Vara", "Negru", 10),
            Articol("Tricou2", "Vara", "Gri", 10),
            Articol("Tricou3", "Vara", "Albastru", 10),
            Articol("Tricou4", "Vara", "Roz", 10),
        
            //pantaloni vara
            Articol("Pantaloni1", "Vara", "Negru", 20),
            Articol("Pantaloni2", "Vara", "Gri", 20),
            Articol("Pantaloni3", "Vara", "Albastru", 20),
            Articol("Pantaloni4", "Vara", "Roz", 20),

            //top iarna
            Articol("Hanorac1", "Iarna", "Negru", 25),
            Articol("Hanorac2", "Iarna", "Roz", 25),

            //pantaloni iarna
            Articol("Pantaloni5", "Iarna", "Alb", 30),
            Articol("Pantaloni6", "Iarna", "Roz", 30),
            Articol("Pantaloni7", "Iarna", "Gri", 30),

            //pantofi
            Articol("Adidasi2", "Vara", "Gri", 40),
            Articol("Adidasi3", "Vara", "Negru", 40),
            Articol("Sandale", "Vara", "Roz", 35),
            Articol("Bocanci2", "Iarna", "Alb", 50),
            Articol("Cizme", "Iarna", "Gri", 55),

            //accesorii
            Articol("Ochelari de soare", "Vara", "Negru", 15),
            Articol("Sapca", "Vara", "Albastru", 10),
            Articol("Fular", "Iarna", "Rosu", 15),
            Articol("Caciula", "Iarna", "Negru", 12)

        };

    }

    public:
    explicit Magazin(const std::string& nume)
    : Articole(Articolele()), Nume(nume) {
        this->Nume=nume;
    }

    void GetInfo() const {
        std::cout << "Magazin: " << Nume << "\n";
        std::cout << "Articole disponibile:\n";
        for ( const Articol& articol : Articole) {
            articol.GetInfo();
        }
    }

    const std::list<Articol>& GetArticole() const { return Articole; }


    friend std::ostream& operator<<(std::ostream& os, const Magazin& magazin){
        os<<"Magazinul: " << magazin.Nume << "\n"
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
    //char rasp;

    /*while(true){
        std::cout << "START JOC?! (Y/N) : ";
        std::cin >> rasp ;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if(rasp=='Y' || rasp=='y'){
            break;
        }
        else if(rasp=='N' || rasp=='n'){
            std::cout << "Oprim jocul.!\n";
            return 0;
        }
        else{
            std::cout << "Raspuns invalid. Te rog sa alegi Y sau N.\n"; 
        }
    }
        */
    std::string nume;
    std::vector<std::string> nationalitati = {"Romanian", "French", "Spanish", "Italian"};

    std::cout << "Care vrei sa fie numele personajului?\n";
    std::getline(fin, nume);

    std::cout << "Nationalitatile:\n";
    for(size_t i=0; i < nationalitati.size(); i++){
        std::cout << i+1 << "; " << nationalitati[i]<<"\n";
    }

    int optiune;
    while(true){
        std::cout<< "Alege nationalitatea: ";
        fin >> optiune;
        if (optiune > 0 && optiune <= (int)nationalitati.size()) break;
        std:: cout << "Alegere invalida. Haide sa intelegem din nou!\n";
    }

   Personaj player(nume, nationalitati[optiune - 1], 1, 100);

   std::cout << "Dulapul initial al personajului:\n" << player.GetDulap() << "\n";

    std::string rasp2;
    fin>>rasp2;
    if (rasp2 == "Y" || rasp2 == "y") {
        Magazin magazin("Magazinul Jocului");
        std::cout<< magazin << "\n";

        std::cout <<"Ai "<<player.GetSold()<<"bani \n";

        std::cout<<"Ce vrei sa cumperi? *introduci numele aici\n";
        std::string raspArticol;
        fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character from the input buffer
        std::getline(fin, raspArticol);

        const Articol* articolGasit = nullptr;
        for (const Articol& articol : magazin.GetArticole()) {
            if (articol.GetNume() == raspArticol) {
                articolGasit = &articol;
                break;
            }
        }
    if(articolGasit) {
        if(player.Cumparaturi(*articolGasit)){
            std::cout << "Ai cumparat: " << articolGasit->GetNume() << ". Soldul tau este acum: " << player.GetSold() << "\n";
        } else {
            std::cout << "Nu ai suficienti bani sau dulapul este plin.\n";
        }
        } else {
        std::cout << "Articolul nu a fost gasit in magazin.\n";
        }
        std::cout<<"Dulapul acum:\n"<< player.GetDulap() << "\n";

        return 0;
    }
   
    //Personaj personajul1("Anelise", "French", 10);
    //Personaj personajul2("Claudia", "Romanian", 5);
    
    //personajul1.GetInfo();
    //personajul2.GetInfo();
    return 0;
}
