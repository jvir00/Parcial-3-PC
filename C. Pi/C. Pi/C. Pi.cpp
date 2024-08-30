#include <chrono>	
#include <iostream> 
#include <omp.h> //API para programación paralela en C++
//Fórmula: pi/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 - ...

//Cálculo de pi con programación serial. 
double compute_pi_serial(long num_steps)
{
	double step = 1.0 / num_steps;
	double sum = 0.0;
	for (long i = 0; i < num_steps; i++) {
		double x = (i + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);
	}
	return sum * step;
}

//Cálculo de pi con programación paralela.  
double compute_pi_parallel(long num_steps)
{
	double step = 1.0 / num_steps;
	double sum = 0.0;
	//Ciclo paralelizado y  variable sum reducida
#pragma omp parallel for reduction(+ : sum) //Código que será ejecutado en paralelo
	for (long i = 0; i < num_steps; i++) {
		double x = (i + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);
	}
	return sum * step;
}

// Función principal 
int main()
{
	const long num_steps = 1000000000L;

	// Calcula pi usando computación serial y lo cronometra 
	auto start_time
		= std::chrono::high_resolution_clock::now();
	double pi_serial = compute_pi_serial(num_steps);
	auto end_time
		= std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> serial_duration
		= end_time - start_time;

	// Calcula pi usando computación paralela y lo cronometra
	start_time = std::chrono::high_resolution_clock::now();
	double pi_parallel = compute_pi_parallel(num_steps);
	end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> parallel_duration
		= end_time - start_time;

	std::cout << "Serial result: " << pi_serial //Impresión del cálculo serial
		<< std::endl;
	std::cout << "Parallel result: " << pi_parallel //Impresión del cálculo paralelo
		<< std::endl;
	std::cout << "Serial duration: "
		<< serial_duration.count() << " seconds" //Impresión del cronómetro serial
		<< std::endl;
	std::cout << "Parallel duration: "
		<< parallel_duration.count() << " seconds" //Impresión del cronómetro paralelo
		<< std::endl;
	std::cout << "Speedup: " //Impresión de la mejoría en tiempo
		<< serial_duration.count()
		/ parallel_duration.count()
		<< std::endl;

	return 0;
}
