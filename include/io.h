#pragma once
// This file is borrowed from Task1
// Changes: added #include "Types.h" row
#include "matrix.h"
#include "EasyBMP.h"
#include "Types.h"

#include <tuple>

Image load_image(BMP*);
void save_image(const Image&, const char*);
