#include <iostream>
#include <cstdlib> // Para malloc y free

using namespace std;

// Definición de la estructura Cliente
struct Cliente {
    int numeroCuenta;
    int tipoCuenta; // 1 para preferencial, 2 para tradicional
    Cliente* siguiente; // Puntero al siguiente cliente en la fila
};

class GestorFilasEspera {
private:
    Cliente* inicioTradicional;
    Cliente* finTradicional;
    Cliente* inicioPreferencial;
    Cliente* finPreferencial;
    int turnoTradicional;
    int turnoPreferencial;

    // Método para transferir cliente de la fila tradicional a la preferencial
    void transferirCliente() {
        if (contarClientes(inicioTradicional) >= 3 && contarClientes(inicioPreferencial) <= 2) {
            Cliente* clienteTransferido = inicioTradicional;
            inicioTradicional = inicioTradicional->siguiente;
            clienteTransferido->siguiente = nullptr;
            clienteTransferido->numeroCuenta = ++turnoPreferencial;
            if (inicioPreferencial == nullptr) {
                inicioPreferencial = finPreferencial = clienteTransferido;
            } else {
                finPreferencial->siguiente = clienteTransferido;
                finPreferencial = clienteTransferido;
            }
        }
    }

public:
    // Constructor
    GestorFilasEspera() : inicioTradicional(nullptr), finTradicional(nullptr), inicioPreferencial(nullptr), finPreferencial(nullptr), turnoTradicional(1), turnoPreferencial(1) {}

    // Método para registrar un nuevo cliente
    void registrarCliente(int numeroCuenta, int tipoCuenta) {
        Cliente* nuevoCliente = (Cliente*)malloc(sizeof(Cliente));
        nuevoCliente->numeroCuenta = (tipoCuenta == 1) ? turnoPreferencial++ : turnoTradicional++;
        nuevoCliente->tipoCuenta = tipoCuenta;
        nuevoCliente->siguiente = nullptr;

        if (tipoCuenta == 1) {
            if (inicioPreferencial == nullptr) {
                inicioPreferencial = finPreferencial = nuevoCliente;
            } else {
                finPreferencial->siguiente = nuevoCliente;
                finPreferencial = nuevoCliente;
            }
        } else {
            if (inicioTradicional == nullptr) {
                inicioTradicional = finTradicional = nuevoCliente;
            } else {
                finTradicional->siguiente = nuevoCliente;
                finTradicional = nuevoCliente;
            }
            transferirCliente(); // Verificar si es necesario transferir un cliente
        }
    }

    // Método para visualizar las filas de espera
    void visualizarFilas() {
        cout << "Clientes en la fila tradicional:" << endl;
        visualizarFila(inicioTradicional);
        cout << "Clientes en la fila preferencial:" << endl;
        visualizarFila(inicioPreferencial);
    }

private:
    // Método para visualizar una fila de clientes
    void visualizarFila(Cliente* inicioFila) {
        int turno = 1;
        Cliente* temp = inicioFila;
        while (temp != nullptr) {
            cout << "Turno " << temp->numeroCuenta << ": Cuenta " << temp->numeroCuenta << endl;
            temp = temp->siguiente;
        }
        cout << endl;
    }

    // Método para contar el número de clientes en una fila
    int contarClientes(Cliente* inicioFila) {
        int contador = 0;
        Cliente* temp = inicioFila;
        while (temp != nullptr) {
            contador++;
            temp = temp->siguiente;
        }
        return contador;
    }
};

int main() {
    GestorFilasEspera gestor;

    // Ejemplo de registro de clientes
    gestor.registrarCliente(1001, 2);
    gestor.registrarCliente(1002, 2);
    gestor.registrarCliente(2001, 1);
    gestor.registrarCliente(1003, 2); // Se traslada a la fila preferencial
    gestor.registrarCliente(1004, 2);
    gestor.registrarCliente(1005, 2);
    gestor.registrarCliente(1006, 2);
    gestor.registrarCliente(1007, 2);
    gestor.registrarCliente(1008, 2);
    gestor.registrarCliente(1009, 2); // Se traslada a la fila preferencial

    // Visualización de las filas de espera
    gestor.visualizarFilas();

    return 0;
}