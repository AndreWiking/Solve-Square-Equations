// Компилирую в Visual Studio
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define UT 6 // Количество Unit тестов

#define UNIT_TESTS  

// Проверяем число на близость к 0
char isNull(double a) {
	if (fabs(a) < 0.000000001) return 1;
	else return 0;
}

// Проверяем числа на равность с учётом погрешности
char isEqual(double a, double b) {
	if (fabs(a - b) < 0.000001) return 1;
	else return 0;
}

// Выводим корень уравнения
void PrintAns(int n, double x) {
	printf("x%d = %lf\n", n, isNull(x) ? 0.0 : x);
}

// Решение квадратного уравнения
// ax^2 + bx + c = 0
// a - старший коэффициент
// b - средний коэффициент
// c - свободный член
// *x - указатель на массив решений
// Solve возвращает колличетсво решений.
int Solve(double a, double b, double c, double* x) {

	// Рассматриваем случаи при нулевых коэффициентах
	if (isNull(a) && isNull(b) && isNull(c)) return -1;
	else if (isNull(a) && isNull(b)) return 0;
	else if (isNull(a)) {
		x[0] = -c / b;
		return 1;
	}

	double D = b * b - 4 * a * c;

	if (isNull(D)) {
		x[0] = -b / a / 2.0;
		return 1;
	}
	else if (D > 0) {
		x[0] = (-b + sqrt(D)) / a / 2.0;
		x[1] = (-b - sqrt(D)) / a / 2.0;
		return 2;
	}
	else return 0;
}


int main() {

#ifdef UNIT_TESTS
	
	double at[UT], bt[UT], ct[UT], xt[UT][2];
	int nt[UT];

	double xr[UT][2];
	int nr[UT];

	// Unit Test 1
	at[0] = 4.0, bt[0] = 5.0, ct[0] = -2.0;
	nr[0] = 2;
	xr[0][0] = 0.318729;
	xr[0][1] = -1.568729;

	// Unit Test 2
	at[1] = 1.0, bt[1] = 2.0, ct[1] = 1.0;
	nr[1] = 1;
	xr[1][0] = -1.0;

	// Unit Test 3
	at[2] = 3.6, bt[2] = 2.1, ct[2] = 5.55;
	nr[2] = 0;

	// Unit Test 4
	at[3] = 11.88, bt[3] = 0.0, ct[3] = 0.0;
	nr[3] = 1;
	xr[3][0] = 0.0;

	// Unit Test 5
	at[4] = 0.0, bt[4] = 0.0, ct[4] = 0.0;
	nr[4] = -1;

	// Unit Test 6
	at[5] = -6.0, bt[5] = 0.0, ct[5] = 1.6;
	nr[5] = 2;
	xr[5][0] = 0.516398;
	xr[5][1] = -0.516398;

	// Проверка функции Solve Unit тестами
	for (int k = 0; k < UT; ++k) {

		nt[k] = Solve(at[k], bt[k], ct[k], xt[k]);

		if (nt[k] != nr[k]) fprintf(stderr, "Solve Faile (Unit Test %d)\n", k + 1);
		else {
			char f = 0;
			if (nt[k] == 1 && !isEqual(xt[k][0], xr[k][0])) f = 1;
			if (nt[k] == 2 && !(isEqual(xt[k][0], xr[k][0]) && isEqual(xt[k][1], xr[k][1])) &&
					!(isEqual(xt[k][0], xr[k][1]) && isEqual(xt[k][1], xr[k][0]))) f = 1;
		
			if (f) fprintf(stderr, "Solve Faile (Unit Test %d)\n", k + 1);
		}
	}

#endif // UNIT_TESTS

	printf("ax^2 + bx + c = 0\n");
	
	double a, b, c;

	// Считываем коэффиценты
	printf("a = "); scanf("%lf", &a);
	printf("b = "); scanf("%lf", &b);
	printf("c = "); scanf("%lf", &c);

	// Решаем уравнение
	double x[2];
	int n = Solve(a, b, c, x);

	// Выводим ответ
	if (n == -1) printf("Any X\n");
	else if (n == 0) printf("No Solution\n");
	else {
		for (int i = 0; i < n; ++i)
			PrintAns(i + 1, *(x + i));
	}

	return 0;
}
