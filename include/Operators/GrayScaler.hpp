int GrayScaler::vert_radius = 0;
int GrayScaler::hor_radius = 0;

Pixel GrayScaler::operator () (const Image &image) const {
	uint r, g, b;
	std::tie(r, g, b) = image(0, 0);
	double y = 0.299 * double(r) + 0.587 * double(g) + 0.114 * double(b);
	uint result_pixel = uint(y);
	return std::make_tuple(result_pixel, result_pixel, result_pixel);
}

