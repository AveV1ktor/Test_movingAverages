#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>

// c style
extern void moving_avg(double* mass, unsigned int* size_mass, const unsigned int size_window);
extern void moving_avg(float* mass, unsigned int* size_mass, const unsigned int size_window);


int main() {

	srand(time(0));

	int min_value = -1000;
	int max_value = 1000;

	unsigned int size_mass = 0;

	double* mass_double; 
	float* mass_float; 

	//double rez_time = 0; 
	float rez_time = 0; 
	

	unsigned int size_window = 128;

	for (size_t j = 0; j < 100; j++)
	{
		size_mass = 1000000;
		//mass_float = new double[size_mass];
		mass_float = new float[size_mass];

		for (unsigned int i = 0; i < size_mass; i++) {
			//mass_float[i] = rand() / static_cast<double>(RAND_MAX) * (max_value - min_value) + min_value;
			mass_float[i] = rand() / static_cast<float>(RAND_MAX) * (max_value - min_value) + min_value;
			//std::cout << "mass = " << mass[i] << "\t i = " << i <<"\n";
		}

		auto start_time = std::chrono::steady_clock::now();

		moving_avg(mass_float, &size_mass, size_window);

		auto end_time = std::chrono::steady_clock::now();
		auto diff_mks = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
		std::cout << "diff_ns = " << static_cast<double>(diff_mks.count())/ 1e6 << "s \n";
		rez_time += static_cast<double>(diff_mks.count());
	}

	std::cout << "rez_time = " << rez_time / 100e6 << "s \n";

	return 0;
}

