#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#define INIF 65536
extern bool flag;
#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <functional>
#include <queue>

using std::vector;

typedef std::pair<int,int> ipair;

void addedge_non_direct(vector<ipair> *adj,int u,int v,int wt=1);

void addedge_direct(vector<ipair> *adj,int u,int v,int wt=1);

int edge_count(vector<vector<int>> const&g,int direct);

void getMatrix(vector<vector<int>> &g,int numv,int nume,int direct);

void solve1();

void Dijkstra(vector<vector<int>> const&g,vector<int> &d,int numv,int v);

void Dijkstra_heap(vector<ipair> *,int,int);

void solve21();

void solve22();

int Find(int);

void Union(int,int);

void init();

bool root_check();

void degree_check();

void check();

void solve3();

void DFSTravel(int,vector<vector<int>> const&,int);

void DFS(int,vector<bool>&,vector<vector<int>> const&);

void solve4();
#endif // MATRIX_H_INCLUDED
