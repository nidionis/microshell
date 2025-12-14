#pragma once

#include "searchable_bag.hpp"
#include "tree_bag.hpp"

class searchable_tree_bag : public searchable_bag, public tree_bag {

private:
	bool has_helper(node *n, int value) const;
public:
	searchable_tree_bag();
	searchable_tree_bag(const searchable_tree_bag & other);
	searchable_tree_bag &operator=(const searchable_tree_bag & other);
	virtual ~searchable_tree_bag();
	
	virtual bool has(int value) const;
};
