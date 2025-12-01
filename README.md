# Proyecto Tienda de Belleza

Aplicación con **interfaz gráfica (Qt 6)** y **modo consola** para gestionar productos de una tienda de belleza.
Desarrollada en **C++**, con **CMake** y compilador **MinGW**.

---

##  Requisitos

Antes de compilar el proyecto en una nueva PC, asegúrate de tener instalado:

1. **Git**
   Para clonar el repositorio.

   * Descargar: [Git](https://git-scm.com/download/win)
   * Verificar instalación:

     ```powershell
     git --version
     ```

2. **CMake** (≥ 3.22 recomendado)
   Para generar el proyecto.

   * Descargar: [CMake](https://cmake.org/download/)
   * Verificar instalación:

     ```powershell
     cmake --version
     ```

3. **Qt 6 con MinGW**
   Necesario para las ventanas gráficas (Qt Widgets).

   * Descargar: [Qt Online Installer](https://www.qt.io/download-open-source)
   * Durante la instalación, selecciona:

     * Qt 6.x.x (ejemplo: **6.5.3**)
     * Kit de compilación **MinGW 64-bit** (ejemplo: **MinGW 11.2.0**)
   * Verificar que Qt y MinGW están instalados:

     ```powershell
     dir "C:\Qt\6.5.3\mingw_64\bin\uic.exe"
     dir "C:\Qt\Tools\mingw1120_64\bin\g++.exe"
     
     ```

4. **MinGW (si no lo instalaste junto a Qt)**

   * Descargar: [MinGW](https://sourceforge.net/projects/mingw/)
   * Verificar instalación:

     ```powershell
     g++ --version
     ```

---

##  Pasos para compilar

1. Clona el repositorio:

   ```powershell
   git clone https://github.com/vane1499/vanessa.git
   cd vanessa
   ```

2. Entrar a la carpeta de compilación:

   ```powershell
   cd build
   ```

3. Preparacion:

   ```powershell
   cmake .. -G "MinGW Makefiles" ^
     -DCURSES_LIBRARY="C:/pdcurses/wincon/pdcurses.a" ^
     -DCURSES_INCLUDE_PATH="C:/pdcurses"
   ```

4. Cargando para que no haya fallos:

   ```powershell
   mingw32-make -j8
   ```
5. Si todo salio bien, entrar a la carpeta "src" para poder correr desde algun artefacto a escoger
- Para correr la consola:
 ```powershell
   cd vanessa\build\src
   tienda_consola.exe
 ```
 - Para correr la TUI:
 ```powershell
   cd vanessa\build\src
   tienda_tui.exe
 ```
 - Para correr Desktop se tiene que entrar a desktop(es fuera de src):
 ```powershell
  cd vanessa\build\desktop
  tienda_desktop.exe
 ```
 
 ---



##  Resumen de verificaciones

Antes de compilar, revisa que todos los componentes estén instalados:

```powershell
git --version
cmake --version
g++ --version
dir "C:\Qt\6.5.3\mingw_64\bin\uic.exe"
```

Si todos responden sin error, ya puedes compilar el proyecto 🚀

---
# ¡¡¡¡¡CUIDADO!!!!
## Comandos para REINICIAR todos los registros o productos guardados en el proyecto

```powershell
rmdir /s /q build
mkdir build
cd build

cmake .. -G "MinGW Makefiles" ^
 -DCURSES_LIBRARY="C:/pdcurses/wincon/pdcurses.a" ^
 -DCURSES_INCLUDE_PATH="C:/pdcurses"

mingw32-make
```
se reinicia los registros de los productos por que se elimina la carpeta "build", que es donde se esta "data/tienda.db"
{se reinicia la carpeta build cuando se modifica algun CMakeLists.txt}