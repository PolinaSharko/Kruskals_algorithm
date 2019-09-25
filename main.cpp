using namespace std;
#include "graph.h"




/*! Function takes 2 input parameters
@param int argc - parameter acceps a number of commands
@param char* argv[] - parameter takes the value of the parameters*/
int main(int argc, char* argv[]) {
	/*source\repos\Project31\Debug\Project31.exe 3 1 "C:\Users\Ўмель\source\repos\Project31\Project31\graph.txt" "C:\Users\Ўмель\source\repos\Project31\Project31\res121.dot"*/

	std::string file_name = argv[3];
	std::string res_name = argv[4];
	try {
		ifstream gr(file_name);
		ofstream res(res_name);
		graph d(gr);
		if (atoi(argv[2]) == 1) {
			std::cout << "bubble sort" << std::endl;
			d.bubble_sort();
			d.find_min_tree();
			d.make_graphviz(d.get_index(), res);
		}
		if (atoi(argv[2]) == 2) {
			std::cout << "binary tree sort" << std::endl;
			sort_tree tree;
			for (int i = 0; i < d.get_w().size(); i++) {
				tree.add_to_heap(d.get_w()[i]);
			}
			tree.sorted();
			tree.show_tree();
			node_set a0;
			for (int i = 0; i < d.get_gr_size(); i++)
			{
				a0.make_set(i, d);
			}
			a0.find_min_tree_(tree);
			d.set_w(tree.get_tree());
			d.make_graphviz(a0.get_index(), res);
		}
	}
	catch (std::exception &ex) {
		std::cout << ex.what();
	}
		system("pause");
}