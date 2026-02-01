#ifndef CLIENTE_HPP
#define CLIENTE_HPP

    #include <vector>
    #include "cpf.hpp"
    #include "conta.hpp"

    class Cliente {
        /*
        Classe utilizada para representar um cliente do banco
        */
    private:
        std::string nome; // nome do cliente
        CPF cpf; // CPF do cliente
        std::string senha; // senha do cliente
        int maxContas; // número máximo de contas permitidas
        std::vector<Conta> contas = {}; // contas do cliente

        int findConta(const std::string& nome) {
            /*
            Método para encontrar o índice de uma conta pelo nome
            Retorna:
                -1: conta não encontrada
                 i: índice da conta encontrada
            */
            int tamanho = static_cast<int>(contas.size());
            for (int i = 0; i < tamanho; i++)
                if (contas[i].getNome() == nome)
                    return static_cast<int>(i);
            return -1;
        }

    public:
        // construtor
        Cliente(const std::string& nome, const CPF& cpf, const std::string& senha, const int& maxContas)
            : nome(nome), cpf(cpf), senha(senha), maxContas(maxContas) {}

        bool validar(const std::string& senha) {
            /*
            Método para validar a senha do cliente
            Retorna true se a senha estiver correta, false caso contrário
            */
            return this->senha == senha;
        }

        int criarConta(const std::string& nome) {
            /*
            Método para adicionar uma nova conta ao cliente
            Retorna:
                0: sucesso
                2: já existe
                3: limite atingido
            */
            if (findConta(nome) != -1) return JA_EXISTE; // já existe
            if (static_cast<int>(contas.size()) >= maxContas) return LIMITE_ATINGIDO; // limite atingido
            contas.emplace_back(nome); // adicionar conta ao vetor
            return SUCESSO;
        }
        
        int delConta(const std::string& nome) {
            /*
            Método para remover uma conta do cliente
            Retorna:
                -1: não encontrado
                0: sucesso
            */
            int indice = findConta(nome); // encontrar índice da conta
            if (indice == -1) return NAO_ENCONTRADO; // não encontrado
            contas.erase(contas.begin() + indice); // remover conta do vetor
            return SUCESSO;
        }

        // getters
        std::vector<Conta> getContas() {
            return contas;
        }

        std::string getNome() {
            return nome;
        }
        
        CPF getCPF() {
            return cpf;
        }
        
        Conta* getConta(const std::string& nome) {
            /*
            Retorna um ponteiro para a conta correspondente ao nome
            ou nullptr se não encontrada
            */
            int indice = findConta(nome); // encontrar índice da conta
            if (indice == -1) return nullptr; // não encontrado
            return &contas[indice]; // ponteiro para a conta
        }
    };

#endif // CLIENTE_HPP