#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Carta {
private:
    string nome;
    unsigned long long populacao;
    unsigned long long area;
    unsigned long long idh;
    unsigned long long pib;

    unsigned long long lerNumero(const string& prompt) {
        unsigned long long valor;
        while (true) {
            cout << prompt;
            if (cin >> valor) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return valor;
            } else {
                cout << "Entrada invalida! Por favor, digite um numero valido.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

public:
    Carta() : populacao(0), area(0), idh(0), pib(0) {}

    void lerDados() {
        cout << "Nome da carta: ";
        getline(cin, nome);
        populacao = lerNumero("Populacao: ");
        area = lerNumero("Area: ");
        idh = lerNumero("IDH: ");
        pib = lerNumero("PIB: ");
    }

    unsigned long long calcularSuperPoder() const {
        return populacao + area + idh + pib;
    }

    string getNome() const { return nome; }
    unsigned long long getPopulacao() const { return populacao; }
    unsigned long long getArea() const { return area; }
    unsigned long long getIDH() const { return idh; }
    unsigned long long getPIB() const { return pib; }

    void mostrar() const {
        cout << "Nome: " << nome << " | Populacao: " << populacao
             << " | Area: " << area << " | IDH: " << idh
             << " | PIB: " << pib << endl;
    }
};

void compararPropriedade(const string& propriedade, unsigned long long val1, unsigned long long val2, const string& nome1, const string& nome2, bool maiorVence = true) {
    cout << propriedade << ": ";
    if (maiorVence) {
        if (val1 > val2) cout << nome1 << " vence";
        else if (val1 < val2) cout << nome2 << " vence";
        else cout << "Empate";
    } else {
        if (val1 < val2) cout << nome1 << " vence";
        else if (val1 > val2) cout << nome2 << " vence";
        else cout << "Empate";
    }
    cout << " (" << val1 << " x " << val2 << ")" << endl;
}

void compararCartas(const Carta& c1, const Carta& c2) {
    if (c1.getArea() == 0 || c2.getArea() == 0) {
        cout << "Erro: Area nao pode ser zero para calcular densidade populacional.\n";
        return;
    }

    unsigned long long densidade1 = c1.getPopulacao() / c1.getArea();
    unsigned long long densidade2 = c2.getPopulacao() / c2.getArea();

    cout << "\n=== Comparando " << c1.getNome() << " x " << c2.getNome() << " ===\n";
    compararPropriedade("Densidade Populacional", densidade1, densidade2, c1.getNome(), c2.getNome(), false);
    compararPropriedade("Populacao", c1.getPopulacao(), c2.getPopulacao(), c1.getNome(), c2.getNome());
    compararPropriedade("Area", c1.getArea(), c2.getArea(), c1.getNome(), c2.getNome());
    compararPropriedade("IDH", c1.getIDH(), c2.getIDH(), c1.getNome(), c2.getNome());
    compararPropriedade("PIB", c1.getPIB(), c2.getPIB(), c1.getNome(), c2.getNome());
    compararPropriedade("Super Poder", c1.calcularSuperPoder(), c2.calcularSuperPoder(), c1.getNome(), c2.getNome());
    cout << endl;
}

int main() {
    vector<Carta> cartas;
    int opcao;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Cadastrar nova carta\n";
        cout << "2. Listar cartas cadastradas\n";
        cout << "3. Comparar duas cartas\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            Carta nova;
            cout << "\nCadastro de nova carta:\n";
            nova.lerDados();
            cartas.push_back(nova);
            cout << "Carta cadastrada com sucesso!\n";
        } else if (opcao == 2) {
            cout << "\n=== Cartas cadastradas ===\n";
            if (cartas.empty()) {
                cout << "Nenhuma carta cadastrada.\n";
            } else {
                for (size_t i = 0; i < cartas.size(); ++i) {
                    cout << i + 1 << ". ";
                    cartas[i].mostrar();
                }
            }
        } else if (opcao == 3) {
            if (cartas.size() < 2) {
                cout << "Cadastre pelo menos duas cartas para comparar.\n";
            } else {
                size_t idx1, idx2;
                cout << "\nEscolha o numero da primeira carta: ";
                cin >> idx1;
                cout << "Escolha o numero da segunda carta: ";
                cin >> idx2;
                cin.ignore();

                if (idx1 < 1 || idx1 > cartas.size() || idx2 < 1 || idx2 > cartas.size() || idx1 == idx2) {
                    cout << "Indices invalidos!\n";
                } else {
                    compararCartas(cartas[idx1 - 1], cartas[idx2 - 1]);
                }
            }
        } else if (opcao == 0) {
            cout << "Saindo...\n";
        } else {
            cout << "Opcao invalida!\n";
        }
    } while (opcao != 0);

    return 0;
}
