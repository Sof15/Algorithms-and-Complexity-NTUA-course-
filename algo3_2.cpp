#include <iostream>  
#include <vector>  
#include <algorithm>  
#include <unordered_map>  
#include <string>  
using namespace std;  
  
//construct parents array  
long long int counter, lastW;  
long long int *parArr, *length;  
unordered_map <string,int> map;
unordered_map <string,int> :: iterator elem;
vector <long long int> list;

vector<long long int> visited,tin,fup;  
// graph in form of adj list  
  
struct edge{  
    long long int src;  
    long long int dst;  
    long long int cost;  
};  
vector<edge> E;//vector containing all the edges  

unordered_map<long long int, vector<long long int>> group;  
vector<edge> omada;  
bool compareCost(edge e1, edge e2){  
    return(e1.cost<e2.cost);  
}  
//union find method implementation from link [...]  
long long int root(long long int i){ 
    while(parArr[i]!=i){  
        parArr[i]=parArr[parArr[i]];  
        i=parArr[i];  
    }
    return i;  
}  
  
bool find(int u, int v){  
    if(root(u)==root(v)) {return true;}  
    return false;  
}  
void Union(long long int u ,long long int v){  
    long long int rootU = root(u);  
    long long int rootV = root(v);  
    if(length[rootU]<length[rootV]){  
        length[rootV]+=length[rootU];  
        parArr[rootU]=parArr[rootV];  
    }  
    else{  
        length[rootU]+=length[rootV];  
        parArr[rootV]=parArr[rootU];  
    }  
}  
long long int all;  
void myDFS(long long int v, long long int par) {  
    visited[v] = 1;  
    tin[v] = fup[v] = counter;  
    counter++;  
    vector<long long int > vec;  
 
    vec=group.find(v)->second;  
    for (long long int to : vec) {  
        if (to == par) {continue;}  
        if (visited[to]) {  
            fup[v] = min(fup[v], tin[to]);  
        } else {  
            myDFS(to, v);  
            fup[v] = min(fup[v], fup[to]);  
            if (fup[to] > tin[v]){
            	if(map.find(to_string(to)+to_string(v))!=map.end()) {
            		if(map.find(to_string(to)+to_string(v))->second==1){all++;}
            	}
            	else if(map.find(to_string(v)+to_string(to))!=map.end()) {
            		if(map.find(to_string(v)+to_string(to))->second==1){all++;}
            	}
            }
    
        }  
    }  
}  
  
void getBridges(long long int nodes) {  

    counter = 0;  
    visited.assign(nodes+1, 0);  
    tin.assign(nodes+1, -1);  
    fup.assign(nodes+1, -1);  
    for (int i = 1; i < nodes+1; i++) {  
        if (!visited[i]&&group.find(i)!=group.end()){myDFS(i,-1);}  
    }  
}  
vector<edge>::iterator itr,it;  
int main(){  
	ios_base::sync_with_stdio(false);
	cin.tie(static_cast<ostream*>(0));
    long long int n,m,src,dst, cost;  
    cin >> n>>m;  
    edge e;  
    all=0;
    for (long long int i=0; i<m; i++){  
        cin >> src >> dst>>cost;  
        e.src=src;  
        e.dst=dst;  
        e.cost=cost;  
   
        E.push_back(e);  
    }  
  
    sort(E.begin(),E.end(),compareCost);//O(mlogm)  
    
    long long int costN;  
    long long int none=0, some=0;  
    parArr=new long long int [n+1];  
    length=new long long int [n+1];  
    for (long long int i=1; i<n+1; i++){  
        parArr[i]=i;//initially parent of a node is the same node cause they are desconnected  
        length[i]=1;  
    }  
    //kruskal mst find mst cost O(mlogm)
  	long long int mst_e=0, mst_w=0;;
    for(itr=E.begin(); itr!=E.end(); itr++){  
    	src=itr->src;  
        dst=itr->dst;  

        if(!find(src,dst)){Union(src,dst);  mst_w=itr->cost; mst_e++;}
        if(mst_e==n-1){break;}
    }
    for(long long int i=1; i<n+1; i++){parArr[i]=i; length[i]=1;}

    cost=(E.begin())->cost;  
  
    
    long long int u,v;
    for(itr=E.begin(); itr!=E.end(); itr++){  
        if(itr->cost>mst_w){ none++; continue;}  //if cost is more than the bigger used in mst none++
		//if(itr->cost==3){cout<<1<<"\n";}
        costN=itr->cost;    
        if (costN==cost){
        
            u=root(itr->src);
            v=root(itr->dst);
            if(find(u,v)){none++;}//O(logn)  
            else{  
                //create the group which is an adj list  
                omada.push_back(*itr);  
                if(group.find(u)==group.end()){  
                	map[to_string(u)+to_string(v)]=1;
                    list.clear();  
                    list.push_back(v);  
                    group[u]=list;    
                }  
                else{  
                	if(map.find(to_string(u)+to_string(v))!=map.end()){map.find(to_string(u)+to_string(v))->second++;;}
                	else if(map.find(to_string(v)+to_string(u))!=map.end()){map.find(to_string(v)+to_string(u))->second++;}
                	else{map[to_string(u)+to_string(v)]=1;}
                    list=group.find(u)->second;  
                    list.push_back(v);  
                    group[u]=list;  
                }  
              
                if(group.find(v)==group.end()){  
                	
                    list.clear();  
                    list.push_back(u);  
                    group[v]=list;  
                }  
                else{  
                    list=group.find(v)->second;  
                    list.push_back(u);  
                    group[v]=list;  
                }  
                  
            }  
            if((itr+1)==E.end() || (itr+1)->cost>costN)
            {
            	//means there is a complete group  
			    getBridges(n);

			    for(edge ed: omada){  
			        Union(ed.src,ed.dst);  
			    }
            	if(itr+1!=E.end()) cost=(itr+1)->cost;   
            	list.clear();  
            	group.clear();
            	list.clear();
            	map.clear();
            	omada.clear();  
            }
        }
    }  
    cout<<all<<"\n"<<none<<"\n"<<m-all-none<<"\n";  
    return 0;  
}  