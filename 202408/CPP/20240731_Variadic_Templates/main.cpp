#include <iostream>
#include <vector>
#include <algorithm>
#include <sys/resource.h>
#include <unistd.h>

template <typename T>
void print(T arg) 
{
	std::cout << arg << '\n';
}

template <typename T, typename... Args>
void print(T first, Args... rest)
{
	std::cout << first << ' ';
	print(rest...);
}

void wlc_test()
{
	std::cout << "wlc" << std::endl;
	std::cout << "wlc" << std::endl;

}

void test()
{
	const int N = 50;
	auto fibonacci = [N]() {
		std::vector<int> sequence;
		int a = 1, b = 1;

		sequence.push_back(a);
		if (N > 1) {
			sequence.push_back(b);
		}

		for (int i = 2; i != N; i++) {
				int next = a + b;
				sequence.push_back(next);
				a = b;
				b = next;
			}
		return sequence;
	};
	std::vector<int> fib_sequence = fibonacci();
	std::for_each(fib_sequence.begin(), fib_sequence.end(), [](int x) {
			std::cout << x << std::endl;
		}
	);
}

void test_2()
{
	int N = 100000;
	int* p = &N;
	for (int i = 0; i != N; ++i) {
			for (int j = 0; j != N; ++j) 
					p = &N;
	}
}

void test_3()
{
	test_2();
	struct rusage usage;
	getrusage(RUSAGE_SELF, &usage);

	std::cout << "user cpu time : " << usage.ru_utime.tv_sec << "s"
				<< usage.ru_utime.tv_usec <<  "us\n";
	std::cout << "system cpu time : " << usage.ru_stime.tv_sec << "s"
				<< usage.ru_stime.tv_usec <<  "us\n";

}

int main()
{
	print(1, 2, 3, 5, 7, 11, 13, "wlc", "2.5");
	wlc_test();
	//test();
	//test_2();
	test_3();
	return 0;
}
