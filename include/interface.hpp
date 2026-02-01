#ifndef INTERFACE_HPP
#define INTERFACE_HPP

    #include <iostream>
    #include "banco.hpp"

    class Interface {
    private:
        Banco banco = Banco(); // instância do banco

    public:
        void menu() {
            /*
            Método para exibir o menu principal do sistema bancário
            */
            std::cout << "=== Sistema Bancário ===\n"
                    << "1. Cadastrar Cliente\n"
                    << "2. Remover Cliente\n"
                    << "3. Acessar Cliente\n"
                    << "0. Sair\n"
                    << "Escolha uma opção: ";
            
            std::string entrada;
            std::getline(std::cin, entrada);

            switch (entrada[0]) {
                case '1':
                    // cadastrar cliente
                    cadastrarCliente();
                    break;
                case '2':
                    // remover cliente
                    removerCliente();
                    break;
                case '3':
                    // acessar cliente
                    acessarCliente();
                    break;
                case '0':
                    std::cout << "Saindo do sistema...\n";
                    return;
                default:
                    std::cout << "Opção inválida. Tente novamente.\n";
                    break;
            }
            menu();
        }

        void cadastrarCliente() {
            /*
            Método responsável por mostrar a interface de cadastro de cliente
            */
            std::string nome, cpf, senha, entrada;
            int maxContas;

            std::cout << "=== Cadastro de Cliente ===\n"
                    << "Nome: ";
            std::getline(std::cin, nome);

            std::cout << "CPF: ";
            std::getline(std::cin, cpf);

            std::cout << "Senha: ";
            std::getline(std::cin, senha);

            std::cout << "Maximo de Contas: ";
            try {
                std::getline(std::cin, entrada);
                maxContas = std::stoi(entrada);
            } catch (const std::invalid_argument& e) {
                std::cout << "Erro: valor inválido para máximo de contas\n";
                return;
            }

            Cliente cliente = Cliente(nome, CPF(cpf), senha, maxContas);
            int resultado = banco.cadastrar(cliente);
            switch (resultado) {
                case SUCESSO:
                    std::cout << "Cliente cadastrado com sucesso!\n";
                    break;
                case JA_EXISTE:
                    std::cout << "Cliente já cadastrado!\n";
                    break;
                case CPF_INVALIDO:
                    std::cout << "CPF inválido!\n";
                    break;
            }
        }

        void removerCliente() {
            /*
            Método responsável por mostrar a interface de remoção de cliente
            */
            std::string cpf, senha;
            std::cout << "=== Remoção de Cliente ===\n"
                        << "CPF: ";
            std::getline(std::cin, cpf);
            std::cout << "Senha: ";
            std::getline(std::cin, senha);
            int resultado = banco.remover(CPF(cpf), senha);
            switch (resultado) {
                case SUCESSO:
                    std::cout << "Cliente removido com sucesso!\n";
                    break;
                case NAO_ENCONTRADO:
                    std::cout << "Cliente não encontrado!\n";
                    break;
                case SENHA_INCORRETA:
                    std::cout << "Senha incorreta!\n";
                    break;
            }
        }

        void acessarCliente() {
            /*
            Método responsável por mostrar a interface de acesso ao cliente
            */
            std::string cpf, senha;
            std::cout << "=== Acesso ao Cliente ===\n"
                        << "CPF: ";
            std::getline(std::cin, cpf);
            std::cout << "Senha: ";
            std::getline(std::cin, senha);
            Cliente* cliente = banco.getCliente(CPF(cpf), senha);
            if (cliente == nullptr) {
                std::cout << "Cliente não encontrado ou senha incorreta!\n";
                return;
            }
            clienteMenu(cliente);
        }

        void clienteMenu(Cliente* cliente) {
            /*
            Método para exibir o menu do cliente
            */
            std::cout << "=== Menu do Cliente: " << cliente->getNome() << " ===\n"
                    << "1. Criar Conta\n"
                    << "2. Deletar Conta\n"
                    << "3. Listar Contas\n"
                    << "4. Acessar Conta\n"
                    << "0. Voltar\n"
                    << "Escolha uma opção: ";
            
            std::string entrada;
            std::getline(std::cin, entrada);

            switch (entrada[0]) {
                case '1': 
                    // criar conta
                    criarConta(cliente);
                    break;
                case '2': {
                    // deletar conta
                    delConta(cliente);
                    break;
                }
                case '3':
                    // listar contas
                    listarContas(cliente);
                    break;
                case '4': {
                    // acessar conta
                    acessarConta(cliente);
                    break;
                }
                case '0':
                    return;
                default:
                    std::cout << "Opção inválida. Tente novamente.\n";
                    break;
            }
            clienteMenu(cliente);
        }

        void criarConta(Cliente* cliente) {
            /*
            Método responsável por mostrar a interface de criação de conta
            */
            std::string nome;
            std::cout << "=== Criação de Conta ===\n"
                      << "Nome da Nova Conta: ";
                    std::getline(std::cin, nome);
                    int erro = cliente->criarConta(nome);
                    switch (erro) {
                    case SUCESSO:
                        std::cout << "Conta criada com sucesso!\n";
                        break;
                    case JA_EXISTE:
                        std::cout << "Nome da conta já existe!\n";
                        break;
                    case LIMITE_ATINGIDO:
                        std::cout << "Número máximo de contas atingido!\n";
                        break;
                    default:
                        std::cout << "Um erro inesperado ocorreu!\n";
                        break;
                    }
        }

        void delConta(Cliente* cliente) {
            /*
            Método responsável por mostrar a interface de deleção de conta
            */
            std::string nome;
            std::cout << "=== Deleção de Conta ===\n"
                      << "Nome da Conta a ser deletada: ";
            std::getline(std::cin, nome);
            int erro = cliente->delConta(nome);
            switch (erro) {
                case SUCESSO:
                    std::cout << "Conta deletada com sucesso!\n";
                    break;
                case NAO_ENCONTRADO:
                    std::cout << "Conta não encontrada!\n";
                    break;
                default:
                    std::cout << "Um erro inesperado ocorreu!\n";
                    break;
            }
        }

        void listarContas(Cliente* cliente) {
            /*
            Método responsável por listar as contas do cliente
            */
            std::cout << "=== Contas do Cliente ===\n";
            for (const auto& conta : cliente->getContas()) {
                std::cout << "Conta: " << conta.getNome()
                        << " | Saldo: " << conta.getSaldo() / 100.0 << "\n";
            }
        }

        void acessarConta(Cliente* cliente) {
            /*
            Método responsável por mostrar a interface de acesso à conta
            */
            std::string nome;
            std::cout << "Nome da Conta a ser acessada: ";
            std::getline(std::cin, nome);

            Conta* conta = cliente->getConta(nome);
            if (conta == nullptr) {
                std::cout << "Conta não encontrada!\n";
                return;
            }

            contaMenu(conta);
            return;
        }
        

        void contaMenu(Conta* conta) {
            /*
            Método para exibir o menu da conta
            */
            std::cout << "=== Menu da Conta: " << conta->getNome() << " | Saldo: " << conta->getSaldo() / 100.0 << " ===\n"
                    << "1. Depositar\n"
                    << "2. Sacar\n"
                    << "0. Voltar\n"
                    << "Escolha uma opção: ";
            
            std::string entrada;
            std::getline(std::cin, entrada);

            switch (entrada[0]) {
                case '1':
                    // depositar
                    long long valor;
                    std::cout << "Valor a depositar (em centavos): ";
                    std::cin >> valor;
                    std::cin.ignore(); // limpar o buffer do newline
                    conta->depositar(valor);
                    break;
                case '2':
                    // sacar
                    std::cout << "Valor a sacar (em centavos): ";
                    std::cin >> valor;
                    std::cin.ignore(); // limpar o buffer do newline
                    conta->sacar(valor);
                    break;
                case '0':
                    return;
                default:
                    std::cout << "Opção inválida. Tente novamente.\n";
                    break;
            }
            contaMenu(conta);
        }
    };

#endif // INTERFACE_HPP