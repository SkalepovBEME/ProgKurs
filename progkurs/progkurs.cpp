#include <chrono>
#include <cstdlib>  
#include <ctime>
#include <vector>
#include <iomanip> 
#include <Windows.h> 
#include <thread> 
#include <random>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <conio.h>
#include <iostream>

using namespace std;
using namespace chrono;

vector<int> suffixes(const string& pattern) {
	int length = pattern.length();
	vector<int> suffix(length, 0);

	int g, f;
	g = f = length - 1;
	for (int i = length - 2; i >= 0; --i) {
		if (i > g && suffix[i + length - 1 - f] < i - g) {
			suffix[i] = suffix[i + length - 1 - f];
		}
		else {
			if (i < g) {
				g = i;
			}
			f = i;
			while (g >= 0 && pattern[g] == pattern[g + length - 1 - f]) {
				--g;
			}
			suffix[i] = f - g;
		}
	}

	return suffix;
}

vector<int> boyerMoore(const string& text, const string& pattern) {
	int n = text.length();
	int m = pattern.length();
	std::vector<int> occurrences;

	std::vector<int> shift(256, m);
	for (int i = 0; i < m - 1; ++i) {
		shift[pattern[i]] = m - i - 1;
	}

	std::vector<int> suffix = suffixes(pattern);

	int i = 0;
	while (i <= n - m) {
		int j = m - 1;
		while (j >= 0 && pattern[j] == text[i + j]) {
			--j;
		}
		if (j < 0) {
			occurrences.push_back(i);
			i += shift[text[i + m]];
		}
		else {
			int x = suffix[j];
			int y = j - x;
			int z = m - 1 - j;
			i += max(shift[text[i + j]] - y, z);
		}
	}

	return occurrences;
}


string cleanString(const string & input) {
	setlocale(0, "");
	string result;
	bool lastWasSpace = false;
	bool lastWasPunctuation = false;

	for (size_t i = 0; i < input.size(); ++i) {
		char ch = input[i];

		if (ch == ' ') {
			if (!lastWasSpace) {
				result += ch;
				lastWasSpace = true;
			}
		}
		else if (ch == '.' || ch == ',' || ch == ';' || ch == ':') {
			if (!lastWasPunctuation) {
				result += ch;
				lastWasPunctuation = true;
			}
		}
		else {
			result += ch;
			lastWasSpace = false;
			lastWasPunctuation = false;
		}
	}

	return result;
}

bool containsDigit(const string & word) {
	for (char c : word) {
		if (isdigit(c)) {
			return true;
		}
	}
	return false;
}

vector<size_t> findSubstring(const string & text, const string & substring) {
	vector<size_t> positions;
	size_t pos = text.find(substring, 0);

	while (pos != string::npos) {
		positions.push_back(pos);
		pos = text.find(substring, pos + 1);
	}

	return positions;
}
void lab4() {
	system("cls");
	setlocale(LC_ALL, "ru-RU");
	cout << "Введите слова: ";
	string inpute;
	getline(cin >> ws, inpute);
	string input = cleanString(inpute);
	inpute = cleanString(inpute);
	istringstream ss(input);
	string word;

	cout << "\nСлова без цифр: ";
	while (ss >> word) {
		if (!containsDigit(word)) {
			cout << word << " ";
		}
	}
	cout << endl;
	string substring;
	cout << "Подстрока для поиска: ";
	cin >> substring;

	vector<size_t> positions = findSubstring(input, substring);

	if (positions.empty()) {
		cout << "Не найдено." << endl;
	}
	else {
		cout << "Подстрока найдена на позиции: ";
		for (size_t pos : positions) {
			cout << pos << " ";
		}
		cout << endl;
	}


	cout << "Подстрока для поиска методом Бойера-Мура: ";
	string substring2;
	cin >> substring2;
	vector<int> vec = boyerMoore(input, substring2);

	if (!vec.empty()) {
		cout << "Pattern found at positions: ";
		for (int i = 0; i < vec.size(); ++i) {
			std::cout << vec[i] << " ";
		}
	}
	else {
		std::cout << "Pattern not found.";
	}

	cout << "\nВывод строки вертикально: " << endl;
	for (int i = 0; i < inpute.length(); i++)
		cout << inpute[i] << endl;
}

