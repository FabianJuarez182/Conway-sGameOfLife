#pragma once

#include <vector>

// Incluimos el archivo de encabezado "color.h" que contiene la definición de la clase Color
#include "color.h"

constexpr size_t FRAMEBUFFER_WIDTH = 80;
constexpr size_t FRAMEBUFFER_HEIGHT = 80;
constexpr size_t FRAMEBUFFER_SIZE = FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT;

// Vector unidimensional para representar el framebuffer
Color framebuffer[FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT];

// Color base del framebuffer
Color clearColor{0, 0, 0};

Color currentColor{255, 255, 255};

// Función para limpiar el framebuffer y llenarlo con el color clearColor
void clear() {
  std::fill(framebuffer, framebuffer + FRAMEBUFFER_SIZE, clearColor);
}

