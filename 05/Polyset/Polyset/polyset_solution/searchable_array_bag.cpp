#include "searchable_array_bag.hpp"
#include "array_bag.hpp"
#define SAB searchable_array_bag
#define AB array_bag

SAB::SAB() : AB(){}
SAB::SAB(const SAB& other) : AB (other){}
SAB& SAB::operator=(const SAB& other){
	if(this != &other)
	{
		AB::operator=(other);
	}
	return *this;
}
SAB::~SAB(){};
bool SAB::has(int value)const{
	for(unsigned int i = 0; value < size; i++)
	{
		if(data[i]== value)
			return true;
	}
	return false;
}

