    #include <iostream>  
    #include <unordered_map>  
    #include <queue>  
    using namespace std;  
      
    struct edge{  
        int destination, cost, weight;  
    };  
      
    unordered_map<string, vector<edge>> g;   
    unordered_map<string, string> notFinished;   
    class prioritize{public: bool operator ()(pair<string, int>&p1 ,pair<string, int>&p2){return p1.second>p2.second;}};  
    priority_queue<pair<string,int> ,vector<pair<string,int> >, prioritize> setNodes;   
    int N,s,desti,p;  
      
    int dijkstra(){  
        int dist[N][p+1];  
      
        for (int i=1; i<N+1; i++){  
            for(int j=0; j<p+1; j++){  
                dist[i][j]=2000000000;    
                notFinished[to_string(i)+" "+to_string(j)]=to_string(i)+" "+to_string(j);     
            }         
        }  
      
        dist[s][0]=0;  
          
        setNodes.push(make_pair(to_string(s)+" 0",0));  
        while(setNodes.size()>0){  
      
            pair <string, int> curr=setNodes.top(); //Current vertex. The shortest distance for this has been found  
            string delimiter = " ";  
            string token = (curr.first).substr(0, (curr.first).find(delimiter));  
            string token2 = (curr.first).substr((curr.first).find(delimiter), (curr.first).length());  
        
            if(stoi(token)==desti){return curr.second;}  
            setNodes.pop();  
      
            if(notFinished.find(curr.first)!=notFinished.end()){  
                notFinished.erase(notFinished.find(curr.first));  
            }  
            else {continue;}  
      
            for(int i=0;i<(g[curr.first]).size();i++) {//Iterating through all adjacent vertices  
                edge temp = g[curr.first][i];  
                if(temp.cost>p){continue;}  
      
                if(dist[stoi(token)][stoi(token2)]+temp.weight < dist[g[curr.first][i].destination][g[curr.first][i].cost]){  
                    dist[temp.destination][temp.cost]=dist[stoi(token)][stoi(token2)]+temp.weight;  
                     
                    setNodes.push(make_pair(to_string(temp.destination)+" "+to_string(temp.cost),dist[temp.destination][temp.cost]));  
                }  
            }  
        }  
      
        return 0;     
    }  
      
    int main(){  
        int M,K,Q,u,v,d;  
        cin >> N >>M>>K>>Q;  
        vector<edge> myVec;  
        for (int i=0; i<M ; i++){  
            cin >>u>>v>>d;  
            for(int j=0; j<K+1; j++){  
                edge e;  
                e.destination=v;  
                e.cost=j;  
                e.weight=d;  
                if(g.find(to_string(u)+" "+to_string(j))!=g.end()){  
                    myVec = g[to_string(u)+" "+to_string(j)];  
                    myVec.push_back(e);  
                }  
                else{  
                    myVec.clear();  
                    myVec.push_back(e);  
                }  
                g[to_string(u)+" "+to_string(j)]=myVec;  
                if(j!=K){  
                    //illegal  
                    e.destination=u;  
                    e.cost=j+1;  
                    if(g.find(to_string(v)+" "+to_string(j))!=g.end()){  
                        myVec = g[to_string(v)+" "+to_string(j)];  
                        myVec.push_back(e);  
                    }  
                    else{  
                        myVec.clear();  
                        myVec.push_back(e);  
                    }  
                    g[to_string(v)+" "+to_string(j)]=myVec;  
                }  
            }  
              
        }  
        for(int i=0; i<Q; i++){  
            cin>>s>>desti>>p;  
            int result = dijkstra();  
            if(result==0){  
                if(s==desti){cout<<0<<"\n";}  
                else {cout<<"IMPOSSIBLE\n";}  
            }  
            else{cout << result<<"\n";}  
            notFinished.clear();  
            setNodes=priority_queue<pair<string,int> ,vector<pair<string,int> >, prioritize>();  
        }  
    /*  for(auto i : graph){ 
            for(int j=0; j<(i.second).size();j++) 
                { cout <<(i.first)<<"..."<< (i.second)[j].destination << " " << (i.second)[j].cost<<"\n";} 
            cout<<"\n"; 
        } 
    */  
      
        //graph creation done!  
      
        return 0;  
    }  