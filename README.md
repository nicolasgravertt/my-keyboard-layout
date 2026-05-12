# Guía Simple QMK Lily58 Pro (Mechboards)

# 1. Instalar programas

Instalar:

- QMK MSYS
- QMK Toolbox

Sitios oficiales:

- QMK MSYS: https://msys.qmk.fm/
- QMK Toolbox: https://qmk.fm/toolbox

---

# 2. Abrir QMK MSYS

Abrir “QMK MSYS”.

Ir a la carpeta del firmware:

```bash
cd qmk_firmware
```

---

# 3. Verificar teclado

Listar variantes disponibles:

```bash
qmk list-keyboards | grep lily58
```

En este caso se usa:

```bash
mechboards/lily58/pro
```

---

# 4. Crear carpeta del keymap

Crear carpeta personalizada:

```bash
mkdir -p keyboards/mechboards/lily58/pro/keymaps/NicolasKeyboard
```

---

# 5. Agregar archivos

Dentro de:

```text
keyboards/mechboards/lily58/pro/keymaps/NicolasKeyboard
```

copiar estos archivos:

```text
config.h
keymap.c
rules.mk
```

---

# 6. Compilar firmware

Compilar con:

```bash
qmk compile -kb mechboards/lily58/pro -km NicolasKeyboard
```

El archivo `.hex` se genera en:

```text
qmk_firmware/.build/
```

---

# 7. Abrir QMK Toolbox

Abrir QMK Toolbox.

Presionar:

```text
Open
```

y seleccionar el archivo `.hex`.

---

# 8. Flashear teclado

## Mitad izquierda

- Conectar mitad izquierda
- Presionar RESET
- Presionar:

```text
Flash
```

---

## Mitad derecha

- Desconectar izquierda
- Conectar mitad derecha
- Presionar RESET
- Presionar:

```text
Flash
```

---

# 9. Verificar funcionamiento

Revisar:

- RGB
- OLED
- Layers
- Comunicación entre mitades
