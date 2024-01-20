#include <iostream>
#include <math.h>
#include <iomanip>
#include <windows.h>
using namespace std;
int vibor;			//пользовательский выбор
double a;			//пользовательские значения
double b;
double returned_a;	 //получаемые из реестра значения
double returned_b;

/// <summary>
/// GetFunction method
/// </summary>
double f(double x) //функция возвращающая подынтегральное выражение
{
	return 1 / (x * log(x)); //подынтегральное выражение
}

/// <summary>
/// reshenie method solving integrals
/// </summary>
void reshenie(double m, double l) //функция решения определенного интеграла от m(a) до l(b)
{
	int n; //число отрезков разбиения
	int k; //число нулей после запятой в ответе
	cout << "\nРешение определенного интеграла методом левых прямоугольников" << "\na = " << m << "\nb = " << l << endl << "\nВведите число отрезков разбиения:\n";
	try //в функциях ввода n и k проверяем исключения ввода неопределенного символа
	{
		cin >> n;
	}
	catch (istream::failure e)
	{
		cerr << "Exeption: unidentified characters\n";
		exit(0);
	}
	cout << "\nВведите число сиволов после запятой в ответе:\n";
	try
	{
		cin >> k;
	}
	catch (istream::failure e)
	{
		cerr << "Exeption: unidentified characters\n";
		exit(0);
	}

	double s = (f(m) + f(l)) / 2; //решаем интеграл методом левых прямоугольников
	double h = (l - m) / n;
	for (int i = 1; i <= n - 1; i++)
	{
		s += f(m + i * h);
	}
	double I = h * s;
	cout << "\nОтвет:\n";
	cout << setprecision(k) << I << endl; //выводим интеграл с k символами после запятой
}

/// <summary>
/// sozdanie reestra
/// </summary>
int sozdanie(double x, double y) //функция создания реестра, где x(a), а y(b)
{
	HKEY hKey = NULL; //создаем дескриптор раздела
	if (RegOpenKey(HKEY_CURRENT_USER, L"SOFTWARE", &hKey) != ERROR_SUCCESS) //Открываем ключ в реестре и записываем его путь в Hkey
	{																		//при помощи if проверяем успешность открытия ключа (ERROR_SUCCESS - удачное выполнение)
		return 1;															//возвращаем ошибку - 1 при неудаче
	}
	if (RegCreateKey(hKey, L"Работа 5", &hKey) != ERROR_SUCCESS)			//Создаем новый ключ по пути hKey и задаем в hKey новый путь к созданному ключу
	{																		//проверяем успешность выполнения
		return 1;
	}
	BYTE* data_a = (BYTE*)calloc(1, 4);										//Создаем переменные типа BYTE* со значениями x и y
	data_a[1] = x;
	BYTE* data_b = (BYTE*)calloc(1, 4);
	data_b[1] = y;
	if (LSTATUS status_a = RegSetValueEx(hKey, L"PARAM_a", NULL, REG_DWORD, data_a, 4) != ERROR_SUCCESS)	//Записываем в наш созданный ключ параметры x и y типа BYTE*
	{																										//проверяем успешность создания параметров
		return 1;
	}
	if (LSTATUS status_b = RegSetValueEx(hKey, L"PARAM_b", NULL, REG_DWORD, data_b, 4) != ERROR_SUCCESS)
	{
		return 1;
	}
	RegCloseKey(hKey);	//Закрываем дескриптор
	return 0;
}

/// <summary>
/// chtenie reestra
/// </summary>
int chtenie() { //функция чтения реестра
	HKEY hkey = NULL;																					//Создаем дескриптор
	LONG error = RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Работа 5", NULL, KEY_QUERY_VALUE, &hkey);	//создаем переменную, в которой открываем наш ключ
	if (error == ERROR_SUCCESS)	//Проверяем успешность открытия нашего ключа
	{
		unsigned int buffer_a(MAX_PATH); //Создаем переменные, в которые запишем наши получаемые параметры
		DWORD buffersize_a = MAX_PATH;
		unsigned int buffer_b(MAX_PATH);
		DWORD buffersize_b = MAX_PATH;
		LONG result_a = RegQueryValueEx(hkey, L"PARAM_a", NULL, NULL, (LPBYTE)&buffer_a, &buffersize_a);	//считываем параметры из реестра и
		if (result_a != ERROR_SUCCESS)																		//проверяем успешность выполнения
		{
			return 1;
		}
		LONG result_b = RegQueryValueEx(hkey, L"PARAM_b", NULL, NULL, (LPBYTE)&buffer_b, &buffersize_b);
		if (result_b != ERROR_SUCCESS)
		{
			return 1;
		}
		returned_a = (int)buffer_a / 256;	//записываем полученные переменные и
		returned_b = (int)buffer_b / 256;	//делим их на 256, чтобы получить их изначальное значение типа int
	}
	else {
		return 1;
	}
	return 0;
}

/// <summary>
/// main method
/// </summary>
int main()
{
	cin.exceptions(istream::failbit | istream::failbit); //Задаем исключения
	setlocale(LC_ALL, "ru");							//включаем поддержку русских символов
	cout << "Для введения пользовательский данных введите 1\n"				//создаем небольшой пользовательский интерфейс с элементами выбора
		<< "Для использования сохраненных в реестре данных введите 2\n";	//и добавляем в интерфейс обработку исключений
	try
	{
		cin >> vibor;
	}
	catch (istream::failure e)
	{
		cerr << "Exeption: unidentified characters\n";
		exit(0);
	}
	if (vibor == 1) {
		cout << "Введите a:\n";
		try
		{
			cin >> a;
		}
		catch (istream::failure e)
		{
			cerr << "Exeption: unidentified characters\n";
			exit(0);
		}
		cout << "Введите b:\n";
		try
		{
			cin >> b;
		}
		catch (istream::failure e)
		{
			cerr << "Exeption: unidentified characters\n";
			exit(0);
		}
		cout << "Желаете ли вы сохранить новые данные в реестр, введите 1 - да, 2 - нет\n";
		cin >> vibor;
		if (vibor == 1) {
			if (sozdanie(a, b) == 1)
			{
				cerr << "Error sozdania";
				return 1;
			}
		}
		else {
			if (vibor != 2) {
				cout << "Ошибка Ввода";
				return 1;
			}
		}
		reshenie(a, b);
	}
	else {
		if (vibor == 2) {
			if (chtenie() == 1)
			{
				cerr << "Error chtenia";
				return 1;
			}
			reshenie(returned_a, returned_b);
		}
		else {
			cout << "Ошибка Ввода";
			return 1;
		}
	}
	system("pause");
	return 0;
}
