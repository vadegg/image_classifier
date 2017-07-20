//
//  EdgesMirrorer.hpp
//  align
//
//  Created by Вадим Глазков on 23.09.16.
//  Copyright © 2016 Vadim Glazkov. All rights reserved.
//

template<typename ValueT>
Matrix<ValueT> mirror_edges (const Matrix<ValueT> &src_image, int ver_radius, int hor_radius) {
    if (ver_radius <= 0 || hor_radius <= 0)
        return src_image;

    int new_rows = int(src_image.n_rows) + 2 * ver_radius;
    int new_cols = int(src_image.n_cols) + 2 * hor_radius;

    Matrix<ValueT> dst_image(new_rows, new_cols);
    for (int x = 0; x < new_rows; x++) {
        for (int y = 0; y < new_cols; y++) {
            
            int modified_x = x - ver_radius;
            if (modified_x < 0)
                modified_x = ver_radius - x - 1;
            else if (modified_x >= int(src_image.n_rows))
                modified_x = x - 2 * ver_radius;
            
            int modified_y = y - hor_radius;
            if (modified_y < 0)
                modified_y = hor_radius - y - 1;
            else if (modified_y >= int(src_image.n_cols))
                modified_y = y - 2 * hor_radius;
            
            dst_image(x, y) = src_image(modified_x, modified_y);
        }
    }
    return dst_image;
}

template<typename ValueT>
Matrix<ValueT> unmirror_edges (const Matrix<ValueT> &src_image, int ver_radius, int hor_radius) {
    
	if (ver_radius <= 0 || hor_radius <= 0) {
        return src_image;
	}
    int new_rows = int(src_image.n_rows) - 2 * ver_radius;
    int new_cols = int(src_image.n_cols) - 2 * hor_radius;
    if (new_rows < 0 || new_cols < 0)
        return src_image;

    Matrix<ValueT> dst_image(new_rows, new_cols);
    for (int x = 0; x < new_rows; x++) {
        for (int y = 0; y < new_cols; y++) {
            dst_image(x, y) = src_image(x + ver_radius, y + hor_radius);
        }
    }
    
    return dst_image;
}
