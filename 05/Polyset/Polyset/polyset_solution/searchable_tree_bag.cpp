#include "searchable_tree_bag.hpp"

#define STB searchable_tree_bag
#define TB tree_bag
	
STB::STB() : TB(){}
STB::STB(const STB& other) : TB (other){}
STB& STB::operator=(const STB& other){
	if(this != &other)
	{
		TB::operator=(other);
	}
	return *this;
}
STB::~STB(){};
bool STB::has(int value)const{
	return has_helper(tree, value);
}

bool STB::has_helper(node *n, int value) const{
	//check nullptr
	if(n == nullptr)
		return false;
	//check ==value
	if (n->value == value)
		return true;
	//recursive call
	if(value < n->value)
		return has_helper(n->l, value);
	else
		return has_helper(n->r, value);

}
