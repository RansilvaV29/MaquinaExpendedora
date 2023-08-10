#include "maquina.h"
#include "producto.h"
#include "moneda.cpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <iomanip> // para formatear la salida del archivo
#include <ctime>
#include <conio.h>
#include <map>

MaquinaExpendedora::MaquinaExpendedora() {}

int generarNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

void MaquinaExpendedora::generarMontoInicial() {
    // Generar cantidades aleatorias para cada billete y moneda
    int billete10 = generarNumeroAleatorio(0, 100);
    int billete5 = generarNumeroAleatorio(0, 100);
    int billete1 = generarNumeroAleatorio(0, 100);
    int moneda1 = generarNumeroAleatorio(0, 100);
    int moneda50 = generarNumeroAleatorio(0, 100);
    int moneda25 = generarNumeroAleatorio(0, 100);
    int moneda10 = generarNumeroAleatorio(0, 100);
    int moneda5 = generarNumeroAleatorio(0, 100);
    int moneda1centavo = generarNumeroAleatorio(0, 100);

    // Guardar los valores en el vector 'monedas_'
    monedas_.emplace_back(10.0, billete10, "Billete de");
    monedas_.emplace_back(5.0, billete5, "Billete de");
    monedas_.emplace_back(1.0, billete1, "Billete de");
    monedas_.emplace_back(1.0, moneda1, "Moneda de");
    monedas_.emplace_back(0.5, moneda50, "Moneda de");
    monedas_.emplace_back(0.25, moneda25, "Moneda de");
    monedas_.emplace_back(0.10, moneda10, "Moneda de");
    monedas_.emplace_back(0.05, moneda5, "Moneda de");
    monedas_.emplace_back(0.01, moneda1centavo, "Moneda de");
}
void MaquinaExpendedora::mostrarSaldoDetallado() {
    std::cout << "Saldo detallado de la máquina:" << std::endl;
    
    for (const Moneda& moneda : monedas_) {
        std::cout << moneda.getCantidad() << " " << moneda.getNombre() << " " << moneda.getValor() << std::endl;
    }
}
void MaquinaExpendedora::guardarMontoInicialEnArchivo(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    // Guardar los valores en el archivo de texto
    for (const Moneda& moneda : monedas_) {
        archivo <<moneda.getCantidad() << " " << moneda.getNombre() << " " << moneda.getValor() << std::endl;
    }

    archivo.close();
}

void MaquinaExpendedora::cargarProductosDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        int identificador;
        std::string nombre;
        double precio;
        int cantidad;

        if ((ss >> identificador) &&
            (ss.ignore() && std::getline(ss, nombre, ',')) &&
            (ss >> precio) &&
            (ss.ignore() && (ss >> cantidad))) {
            productos_.emplace_back(identificador, nombre, precio, cantidad);
        } else {
            std::cerr << "Error en el formato de linea: " << linea << std::endl;
        }
    }

    archivo.close();
}
void MaquinaExpendedora::actualizarMontoInicial(double montoAAnadir) {
    double montoExistente = 0.0;  

    montoExistente += montoAAnadir;

    std::ofstream archivo("monto_inicial.txt");
    if (archivo.is_open()) {
        archivo << montoExistente;
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo para actualizar el monto inicial." << std::endl;
    }
    montoExistente += montoAAnadir;
    std::ofstream archivoSalida("monto_inicial.txt");
    if (archivoSalida.is_open()) {
        archivoSalida << montoExistente;
        archivoSalida.close();
    } else {
        std::cout << "No se pudo abrir el archivo para actualizar el monto inicial." << std::endl;
    }

}
void MaquinaExpendedora::guardarProductosEnArchivo(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    for (const Producto& producto : productos_) {
        archivo << producto.getIdentificador() << ","
               << producto.getNombre() << ","
               << producto.getPrecio() << ","
               << producto.getCantidad() << std::endl;
    }

    archivo.close();
}

Producto* MaquinaExpendedora::buscarProductoPorIdentificador(int identificador) {
    for (auto& producto : productos_) {
        if (producto.getIdentificador() == identificador) {
            return &producto;
        }
    }
    return nullptr;
}

int validarEntradaNumerica() {
    int valor = 0;
    char ch;
    
    while (true) {
        ch = _getch();
        
        if (ch >= '0' && ch <= '9') {
            std::cout << ch;
            valor = valor * 10 + (ch - '0');
        } else if (ch == 13) { // Enter
            break;
        }
    }


    std::cout << std::endl; // Imprime una nueva línea después de la validación

    return valor;
}
double validarEntradaNumericaConDecimales() {
    double valor = 0.0;
    char ch;
    int digitosEnteros = 0;
    int digitosDecimales = 0;
    bool decimalEncontrado = false;
    
    while (true) {
        ch = _getch();
        
        if (ch >= '0' && ch <= '9') {
            if (!decimalEncontrado) {
                if (digitosEnteros < 10) { // Máximo 10 dígitos enteros
                    std::cout << ch;
                    valor = valor * 10 + (ch - '0');
                    digitosEnteros++;
                }
            } else {
                if (digitosDecimales < 2) { // Máximo 2 dígitos decimales
                    std::cout << ch;
                    valor = valor + (ch - '0') * pow(10, -digitosDecimales);
                    digitosDecimales++;
                }
            }
        } else if (ch == '.' && !decimalEncontrado) {
            std::cout << ch;
            decimalEncontrado = true;
        } else if (ch == 13) { // Enter
            break;
        }
    }

    std::cout << std::endl; // Imprime una nueva línea después de la validación

    return valor;
}

