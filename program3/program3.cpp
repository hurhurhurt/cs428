#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <climits>
#include <algorithm>

using namespace std;

struct node{
  int cost;
  int previous;

  node(int cost, int previous){
    this->cost = cost;
    this->previous = previous;
  }
};


bool checkEdge(vector<vector<int>> &matrix, int num1, int num2){
  if (matrix[num1][num2] != 0)
    return true;
  return false;
}

int main(int argc, char *argv[])
{
  int input;
  cout << "Please enter the # node you want to start with (must be < size of matrix):  ";
  cin >> input;
  cout << input;
  string file_name = argv[1];
  int size = atoi(argv[2]);
  ifstream file(file_name);

  int temp[size][size];
  for (int row = 0; row < size; row++){
    for (int column = 0; column < size; column++){
      file >> temp[row][column];
    }
  }
  file.close();
  
  vector<vector<int>> matrix(size, vector<int> (size, 0));
  for (int row = 0; row < size; row++){
    for (int column = 0; column < size; column++){
      matrix[row][column] = (temp[row][column]);
    }
  }

  vector<int> visited;
  vector<node> nodes;
  for (int i = 0; i < size; i++){
    visited.push_back(0);
  }
  string path = "0";
  /* INITIALIZATION */
  for (int i =0; i < size; i++){
    if (checkEdge(matrix, 0, i)){ // edge
      nodes.push_back(node(matrix[0][i], 0));
    }
    else{ // not an edge
      nodes.push_back(node(INT_MAX, INT_MAX));
    }
  }

  cout << "STEP\tPATH\t";
  for (int i = 0; i < size; i++){
    cout << "NODE" << i << "\t";
  }
  cout << endl << "0\t0\t";
  for (node n : nodes){
    if (n.cost == INT_MAX && n.previous == INT_MAX){
      cout << "null\t";
    }
    else{
      cout << n.cost << "," << n.previous << "\t";
    }
  }
  cout << endl;
 
  for (int i = 1; i < size; i++){
    node lowest(INT_MAX, 0);
    for (int j = 1; j < nodes.size(); j++){
      if (nodes[j].cost < lowest.cost){
	lowest.cost = nodes[j].cost;
	lowest.previous = j;
      }
      // now lowest holds curr min & the corresponding node
    }
    path.append(to_string(lowest.previous)); // path now adds the lowest cost node
    visited[lowest.previous] = 1;
   
    // recalculate nodes with next lowest
    for (int k = 1; k < nodes.size(); k++){
      if (k != lowest.previous && visited[k] != 1 && checkEdge(matrix, lowest.previous, k)){
	if (lowest.cost + matrix[lowest.previous][k] <= nodes[k].cost){
	  nodes[k].cost = lowest.cost + matrix[lowest.previous][k];
	  nodes[k].previous = lowest.previous;
	}
      }
    }
    nodes[lowest.previous].cost = 10000;

    cout << i << "\t" << path << "\t";
    for (int n = 0; n < nodes.size(); n++){
      if (nodes[n].cost == INT_MAX && nodes[n].previous == INT_MAX){
	cout << "null\t";
      }
      else if (nodes[n].cost == 10000){
	cout << " \t";
      }
      else{
	cout << nodes[n].cost << "," << nodes[n].previous << "\t";
      }
    }
    cout << endl;
  }
  
  /*
  vector<int> dist;
  vector<bool> included;
  for (int i = 0; i < size; i++){
    dist.push_back(INT_MAX);
    included.push_back(false);
  }
  dist[0] = 0;

  for (int i = 0; i < size -1; i++){
    int min = minDistance(dist, included, size);
    included[min] = true;
    for (int j = 0; j < size; j++){
      if (!included[j] && matrix[min][j] && dist[min] != INT_MAX && dist[min] + matrix[min][j] < dist[j]){
	dist[j] = dist[min] + matrix[min][j];
      }
    }
  }

  cout << "Vertex \t\t Distance from Source" << endl;
  for (int i = 0; i < size; i++)
    cout << i << "\t\t" << dist[i] << endl;
 
  */
}
