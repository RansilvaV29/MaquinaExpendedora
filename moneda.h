#ifndef MONEDA_H
#define MONEDA_H

#include <string>

class Moneda {
public:
    Moneda(double valor, int cantidad, const std::string& nombre);

    double getValor() const;
    int getCantidad() const;
    const std::string& getNombre() const;

    void restarCantidad(int cantidad);
    void sumarCantidad(int cantidad);
   

private:
    double valor_;
    int cantidad_;
    std::string nombre_;
};

#endif // MONEDA_H
