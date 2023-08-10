#include "producto.h"
#include <iostream>

Producto::Producto(int identificador, const std::string& nombre, double precio, int cantidad)
    : identificador_(identificador), nombre_(nombre), precio_(precio), cantidad_(cantidad) {}

int Producto::getIdentificador() const {
    return identificador_;
}

std::string Producto::getNombre() const {
    return nombre_;
}


double Producto::getPrecio() const {
    return precio_;
}

int Producto::getCantidad() const {
    return cantidad_;
}

void Producto::venderProducto(int cantidadVendida) {
    cantidad_ -= cantidadVendida;
    if (cantidad_ < 0) {
        cantidad_ = 0;
    }
}

void Producto::mostrarInformacion() const {
	std::cout << identificador_ << std::endl;

    std::cout << "Nombre: " << nombre_ << std::endl;
    std::cout << "Precio: $" << precio_ << std::endl;
    std::cout << "Cantidad disponible: " << cantidad_ << std::endl;
}