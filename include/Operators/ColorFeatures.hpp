void cell_processor (const Image &image, TOneFileFeature *vector,
		uint row_start, uint col_start,
		uint row_number, uint cols_number) {

	Image subimage = image.submatrix(row_start, col_start, row_number, cols_number);
	uint r_sum = 0;
	uint g_sum = 0;
	uint b_sum = 0;

	for (uint x = 0; x < row_number; x++) {
		for (uint y = 0; y < cols_number; y++) {
			r_sum += std::get<0>(subimage(x,y));
			g_sum += std::get<1>(subimage(x,y));
			b_sum += std::get<2>(subimage(x,y));
		}
	}
	vector->push_back((TSingleFeature(r_sum) / TSingleFeature(row_number * cols_number)) / TSingleFeature(COLOR_FEATURES_COLORS_MAX_NUMBER));
	vector->push_back((TSingleFeature(g_sum) / TSingleFeature(row_number * cols_number)) / TSingleFeature(COLOR_FEATURES_COLORS_MAX_NUMBER));
	vector->push_back((TSingleFeature(b_sum) / TSingleFeature(row_number * cols_number)) / TSingleFeature(COLOR_FEATURES_COLORS_MAX_NUMBER));
}

void color_features (TOneFileFeature *vector, const Image& image) {

	uint cell_rows, cell_cols;

	cell_rows = image.n_rows / COLOR_FEATURES_CELLS_NUMBER_VER;
	cell_cols = image.n_cols / COLOR_FEATURES_CELLS_NUMBER_HOR;

	for (uint row = 0; row < COLOR_FEATURES_CELLS_NUMBER_VER; row++) {
		for (uint col = 0; col < COLOR_FEATURES_CELLS_NUMBER_HOR; col++) {
			uint rows_number, cols_number;
			if (row == COLOR_FEATURES_CELLS_NUMBER_VER - 1)
				rows_number = uint(image.n_rows - row * cell_rows);
			else
				rows_number = cell_rows;

			if (col == COLOR_FEATURES_CELLS_NUMBER_HOR - 1)
				cols_number = uint(image.n_cols - col * cell_cols);
			else
				cols_number = cell_cols;
			if (rows_number != 0 && cols_number != 0) {
				cell_processor(image, vector,
						uint(row * cell_rows), uint(col * cell_cols),
						rows_number, cols_number
				);
			}
		}
	}
}
