#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char *argv){
	enum days {SUN, MON, TUES, WED, THUR, FRI, SAT};
	
	enum days d;
	d = WED;
	
	cout << d;
	
}
