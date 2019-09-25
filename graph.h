#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <ctime>

/*! \brief Class graph keeps undirected graph.*/
class graph {
private:
	std::vector<std::list<int>> gr;
	std::vector<int> index;
	std::vector <std::pair<std::pair<int, int>, int>> EW;
	std::vector<std::pair<int, int>> min_tree;
public:
	graph(std::ifstream &f);
	void bubble_sort();
	void find_min_tree();

	/*!
	Get size of graph
	@return size - graph size
	*/
	int get_gr_size() { return gr.size() - 1; } 
	
	/*!
	Get indexes of minimal tree
	@return std::vector<int> index - indexes of minimal tree
	*/
	std::vector<int> get_index() { return this->index; }

	/*!
	Get vector of weigths and numbers of nodes making edges
	@return vector<pair<pair<int,int>, int>> EW vector of weight and edges
	*/
	std::vector<std::pair<std::pair<int,int>, int>> get_w() {return this->EW;}
	
	/*!
	Set new vector of weigths and numbers of nodes making edges
	@param [in] a - vector of egdes and weights
	*/
	void set_w(std::vector<std::pair<std::pair<int, int>, int>> a) { this->EW = a; }
	const void make_graphviz(std::vector<int> index, std::ofstream &graph_res);
};



/*! \brief Class considered sorted tree structure*/
class sort_tree {
private:	
	std::vector<std::pair<std::pair<int, int>, int>> tree;
public:
	void add_to_heap(std::pair<std::pair<int, int>, int> &a);
	void heapify(int i);
	const void show_tree();

	/*! Get sorted tree
	@return std::vector<pair<pair<int, int>, int>> tree vector of sorted tree
	*/
	std::vector<std::pair<std::pair<int, int>, int>> get_tree() { return this->tree; }
	std::pair<std::pair<int, int>, int> get_min();
	void sorted();
};

/*! \brief class is considered disjoint-set-union structure*/
class node_set {
private:
	std::vector<int> rank;
	std::vector<int> parent;
	std::vector<int> diff;
	std::vector<int> index;
	std::vector<std::pair<int, int>> min_tree_;
public:
	node_set() {};
	void make_set(int i, graph &a);
	void unite(int a, int b);
	int find(int i);
	void find_min_tree_(sort_tree &tree);
	/*! Get indexes of minimal tree
	@return vector<int> index */
	std::vector<int> get_index() { return this->index;}
};