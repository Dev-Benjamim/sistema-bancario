#ifndef CPF_HPP
#define CPF_HPP

    #include <string>
    
    class CPF {
        /*
        Classe utilizada para armazenar e validar CPFs
        */
    private:
        std::string num; // número do CPF
        bool valido; // indicador de validade

        void validar() {
            /*
            Método para validar o CPF
            1. Deve conter 11 dígitos numéricos
            2. Não pode ser uma sequência de números iguais
            3. Deve obedecer o cálculo dos dígitos verificadores
            4. Atualiza o atributo 'valido'
            */
            
            // Remover caracteres não numéricos
            std::string d;
            for (char c : num)
                if (std::isdigit(c)) d += c;

            // Verificar quantidade de dígitos
            if (d.size() != 11) {
                valido = false;
                return;
            }

            // Verificar dse todos os dígitos são iguais
            bool iguais = true;
            for (int i = 1; i < 11; i++)
                if (d[i] != d[0]) {
                    iguais = false;
                    break;
                }

            if (iguais) {
                valido = false;
                return;
            }

            // Calcular dígitos verificadores
            int soma = 0;
            for (int i = 0; i < 9; i++)
                soma += (d[i] - '0') * (10 - i);
            
            int dig1 = (soma * 10) % 11;
            if (dig1 == 10) dig1 = 0;

            soma = 0;
            for (int i = 0; i < 10; i++)
                soma += (d[i] - '0') * (11 - i);
            int dig2 = (soma * 10) % 11;
            if (dig2 == 10) dig2 = 0;

            // Verificar dígitos
            valido = (dig1 == d[9] - '0' && dig2 == d[10] - '0');
        }


    public:
        // construtor
        CPF(const std::string& numero) : num(numero) {
            // Validar ao criar
            validar();
        }
        
        // getters
        std::string getNumero() const {
            return num;
        }

        bool ehValido() const {
            return valido;
        }
    }; // class CPF

#endif // CPF_HPP