#include <iostream>
#include <stdio.h>
#include "producto.cpp"
#include "maquina.cpp"
#include <Windows.h>
#include <conio.h> // Agregamos esta librería para getch()
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define TECLA_ENTER 13
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int menu(const char titulo[], const char *opciones[], int n){
	int opcionSeleccionada = 1;
	int tecla;
	bool repite = true;
	
	do{
		system("cls");
		gotoxy(5, 3 + opcionSeleccionada);std::cout << "->" << std::endl;
		gotoxy(15, 2);std::cout << titulo;
		for(int i = 0; i < n; ++i){
			gotoxy(10, 4 + i);std::cout<<"["<< i + 1 <<"] |"<< opciones[i];
		}
		do{
			tecla = _getch();
		}while(tecla != TECLA_ARRIBA && tecla != TECLA_ABAJO && tecla != TECLA_ENTER);
		switch(tecla){
			case TECLA_ARRIBA:
				opcionSeleccionada--;
				if(opcionSeleccionada < 1){
					opcionSeleccionada = n;
				}
				break;
			case TECLA_ABAJO:
				opcionSeleccionada++;
				if(opcionSeleccionada > n){
					opcionSeleccionada= 1;
				}
				break;
			case TECLA_ENTER:
				repite = false;
				break;
		}
		
	}while (repite);
	return opcionSeleccionada;
}

int main(){
	srand(time(0));
	MaquinaExpendedora maquina;
	maquina.generarMontoInicial();
    maquina.guardarMontoInicialEnArchivo("monto_inicial.txt");
    maquina.cargarProductosDesdeArchivo("productos.txt");
	bool repite = true;
	int opcion, longitud;
	
	std::string op;
	std::string cadena;
	const char *titulo = "Bienvenido a la maquina expendedora";
	const char *opciones[] = {"Mostrar productos", "Comprar productos", "mostrar saldo en la maquina", "Salir"};
	int n = 4;
	do{
		opcion = menu(titulo, opciones, n);
		switch(opcion){
			case 1:
				printf("\n\n");

				for (const auto& producto : maquina.getProductos()){
					producto.mostrarInformacion();
					std::cout << std::endl;
				}
				getchar();
				break;
			case 2:
				printf("\n\n");
				maquina.realizarVenta();
				getchar();
				break;
			case 3:{
				printf("\n\n");
    			maquina.mostrarSaldoDetallado();
    			break;
			}    			
			case 4:
				printf("\n\n");
				std::cout << "Hasta luego\n";
                repite=false;
                break;
		}
		std::cout<<"presione enter para continuar";
		std::cin.ignore();
		
	}while(repite);
	return 0;
}