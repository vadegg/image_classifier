#pragma once

#include "Types.h"
#include "Constants.h"

class GrayScaler {
public:
	GrayScaler() {}
    Pixel operator () (const Image &m) const;
    static int vert_radius;
    static int hor_radius;
};

class Kerneler {
public:
    Kerneler (Kernel ker);
    static int vert_radius;
    static int hor_radius;
    static int vert_size;
    static int hor_size;
    Pixel operator () (const Image &m) const;
private:
    Kernel kernel;
};

class GradiendMatrixOperator {
public:
	GradiendMatrixOperator (Kernel ker);
    static int vert_radius;
    static int hor_radius;
    static int vert_size;
    static int hor_size;
    GradientComponent operator () (const GradientComponentMatrix &m) const;
private:
    Kernel kernel;
};


Matrix<int> kernel_applier_grad (const Matrix<int> &src_image, Kernel kernel);

template<typename ValueT>
Matrix<ValueT> mirror_edges (const Matrix<ValueT> &src_image, int ver_radius, int hor_radius);
template<typename ValueT>
Matrix<ValueT> unmirror_edges (const Matrix<ValueT> &src_image, int ver_radius, int hor_radius);

GradientMatrix create_gradient_matrix (const Image &gray_scaled_image);

void norm_histogram(TOneFileFeature *vector);

TOneFileFeature HistogramMaker (const Image &image);


void local_binary_patterns(TOneFileFeature *vector, const Image& image);

void color_features (TOneFileFeature *vector, const Image& image);

#include "Operators/GrayScaler.hpp"
#include "Operators/EdgesMirrorer.hpp"
#include "Operators/Kerneler.hpp"
#include "Operators/Gradienter.hpp"
#include "Operators/Histograms.hpp"
#include "Operators/LBP.hpp"
#include "Operators/ColorFeatures.hpp"
