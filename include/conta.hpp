#ifndef CONTA_HPP
#define CONTA_HPP

    #include <string>
    #include <erros.hpp>

    class Conta {
        /*
        Classe utilizada para representar uma conta bancária
        */
    private:
        std::string nome; // nome identificador da conta
        long long saldo = 0; // saldo em centavos
        
    public:
        // construtor
        Conta(const std::string& nome) : nome(nome) {}

        int depositar(const long long& dinheiro) {
            /*
            Método para depositar dinheiro na conta
            Retorna:
                0: sucesso
            */

            saldo += dinheiro;
            return SUCESSO;
        }
        
        int sacar(const long long& dinheiro) {
            /*
            Método para sacar dinheiro da conta caso tenha saldo suficiente
            retorna:
                0: sucesso
                1: saldo insuficiente
            */

            if (saldo >= dinheiro) return SALDO_INSUFICIENTE; // saldo insuficiente
            saldo -= dinheiro;
            return SUCESSO;
        }

        // getters
        std::string getNome() const {
            return nome;
        }

        long long getSaldo() const {
            return saldo;
        }
    };

#endif // CONTA_HPP