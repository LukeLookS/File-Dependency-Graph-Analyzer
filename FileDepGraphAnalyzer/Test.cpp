/////////////////////////////////////////////////////////////////////
// Test.cpp                                                        //
// Mengjie Shi                                                     //
// SUID: 457056896                                                 //
/////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <io.h>    

#include "Utilities.h"
#include "Key_Value_Table.h"
#include "DependencyAnalysis.h"
#include "Graph.h"


std::vector<std::string> getFilesWithPatterns(std::string path, std::vector<std::string>& files, std::vector<std::string> patterns)
{
	std::vector<std::string> files_;
	for (auto format : patterns)
	{
		long h = 0;    
		struct _finddata_t fileinfo;
		std::string p;
		if ((h = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1)
		{
			do
			{
				files.push_back(p.assign(fileinfo.name)); // save the files to the vector  
			} while (_findnext(h, &fileinfo) == 0);
			_findclose(h);
		}
	}
	return files_;
}

Graph<std::string, std::string> AddtoGraph(KeyValueTable kv)
{
	KeyValueTable _kv = kv;
	Graph<std::string, std::string> g;

	Keys ikeys = _kv.keys();

	int count = 1;
	for (Key key : ikeys)
	{
		Vertex<std::string, std::string> vBase(key);
		g.addVertex(vBase);
		std::vector<std::string> temp = _kv.value(key).filenames;
		for (unsigned i = 0; i < temp.size(); i++)
		{
			Vertex<std::string, std::string> vChild(temp[i]);
			g.addVertex(vChild);
			Utilities cc;
			std::string edgeName = "edge" + cc.toString(count);
			g.addEdge(edgeName, vBase, vChild);
			count++;
		}
	}
	return g;
}

Graph<std::string, std::string> AddtoGraph(std::vector<std::vector<int>> matrix)
{
	Utilities ut;
	Graph<std::string, std::string> g;

	std::vector<std::vector<int>> _matrix = matrix;
	int count = 1;
	for (unsigned c = 0; c < _matrix.size(); c++)  //  add all vertex to matrix
	{
		Vertex<std::string, std::string> v(ut.toString(c));
		g.addVertex(v);
	}

	for (unsigned r = 0; r < _matrix.size(); r++)
	{
		Vertex<std::string, std::string> vP(ut.toString(r));
		for (unsigned l = 0; l < _matrix.size(); l++)
			if (_matrix[r][l] == 1)    //  is child of 'r'
			{
				Vertex<std::string, std::string> vC(ut.toString(l));
				std::string edgeName = "edge" + ut.toString(count);
				g.addEdge(edgeName, vP, vC);    //  add dependency to graph
				Graph<std::string, std::string>::iterator iter = g.begin();
				count++;
			}
	}
	return g;
}

int main()
{
	std::vector<std::string> patterns;
	std::vector<std::string> files;

	patterns.push_back("*.cpp");
	patterns.push_back("*.h");

	std::string path = "./TestFile2/";
	
	getFilesWithPatterns(path, files, patterns);

	KeyValueTable db;

	std::cout << "\n  Dependency Analysis";
	std::cout << "\n ---------------------";
	for (std::string file : files)
	{
		DepAnal de(path + file);
		de.savetoDb(de.DepAnalyzer(files), db);
	}

	Keys keys = db.keys();
	for (Key key : keys) {
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}

	Graph<std::string, std::string> g1 = AddtoGraph(db);
	std::vector<std::vector<int>> matrix1 = g1.addToMatrix(g1);

	Display<std::string, std::string>::show(g1);
	std::cout << "\n\n  Construct Adjacency Matrix with given Graph";
	std::cout << "\n ---------------------------------------------\n";
	Display<std::string, std::string>::showMatrix(matrix1);

	Display<std::string, std::string>::showDFS(g1);

	std::cout << "\n\n  Topological Sort Result";
	std::cout << "\n -------------------------";
	std::vector<Vertex<std::string, std::string>> vvss = Display<std::string, std::string>::topologicalSort(g1);
	Display<std::string, std::string>::showTopoSortResult(vvss);

	std::cout << "\n\n  Strong Components Analyze";
	std::cout << "\n ---------------------------\n";
	std::vector< std::vector<std::string> > vvs = g1.Scc();

	std::cout << "\n\n  Build Graph with given Matrix";
	std::cout << "\n -------------------------------\n";

	std::vector<std::vector<int>> matrix2 = matrix1;
	Display<std::string, std::string>::showMatrix(matrix2);
	Graph<std::string, std::string> g2 = AddtoGraph(matrix2);
	Display<std::string, std::string>::show(g2);
	
	std::cout << "\n\n";
	system("pause");
	return 0;
}
