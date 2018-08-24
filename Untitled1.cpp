#include<bits/stdc++.h>
#define ll long long
#define INF 1002000
#define mod 1000000007
using namespace std;

static int id = 1;

typedef struct timestamp{
	int day,month,year;
};

typedef struct node{
	int node_number;
	timestamp t;
	string data , node_id , referenceNodeId , childReferenceId , genesisReferenceid , HashValue;
};

string encryptData(string data , string hash ,string ownerKey){
	if(ownerKey != hash ) // if key doesn't match hash key
		return NULL; 
	string temp;
	for(int i=0;i<data.size(); ++i) // replace each character in data string with its position in hash string
		temp.push_back(hash.find(data[i]) - data.begin());	
	return temp;
}

string decryptData(string data ,string hash){
	string temp;
	for(int i=0;i<data.size();++i)
		temp.push_back(hash[data[i]]);
	return temp;
}

int main(){
	
	//1.Genesis Node
	
	node * genesisNode = (node *)malloc(sizeof(node)); 
	genesisNode -> node_number =id;
	genesisNode -> node_id = to_string(id++);
	genesisNode -> genesisReferenceid = NULL;
	
	//2.Child Node
	
	node* childNode = (node*)malloc(sizeof(node));
	childNode -> node_number =id;
	childNode -> node_id = to_string(id++);
	childNode -> genesisReferenceid = genesisNode -> node_id;
	childNode -> referenceNodeId = genesisNode -> node_id;
	genesisNode -> childReferenceId = childNode -> node_id;
	
	//3.Encrypt Data
	childNode -> data = encryptData(childNode -> data, childNode->HashValue ,childNode ->HashValue );
	
	//4.Decrypt Data
	childNode ->data = decryptData( childNode->data ,childNode->HashValue);

}
