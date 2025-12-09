# Versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.10)

# 1. Definir el nombre del proyecto
project(Grafo_Proyecto CXX)

# 2. Especificar el estándar C++ que estás usando (ej. C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 3. Definir la lista de archivos fuente
# Incluye tu archivo principal (main.cpp) y cualquier otro archivo .cpp.
# En tu caso, todo el código parece estar en main.cpp, pero si tuvieras una
# clase Grafo implementada en Grafo.cpp, deberías incluirla.

# Si solo tienes el main.cpp en la raíz:
set(SOURCE_FILES 
    parte-2.cpp
    grafo.cpp
    abierta.cpp
    cerrada.cpp)

# Si tu código fuera modular (e.g., Grafo.cpp y main.cpp):
# set(SOURCE_FILES 
#     main.cpp 
#     Grafo.cpp
# )

# 4. Crear el ejecutable
# El ejecutable se llamará 'grafo_app' (puedes cambiarlo) y usará los archivos en SOURCE_FILES.
add_executable(out ${SOURCE_FILES})

# 5. Configurar directorios de inclusión (si tienes archivos .h en carpetas separadas)
# Si tu archivo Grafo.h está en la raíz, no necesitas esto.
# Si lo movieras a una carpeta 'include':
# include_directories(include)

# 6. Copiar los archivos de datos (Opcional pero útil)
# Para que el ejecutable encuentre los archivos .co y .gr en 'parte-2',
# es buena práctica copiarlos al directorio de compilación (build directory).

# Definir la ruta de los archivos de datos
set(DATA_DIR "${CMAKE_SOURCE_DIR}/parte-2")
set(DEST_DIR "${CMAKE_BINARY_DIR}/parte-2") # Copia al directorio de build

# Crear una función para copiar archivos si no existen (solo si es necesario en tu flujo)
# install(FILES "${DATA_DIR}/USA-road-d.NY.co"
#         "${DATA_DIR}/USA-road-d.NY.gr"
#         DESTINATION "${DEST_DIR}")