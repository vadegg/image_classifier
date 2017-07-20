int GradiendMatrixOperator::vert_radius = 0;
int GradiendMatrixOperator::hor_radius = 0;
int GradiendMatrixOperator::vert_size = 0;
int GradiendMatrixOperator::hor_size = 0;


GradiendMatrixOperator::GradiendMatrixOperator (Kernel ker) : kernel(ker) {
	vert_size = kernel.n_rows;
	hor_size = kernel.n_cols;
	vert_radius = (vert_size - 1) / 2;
	hor_radius = (hor_size - 1) / 2;
}


GradientComponent GradiendMatrixOperator::operator () (const GradientComponentMatrix &m) const {
	GradientComponent sum = 0.0;
    for (uint k = 0; k < m.n_rows; k++) {
        for (uint l = 0; l < m.n_cols; l++) {
        	GradientComponent x = m(k, l);
            sum += GradientComponent(x) * kernel(k, l);
        }
    }
    return sum;

    return 0;
}


GradientMatrix create_gradient_matrix (const Image &gray_scaled_image) {

	GradientComponentMatrix one_component_matrix(gray_scaled_image.n_rows, gray_scaled_image.n_cols);

	for (uint x = 0; x < one_component_matrix.n_rows; x++) {
		for (uint y = 0; y < one_component_matrix.n_cols; y++) {
			one_component_matrix(x, y) = GradientComponent(std::get<0>(gray_scaled_image(x, y)));
		}
	}

	std::initializer_list<double> first = {-1};
	std::initializer_list<double> second = {0};
	std::initializer_list<double> third = {1};

	Kernel ver_sobel = 	{	first,
							second,
							third
						};
	Kernel hor_sobel = 	{	{-1, 0, 1}
						};

	GradientComponentMatrix ver_sobeled = kernel_applier_grad(one_component_matrix, ver_sobel);
	GradientComponentMatrix hor_sobeled = kernel_applier_grad(one_component_matrix, hor_sobel);

	GradientMatrix matrix(gray_scaled_image.n_rows, gray_scaled_image.n_cols);

	for (uint k = 0; k < matrix.n_rows; k++) {
		for (uint l = 0; l < matrix.n_cols; l++) {
			int x = hor_sobeled(k, l);

			int y = ver_sobeled(k, l);

			GradientComponent module = sqrt(x*x + y*y);
			GradientComponent direction = fabs(module) < EPSILON ? 0 : asin (y / module);
			GradientVector vector = std::make_pair(module, direction);
			matrix(k, l) = vector;
		}
	}
	return matrix;
}

