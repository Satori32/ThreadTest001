#include <iostream>
#include <thread>
#include <tuple>
#include<atomic>

//not develop complete.
//cant run on vc++

template<class T, class ...Arg>
class MyThread {

public:
	MyThread(const T& F, Arg&... P) :Tr(
		[&](Arg&&... P) {IsR = true;F(P...);IsR = false;}
	) {}

		bool IsRunning() {
			return IsR;
		}

		operator std::thread& () {
			return Tr;
		}
		/**/
		std::thread& Get() {
			return Tr;
		}
		/**/
protected:
	std::thread Tr;
	bool IsR = false;
};
/*
template<class T,class ...A>
MyThread<T, A...> RunThead(T F, A&&... P) {
	return MyThread<T,A...>(F, A...);
}
*/
template<class T, class ...A>
MyThread<T, A...> RunThead(T F, A&... P) {
	return MyThread<T, A...>(F, P...);
}
int main() {

	volatile bool S(true);

	auto F = [&]() {while (S) {
		std::cout << "Running." << std::endl;
	} };

	auto T = RunThead(F);

	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	S=false;
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	std::cout << "A" << std::endl;

	T.Get().join();
	std::cout << "B" << std::endl;

	return 0;
}