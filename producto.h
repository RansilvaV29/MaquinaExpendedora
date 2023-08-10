#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <iostream>
class Producto {
public:
    Producto(int identificador, const std::string& nombre, double precio, int cantidad);

    // Métodos de acceso
    int getIdentificador() const;
    std::string getNombre() const;
    double getPrecio() const;
    int getCantidad() const;
	void mostrarInformacion() const;
    // Método para restar la cantidad de productos vendidos
    void venderProducto(int cantidadVendida);
	
private:
	int identificador_;
    std::string nombre_;
    double precio_;
    int cantidad_;
    
};
#endif // PRODUCTO_H
