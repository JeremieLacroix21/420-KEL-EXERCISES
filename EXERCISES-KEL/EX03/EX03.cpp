// EX03.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;



template<class F, class ... Args>
auto test(F f, Args&& ... args)
{
	auto pre = high_resolution_clock::now();
	auto res = f(std::forward<Args>(args)...);
	auto post = high_resolution_clock::now();
	return pair(res, post - pre);

}

vector<double> f(vector<double> v)
{
	for (auto& x : v)
		x = sqrt(x);
	return v;
}
void g(vector<double> v)
{
	for (auto& x : v)
		x = sqrt(x);
}

int main()
{
	enum { N = 10'000'000 };
	vector<double> v(N);
	for (int i = 0; i != N; i++)
	{
		v[i] = i + 1;
	}
	auto [r0, dt0] = test([v]() mutable
		{
			v = f(v);
			return v.back();
		});

	auto [r1, dt1] = test([v]() mutable
		{
			g(v);
			return v.back();
		});

	auto [r2, dt2] = test([v]() mutable
		{
			v = f(std::move(v));
			return v.back();
		});
	cout << "v = f(v)" << duration_cast<microseconds>(dt0).count() << "us." << endl;
	cout << "g(v)" << duration_cast<microseconds>(dt1).count() << "us." << endl;
	cout << "v = f(std::move(v));" << duration_cast<microseconds>(dt1).count() << "us." << endl;
}



