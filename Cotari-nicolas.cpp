#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define medicamentos 10
#define farmacias 100

struct Asignacion {
    int codigo_medicamento;
    int cantidad;
    char farmacia[50];
};

void mostrarAsignaciones(int codigo_medicamento, struct Asignacion asignaciones[farmacias], int cantidad_asignaciones, int precios[medicamentos]) {
    int i;
    int total_asignado = 0;
    int valor_percibir = 0;

    printf("Medicamento: %d\n", codigo_medicamento);
    printf("\n");
    printf("\t\tFarmacia\tCantidad\n");

    for (i = 0; i < cantidad_asignaciones; i++) {
        if (asignaciones[i].codigo_medicamento == codigo_medicamento) {
            int cantidad = asignaciones[i].cantidad;
            char* farmacia = asignaciones[i].farmacia;

            printf("\t\t%s\t%d\n", farmacia, cantidad);

            total_asignado += cantidad;
            valor_percibir += cantidad * precios[i];
        }
    }

    printf("\n");
    printf("Cantidad total: %d\n", total_asignado);
    printf("Monto total: %d\n", valor_percibir);
    printf("\n\n");
}

int main() {
    int medicamento[medicamentos] = {120, 150, 130, 180, 160, 250, 200, 300, 140, 110};
    int precio[medicamentos] = {10, 15, 20, 18, 12, 25, 20, 30, 15, 18};
    struct Asignacion asignaciones[farmacias];
    int cantidad_asignaciones = 0;

    int cantidad, codigo_medicamento;
    char farmacia[50];

    while (1) {
        printf("Ingrese el codigo del medicamento (0 para finalizar): ");
        scanf("%d", &codigo_medicamento);

        if (codigo_medicamento == 0) {
            break;
        }

        int medicamento_existente = 0;
        int i;

        for (i = 0; i < medicamentos; i++) {
            if (medicamento[i] == codigo_medicamento) {
                medicamento_existente = 1;
                break;
            }
        }

        if (medicamento_existente) {
            printf("Ingrese la cantidad del medicamento: ");
            scanf("%d", &cantidad);

            printf("Ingrese el nombre de la farmacia: ");
            scanf("%s", farmacia);

            asignaciones[cantidad_asignaciones].codigo_medicamento = codigo_medicamento;
            asignaciones[cantidad_asignaciones].cantidad = cantidad;
            strcpy(asignaciones[cantidad_asignaciones].farmacia, farmacia);
            cantidad_asignaciones++;
        } else {
            printf("Código inexistente\n");
        }
    }

    int i;
    int menor_asignacion = farmacias + 1;
    int medicamento_menos_ingresado = 0;
    int medicamento_asignado[medicamentos] = {0};

    for (i = 0; i < cantidad_asignaciones; i++) {
        medicamento_asignado[asignaciones[i].codigo_medicamento] = 1;
    }

    for (i = 0; i < medicamentos; i++) {
        int codigo_medicamento = medicamento[i];

        if (!medicamento_asignado[codigo_medicamento]) {
            continue;
        }

        mostrarAsignaciones(codigo_medicamento, asignaciones, cantidad_asignaciones, precio);

        int cantidad_total = 0;
        int j;
        for (j = 0; j < cantidad_asignaciones; j++) {
            if (asignaciones[j].codigo_medicamento == codigo_medicamento) {
                cantidad_total += asignaciones[j].cantidad;
            }
        }

        if (cantidad_total < menor_asignacion) {
            menor_asignacion = cantidad_total;
            medicamento_menos_ingresado = codigo_medicamento;
        }
    }

    if (cantidad_asignaciones == 1) {
        medicamento_menos_ingresado = asignaciones[0].codigo_medicamento;
        menor_asignacion = asignaciones[0].cantidad;
    }

    printf("El medicamento que tuvo la menor asignacion es: %d con una cantidad de %d\n", medicamento_menos_ingresado, menor_asignacion);
    printf("Los medicamentos SIN asignar son -> ");
    for (i = 0; i < medicamentos; i++) {
        if (!medicamento_asignado[medicamento[i]]) {
            printf("%d ", medicamento[i]);
        }
    }

    return 0;
}

