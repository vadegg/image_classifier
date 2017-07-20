TOneFileFeature lbp_cell_to_histogram(const Image& image) {
	TOneFileFeature vector(LBP_FEATURES_VECTOR_SIZE);

		for (uint x = 1; x < image.n_rows - 1; x++) {
			for (uint y = 1; y < image.n_cols - 1; y++) {
				uint res = 0;
				uint pixel = std::get<0>(image (x, y));
				res |= (pixel > std::get<0>(image(x - 1, y)) ? 0 : 1);
				res <<=1;
				res |= (pixel > std::get<0>(image(x - 1, y + 1)) ? 0 : 1);
				res <<=1;
				res |= (pixel > std::get<0>(image(x, y + 1)) ? 0 : 1);
				res <<=1;
				res |= (pixel > std::get<0>(image(x + 1, y + 1)) ? 0 : 1);
				res <<=1;
				res |= (pixel > std::get<0>(image(x + 1, y)) ? 0 : 1);
				res <<=1;
				res |= (pixel > std::get<0>(image(x + 1, y - 1)) ? 0 : 1);
				res <<=1;
				res |= (pixel > std::get<0>(image(x, y - 1)) ? 0 : 1);
				res <<=1;
				res |= (pixel > std::get<0>(image(x - 1, y - 1)) ? 0 : 1);
				vector[res]++;
			}
		}

	norm_histogram(&vector);
	return vector;
}

void local_binary_patterns(TOneFileFeature *vector, const Image &image) {
	int cell_rows, cell_cols;

	cell_rows = image.n_rows / LBP_CELLS_NUMBER_VER;
	cell_cols = image.n_cols / LBP_CELLS_NUMBER_HOR;

	Image extra_image = mirror_edges(image, 1, 1);

	for (uint row = 0; row < LBP_CELLS_NUMBER_VER; row++) {
		for (uint col = 0; col < LBP_CELLS_NUMBER_HOR; col++) {
			uint rows_number, cols_number;
			if (row == LBP_CELLS_NUMBER_VER - 1)
				rows_number = uint(extra_image.n_rows - row * cell_rows - 2);
			else
				rows_number = cell_rows;
			if (col == LBP_CELLS_NUMBER_HOR - 1)
				cols_number = uint(extra_image.n_cols - col * cell_cols - 2);
			else
				cols_number = cell_cols;
			Image subimage = extra_image.submatrix(row * cell_rows, col * cell_cols, rows_number + 2, cols_number + 2);
			TOneFileFeature lbp_vector = lbp_cell_to_histogram(subimage);
			vector->insert(vector->end(), lbp_vector.begin(), lbp_vector.end());
		}
	}
}
