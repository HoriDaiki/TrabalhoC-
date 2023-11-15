#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Pessoa {
    int codigo;
    string nome;
    string rua;
    string bairro;
    string cidade;
    string estado;
    string cep;
    string celular;
    string email;
    string cpf;
    string rg;
};

// Protótipo das funções
void adicionarPessoa(const Pessoa &pessoa);
Pessoa obterDadosDoUsuario();
void listarPessoas();
void excluirPessoa(int codigo);
void alterarPessoa(int codigo);
vector<Pessoa> carregarPessoas();
void salvarPessoas(const vector<Pessoa> &pessoas);

int main() {
    int escolha;

    do {
        cout << "Escolha uma opção:\n";
        cout << "1. Cadastrar novo usuário\n";
        cout << "2. Consultar usuários cadastrados\n";
        cout << "3. Excluir usuário cadastrado\n";
        cout << "4. Alterar usuário cadastrado\n";
        cout << "5. Sair\n";
        cout << "Escolha: ";
        cin >> escolha;

        switch (escolha) {
        case 1: {
            // Cadastrar novo usuário
            Pessoa pessoa = obterDadosDoUsuario();
            adicionarPessoa(pessoa);
            break;
        }
        case 2:
            // Consultar usuários cadastrados
            listarPessoas();
            break;
        case 3: {
            // Excluir usuário cadastrado
            int codigo;
            cout << "Digite o código do usuário a ser excluído: ";
            cin >> codigo;
            excluirPessoa(codigo);
            break;
        }
        case 4: {
            // Alterar usuário cadastrado
            int codigo;
            cout << "Digite o código do usuário a ser alterado: ";
            cin >> codigo;
            alterarPessoa(codigo);
            break;
        }
        case 5:
            cout << "Saindo do programa. Até mais!\n";
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 5);

    return 0;
}

// Função para adicionar uma pessoa ao arquivo
void adicionarPessoa(const Pessoa &pessoa) {
    ofstream arquivo("dados.txt", ios::app);

    if (arquivo.is_open()) {
        arquivo << pessoa.codigo << ","
                << pessoa.nome << ","
                << pessoa.rua << ","
                << pessoa.bairro << ","
                << pessoa.cidade << ","
                << pessoa.estado << ","
                << pessoa.cep << ","
                << pessoa.celular << ","
                << pessoa.email << ","
                << pessoa.cpf << ","
                << pessoa.rg << "\n";

        cout << "Pessoa adicionada com sucesso!\n";
    } else {
        cerr << "Erro ao abrir o arquivo.\n";
    }

    arquivo.close();
}

// Função para obter os dados da pessoa do usuário
Pessoa obterDadosDoUsuario() {
    Pessoa pessoa;

    cout << "Digite o código: ";
    cin >> pessoa.codigo;

    cout << "Digite o nome: ";
    cin.ignore();
    getline(cin, pessoa.nome);

    cout << "Digite a rua: ";
    getline(cin, pessoa.rua);

    cout << "Digite o bairro: ";
    getline(cin, pessoa.bairro);

    cout << "Digite a cidade: ";
    getline(cin, pessoa.cidade);

    cout << "Digite o estado: ";
    getline(cin, pessoa.estado);

    cout << "Digite o CEP: ";
    getline(cin, pessoa.cep);

    cout << "Digite o celular: ";
    getline(cin, pessoa.celular);

    cout << "Digite o e-mail: ";
    getline(cin, pessoa.email);

    cout << "Digite o CPF: ";
    getline(cin, pessoa.cpf);

    cout << "Digite o RG: ";
    getline(cin, pessoa.rg);

    return pessoa;
}

// Função para listar todas as pessoas no arquivo
void listarPessoas() {
    vector<Pessoa> pessoas = carregarPessoas();

    for (const auto &pessoa : pessoas) {
        cout << pessoa.codigo << ","
             << pessoa.nome << ","
             << pessoa.rua << ","
             << pessoa.bairro << ","
             << pessoa.cidade << ","
             << pessoa.estado << ","
             << pessoa.cep << ","
             << pessoa.celular << ","
             << pessoa.email << ","
             << pessoa.cpf << ","
             << pessoa.rg << "\n";
    }
}

// Função para excluir uma pessoa do arquivo
void excluirPessoa(int codigo) {
    vector<Pessoa> pessoas = carregarPessoas();
    bool pessoaEncontrada = false;

    for (auto it = pessoas.begin(); it != pessoas.end(); ++it) {
        if (it->codigo == codigo) {
            pessoas.erase(it);
            pessoaEncontrada = true;
            cout << "Usuário excluído com sucesso!\n";
            break;
        }
    }

    if (!pessoaEncontrada) {
        cout << "Usuário não encontrado.\n";
    }

    salvarPessoas(pessoas);
}

// Função para alterar uma pessoa do arquivo
void alterarPessoa(int codigo) {
    vector<Pessoa> pessoas = carregarPessoas();
    bool pessoaEncontrada = false;

    for (auto &pessoa : pessoas) {
        if (pessoa.codigo == codigo) {
            cout << "Digite os novos dados para o usuário:\n";
            Pessoa novosDados = obterDadosDoUsuario();
            pessoa = novosDados;
            pessoaEncontrada = true;
            cout << "Usuário alterado com sucesso!\n";
            break;
        }
    }

    if (!pessoaEncontrada) {
        cout << "Usuário não encontrado.\n";
    }

    salvarPessoas(pessoas);
}

// Função para carregar todas as pessoas do arquivo
vector<Pessoa> carregarPessoas() {
    vector<Pessoa> pessoas;
    ifstream arquivo("dados.txt");

    if (arquivo.is_open()) {
        Pessoa pessoa;
        while (arquivo >> pessoa.codigo >> ws && getline(arquivo, pessoa.nome, ',') &&
               getline(arquivo, pessoa.rua, ',') && getline(arquivo, pessoa.bairro, ',') &&
               getline(arquivo, pessoa.cidade, ',') && getline(arquivo, pessoa.estado, ',') &&
               getline(arquivo, pessoa.cep, ',') && getline(arquivo, pessoa.celular, ',') &&
               getline(arquivo, pessoa.email, ',') && getline(arquivo, pessoa.cpf, ',') &&
               getline(arquivo, pessoa.rg)) {
            pessoas.push_back(pessoa);
        }
    } else {
        cerr << "Erro ao abrir o arquivo.\n";
    }

    arquivo.close();
    return pessoas;
}

// Função para salvar todas as pessoas no arquivo
void salvarPessoas(const vector<Pessoa> &pessoas) {
    ofstream arquivo("dados.txt");

    if (arquivo.is_open()) {
        for (const auto &pessoa : pessoas) {
            arquivo << pessoa.codigo << ","
                    << pessoa.nome << ","
                    << pessoa.rua << ","
                    << pessoa.bairro << ","
                    << pessoa.cidade << ","
                    << pessoa.estado << ","
                    << pessoa.cep << ","
                    << pessoa.celular << ","
                    << pessoa.email << ","
                    << pessoa.cpf << ","
                    << pessoa.rg << "\n";
        }
    } else {
        cerr << "Erro ao abrir o arquivo para salvar.\n";
    }

    arquivo.close();
}
