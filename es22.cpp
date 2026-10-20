#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Computer {
private:
    static int prossimoCodice;
    int codice;
    string marca, modello;
    double velocitaCPU, monitor;
    int ram, disco, annoAcquisto;

public:
    // costruttore normale: codice automatico
    Computer(string marca, string modello, double vel,
             int ram, int disco, double monitor, int anno)
        : codice(prossimoCodice++), marca(marca), modello(modello),
          velocitaCPU(vel), monitor(monitor), ram(ram),
          disco(disco), annoAcquisto(anno) {}

    // costruttore per il ripristino da file (codice già noto)
    Computer(int cod, string marca, string modello, double vel,
             int ram, int disco, double monitor, int anno)
        : codice(cod), marca(marca), modello(modello),
          velocitaCPU(vel), monitor(monitor), ram(ram),
          disco(disco), annoAcquisto(anno) {
        if (cod >= prossimoCodice) prossimoCodice = cod + 1;
    }

    int getCodice() const { return codice; }
    string getMarca() const { return marca; }
    string getModello() const { return modello; }
    double getVelocitaCPU() const { return velocitaCPU; }
    int getRam() const { return ram; }
    int getDisco() const { return disco; }
    double getMonitor() const { return monitor; }
    int getAnnoAcquisto() const { return annoAcquisto; }
};


int Computer::prossimoCodice = 1;

class Catalogo {
private:
    vector<Computer> computer;

public:
    void aggiungi(const Computer& c) {
        computer.push_back(c);
    }

    bool elimina(int codice) {
        for (size_t i = 0; i < computer.size(); i++) {
            if (computer[i].getCodice() == codice) {
                computer.erase(computer.begin() + i);
                return true;
            }
        }
        return false;
    }

    Computer* cercaPerCodice(int codice) {
        for (auto& c : computer)
            if (c.getCodice() == codice) return &c;
        return nullptr;
    }

    vector<Computer> cercaMigliori(double vel, int ram, int disco) const {
        vector<Computer> risultato;
        for (const auto& c : computer)
            if (c.getVelocitaCPU() >= vel && c.getRam() >= ram && c.getDisco() >= disco)
                risultato.push_back(c);
        return risultato;
    }

    void salva(const string& nomeFile) const {
        ofstream out(nomeFile);
        for (const auto& c : computer) {
            out << c.getCodice() << " " << c.getMarca() << " "
                << c.getModello() << " " << c.getVelocitaCPU() << " "
                << c.getRam() << " " << c.getDisco() << " "
                << c.getMonitor() << " " << c.getAnnoAcquisto() << "\n";
        }
    }

    void ripristina(const string& nomeFile) {
        ifstream in(nomeFile);
        computer.clear();
        int cod, ram, disco, anno;
        string marca, modello;
        double vel, monitor;
        while (in >> cod >> marca >> modello >> vel >> ram >> disco >> monitor >> anno)
            computer.push_back(Computer(cod, marca, modello, vel, ram, disco, monitor, anno));
    }
};