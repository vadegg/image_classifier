//
//  Kerneler.hpp
//  align
//
//  Created by Вадим Глазков on 23.09.16.
//  Copyright © 2016 Vadim Glazkov. All rights reserved.
//

#pragma once

int Kerneler::vert_radius = 0;
int Kerneler::hor_radius = 0;
int Kerneler::vert_size = 0;
int Kerneler::hor_size = 0;


Kerneler::Kerneler (Kernel ker) : kernel(ker) {
	vert_size = kernel.n_rows;
	hor_size = kernel.n_cols;
	vert_radius = (vert_size - 1) / 2;
	hor_radius = (hor_size - 1) / 2;
}


Pixel Kerneler::operator () (const Image &m) const {
    double sum_r = 0.0, sum_g = 0.0, sum_b = 0.0;
    for (uint k = 0; k < m.n_rows; k++) {
        for (uint l = 0; l < m.n_cols; l++) {
            uint r, g, b;
            std::tie(r,g,b) = m(k, l);
            sum_r += double(r) * kernel(k, l);
            sum_g += double(g) * kernel(k, l);
            sum_b += double(b) * kernel(k, l);
        }
    }
    return std::make_tuple (uint(sum_r), uint(sum_g), uint(sum_b));
}


GradientComponentMatrix kernel_applier_grad (const GradientComponentMatrix &src_image, Kernel kernel) {
	GradientComponentMatrix mirrored_image = mirror_edges(src_image, kernel.n_rows, kernel.n_cols);
	GradiendMatrixOperator kerneler(kernel);

	GradientComponentMatrix kerneled_mirrored_image = mirrored_image.unary_map(kerneler);
	GradientComponentMatrix dst_image = unmirror_edges(kerneled_mirrored_image, kernel.n_rows, kernel.n_cols);
	return dst_image;
}
