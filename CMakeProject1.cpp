#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>

//vector
void moving_avg_p(std::vector<double>&, unsigned int);
std::vector<double> moving_avg(std::vector<double>, unsigned int);
// c style
void moving_avg_c(double* mass, unsigned int* size_mass, const unsigned int size_window);


int main() {

	srand(time(0));

	int min = -1000;
	int max = 1000;

	unsigned int size_mass = 100000;

	double * mass_c{ new double[size_mass] };
	//unsigned int size_mass = _msize(mass) / sizeof(mass[0]);
	std::vector<double> mass(size_mass);


	unsigned int size_window = 4;

	for (unsigned int i = 0; i < size_mass; i++) {
		//mass[i] = rand() / static_cast<double>(RAND_MAX) * (max - min) + min;
		mass_c[i] = rand() / static_cast<double>(RAND_MAX) * (max - min) + min;
		std::cout << "mass = " << mass_c[i] << "\t i = " << i <<"\n";
	}

	for (size_t i = 0; i < mass.size(); i++)
		std::cout << "mass = " << mass[i] << "\n";


	auto start_time = std::chrono::steady_clock::now();


	//moving_avg_p(mass, size_window);
	moving_avg(mass, size_window);
	//moving_avg_c(&mass_c[0], &size_mass, size_window);


	auto end_time = std::chrono::steady_clock::now();
	auto diff_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	std::cout << diff_ns.count() << "ns \n";

	//for (size_t i = 0; i < size_mass; i++)
	//	std::cout << "mass = " << mass_c_rez[i] << "\t i = " << i << "\n";



	return 0;
}

void moving_avg_c(double* mass, unsigned int *size_mass, const unsigned int size_window) {
	
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


void moving_avg_p(std::vector<double> &mass, const unsigned int size_window) {
	
	double sma = 0;
	double first_num_window = 0;

	for (unsigned int i = 0; i < size_window; i++)
		sma += mass[i] / size_window;

	for (unsigned int i = 0; i < mass.size() - size_window; i++) {
		first_num_window = mass[i];
		mass[i] = sma ;
		sma += ((mass[i + size_window]) - first_num_window) / size_window;
	}

	mass.resize(mass.size() - size_window);
	mass.shrink_to_fit();
	
	return;
}

std::vector<double> moving_avg(std::vector<double> mass, const unsigned int size_window) {

	double sma = 0;
	double first_num_window = 0;

	std::vector<double> mass_rez(mass.size() - size_window);

	for (unsigned int i = 0; i < size_window; i++)
		sma += mass[i] / size_window;

	for (unsigned int i = 0; i < mass.size() - size_window; i++) {
		first_num_window = mass[i];
		mass_rez[i] = sma;
		sma += ((mass[i + size_window]) - first_num_window) / size_window;
	}

	return mass_rez;
}