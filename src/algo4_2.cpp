#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
unordered_map <int,vector<int>> graph;

unordered_map <int,vector<int>> inGraph;

unordered_map <int,int> notVisited;
unordered_map <int,unordered_map<int,int>> count;
unordered_map <int,int> map = unordered_map<int,int>();
vector<int> myVec;
vector<int> L;

void recursive(int v){
	if(notVisited.find(v)!=notVisited.end()){
		//if not visited
		notVisited.erase(v);
		for(int u=0; u<graph[v].size(); u++){
			recursive(graph[v][u]);
		}
		L.push_back(v);
	}
}
int *arr ;

void assign(int a, int b){
	
	arr[a]=b;
	if(count.find(b)!=count.end()){
		map=count[b];
	}
	else{
		map= unordered_map<int,int>();
	}
	map[a]=a;
	count[b]=map;

	for(int j=0; j< inGraph[a].size(); j++){
		int temp=inGraph[a][j];
		if(arr[temp]!=0){continue;}
		assign(temp,b);
	}
}

void scc(){
	//every vertex is unvisited at the beginning
	for (auto v: graph){
		notVisited[v.first]=v.first;
	}

	for (auto v: graph){
		recursive(v.first);
	}
	for (int u=L.size()-1; u>0; u--){
		if(arr[L[u]]!=0){continue;}
		assign(L[u],L[u]);
	}
}

int main(){

	int n, num,a;
	cin >>n;
	arr=new int[n+1];

	for(int i=1; i<n+1; i++){
		arr[i]=0;
	}
	//geting input and creating directed graph
	for (int i=1; i <n+1 ; i ++){
		cin >> num;
		for(int j=0; j<num; j++){
			cin>> a;
			
			if(graph.find(i)!=graph.end()){
				myVec = graph[i];
				myVec.push_back(a);
			}
			else{
				myVec.clear();
				myVec.push_back(a);
			}
			graph[i]=myVec;
			if(inGraph.find(a)!=inGraph.end()){
				myVec = inGraph[a];
				myVec.push_back(i);
			}
			else{
				myVec.clear();
				myVec.push_back(i);
			}
			inGraph[a]=myVec;

		}
	}
	/*for(auto sth: graph){
		for(int i=0; i < sth.second.size();i++){
			cout<<sth.first<<" "<<sth.second[i];
		}
		cout<<endl;
	}*/
	//done input!
bool flag=false, flag2=false;
	scc();
	int result=0,i;
	for(auto a: count){
		map=count[a.first];
		for(auto b: map){
			myVec=graph[b.first];
			for( i=0; i<myVec.size(); i++){
				if(myVec[i]==a.first){continue;};
		
				if((map).find(myVec[i])==map.end()){
					flag=true;	
					break;			
				}
			}
			if(flag==true){flag2=true; flag=false; break;}
		}
		if(flag2!=true){
			result+=map.size();
		}
		flag2=false; 
	}
	/*for(auto a: count){
		for(auto b:count[a.first]){
			cout << a.first <<" " <<b.second<<"\n";
		}
		cout<<endl;
	}*/
	cout<<result<<"\n";

	return 0;
}