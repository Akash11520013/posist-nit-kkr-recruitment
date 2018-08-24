
#include<bits/stdc++.h>

using namespace std;

long long rootsum = 0;
long long countnode = 0;
long long restsum = 0;

class Node {
	public:
	time_t timestamp;
	string data;
	long long nodeNumber;
	string nodeId;
	Node* parent;
	vector<Node*> child;
	string root;
	string hashValue;
	int isroot = 0;
	
	Node(string d) {
		timestamp = time(0);
		data = d;
		nodeNumber = ++countnode;
		nodeId = to_string(nodeNumber);
		parent = NULL;
		root = "1";
		if (countnode == 1) {
			isroot = 1;
			rootsum = stoi(d);
		}
		encrypt();
	}
	
	void setParent(Node* par) {
		if (nodeNumber != 1)
			parent = par;
	}
	
	void encrypt() {
		for (int i = 0; i < data.size(); i++) {
			data[i] += 3;
		}
	}

	void decrypt() {
		for (int i = 0; i < data.size(); i++) {
			data[i] -= 3;
		}
	}
};

Node* createGenesis(string data) {
	Node* root = new Node(data);
	return root;
}

Node* find(Node* root, string nodeid) {
	if (!root)
		return NULL;
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* temp = q.front();
		q.pop();
		if (temp->nodeId == nodeid)
			return temp;
		for (int i = 0; i < temp->child.size(); i++) {
			q.push(temp->child[i]);
		}
	}
	return NULL;
}

void editValue(Node* root, string d) {
	int n = stoi(d);
	int a = stoi(root->data);
	if (rootsum - (restsum - a + n) >= 0)
		root->data = d;
	else
		cout << "\nNot possible to modify data.\n";
}

void addChildren(Node* root, int n) {
	string val;
	for (int i = 0; i < n; i++) {
		cout << "Enter value of child " << i + 1 << " : ";
		cin >> val;
		if (rootsum - restsum < stoi(val)) {
			cout << "Cannot create this child.\n";
		}
		else {
			Node* child = new Node(val);
			root->child.push_back(child);
			restsum += stoi(val);
		}
	}
}


int longestchain(Node* root) {
    // Base case
    if (!root)
        return 0;
 
    // Check for all children and find the maximum depth
    int maxdepth = 0;
    for (auto it = root->child.begin(); it != root->child.end(); it++)
        maxdepth = max(maxdepth, longestchain(*it));
 
    return maxdepth + 1;

}

void merge(Node* a, Node* b) {
	int a_len = longestchain(a);
	int b_len = longestchain(b);
	if (a_len >= b_len) {
		Node* par_b = b->parent;
		for (int i = 0; i < b->child.size(); i++) {
			par_b->child.push_back(b->child[i]);
		}
		int a_data = stoi(a->data) + stoi(b->data);
		a->data = to_string(a_data);
		b->child.clear();
		for (int i = 0; i < par_b->child.size(); i++) {
			if (par_b->child[i] == b) {
				par_b->child.erase(par_b->child.begin() + i);
				break;
			}
		}
		delete(b);
	}
}

int main() 
{
	int ch = 0;
	Node* genesis;
	while (true) {
		cout << "Enter 1 to create genesis node.\n";
		cout << "Enter 2 to create children of a node.\n";
		cout << "Enter 3 to edit value of a node.\n";
		cout << "Enter 4 to find longest chain of a node.\n";
		cout << "Enter 5 to merge 2 nodes.\n";
		cout << "Enter 6 to exit.\n";
		cin >> ch;
		string nodeId;
		switch(ch) {
			case 1: if (countnode == 0) {
						string data;
						cout << "Enter data: ";
						cin >> data;
						genesis = createGenesis(data);
					}
					break;
			case 2: 
					int n;
					cout << "Enter nodeId and number of children to add : ";
					cin >> nodeId;
					cin >> n;
					Node* temp = find(genesis, nodeId);
					addChildren(temp, n);
					break;
			case 3:	string data;
					cout << "Enter NodeId and new data : ";
					cin << nodeId;
					cin >> data;
					Node* temp = find(genesis, nodeId);
					Editnode(temp, data);
					break;
			case 4:	
					cout << "Enter NodeId : ";
					cin << nodeId;
					Node* temp = find(genesis, nodeId);
					cout << longestchain(temp);
					break;
			case 5:	string a, b;
					cout << "Enter NodeId of first and second node : ";
					cin >> a >> b;
					Node* aaa = find(genesis, a);
					Node* bbb = find(genesis, b);
					merge(aaa, bbb);
					break;
			case 6:	exit();
			default:cout << "Enter a valid number.\n";
		}
	}
	return 0;
}









