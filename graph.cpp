#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "vertex.cpp"

using namespace std;

class Graph {
private:
    bool directed;
    vector<Vertex*> vertices;
    map<pair<Vertex*, Vertex*>, int> matrix;

    Vertex* getVertex(char label) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i]->getLabel() == label) {
                return vertices[i];
            }
        }
        return nullptr;
    }

    void clearMarks() {
        for (int i = 0; i < vertices.size(); i++) {
            vertices[i]->clearMark();
        }
    }

    void dfsHelper(Vertex* from, Vertex* to) {
        if (from) {
            cout << from->getLabel() << " - " << to->getLabel() << endl;
        }
        to->setMark();
        for (int i = 0; i < vertices.size(); i++) {
            if (matrix.find(make_pair(to, vertices[i])) != matrix.end() && !vertices[i]->isMarked())
                dfsHelper(to, vertices[i]);
        }
    }

    void topSortHelper(Vertex* to) {
        to->setMark();
        for (int i = 0; i < vertices.size(); i++) {
            if (matrix.find(make_pair(to, vertices[i])) != matrix.end() && !vertices[i]->isMarked())
                topSortHelper(vertices[i]);
        }

        cout << to->getLabel() << " ";
    }

public:
    Graph(bool directed) { this->directed = directed; }

    Graph(string filename, bool directed) {
        this->directed = directed;
        ifstream file(filename);
        string line;
        bool vert = true;
        while (getline(file, line)) {
            if (line == "Vertices") { vert = true; }
            else if (line == "Edges") vert = false;
            else {

                if (vert) {
                    Vertex* v = getVertex(line[0]);
                    if (!v) {
                        addVertex(line[0]);
                    }
                }
                else {
                    istringstream iss(line);

                    string vert1, vert2, weight;
                    iss >> vert1 >> vert2 >> weight;
                    addEdge(vert1[0], vert2[0], stoi(weight));
                }
            }
        }
    }
    
    bool addVertex(char label) {
        if (getVertex(label)) return false;  
        Vertex* newV = new Vertex(label);
        vertices.push_back(newV);
        return true;
    }

    bool addEdge(char label1, char label2) {
        Vertex* v1 = getVertex(label1);
        Vertex* v2 = getVertex(label2);
        if (!v1 || !v2) {  
            return false;
        }
        matrix[make_pair(v1, v2)] = 1; 
        if (!directed) {
            matrix[make_pair(v2, v1)] = 1;
        }
        return true;
    }

    bool addEdge(char label1, char label2, int edgeWeight) {
        Vertex* v1 = getVertex(label1);
        Vertex* v2 = getVertex(label2);
        if (!v1 || !v2) {  
            return false;
        }
        matrix[make_pair(v1, v2)] = edgeWeight;
        if (!directed) {
            matrix[make_pair(v2, v1)] = edgeWeight;
        }
        return true;
    }

    void dfs() {
        clearMarks();
        for (int i = 0; i < vertices.size(); i++) {
            if (!vertices[i]->isMarked()) {
                dfsHelper(nullptr, vertices[i]);
            }
        }
        clearMarks();
    }

    void topologicalSort(char label) {
        clearMarks();
        topSortHelper(getVertex(label));
        cout << endl;
        clearMarks();
    }

    void bfs() {
        clearMarks();
        queue<Vertex*> q;
        q.push(vertices[0]);
        vertices[0]->setMark();
        while (!q.empty()) {
            Vertex* v = q.front();
            q.pop();
            cout << v->getLabel() << " " << endl;
            for (int i = 0; i < vertices.size(); i++) {
                if (matrix.find(make_pair(v, vertices[i])) != matrix.end() && !vertices[i]->isMarked()) {
                    vertices[i]->setMark();
                    q.push(vertices[i]);
                }
            }
        }
        clearMarks();
    }

    void dijkstrasAlg(char sourceLabel) {
        clearMarks();
        unordered_map<Vertex*, int> distances;
        int count = 0;

        for (int i = 0; i < vertices.size(); i++) {
            distances.insert(make_pair(vertices[i], INT_MAX));
        }

        Vertex* current = getVertex(sourceLabel);
        if (!current) return;
        distances[current] = 0;

        while (count < vertices.size()) {
            int smallest = INT_MAX;
            Vertex* current = nullptr;

            for (auto& it : distances) {
                if (it.second < smallest && !it.first->isMarked()) {
                    smallest = it.second;
                    current = it.first;
                }
            }

            for (int i = 0; i < vertices.size(); i++) {
                if (matrix.find(make_pair(current, vertices[i])) != matrix.end()) {
                    int sourceToCurrent = distances[current];
                    int currentToNeighbor = matrix[make_pair(current, vertices[i])];
                    if (sourceToCurrent + currentToNeighbor < distances[vertices[i]]) {
                        distances[vertices[i]] = sourceToCurrent + currentToNeighbor;
                    }
                }
            }
            current->setMark();
            count++;
        } // while there are still unmarked vertices

        // display results
        for (auto& it : distances) {
			cout << it.first->getLabel() << ": " << it.second << endl;
        }

        clearMarks();
    }


	void prim() {

		clearMarks();

		// empty graph
		if (!vertices.size()) return;

        unordered_map<Vertex*, pair<int, Vertex*> > distances;
        int count = 0;

        for (int i = 0; i < vertices.size(); i++) {
            distances.insert(make_pair(vertices[i], make_pair(INT_MAX, nullptr)));
        }

        Vertex* current = vertices[0]; 

		while (count < vertices.size()-1) {
			distances[current] = make_pair(0, nullptr);
			current->setMark();
			count++;

            for (int i = 0; i < vertices.size(); i++) {
                if (matrix.find(make_pair(current, vertices[i])) != matrix.end()) {
                    if (matrix[make_pair(current, vertices[i])] < distances[vertices[i]].first) {
                        distances[vertices[i]] = make_pair(matrix[make_pair(current, vertices[i])], current);
                    }
                }
            }

			int smallest = INT_MAX;
			Vertex* next = nullptr;
			Vertex* from = nullptr;

			for (auto& it : distances) {
				if (it.second.first < smallest && !it.first->isMarked()) {
					smallest = it.second.first;
					next = it.first;
					from = it.second.second;
				}
			}
			
			cout << from->getLabel() << " - " << next->getLabel() << endl;
			current = next;
		}

		clearMarks();

	}

    int getInDegree(char vertexLabel) {
        Vertex* v = getVertex(vertexLabel);
        if (!v)
            return 0;
        int count = 0;
        for (int i = 0; i < vertices.size(); i++) {
            if (matrix.find(make_pair(vertices[i], v)) != matrix.end()) {
                count++;
            }
        }
        return count;
        
    }

    int getOutDegree(char vertexLabel) {
        Vertex* v = getVertex(vertexLabel);
        if (!v)
            return 0;
        int count = 0;
        for (int i = 0; i < vertices.size(); i++) {
            if (matrix.find(make_pair(v, vertices[i])) != matrix.end()) {
                count++;
            }
        }
        return count;
  
    }
    vector<Vertex*> getMaxInDegree(int& maxDegree) {
        vector<Vertex*> items;
        maxDegree = 0;
        for (int i = 0; i < vertices.size(); i++) {
            int num = getInDegree(vertices[i]->getLabel());
            if (num > maxDegree) {
                items.clear();
                items.push_back(vertices[i]);
                maxDegree = num;
            }
            else if (num == maxDegree) {
                items.push_back(vertices[i]);
            }
        }
        return items;
   
    }

    vector<Vertex*> getMaxOutDegree(int& maxDegree) {
        vector<Vertex*> items;
        maxDegree = 0;
        for (int i = 0; i < vertices.size(); i++) {
            int num = getOutDegree(vertices[i]->getLabel());
            if (num > maxDegree) {
                items.clear();
                items.push_back(vertices[i]);
                maxDegree = num;
            }
            else if (num == maxDegree) {
                items.push_back(vertices[i]);
            }
        }
        return items;

    }

    vector<Vertex*> getNeighborhood(char vertexLabel, int neighborhoodSize) {
        clearMarks();
        vector<Vertex*> neigh;
        Vertex* prime = getVertex(vertexLabel);
        if (!prime)
            return neigh;
        neigh.push_back(prime);
        map<int, vector<Vertex*>> level;
        level[0].push_back(prime);
        prime->setMark();
        for (int set = 0; set < neighborhoodSize; set++) {
            for (int at = 0; at < level[set].size(); at++) {
                for (int i = 0; i < vertices.size(); i++) {
                    if (matrix.find(make_pair(level[set][at], vertices[i])) != matrix.end() && !vertices[i]->isMarked()) {
                        neigh.push_back(vertices[i]);
                        vertices[i]->setMark();
                        level[1 + set].push_back(vertices[i]);
                    }
                }
            }
        }
        clearMarks();
        return neigh;
     
    }


    vector<Vertex*> getLargestConnectedComponent() {
        clearMarks();
        vector<Vertex*> largest;
        
        vector<Vertex*> current;
        for (int i = 0; i < vertices.size(); i++) {
            current.push_back(vertices[i]);
            vertices[i]->setMark();
            for (int run = 0; run < current.size(); run++) {
                for (int j = 0; j < vertices.size(); j++) {
                    if (matrix.find(make_pair(current[run], vertices[j])) != matrix.end() && !vertices[j]->isMarked()) {
                        vertices[j]->setMark();
                        current.push_back(vertices[j]);
                    }
                }
            }
            if (current.size() > largest.size()) {
                largest.clear();
                for (int k = 0; k < current.size(); k++) {
                    largest.push_back(current[k]);
                }
            }
            current.clear();
            clearMarks();
        }


        clearMarks();
        return largest;
    }



};
