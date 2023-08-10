#ifndef MAQUINA_EXPENDEDORA_H
#define MAQUINA_EXPENDEDORA_H
#include <vector>
#include <iostream>
#include "producto.h"
#include "moneda.h"
class MaquinaExpendedora {
public:
    MaquinaExpendedora();


    // Métodos para cargar los productos y las monedas desde archivos
    void cargarProductosDesdeArchivo(const std::string& nombreArchivo);
    void cargarMonedasDesdeArchivo(const std::string& nombreArchivo);

    // Método para mostrar el menú de productos y realizar una venta
    void realizarVenta();
    const std::vector<Producto>& getProductos() const;
	void generarMontoInicial();
	void guardarMontoInicialEnArchivo(const std::string& nombreArchivo);
	Producto* buscarProductoPorIdentificador(int identificador);
    void calcularCambio(double cambio);
    void actualizarCantidadesEnArchivo(const std::string& nombreArchivo);
	void actualizarMontoInicial(double montoAAnadir);

    void mostrarSaldoDetallado();

    void guardarProductosEnArchivo(const std::string& nombreArchivo);

    void guardarDatosEnArchivo(const std::string& nombreArchivo);
    double calcularTotalDinero(double montoAAnadir);
    
    double procesarCobro();


private:
    std::vector<Producto> productos_;
    std::vector<Moneda> monedas_;
    double montoInicial_;

    // Métodos privados para buscar productos y realizar cálculos
    
};
#endif // MAQUINA_EXPENDEDORA_H
