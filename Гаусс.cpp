
#include <iostream>

//Просто вывод матрицы
void VivodMatrix(int M, int N, double** matrix, int NumberOfShag, int ShagOfShag) { 
	std::cout << '\n';
	std::cout << "Шаг " << NumberOfShag<<"."<<ShagOfShag<<".\n"; //В шагах есть только два подпункта, 1 - на замену, 2 - на обнуление, поэтому будут повторяться
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cout << matrix[i][j] << " ";

		}
		std::cout << '\n';
	}
}

//Тут замена строки с нулем, на строку без нуля, шаг 1 в лекциях
void ZamenaStroki(int M, int N, double** matrix, int number,int NumberOfShag,int ShagOfShag) {
	if (matrix[number][number] == 0) {                                                                                   //Выполняем когда элемент на диагонали равен 0
		for (int i = number + 1; i < M; i++) {
			if (matrix[i][number] != 0) {                                                                        //Ищем неравный
				double* array = new double[N]; for (int k = 0; k < N; k++) { array[k] = matrix[number][k]; } //Вписываем ненулевую строку в сторонний массив
				for (int k = 0; k < N; k++) { matrix[number][k] = matrix[i][k]; }                            //Меняем первую на строку с ненулем
				for (int k = 0; k < N; k++) { matrix[i][k] = array[k]; }                                     //Меняем строку с ненулем на первую
				VivodMatrix(M, N, matrix, NumberOfShag, ShagOfShag);                                         //Вызываем вывод
				break;
			}
		}
	}
}

//Обнуление вниз, это шаг 2
void Obnulaem(int M, int N, double** matrix, int number, int  NumberOfShag, int ShagOfShag) {
	for (int i = number + 1; i < M; i++) {
		if (matrix[i][number] != 0) {                                                      //Ищу ненулевые значения в столбце
			double constanta = (matrix[i][number] / matrix[number][number]);           //Нахожу константу
			for (int k = 0; k < N; k++) { 
				matrix[i][k] = matrix[i][k] - matrix[number][k] * constanta;       //Отнимаю от строки с ненулевым значением нашу "диагональную" строку, умноженную на константу
			}
			VivodMatrix(M, N, matrix, NumberOfShag, ShagOfShag);                       //Вызываю вывод
		}
	}
}



int main()
{
	std::cout << "Введите количество стобцов и строк в квадратной(!) матрице \n";
	std::cout << "!Количество столбцов для чисел после равно увеличится автоматически! \n";
	int M, N;
	int NumberOfShag{ 1 };                                               //Переменная для обозначения шага
	bool nul = false;                                                    //Переменная для обозначения нулевой строки
	std::cin >> M >> N;
	N++;                                                                 //Добавляю столбец для чисел после равно
	
	//Инициализация матрицы
	std::cout << "Введите значение матрицы и числа после равно \n";
	double** matrix = new double* [M];
	for (int i = 0; i < M; i++) matrix[i] = new double[N];
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> matrix[i][j];

		}
	}

	//Создаем нули под главной диагональю
	for (int i = 0; i < M-1; i++) {
		int ShagOfShag = 1;
		ZamenaStroki(M, N, matrix, i, NumberOfShag, ShagOfShag);
		ShagOfShag++;		
		Obnulaem(M, N, matrix, i, NumberOfShag, ShagOfShag);
		NumberOfShag++;
	}
	
	//Вывожу красивую систему
	std::cout << "\nСистема: \n";
	for (int i = M-1; i > -1; i--) {                                                 //Отсчет с конца, так как внизу уже готовое значение переменной
		for (int k = 0; k < N - 1; k++) {
			if (matrix[i][k] != 0) {                                         //Если число не ноль
				std::cout << matrix[i][k] << char(97+k);                 //Вывожу коэффицент, умноженный на букву
				if (k != N - 2) {                                        //Если не последнее число, пишу +
					std::cout << " + ";
				}
				if (k == N - 2) {                                        //Если последнее, пишу равно числу после равно
					std::cout << " = " << matrix[i][N - 1];
					std::cout << "\n";
				}
			}
		}		
	}

	//Проверка на нулевую строку
	for (int i = 0; i < M; i++) {
		int numberOfZeros = 0;                                           //Количество нулей в строке
		for (int k = 0; k < N - 1; k++) {
			if (matrix[i][k] == 0) numberOfZeros++;                      
		}
		if (numberOfZeros == N - 1) {                                    //Если равно количеству элементов(не считая того, кто после равно), то это нулевая строка
			nul = true;
			break;
		}
	}

	//Решаю систему
	if (nul == false) {                                                                    //Если есть нулевая строка, то систему оставляю в виде уравнения и не решаю
		int* array = new int[N - 1]; for (int i = 0; i < N - 1; i++) { array[i] = 0; } //Массив полученных переменных
		std::cout << "\nРешаем: \n";
		for (int i = M - 1; i > -1; i--) {                                             //Начиная с конца
			double sum = 0;
			for (int k = N - 2; k > -1; k--) {
				if (k == i) break;                                             //Складываю ДО "диагонального" элемента
				sum += matrix[i][k] * array[k];                                //Сумму формирую из значений переменных, умноженных на их коэффиценты
			}
			array[i] = (matrix[i][N - 1] - sum) / matrix[i][i];                    //От числа после равно отнимаю сумма и делю на коэффицент
			std::cout << char(97 + M - i) << " = " << array[i] << "\n";
		}
	}

	//Удаление
	for (int i = 0; i < M; ++i) {
			delete[] matrix[i];
	}
	delete[] matrix;

	return 0;
}

