#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100

// Codigos SML
#define READ 10
#define WRITE 11

#define LOAD 20
#define STORE 21

#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

// Funciones
void initMemory(int memory[]);
void loadProgram(int memory[]);
void dump(int accumulator, int instructionCounter, int instructionRegister, 
          int operationCode, int operand, const int memory[]);
void executeProgram(int memory[]);

int main() {
    int memory[MEMORY_SIZE];

    printf("*** BIENVENIDO A SIMPLETRON ***\n");
    
    initMemory(memory);
    loadProgram(memory);
    executeProgram(memory);

    return 0;
}

// Inicializa memoria en 0
void initMemory(int memory[]) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }
}

// Cargra instrcciones
void loadProgram(int memory[]) {
    int instruction;
    int count = 0;

    printf("*** Por favor, introduzca su programa instruccion por instruccion. ***\n");
    printf("*** Teclee 9999 para finalizar la entrada de su programa.          ***\n\n");

    while (count < MEMORY_SIZE) {
        printf("%02d ? ", count);
        if (scanf("%d", &instruction) != 1) {
            printf("*** Error de lectura. Intente de nuevo. ***\n");
            while (getchar() != '\n'); // Limpiar buffer
            continue;
        }

        if (instruction == 9999) {
            break; // 
        }

        // Validacion del rango de palabras
        if (instruction < -9999 || instruction > 9998) {
            printf("*** Palabra invalida. Debe estar entre -9999 y +9998. ***\n");
            continue;
        }

        memory[count] = instruction;
        count++;
    }

    printf("*** Carga del programa completada ***\n");
    printf("*** Iniciando ejecucion del programa ***\n\n");
}

// Muestra los registros y memoria
void dump(int accumulator, int instructionCounter, int instructionRegister, 
          int operationCode, int operand, const int memory[]) {
    printf("\nREGISTROS:\n");
    printf("accumulator          %+05d\n", accumulator);
    printf("instructionCounter      %02d\n", instructionCounter);
    printf("instructionRegister  %+05d\n", instructionRegister);
    printf("operationCode           %02d\n", operationCode);
    printf("operand                 %02d\n\n", operand);

    printf("MEMORIA:\n");
    printf("       0     1     2     3     4     5     6     7     8     9\n");
    for (int i = 0; i < MEMORY_SIZE; i += 10) {
        printf("%02d ", i);
        for (int j = 0; j < 10; j++) {
            printf("%+05d ", memory[i + j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Ciclo de busqueda y ejecucion
void executeProgram(int memory[]) {
    int accumulator = 0;
    int instructionCounter = 0;
    int instructionRegister = 0;
    int operationCode = 0;
    int operand = 0;

    int running = 1;

    while (running && instructionCounter < MEMORY_SIZE) {
        // busqueda
        instructionRegister = memory[instructionCounter];

        // decode
        operationCode = instructionRegister / 100;
        operand = instructionRegister % 100;

        
        instructionCounter++;

        // ejecucion
        switch (operationCode) {
            case READ: {
                int value;
                printf("Ingrese un numero entero: ");
                scanf("%d", &value);
                while (value < -9999 || value > 9999) {
                    printf("Valor fuera de rango (-9999 a 9999). Reintente: ");
                    scanf("%d", &value);
                }
                memory[operand] = value;
                break;
            }
            case WRITE:
                printf("SALIDA: %+05d\n", memory[operand]);
                break;

            case LOAD:
                accumulator = memory[operand];
                break;

            case STORE:
                memory[operand] = accumulator;
                break;

            case ADD:
                accumulator += memory[operand];
                if (accumulator > 9999 || accumulator < -9999) {
                    printf("\n*** ERROR FATAL: Desbordamiento del acumulador ***\n");
                    running = 0;
                }
                break;

            case SUBTRACT:
                accumulator -= memory[operand];
                if (accumulator > 9999 || accumulator < -9999) {
                    printf("\n*** ERROR FATAL: Desbordamiento del acumulador ***\n");
                    running = 0;
                }
                break;

            case DIVIDE:
                if (memory[operand] == 0) {
                    printf("\n*** ERROR FATAL: Intento de division entre cero ***\n");
                    running = 0;
                } else {
                    accumulator /= memory[operand];
                }
                break;

            case MULTIPLY:
                accumulator *= memory[operand];
                if (accumulator > 9999 || accumulator < -9999) {
                    printf("\n*** ERROR FATAL: Desbordamiento del acumulador ***\n");
                    running = 0;
                }
                break;

            case BRANCH:
                instructionCounter = operand;
                break;

            case BRANCHNEG:
                if (accumulator < 0) {
                    instructionCounter = operand;
                }
                break;

            case BRANCHZERO:
                if (accumulator == 0) {
                    instructionCounter = operand;
                }
                break;

            case HALT:
                printf("\n*** Simpletron ejecuto su tarea con exito ***\n");
                running = 0;
                break;

            default:
                printf("\n*** ERROR FATAL: Codigo de operacion invalido (%02d) ***\n", operationCode);
                running = 0;
                break;
        }
    }

    // mostrat registro y memoria al terminar
    dump(accumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
}
