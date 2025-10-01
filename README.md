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
   git clone https://github.com/usuario/tienda-belleza.git
   cd tienda-belleza
   ```

2. Genera la carpeta de compilación:

   ```powershell
   cmake -S FRONTEND -B build -G "MinGW Makefiles"
   ```

3. Compila:

   ```powershell
   cmake --build build
   ```

4. Ejecuta:

   ```powershell
   .\build\tienda_belleza.exe
   ```

---

## 💻 Modos de ejecución

* **Modo gráfico (Qt):**

  ```powershell
  .\build\tienda_belleza.exe
  ```

* **Modo consola:**

  ```powershell
  .\build\tienda_belleza.exe --console
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