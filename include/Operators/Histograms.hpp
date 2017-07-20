#include "Constants.h"

TOneFileFeature cell_histogram (const GradientMatrix &matrix) {

	float min_grad = pi / 2;
	float max_grad = - pi / 2;


		for (uint x = 0; x < matrix.n_rows; x++) {
			for (uint y = 0; y < matrix.n_cols; y++) {
				float val = matrix(x, y).second;
				if (val < min_grad)
					min_grad = val;
				if (val > max_grad)
					max_grad = val;
			}
		}
		TOneFileFeature vector(SEGMENT_NUMBER);

		float step = (max_grad - min_grad) / SEGMENT_NUMBER;

		if (fabs(step) < EPSILON)
			return vector;

		for (uint x = 0; x < matrix.n_rows; x++) {
			for (uint y = 0; y < matrix.n_cols; y++) {
				float val = matrix(x, y).second;
				int seg;
				if (fabs(val - max_grad) < EPSILON)
					seg = SEGMENT_NUMBER - 1;
				else
					seg = int ((val - min_grad) / step);
				vector[seg] += matrix(x,y).first;
			}
		}
	return vector;
}

void norm_histogram(TOneFileFeature *vector) {
	GradientComponent sum = 0;
	for (auto item : *vector) {
		sum += item * item;
	}
	sum = sqrt(sum);
	if (fabs(sum) < EPSILON)
		return;
	for (size_t i = 0; i < vector->size(); i++) {
		(*vector)[i] = (*vector)[i] / sum;
	}
}

void vector_inserter(const GradientMatrix &gradient_matrix, TOneFileFeature *vector,
		uint row_start, uint col_start,
		uint row_number, uint cols_number) {
	GradientMatrix submatrix = gradient_matrix.submatrix(row_start, col_start, row_number, cols_number);
	TOneFileFeature subvector = cell_histogram(submatrix);

	norm_histogram(&subvector);
	vector->insert(vector->end(), subvector.begin(), subvector.end());
}


TOneFileFeature HistogramMaker (const Image &image) {
	TOneFileFeature vector;

	Image gray_scaled_image = image.unary_map(GrayScaler());

    GradientMatrix gradient_matrix = create_gradient_matrix(gray_scaled_image);

	int cell_rows, cell_cols;

	cell_rows = gradient_matrix.n_rows / CELLS_NUMBER_VER;
	cell_cols = gradient_matrix.n_cols / CELLS_NUMBER_HOR;

	for (uint row = 0; row < CELLS_NUMBER_VER; row++) {
		for (uint col = 0; col < CELLS_NUMBER_HOR; col++) {
			uint rows_number, cols_number;
			if (row == CELLS_NUMBER_VER - 1)
				rows_number = uint(gradient_matrix.n_rows - row * cell_rows);
			else
				rows_number = cell_rows;

			if (col == CELLS_NUMBER_HOR - 1)
				cols_number = uint(gradient_matrix.n_cols - col * cell_cols);
			else
				cols_number = cell_cols;

			if (rows_number != 0 && cols_number != 0) {
				vector_inserter(gradient_matrix, &vector,
						uint(row * cell_rows), uint(col * cell_cols),
						rows_number, cols_number
				);
			}
		}
	}
	if (LOCAL_BINARY_PATTERNS) {
		local_binary_patterns(&vector, gray_scaled_image);
	}

	if (COLOR_FEATURES) {
		color_features(&vector, image);
	}

	return vector;
}