double MaquinaExpendedora::procesarCobro() {
    std::cout << "\nOpciones de denominaciones:\n";
    std::cout << "1. Billete de 10 dolares\n";
    std::cout << "2. Billete de 5 dolares\n";
    std::cout << "3. Billete de 1 dolares\n";
    std::cout << "4. Moneda de 1 dolar\n";
    std::cout << "5. Moneda de 50 centavos\n";
    std::cout << "6. Moneda de 25 centavos\n";
    std::cout << "7. Moneda de 10 centavos\n";
    std::cout << "8. Moneda de 5 centavos\n";
    std::cout << "9. Moneda de 1 centavo\n";
    std::cout << "0. Finalizar y pagar\n";
    
    double montoRecibido = 0.0;
    int opcion;
    do {
        std::cout << "\nIngrese la opcion de denominacion: ";
        std::cin >> opcion;
        
        switch (opcion) {
    		case 1: montoRecibido += 10.0; monedas_[0].sumarCantidad(1); break;  // Billete de 1 dolar
    		case 2: montoRecibido += 5.0; monedas_[1].sumarCantidad(1); break;  // Billete de 5 dolares
   			case 3: montoRecibido += 1.0; monedas_[2].sumarCantidad(1); break; // Billete de 10 dolares
    		case 4: montoRecibido += 1.0; monedas_[3].sumarCantidad(1); break;  // Moneda de 1 dolar
    		case 5: montoRecibido += 0.5; monedas_[4].sumarCantidad(1); break;  // Moneda de 50 centavos
    		case 6: montoRecibido += 0.25; monedas_[5].sumarCantidad(1); break; // Moneda de 25 centavos
    		case 7: montoRecibido += 0.10; monedas_[6].sumarCantidad(1); break; // Moneda de 10 centavos
    		case 8: montoRecibido += 0.05; monedas_[7].sumarCantidad(1); break; // Moneda de 5 centavos
    		case 9: montoRecibido += 0.01; monedas_[8].sumarCantidad(1); break; // Moneda de 1 centavo
    		case 0: break; // Finalizar y pagar
			}

		std::cout << "Monto recibido: $" << montoRecibido << std::endl;
    } while (opcion != 0 );
	std::cout<<"total que se introdujo: "<<montoRecibido<<std::endl;
	actualizarCantidadesEnArchivo("monto_inicial.txt");

    return montoRecibido;

    
}
std::string decimalToWords(double num) {
    std::string unidades[] = {"", "un", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};
    std::string decenas[] = {"", "", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"};
    std::string decenasEspeciales[] = {"diez", "once", "doce", "trece", "catorce", "quince", "dieciséis", "diecisiete", "dieciocho", "diecinueve"};
    std::string centenas[] = {"", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos"};
    std::string miles[] = {"", "mil", "millón", "mil millones", "billón", "mil billones", "trillón", "mil trillones"};

    if (num == 0.0) {
        return "cero";
    }

    std::string resultado;

    if (num < 0) {
        resultado += "menos ";
        num = -num;
    }

    int parteEntera = static_cast<int>(num);
    int parteDecimal = static_cast<int>((num - parteEntera) * 100);

    int indiceActual = 0;

    while (parteEntera > 0) {
        if (parteEntera % 1000 != 0) {
            resultado = miles[indiceActual] + " " + resultado;
        }

        int centenasParte = parteEntera % 1000 / 100;
        int decenasParte = parteEntera % 100 / 10;
        int unidadesParte = parteEntera % 10;

        if (centenasParte > 0) {
            resultado += centenas[centenasParte] + " ";
        }

        if (decenasParte > 0) {
            if (decenasParte == 1 && unidadesParte > 0) {
                resultado += decenasEspeciales[unidadesParte] + " ";
                unidadesParte = 0;
            } else {
                resultado += decenas[decenasParte] + " ";
            }
        }

        if (unidadesParte > 0) {
            resultado += unidades[unidadesParte] + " ";
        }

        parteEntera /= 1000;
        indiceActual++;
    }

    resultado = resultado + "dolares ";

    if (parteDecimal > 0) {
        resultado = resultado + "con " + std::to_string(parteDecimal) ;
    }

    return resultado;
}

void MaquinaExpendedora::realizarVenta() {
    std::cout << "Ingrese el numero identificador del producto que desea comprar: ";
    int identificador = validarEntradaNumerica();
    Producto* producto = buscarProductoPorIdentificador(identificador);
    if (producto == nullptr) {
        std::cout << "El producto no existe o no esta disponible." << std::endl;
        return;
    }

    std::cout << "Ingrese la cantidad deseada del producto: ";
    int cantidadDeseada = validarEntradaNumerica();

    if (cantidadDeseada <= 0) {
        std::cout << "La cantidad debe ser mayor que cero." << std::endl;
        return;
    }

    if (cantidadDeseada > producto->getCantidad()) {
        std::cout << "No hay suficientes unidades disponibles del producto." << std::endl;
        return;
    }

    double totalAPagar = producto->getPrecio() * cantidadDeseada;
    std::cout << "Total a pagar: $" << totalAPagar << std::endl;
    std::cout << "introduzca el dinero porfavor" << std::endl;
    double totalIngresado = procesarCobro();
    if (totalIngresado>20.00){
    	std::cout<<"la maquina no aceptra valores mayopres a 20"<<std::endl;
    	return;
	}
    double cambio = totalIngresado - totalAPagar;
    if(cambio<0.00){
    	std::cout<<"se introdujo mal el dinero devolviendo"<<std::endl;
    	return;
	}else{
	    std::string cambioEnLetras = decimalToWords(cambio);
		std::cout<<"este es el cambio a dar: "<<cambioEnLetras<<std::endl;
	}
    std::cout << std::fixed << std::setprecision(2);
    

    calcularCambio(cambio);
    producto->venderProducto(cantidadDeseada);
	guardarProductosEnArchivo("productos.txt");
    std::cout << "Venta realizada con exito." << std::endl;

}




std::string convertirNumeroALetras(double numero) {
        // Definir el diccionario de correspondencias entre números y palabras
        std::map<double, std::string> numerosEnLetras = {
            {10.0, "diez dolares"},
            {5.0, "cinco dolares"},
            {1.0, "un dolar"},
            {1.0, "un dolar"},
            {0.5, "cincuenta centavos"},
            {0.25, "veinticinco centavos"},
            {0.10, "diez centavos"},
            {0.05, "cinco centavos"},
            {0.01, "un centavos"},
            // Agrega más valores y sus representaciones en palabras aquí
        };

        // Buscar el número en el diccionario y devolver su representación en palabras
        auto it = numerosEnLetras.find(numero);
        if (it != numerosEnLetras.end()) {
            return it->second;
        } else {
            std::stringstream ss;
            ss << numero;
            return ss.str(); // Si no se encuentra en el diccionario, devolver el número como cadena
        }
    }
    
void MaquinaExpendedora::calcularCambio(double cambio) {
    std::cout << "Calculando cambio..." << std::endl;
    std::sort(monedas_.begin(), monedas_.end(), [](const Moneda& a, const Moneda& b) {
        return a.getValor() > b.getValor();
    });

    double cambioOriginal = cambio; // Guardar el cambio original para una posible devolución

    for (auto& moneda : monedas_) {
        int cantidadUsada = 0;

        // Considerar las denominaciones suficientemente pequeñas para decimales
        if (moneda.getValor() <= cambio + 0.0001) {
            cantidadUsada = static_cast<int>(cambio / moneda.getValor());
            if (cantidadUsada > 0 && cantidadUsada <= moneda.getCantidad()) {
                std::cout << "Entregar " << cantidadUsada << " de " << convertirNumeroALetras(moneda.getValor()) << "($" << moneda.getValor() <<")" <<std::endl;
                moneda.restarCantidad(cantidadUsada);
                cambio -= cantidadUsada * moneda.getValor();
            }
        }
    }

    if (cambio < 0.00) {
        std::cout << "No hay suficientes monedas y billetes para dar el cambio." << std::endl;
        std::cout << "Devolviendo $" << cambioOriginal << std::endl;
		return;
        // Realizar la devolución de dinero aquí (si tienes una función para ello)
    }

    actualizarCantidadesEnArchivo("monto_inicial.txt");
}
    
void MaquinaExpendedora::actualizarCantidadesEnArchivo(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    for (const auto& moneda : monedas_) {
        archivo <<moneda.getCantidad() << " " << moneda.getNombre() << " " << moneda.getValor() << std::endl;
    }

    archivo.close();
}

const std::vector<Producto>& MaquinaExpendedora::getProductos() const {
    return productos_;
}

void MaquinaExpendedora::guardarDatosEnArchivo(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    for (const auto& moneda : monedas_) {
        archivo << moneda.getValor() << " " << moneda.getCantidad() << std::endl;
    }

    archivo.close();
}


double MaquinaExpendedora::calcularTotalDinero(double montoAAnadir) {
    double total = 0.0;

    for (const Moneda& moneda : monedas_) {
        total += moneda.getValor() * moneda.getCantidad();
    }
	total += montoAAnadir;
    return total;
}