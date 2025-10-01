# Tienda Belleza - Frontend Qt (C++)

Proyecto: interfaz gráfica con Qt (Widgets) para gestionar productos de belleza.
## Comandos

1. 
```powershell
cmake -S FRONTEND -B build -G "MinGW Makefiles"
```

 *Este comando configura el proyecto.

-S FRONTEND → le dices a CMake dónde está el código fuente (CMakeLists.txt).

-B build → le dices dónde guardar los archivos de compilación (carpeta build).

-G "MinGW Makefiles" → eliges el generador, en este caso Makefiles para el compilador MinGW.

 *Resultado: CMake analiza tu proyecto y crea todos los Makefiles necesarios para poder compilarlo.

2. 
```powershell
cmake --build build
```

 *Este comando compila el proyecto usando los archivos creados antes.

--build build → le dices que compile desde la carpeta build.

 *Resultado: Genera el archivo ejecutable tienda_belleza.exe dentro de build.

3. 
```powershell
.\build\tienda_belleza.exe
```

 *Este comando ejecuta el programa compilado.

.\build\tienda_belleza.exe → abre el ejecutable que ya se construyó.

 *Resultado: Se abre tu aplicación Qt con las ventanas gráficas (y según cómo lo diseñaste, también puedes usar consola).

## Estructura
FRONTEND/
 ├── data/
 │   └── productos.txt         # Archivo de datos, guarda productos.
 │
 ├── include/                  # Archivos de cabecera (.h)
 │   ├── mainwindow.h          # Clase de la ventana principal (Qt).
 │   ├── product.h             # Clase Producto (atributos y métodos).
 │   ├── store.h               # Clase Tienda (maneja lista de productos).
 │   └── utils.h               # Funciones auxiliares.
 │
 ├── src/                      # Código fuente (.cpp)
 │   ├── console.cpp           # Lógica para modo consola.
 │   ├── main.cpp              # Punto de entrada del programa.
 │   ├── mainwindow.cpp        # Implementación de la ventana principal.
 │   ├── product.cpp           # Implementación de Producto.
 │   ├── store.cpp             # Implementación de Tienda.
 │   └── utils.cpp             # Implementación de utilidades.
 │
 ├── ui/
 │   └── mainwindow.ui         # Archivo Qt Designer → define la ventana.
 │
 ├── CMakeLists.txt            # Configuración de CMake.
 ├── README.md                 # Documentación.
 └── .gitignore                # Archivos a ignorar en Git.

## Requisitos
- CMake >= 3.16
- Qt6 (o Qt5, adaptar CMake)

## Cómo se conecta todo

1. main.cpp

Arranca el programa.

Decide si abre la interfaz gráfica (Qt) o si usa el modo consola.

2. mainwindow.h/.cpp + mainwindow.ui

Son la parte gráfica (ventana principal).

Qt genera código automáticamente a partir de mainwindow.ui para enlazar botones, cuadros de texto, etc.

3. product.h/.cpp

Define qué es un producto (ejemplo: nombre, precio, stock).

4. store.h/.cpp

Maneja una colección de productos.

Agregar, eliminar, buscar, listar.

5. console.cpp

Alternativa al modo gráfico: corre en consola.

6. utils.h/.cpp

Funciones de apoyo (lectura/escritura de archivos, validaciones, etc.).

7. data/productos.txt

Guarda los datos de los productos.

Permite que cuando cierres el programa no se pierda todo.

### En resumen:

- Qt (mainwindow) → interfaz gráfica.

- Consola (console.cpp) → versión por terminal.

- Store/Product → lógica de negocio.

- utils/data → manejo de archivos y persistencia.

- CMake → el pegamento que compila y organiza todo.