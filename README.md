# Proyecto Tienda de Belleza

Aplicación con **interfaz gráfica (Qt 6)** y **modo consola** para gestionar productos de una tienda de belleza.
Desarrollada en **C++**, con **CMake** y compilador **MinGW**.

---

## 🚀 Requisitos

Antes de compilar el proyecto en una nueva PC, asegúrate de tener instalado:

* [CMake](https://cmake.org/download/) (≥ 3.22 recomendado)
* [Qt 6](https://www.qt.io/download-open-source) con **MinGW** (ejemplo: `Qt 6.5.3 MinGW 11.2.0 64-bit`)
* [MinGW](https://sourceforge.net/projects/mingw/) (si no lo tienes con Qt)

⚠️ Asegúrate de que el compilador (`c++.exe` de MinGW) y `cmake.exe` estén en tu **PATH**.

---

## 🛠️ Compilación

1. Clona el repositorio:

   ```powershell
   git clone https://github.com/usuario/tienda-belleza.git
   cd tienda-belleza
   ```

2. Genera la carpeta de compilación con CMake:

   ```powershell
   cmake -S FRONTEND -B build -G "MinGW Makefiles"
   ```

3. Compila el proyecto:

   ```powershell
   cmake --build build
   ```

4. Ejecuta la aplicación:

   ```powershell
   .\build\tienda_belleza.exe
   ```

---

## 💻 Modos de ejecución

### Modo gráfico (por defecto)

Al ejecutar `tienda_belleza.exe`, se abrirá la ventana principal de la aplicación Qt.


---

## 📂 Persistencia de datos

Actualmente el proyecto guarda los datos en memoria, por lo que se pierden al cerrar la aplicación.
Si deseas que la información se mantenga, deberás implementar persistencia en **archivos (CSV/JSON)** o en una **base de datos**.

---

## ✅ Notas

* **No subas la carpeta `build/` al repositorio.** Solo deben versionarse los archivos fuente (`FRONTEND/`, `src/`, `include/`, `ui/`, `CMakeLists.txt`).
* Cada vez que clones el proyecto en una PC nueva, repite los pasos de compilación.

---

