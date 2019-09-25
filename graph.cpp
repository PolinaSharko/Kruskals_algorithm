using namespace std;
#include "graph.h"


/*!Graph is considered
@param gr
Has a list of graph
@param index
Keeps indexes of tree, including minimal tree
@param EW - Egdes and weights
Keeps weigths and numbers of nodes making edge
@param min_tree Keeps minimal tree
*/
/*!
Load graph from file
@param [in] f file is used for loading graph.
Throwing exception if file not found or uncorrectly opend
*/
graph::graph(ifstream &f) {
	if (!f.is_open()) {
		throw exception("File wasn't found");
	}
	else {
		string s;
		f.seekg(0);
		f.clear();
		int i = 0;
		int k = 0;
		while (!f.eof()) { 
			getline(f, s, '\n');
			i++;
		}
		f.seekg(0);
		f.clear();
		gr.resize(i);
		i = 0;
		while (!f.eof()) { //считываем граф и стоимости ребер из файла
			{	getline(f, s, '\n');
				std::stringstream ss(s);
				int buf = 0;
				while (ss >> buf) {
					gr[i].push_back(buf);
				}
				i++;
			}
		}

		int t = 0;
		for (size_t i = 0; i < gr.size() - 1; i++) //заполняем массив вершин, образующих ребра 
		{
			std::list<int>::const_iterator it_b = gr[i].begin();
			std::list<int>::const_iterator it_e = gr[i].end();
			for (it_b; it_b != it_e; it_b++)
			{
				std::pair<pair<int, int>, int> tmp;
				tmp.first.first = i;
				tmp.first.second = *it_b;
				tmp.second = 0;
				if (EW.size() == 0)
					EW.push_back(tmp);
				else {
					for (int n = 0; n < EW.size(); n++) {
						if ((tmp.first.first == EW[n].first.second) && (tmp.first.second == EW[n].first.first)) {
							k = 0;
							break;
						}
						else k++;
					}
					if (k == EW.size()) {
						EW.push_back(tmp);
						k = 0;
					}
				}
			}
		}
		int p = 0;
		std::list<int>::const_iterator it_b = gr[gr.size() - 1].begin();
		std::list<int>::const_iterator it_e = gr[gr.size() - 1].end();
		for (it_b; it_b != it_e; it_b++) {
			if (p < EW.size()) {
				EW[p].second = *it_b;
				p++;
			}
			else break;
		}
		for (int i = 0; i < EW.size(); i++) { cout << '{' << EW[i].first.first << ',' << EW[i].first.second << "} "; }
		cout << endl;
	}
	f.close();
};


/*!
Bubble sort function
*/
void graph::bubble_sort() {
	clock_t time = clock();
	for (int i = EW.size()-1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (EW[j].second > EW[j + 1].second)
			{
				swap(EW[j + 1], EW[j]);
			}
		}
	}
	for (int i = 0; i < EW.size(); i++) { cout << '{' << EW[i].first.first << ',' << EW[i].first.second << "} "; }
	cout<<endl;
	cout << "sort time: "<<(double((clock() - time)) / 1000) << ' ' << endl;
};



/*!
Finding minimal tree function
*/
void graph::find_min_tree() {
	clock_t time = clock();
	int cost = 0;
	vector<int> nodes(gr.size()-1);
	for (int i = 0; i < gr.size() - 1; ++i) {
		nodes[i] = i;
	}
	for (int i = 0; i<EW.size(); ++i)
	{
		if (nodes[EW[i].first.first] != nodes[EW[i].first.second])
		{
			cost += EW[i].second;
			min_tree.push_back(make_pair(EW[i].first.first, EW[i].first.second));
			index.push_back(i);
			int old_nodes = nodes[EW[i].first.second], new_nodes = nodes[EW[i].first.first];
			for (int j = 0; j < gr.size() - 1; ++j) {
				if (nodes[j] == old_nodes)
					nodes[j] = new_nodes;
			}
		}
	}
	cout << "finding tree time for method 1: " << double(clock() - time) / double(CLK_TCK) << endl;
	for (int i = 0; i < min_tree.size(); i++) { cout << '{' << min_tree[i].first << ',' << min_tree[i].second << "} "; }
	cout << endl;
};