void RIMFInteger(int number) {
	unsigned int mask = 1 << sizeof(int) * 8 - 1;
	for (int i = 1; i <= sizeof(int) * 8; i++) {
		putchar(number & mask ? '1' : '0');
		mask >>= 1;
		if (i == 1 | i % 8 == 0)
			putchar(' ');
		if (i == sizeof(int) * 8)
			cout << "(int)\n\n";
	}
}
void RIMFloat(int plugCloneFloat) {
	unsigned int mask = 1 << sizeof(int) * 8 - 1;
	for (int i = 1; i <= sizeof(int) * 8; i++) {
		putchar(plugCloneFloat & mask ? '1' : '0');
		mask >>= 1;
		if (i == 1 | i == 9)
			putchar(' ');
		if (i > 9 & i % 8 == 0)
			putchar(' ');
		if (i == sizeof(int) * 8)
			cout << "(float)\n\n";
	}
}
void RIMFDouble(int cloneDuo[2]) {
	for (int i = 1; i >= 0; i--) {
		int unsigned mask = 1 << sizeof(int) * 8 - 1;
		for (int j = 1; j <= sizeof(int) * 8; j++) {
			putchar(cloneDuo[i] & mask ? '1' : '0');
			mask >>= 1;
			if ((i == 1 & j == 1) | (i == 1 & j == 12))
				putchar(' ');
		}
	}
	cout << " (double)\n\n";
}
void lab1() {
	system("cls");
	setlocale(0, "");
	int сhoice = 1;
	int integerNumber;
	unsigned int mask;
	int shift;
	while (сhoice != 0) {
		cout << "1) Вывод количества пямяти для различных типов данных.\n" \
			<< "2) Вывод на экран двоичного представления в памяти типа int.\n" \
			<< "3) Вывод на экран двоичного представления в памяти типа float.\n" \
			<< "4) Вывод на экран двоичного представления в памяти типа double.\n" \
			<< "5) IDZ 12\n" \
			<< "0) Мне ничего из этого не нужно\n" \
			<< "Введите номер функции, которой вы хотите воспользоваться: ";
		cin >> сhoice;
		switch (сhoice) {
		case(0):
			break;
		case(1):
			cout << "\nint - " << sizeof(int) << endl << "short int - " << sizeof(short int) << endl \
				<< "long int - " << sizeof(long int) << endl << "float - " << sizeof(float) << endl \
				<< "double - " << sizeof(double) << endl << "long double - " << sizeof(long double) << endl \
				<< "char - " << sizeof(char) << endl << "bool - " << sizeof(bool) << endl << endl;
			break;
		case(2):
			cout << "\nВведите целое число, представление в памяти которого вам нужно: ";
			cin >> integerNumber;
			RIMFInteger(integerNumber);
			break;
		case(3):
			cout << "\nВведите число, представление в памяти которого вам нужно: ";
			union {
				float floatNumber;
				int plugCloneFloat;
			};
			cin >> floatNumber;
			RIMFloat(plugCloneFloat);
			break;
		case(4):
			cout << "\nВведите число, представление в пямяти когорого вам нужно: ";
			union {
				double doubleNumber;
				int cloneDuo[2];
			};
			cin >> doubleNumber;
			RIMFDouble(cloneDuo);
			break;
		case(5):
			int secondChoice;
			cout << "\n1) int.\n" \
				<< "2) float.\n" \
				<< "3) double.\n" \
				<< "0) Я хочу выйти в первоначальное меню.\n"
				<< "Введите номер функции, которой вы хотите воспользоваться: ";
			cin >> secondChoice;
			switch (secondChoice) {
			case(0):
				cout << endl;
				break;
			case(1):
				cout << "\nВведите целое число и количество сдвигов вправо: ";
				cin >> integerNumber >> shift;
				RIMFInteger(integerNumber);
				mask = 1 << shift - 1;
				integerNumber >>= shift;
				RIMFInteger(integerNumber);
				break;
			case(2):
				cout << "\nВведите число и количество сдвигов вправо: ";
				union {
					float floatNumber;
					int plugCloneFloat;
				};
				cin >> floatNumber >> shift;
				RIMFloat(plugCloneFloat);
				plugCloneFloat >>= shift;
				RIMFloat(plugCloneFloat);
				break;
			case(3):
				cout << "\nВведите число и количество сдвигов вправо: ";
				union {
					double doubleNumber;
					int cloneDuo[2];
				};
				cin >> doubleNumber >> shift;
				RIMFDouble(cloneDuo);
				cloneDuo[0] >>= shift;
				cloneDuo[0] = (cloneDuo[1] << ((sizeof(int) * 8) - shift)) | cloneDuo[0];
				cloneDuo[1] >>= shift;
				RIMFDouble(cloneDuo);
				break;
			}
		}
	}
}
void newArr(int N, int* arr, bool* sorted) {
	setlocale(0, "");
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		arr[i] = rand() % 199 - 99;
		*sorted = false;
	}
}
void maxMin(int N, int* arr, bool sorted, int* max, int* min) {
	if (!sorted) {
		for (int i = 0; i < N; i++) {
			if (arr[i] < *min)
				* min = arr[i];
			if (arr[i] > * max)
				* max = arr[i];
		}
	}
	if (sorted) {
		*max = arr[N - 1];
		*min = arr[0];
	}
}
void searchAverages(int N, int* arr, bool sorted, int max, int min, int average) {
	int count = 0;
	cout << "\nИндексы элементов, равных среднему значению: ";
	for (int i = 0; i < N; i++) {
		if (arr[i] == average) {
			cout << i << ' ';
			count += 1;
		}
	}
	cout << endl << "Количество таких элементов в массиве: " << count << endl;
}
void bubbleSort(int* arr, int N, bool* sorted) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
		}
	}
	*sorted = true;
}
void shakerSort(int* arr, int N, bool* sorted) {
	bool swapped = true;
	int start = 0;
	int end = N - 1;
	while (swapped) {
		swapped = false;
		for (int i = start; i < end; i++) {
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				swapped = true;
			}
		}
		if (!swapped)
			break;
		swapped = false;
		end--;
		for (int i = end - 1; i >= start; i--) {
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				swapped = true;
			}
		}
		++start;
	}
	*sorted = true;
}
void insertSort(int* arr, int N, bool* sorted) {
	int i, key, j;
	for (i = 1; i < N; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
	*sorted = true;
}
void quickSort(int* arr, int N, bool* sorted, int end, int begin) {
	int mid;
	int f = begin;
	int l = end;
	mid = arr[(f + l) / 2];
	while (f < l)
	{
		while (arr[f] < mid) f++;
		while (arr[l] > mid) l--;
		if (f <= l)
		{
			swap(arr[f], arr[l]);
			f++;
			l--;
		}
	}
	if (begin < l) quickSort(arr, N, sorted, l, begin);
	if (f < end) quickSort(arr, N, sorted, end, f);
	*sorted = true;
}
void combSort(int* arr, int N, bool* sorted) {
	float k = 1.247, S = N - 1;
	int count = 0, swap;
	while (S >= 1) {
		for (int i = 0; i + S < N; i++) {
			if (arr[i] > arr[int(i + S)]) {
				swap = arr[int(i + S)];
				arr[int(i + S)] = arr[i];
				arr[i] = swap;
			}
		}
		S /= k;
	}
	while (true) {
		for (int i = 0; i < N - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				swap = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = swap;
			}
			else count++;
		}
		if (count == N - 1)
			break;
		else
			count = 0;
	}
}
void arrayOutput(int arr[], int N) {
	for (int i = 0; i < N; i++) {
		if (i == 0)
			cout << "{" << arr[i] << ' ';
		else if (i == N - 1)
			cout << arr[i] << "}";
		else
			cout << arr[i] << ' ';
	}
	cout << endl << endl;
}
int binarySearch(int arr[], int value, int start, int end) {
	if (end >= start) {
		int mid = start + (end - start) / 2;
		if (arr[mid] == value) {
			return mid;
		}
		if (arr[mid] > value) {
			return binarySearch(arr, value, start, mid - 1);
		}
		return binarySearch(arr, value, mid + 1, end);
	}
	return -1;
}
void lab2() {
	system("cls");
	auto start1 = steady_clock::now();
	auto end1 = steady_clock::now();
	auto result1 = duration_cast<nanoseconds>(end1 - start1);
	setlocale(0, "");
	const int N = 100;
	int arr[N];
	int count;
	int resault;
	bool sorted = false;
	newArr(N, arr, &sorted);
	int min = arr[0], max = arr[N - 1];
	int average = (min + max) / 2;
	int choice = 1;
	int secondChoice = 1;
	while (choice && secondChoice) {
		if (!sorted) {
			cout << "1. Создать новый рандомный, неотсортированный массив.\n"\
				<< "2. Отсортировать массив.\n"\
				<< "3. Найти максимальный и минимальный элемент.\n"\
				<< "4. Вывести среднее значение максимального и минимального значения и вывести индексы элементов, равных этому значению, их количество.\n"\
				<< "5. Вывести массив \n"\
				<< "Введите номер функции, которой хотите вопользоваться или же 0 для окончания работы программы: ";
			cin >> choice;
			switch (choice) {
			case 0: break;
			case 1: cout << endl;
				newArr(N, arr, &sorted);
				min = arr[0], max = arr[N - 1];
				average = (min + max) / 2;
				break;
			case 2: cout << "\nВы хотите \"прочесать\" массив (Comb sort) перед другими сортировками? \n" \
				<< "Введите любое число, если хотите. Введите 0, если не хотите: ";
				int combSortChoice;
				cin >> combSortChoice;
				if (combSortChoice) {
					start1 = steady_clock::now();
					combSort(arr, N, &sorted);
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "\nВремени потрачено на данную сортировку: " << result1.count() << endl << "Массив отсортирован. Но отсортируйте его ещё раз, для уверенности.) \n\n";
				}
				cout << "\n1. Bubble sort \n" \
					<< "2. Shaker sort \n" \
					<< "3 Insert sort \n" \
					<< "4 Quick sort \n" \
					<< "Введите номер сортировки, с помощью которой вы хотите отсортировать массив и узнать время этой сортировки: ";
				int nestedSelection;
				cin >> nestedSelection;
				cout << endl;
				switch (nestedSelection) {
				case 1: start1 = steady_clock::now();
					bubbleSort(arr, N, &sorted);
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "Массив отсортирован. \n" << "Время потраченное на сортировку: " << result1.count() << " (Bubble sort)" << endl << endl;
					break;
				case 2: start1 = steady_clock::now();
					shakerSort(arr, N, &sorted);
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "Массив отсортирован. \n" << "Время потраченное на сортировку: " << result1.count() << " (shaker sort)" << endl << endl;
					break;
				case 3: start1 = steady_clock::now();
					insertSort(arr, N, &sorted);
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "Массив отсортирован. \n" << "Время потраченное на сортировку: " << result1.count() << " (insert sort)" << endl << endl;
					break;
				case 4: start1 = steady_clock::now();
					quickSort(arr, N, &sorted, N - 1, 0);
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "Массив отсортирован. \n" << "Время потраченное на сортировку: " << result1.count() << " (quick sort)" << endl << endl;
					break;
				}
				break;
			case 3: start1 = steady_clock::now();
				maxMin(N, arr, sorted, &max, &min);
				end1 = steady_clock::now();
				result1 = duration_cast<nanoseconds>(end1 - start1);
				cout << "\nmax = " << max << ',' << " min = " << min << endl \
					<< "Время выполнения данной функции: " << result1.count() << endl << endl; break;
			case 4: average = (min + max) / 2;
				cout << "\nСреднее значение: " << average;
				start1 = steady_clock::now();
				searchAverages(N, arr, sorted, max, min, average);
				end1 = steady_clock::now();
				result1 = duration_cast<nanoseconds>(end1 - start1);
				cout << "Время выполнения данной функции: " << result1.count() << endl << endl; break;
			case 5: arrayOutput(arr, N);
				break;
			}
		}
		if (sorted) {
			cout << "1. Создать новый рандомный, неотсортированный массив.\n"\
				<< "2. Вывести количество элементов, меньших заданного вами числа А \n"\
				<< "3. Вывести количество элементов, больших заданного вами числа B \n"\
				<< "4. Наличие введённого вами числа в массиве (поиск) \n"\
				<< "5. Поменять местами элементы, индексы которых вы введёте \n"\
				<< "6. Вывести массив \n"\
				<< "7. Найти максимальный и минимальный элемент \n"\
				<< "8. Вывести среднее значение максимального и минимального значения и вывести индексы элементов, равных этому значению, их количество.\n"\
				<< "Введите номер функции, которой хотите воспользоваться или же 0 для окончания работы програмы: ";
			cin >> secondChoice;
			switch (secondChoice) {
			case 0: break;
			case 1:	cout << endl;
				newArr(N, arr, &sorted);
				min = arr[0], max = arr[N - 1];
				average = (min + max) / 2;
				break;
			case 2: int A;
				cout << "\nВведите нужное вам число А: ";
				cin >> A;
				count = 0;
				for (int i = 0; arr[i] < A && i < N; i++)
					count += 1;
				cout << "Количество чисел в массиве, меньших А: " << count << endl << endl;
				break;
			case 3: int B;
				cout << "\nВведите нужное вам число B: ";
				cin >> B;
				count = 0;
				for (int i = N - 1; arr[i] > B; i--)
					count += 1;
				cout << "Количество чисел в массиве, больших B: " << count << endl << endl;
				break;
			case 4: int value;
				cout << "\nВведите число, наличие которого в массиве вы хотите узнать: ";
				cin >> value;
				start1 = steady_clock::now();
				resault = binarySearch(arr, value, 0, N - 1);
				end1 = steady_clock::now();
				result1 = duration_cast<nanoseconds>(end1 - start1);
				if (resault == -1)
					cout << "Вашего числа нет в массиве :(" << endl << endl;
				else {
					cout << "Ваше число есть в массиве и оно находится под индексом " << resault << endl << "Время потраченное на его поиск: " << result1.count() << endl;
					start1 = steady_clock::now();
					for (int i = 0; i < N; i++) {
						if (arr[i] == value)
							break;
					}
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "Время потраченное на его поиск простым перебором: " << result1.count() << endl << endl;
				}
				break;
			case 5: int change, secondChange;
				cout << "\nВведите два индекса, элементов, которых вы хотите поменять местами: ";
				cin >> change >> secondChange;
				start1 = steady_clock::now();
				swap(arr[change], arr[secondChange]);
				end1 = steady_clock::now();
				result1 = duration_cast<nanoseconds>(end1 - start1);
				cout << "\nЧисла поменяны. \n" << "Времени затрачено: " << result1.count() << endl << endl;
				sorted = false;
				break;
			case 6: arrayOutput(arr, N);
				break;
			case 7: start1 = steady_clock::now();
				maxMin(N, arr, sorted, &max, &min);
				end1 = steady_clock::now();
				result1 = duration_cast<nanoseconds>(end1 - start1);
				cout << "\nmax = " << max << ',' << " min = " << min << endl \
					<< "Время выполнения данной функции: " << result1.count() << endl << endl; break;
			case 8: maxMin(N, arr, sorted, &max, &min);
				average = (min + max) / 2;
				cout << "\nСреднее значение: " << average;
				start1 = steady_clock::now();
				searchAverages(N, arr, sorted, max, min, average);
				end1 = steady_clock::now();
				result1 = duration_cast<nanoseconds>(end1 - start1);
				cout << "Время выполнения данной функции: " << result1.count() << endl << endl; break;
			}
		}
	}
}
void lab3() {
	system("cls");
	setlocale(0, "");
	cout << "Задание 1.";
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int const N = 10;
	int arr[N][N];
	srand(time(NULL));
	int n = sizeof(arr) / sizeof(*arr);
	int m = sizeof(*arr) / sizeof(**arr);
	int* end = *arr + n * m - 1;
	for (int* p = *arr; p <= end; p++)
		* p = rand() % (1 + N * N);
	int shiftX = 0, shiftY = 0;
	int indicator = 1;
	int additionalVariable;
	int L = N;
	int F = 1;
	for (int* p = *arr; p <= end; p++) {
		if (shiftX < L && indicator == 1) {
			shiftX += 1;
			destCoord.X = (shiftX - 1) * m / (N / 5);
			destCoord.Y = shiftY * 2 + 1;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << *p;
			cout.flush();
			Sleep(20);
			additionalVariable = (shiftX - 1) * m / (N / 5);
		}
		else if (shiftX == L && indicator == 1) {
			shiftY += 1;
			destCoord.X = additionalVariable;
			destCoord.Y = shiftY * 2 + 1;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << *p;
			cout.flush();
			Sleep(20);
			L -= 1;
		}
		else if (shiftY < L && indicator == 1) {
			shiftY += 1;
			destCoord.X = additionalVariable;
			destCoord.Y = shiftY * 2 + 1;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << *p;
			cout.flush();
			Sleep(20);
		}
		else if (shiftY == L && indicator == 1) {
			shiftX -= 1;
			destCoord.X = (shiftX - 1) * m / (N / 5);
			destCoord.Y = shiftY * 2 + 1;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << *p;
			cout.flush();
			Sleep(20);
			additionalVariable = (shiftX - 1) * m / (N / 5);
			indicator *= -1;
		}
		else if (shiftX > F && indicator == -1) {
			shiftX -= 1;
			destCoord.X = (shiftX - 1) * m / (N / 5);
			destCoord.Y = shiftY * 2 + 1;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << *p;
			cout.flush();
			Sleep(20);
			additionalVariable = (shiftX - 1) * m / (N / 5);
		}
		else if (shiftY > F && indicator == -1) {
			shiftY -= 1;
			destCoord.X = additionalVariable;
			destCoord.Y = shiftY * 2 + 1;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << *p;
			cout.flush();
			Sleep(20);
		}
		else if (shiftY == F && indicator == -1) {
			shiftX += 1;
			destCoord.X = (shiftX - 1) * m / (N / 5);
			destCoord.Y = shiftY * 2 + 1;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << *p;
			cout.flush();
			Sleep(20);
			additionalVariable = (shiftX - 1) * m / (N / 5);
			indicator *= -1;
			F += 1;
		}
	}


	int number = 0;
	shiftX = 0;

	for (int* p = *arr; p <= end; p++) {
		if (number % 2 == 0 && shiftX < N) {
			shiftX += 1;
			destCoord.X = number * m / (N / 5);
			destCoord.Y = N * 2 + shiftX * 2;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << *p;
			cout.flush();
			Sleep(20);
		}
		else if (shiftX == N) {
			number += 1;
			destCoord.X = number * m / (N / 5);
			destCoord.Y = N * 2 + shiftX * 2;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << *p;
			cout.flush();
			Sleep(20);
			shiftX -= 1;
		}
		else if (number % 2 != 0 && shiftX > 0) {
			destCoord.X = number * m / (N / 5);
			destCoord.Y = N * 2 + shiftX * 2;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << *p;
			cout.flush();
			Sleep(20);
			shiftX -= 1;
		}
		else if (shiftX == 0) {
			number += 1;
			shiftX += 1;
			destCoord.X = number * m / (N / 5);
			destCoord.Y = N * 2. + shiftX * 2;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << *p;
			cout.flush();
			Sleep(20);
		}
	}
	cout << '\r';
	for (int i = 0; i <= 2 * N; i++)
		cout << endl;


	for (int* p = *arr; p <= end; p++)
		* p = rand() % (1 + N * N);
	bool bul = true;
	while (bul) {
		cout << "\n\n"
			<< "1) 1  -> 2 | 2  -> 4 | 4  -> 3 | 3  - > 1\n"
			<< "2) 1 <-> 4 | 2 <-> 3\n"
			<< "3) 1 <-> 3 | 2 <-> 4\n"
			<< "4) 1 <-> 2 | 3 <-> 4\n"
			<< "5) Вывести матрицу\n"
			<< "6) Сортировка (Shaker sort)\n"
			<< "7) Меняет каждый элемент матрицы, взависимости от вашего выбора\n"
			<< "8) Транспонирование матрицы\n"
			<< "0) Выход из программы\n"
			<< "Введите номер функции, которовый вы хотите воспользоваться: ";
		int choice;
		cin >> choice;
		bool swapped = true;
		int start = 0;
		int end = N - 1;
		char choice2;
		int number;
		switch (choice) {
		case 1:
			int arr2[N / 2][N / 2];
			for (int i = 0; i < N / 2; i++) {
				for (int j = 0; j < N / 2; j++)
					arr2[i][j] = arr[i][j];
			}
			for (int i = 0; i < N / 2; i++) {
				for (int j = N / 2, j2 = 0; j < N; j++, j2++) {
					swap(*(*arr2 + i * (N / 2) + j2), *(*arr + i * N + j));
				}
			}
			for (int i = N / 2, i2 = 0; i < N; i++, i2++) {
				for (int j = N / 2, j2 = 0; j < N; j++, j2++) {
					swap(*(*arr2 + i2 * (N / 2) + j2), *(*arr + i * N + j));
				}
			}
			for (int i = N / 2, i2 = 0; i < N; i++, i2++) {
				for (int j = 0, j2 = 0; j < N / 2; j++, j2++) {
					swap(*(*arr2 + i2 * (N / 2) + j2), *(*arr + i * N + j));
				}
			}
			for (int i = 0, i2 = 0; i < N / 2; i++, i2++) {
				for (int j = 0, j2 = 0; j < N / 2; j++, j2++) {
					swap(*(*arr2 + i2 * (N / 2) + j2), *(*arr + i * N + j));
				}
			}
			break;
		case 2:
			for (int i = 0, i2 = N / 2; i < N / 2; i++, i2++) {
				for (int j = 0, j2 = N / 2; j < N / 2; j++, j2++) {
					swap(*(*arr + i2 * N + j2), *(*arr + i * N + j));
				}
			}
			for (int i = 0, i2 = N / 2; i < N / 2; i++, i2++) {
				for (int j = 0, j2 = N / 2; j < N / 2; j++, j2++) {
					swap(*(*arr + i2 * N + j), *(*arr + i * N + j2));
				}
			}
			break;
		case 3:
			for (int i = 0, i2 = N / 2; i < N / 2; i++, i2++) {
				for (int j = 0, j2 = 0; j < N / 2; j++, j2++) {
					swap(*(*arr + i2 * N + j2), *(*arr + i * N + j));
				}
			}
			for (int i = 0, i2 = N / 2; i < N / 2; i++, i2++) {
				for (int j = N / 2, j2 = N / 2; j < N; j++, j2++) {
					swap(*(*arr + i2 * N + j2), *(*arr + i * N + j));
				}
			}
			break;
		case 4:
			for (int i = 0, i2 = 0; i < N / 2; i++, i2++) {
				for (int j = 0, j2 = N / 2; j < N / 2; j++, j2++) {
					swap(*(*arr + i2 * N + j2), *(*arr + i * N + j));
				}
			}
			for (int i = N / 2, i2 = N / 2; i < N; i++, i2++) {
				for (int j = 0, j2 = N / 2; j < N / 2; j++, j2++) {
					swap(*(*arr + i2 * N + j2), *(*arr + i * N + j));
				}
			}
			break;
		case 6:
			swapped = true;
			start = 0;
			end = N * N - 1;
			while (swapped) {
				swapped = false;

				for (int i = start; i < end; ++i) {
					if (*(*arr + i) > * (*arr + i + 1)) {
						swap(*(*arr + i), *(*arr + i + 1));
						swapped = true;
					}
				}

				if (!swapped) break;

				--end;
				swapped = false;

				for (int i = end - 1; i >= start; --i) {
					if (*(*arr + i) > * (*arr + i + 1)) {
						swap(*(*arr + i), *(*arr + i + 1));
						swapped = true;
					}
				}

				++start;
			}
			break;
		case 7:
			cout << "\n\n+. К каждому элементу прибавить число\n"
				<< "-. Из каждого элемента вычесть число\n"
				<< "*. Каждый элемент умножить на число\n"
				<< "/. Каждый элемент поделить на число\n"
				<< "Введите символ: ";
			cin >> choice2;
			cout << endl;
			switch (choice2) {
			case '+':
				cout << "Введите число, которое хотите прибавить ко всем элементам: ";
				cin >> number;
				for (int i = 0; i < N * N; i++)
					* (*arr + i) += number;
				break;
			case '-':
				cout << "Введите число, которое хотите вычесть из каждого элемента: ";
				cin >> number;
				for (int i = 0; i < N * N; i++)
					* (*arr + i) -= number;
				break;
			case '*':
				cout << "Введите число, на которое хотите умножить каждый элемент: ";
				cin >> number;
				for (int i = 0; i < N * N; i++)
					* (*arr + i) *= number;
				break;
			case '/':
				cout << "Введите число, на которое хотите поделить каждый элемент: ";
				cin >> number;
				for (int i = 0; i < N * N; i++)
					* (*arr + i) /= number;
				break;
			}
			break;
		case 0:
			bul = false;
			break;
		case 8:
			system("cls");
			for (int k = 0; k < N; k++) {
				for (int l = k; l < N; l++) {
					swap(*(*arr + N * k + l), *(*arr + N * l + k));
					for (int i = 0; i < N; ++i) {
						for (int j = 0; j < N; ++j) {
							cout << setw(4) << *(*arr + i * N + j);
						}
						cout << endl;
					}
					Sleep(300);
					system("cls");
				}
			}
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					cout << setw(4) << *(*arr + i * N + j);
				}
				cout << endl;
			}
			break;
		case 5:
			HANDLE hStdout;
			COORD destCoord;
			hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
			int n = sizeof(arr) / sizeof(*arr);
			int m = sizeof(*arr) / sizeof(**arr);

			int* end = *arr + n * m - 1;
			cout << endl;
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					cout << setw(4) << *(*arr + i * N + j);
				}
				cout << endl;
			}
			break;
		}
	}
}




int main()
{
	setlocale(LC_ALL, "ru-RU");
	int choice;
	do {
		system("cls");
		cout << "Меню:\n";
		cout << "1. Лабораторная 1\n";
		cout << "2. Лабораторная 2\n";
		cout << "3. Лабораторная 3\n";
		cout << "4. Лабораторная 4\n";
		cout << "Введите номер лабораторной работы: ";
		cin >> choice;

		switch (choice) {
		case 1:
			lab1();
			break;
		case 2:
			lab2();
			break;
		case 3:
			lab3();
			break;
		case 4:
			lab4();
			break;
		}
		cout << "\n" << "\n";
		cout << "Нажмите 'x' для очистки консоли и возврата в меню.\n";
		while (true) {
			if (_kbhit()) {
				char ch = _getch();
				if (ch == 'x' || ch == 'X') {
					break;
				}
			}
		}

	} while (choice != 0);

	return 0;
}