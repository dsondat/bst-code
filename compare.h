#pragma once
#include<iostream>
using namespace std;

template <class C>
struct compare_func {
	int(*compare)(C, C);
}; 

struct compare_unit {
	const static int GREATER = 2;
	const static int SMALLER = 0;
	const static int EQUAL = 1;
};