/*!
Makes graphviz file
@param [in] index - indexes of min tree
@param [out] graph_res - result graphviz file
*/
const void graph::make_graphviz(vector<int> index, ofstream &graph_res) {
	char k = '"';
	int j = 0;
	graph_res << "graph first { node [shape = circle] " << endl;
	for (int i = 0; i < EW.size(); i++) {
	graph_res << EW[i].first.first << "--" << EW[i].first.second << ' ';
		for (int j = 0; j < index.size(); j++) {
			if (index[j] == i) {
				graph_res << "[color=red]" << endl;
			}
		}
		graph_res << " [label=" << k << EW[i].second << k << "]" << endl;
	}
	graph_res << '}' << endl;
};




/*!Sort tree is considered
@param tree keeps egdes and weigths
*/

/*! add element to the binary heap
@param [in] a is added element
*/
void sort_tree::add_to_heap(pair<pair<int, int>, int> &a) {
	int parent = 0;
	int i = tree.size();
	tree.push_back(a);
	parent = (i - 1) / 2; 
	while (i > 0)
	{ if (tree[parent].second > tree[i].second)
		swap(tree[i], tree[parent]);
		i = parent;
		parent = (i - 1) / 2;
	}
}

/*!sorting binary heap
@param [in] i - index of node for start sorting
*/
void sort_tree:: heapify(int i)
{
	int left_child = 2 * i + 1;
	int	right_child = 2 * i + 2;
	if (left_child < tree.size()) {
		if (tree[i].second > tree[left_child].second) {
			swap(tree[i], tree[left_child]);
			heapify(left_child);
		}
	}
	if (right_child < tree.size()) {
		if (tree[i].second > tree[right_child].second) {
			swap(tree[i], tree[right_child]);
			heapify(right_child);
		}
	}
}
/*! Get minimal element of binary heap
@return pair<pair<int, int>, int> min - minimal element
*/
	pair<pair<int, int>, int> sort_tree::get_min() {
	pair<pair<int, int>, int> i = tree[0];
	tree[0] = tree[tree.size() - 1];
	tree.pop_back();
	heapify(0);
	return(i);
}

	/*!
	Saves sorted tree
	*/
	void sort_tree::sorted() {
	clock_t time = clock();
	vector<pair<pair<int, int>, int>> tmp = tree;
	vector<pair<pair<int, int>, int>> tmp1;
	for (int i = 0; i < tmp.size(); i++) tmp1.push_back(get_min());
	tree = tmp1;
	cout << "sort time: " << (double((clock() - time)) / 1000) << ' '<<endl;
}



/*! Shows sorted tree
*/
const void sort_tree::show_tree()  {
	for (int i = 0; i < tree.size(); i++) { cout << '{' << tree[i].first.first << ',' << tree[i].first.second << "} "; }
	cout << endl;		
}


/*!
@param rank - keeps ranks of the nodoes
@param parent - keeps parents of nodes
@param diff - check difference between parent
@param index - keeps index of minimal tree
@param min_tree_ - keeps minimal tree
*/

/*! Makes set from nodes
@param i - added nodes
@param &a - graph*/
void node_set::make_set(int i, graph &a) {
	parent.resize(a.get_gr_size());
	rank.resize(a.get_gr_size());
	diff.resize(a.get_gr_size());
	parent[i] = i;
	diff = parent;
	rank[i] = 0;

}

/*! find node in the union
@param [in] i - node
@return a - which union is include the node*/
int node_set::find(int i) {
	if (i == parent[i])
		return i;
	return find(parent[i]);
}


/*! Add nodes to the union
@param [in] a - first node
@param [in] b - second node*/
void node_set::unite(int a, int b) {
	a = find(a);
	b = find(b);
	if (a != b) {
		if (rank[a] < rank[b])
			swap(a, b);
		parent[b] = a;
		if (rank[a] == rank[b])
			++rank[a];
	}
}

/*! find minimal tree
@param [in] &tree - sorted tree to find the minimal one
*/
void node_set::find_min_tree_(sort_tree &tree) {
	clock_t time = clock();
	int k = 0; 
	int d = 0;
	for (int i = 0; i < tree.get_tree().size(); i++) {
		k = tree.get_tree()[i].first.first;
		d = tree.get_tree()[i].first.second;
		unite(k,d);
		if (diff != parent) {
			min_tree_.push_back(make_pair(tree.get_tree()[i].first.first, tree.get_tree()[i].first.second)); index.push_back(i);
			diff = parent; }
		}
	cout << "finding tree time for method 2: " << double(clock()-time) / double(CLK_TCK) << endl;
	for (int i = 0; i < min_tree_.size(); i++) { cout << '{' << min_tree_[i].first << ',' << min_tree_[i].second << "} "; }
	cout << endl;
};