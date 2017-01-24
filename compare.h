#pragma once
#include<iostream>
using namespace std;

template <class C>
struct compare_func {
	const static int GREATER = 2;
	const static int SMALLER = 0;
	const static int EQUAL = 1;
	bool(*compare)(C, C);
};