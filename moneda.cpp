#include "moneda.h"

Moneda::Moneda(double valor, int cantidad, const std::string& nombre)
    : valor_(valor), cantidad_(cantidad), nombre_(nombre) {}

double Moneda::getValor() const {
    return valor_;
}

int Moneda::getCantidad() const {
    return cantidad_;
}

const std::string& Moneda::getNombre() const {
    return nombre_;
}

void Moneda::restarCantidad(int cantidad) {
    cantidad_ -= cantidad;
    if (cantidad_ < 0) {
        cantidad_ = 0;
    }
}
void Moneda::sumarCantidad(int cantidad) {
        cantidad_ += cantidad;
}



