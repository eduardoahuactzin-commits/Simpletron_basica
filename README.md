# Simulador de Computadora Simpletron (SML)

Simulador funcional de la computadora hipotética **Simpletron** desarrollado en lenguaje C/C++. Este sistema permite cargar, decodificar y ejecutar programas escritos en el lenguaje máquina Simpletron Machine Language (SML), administrando una memoria de 100 posiciones y manejando errores de ejecución.

## Requisitos e Implementación
- **Memoria:** Arreglo de 100 posiciones (`00` a `99`).
- **Registros:** `accumulator`, `instructionCounter`, `instructionRegister`, `operationCode`, `operand`.
- **SML Operaciones:** Soporta las 12 instrucciones estándar de entrada/salida, carga/almacenamiento, aritmética y transferencia de control.
- **Validación y Manejo de Errores:** Control de rango en palabras (`-9999` a `+9998`), desbordamiento de acumulador, división entre cero y códigos de operación inválidos con vaciado de memoria (*dump*).

## Instrucciones de Compilación y Ejecución

### Compilación
Abrir el archivo `Simpletron Basica Eduardo Ahuactzin.cpp` en Dev-C++ y presionar **F11** (Compilar y Ejecutar), o mediante GCC:
```bash
gcc -Wall -Wextra -std=c99 "Simpletron Basica Eduardo Ahuactzin.cpp" -o simpletron
