#ifndef BANCO_HPP
#define BANCO_HPP

    #include "cliente.hpp"

    class Banco {
        /*
        Classe para fazer o gerenciamento dos clientes do banco
        */
    private:
        std::vector<Cliente> clientes = {}; // vetor de clientes

        int findCliente(const CPF& cpf) {
            /*
            Método para encontrar o índice de um cliente pelo CPF
            Retorna:
                -1: cliente não encontrado
                 i: índice do cliente encontrado
            */
            int tamanho = static_cast<int>(clientes.size());
            for (int i = 0; i < tamanho; i++)
                if (clientes[i].getCPF().getNumero() == cpf.getNumero())
                    return static_cast<int>(i);
            return NAO_ENCONTRADO;
        }

    public:
        int cadastrar(Cliente& cliente) {
            /*
            Método para adicionar um novo cliente ap banco
            Retorna:
                0: sucesso
                2: já existe
                4: CPF inválido
            */
            if (findCliente(cliente.getCPF()) != -1) return JA_EXISTE; // já existe
            if (!cliente.getCPF().ehValido()) return CPF_INVALIDO; // CPF inválido
            clientes.push_back(cliente); // adicionar cliente ao vetor
            return SUCESSO;
        }

        int remover(const CPF& cpf, const std::string& senha) {
            /*
            Método para remover um cliente do banco
            Retorna:
                -1: não encontrado
                0: sucesso
                5: senha incorreta
            */
            int indice = findCliente(cpf); // encontrar índice do cliente
            if (indice == NAO_ENCONTRADO) return NAO_ENCONTRADO; // não encontrado
            if (!clientes[indice].validar(senha)) return SENHA_INCORRETA; // senha incorreta
            clientes.erase(clientes.begin() + indice); // remover cliente do vetor
            return SUCESSO;
        }

        Cliente* getCliente(const CPF& cpf, const std::string& senha) {
            /*
            Retorna um ponteiro para o cliente correspondente ao CPF,
            nullptr se não encontrado ou se a senha estiver incorreta
            */
            int indice = findCliente(cpf); // encontrar índice do cliente
            if (indice == NAO_ENCONTRADO) return nullptr; // não encontrado
            if (!clientes[indice].validar(senha)) return nullptr; // senha incorreta
            return &clientes[indice]; // ponteiro para o cliente
        }
    };

#endif // BANCO_HPP