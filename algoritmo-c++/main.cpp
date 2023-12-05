#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

// Estrutura para armazenar as informações de cada item
struct Item
{
    string nome;
    double valor, peso, razaoValorPeso;
};



// Comparar dois itens com base na rua razão valor-peso
bool comparacao(Item a, Item b)
{
    return a.razaoValorPeso > b.razaoValorPeso;
}

// Função para resolver o problema da mochila fracionária
double mochilaFracionaria(vector<Item> &itens, double capacidadeMochila)
{
    // calcular a razao valor-peso para cada item
    for (auto &item : itens)
    {
        item.razaoValorPeso = item.valor / item.peso;
    }

    // ordena os itens pela razao valor-peso usando introSort
    sort(itens.begin(), itens.end(), comparacao);

    double pesoAtual = 0, valorTotal = 0.0;

    // Itera sobre os itens
    for (auto &item : itens)
    {
        double pesoAdicionado = min(item.peso, capacidadeMochila - pesoAtual);
        pesoAtual += pesoAdicionado;
        valorTotal += item.razaoValorPeso * pesoAdicionado;

        cout << "Item: " << item.nome << " adicionado: Valor = " << (item.razaoValorPeso * pesoAdicionado) << ", Peso = " << pesoAdicionado << endl;

        if (pesoAtual == capacidadeMochila)
        {
            cout << "Mochila cheia!" << endl;
            break;
        }
    }

    cout << "Capacidade total da mochila usada: " << pesoAtual << endl;

    return valorTotal;
}

// Função para ler um valor numérico com validação
template <typename T>
T readInput(const string &prompt)
{
    T value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (cin.fail())
        {
            cin.clear();                                         // limpar o erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignorar a entrada invalida
            cout << "Digite um valor valido!" << endl;
        }
        else
        {
            break;
        }
    }
    return value;
}

int main()
{
    double capacidadeMochila = readInput<double>("Insira a capacidade maxima da mochila (KG): ");

    int n = readInput<int>("Quantos itens serao adicionados: ");

    vector<Item> itens(n);

    for (int i = 0; i < n; i++)
    {
        cout << "--------# ADICIONAR NOVO ITEM #--------" << endl;
        cout << "Nome: ";
        cin >> itens[i].nome;
        itens[i].valor = readInput<double>("Valor: ");
        itens[i].peso = readInput<double>("Peso: ");

        cout << "--------# ITEM '" << itens[i].nome << "' ADICIONADO #--------" << endl;
    }

    double valorMaximo = mochilaFracionaria(itens, capacidadeMochila);
    cout << "Valor maximo que pode ser carregado na mochila: " << valorMaximo << endl;

    return 0;
}