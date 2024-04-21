void moving_avg(double* mass, unsigned int* size_mass, const unsigned int size_window);
void moving_avg(double* mass, unsigned int* size_mass, const unsigned int size_window);

void moving_avg(double* mass, unsigned int* size_mass, const unsigned int size_window) {

	double sma = 0;
	double first_num_window = 0;

	for (size_t i = 0; i < size_window; i++)
		sma += mass[i] / size_window;

	for (unsigned int i = 0; i < *size_mass; i++) {
		first_num_window = mass[i];
		mass[i] = sma;
		sma += ((mass[i + size_window]) - first_num_window) / size_window;
	}

	*size_mass -= size_window;

	return;
}

void moving_avg(float* mass, unsigned int* size_mass, const unsigned int size_window) {

	float sma = 0;
	float first_num_window = 0;

	for (size_t i = 0; i < size_window; i++)
		sma += mass[i] / size_window;

	for (unsigned int i = 0; i < *size_mass; i++) {
		first_num_window = mass[i];
		mass[i] = sma;
		sma += ((mass[i + size_window]) - first_num_window) / size_window;
	}

	*size_mass -= size_window;

	return;
}