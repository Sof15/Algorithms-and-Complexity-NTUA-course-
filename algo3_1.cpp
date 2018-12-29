#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
struct vertex
{
	int x, y, endX, endY;
};

long long int rec(int i, int j, int h, long long int *arr, unordered_map<string, vertex> bridgesStart, int n, int m)
{

	int sum=0;
	if((i>n-1 || i<0)|| (j>m-1 || j<0) || h<0){return 0;}
	else if(i==0 && j==0){return 1;}
	else if(bridgesStart.find(to_string(i)+to_string(j))!=bridgesStart.end()){
		//if it's the end of a passage 
		sum += rec(bridgesStart.find(to_string(i)+to_string(j))->second.endX,bridgesStart.find(to_string(i)+to_string(j))->second.endY, h-1, arr, bridgesStart,n,m);
	}
	else{
		//cout<<i<<" "<<j<<"\n";
		sum+=rec(i-1,j, h, arr, bridgesStart, n,m);
		sum+=rec(i,j-1,h, arr, bridgesStart, n,m);
	}

	return sum;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(static_cast<ostream*>(0));
	int n,m,k,x;
	long long int start, end;
	long long int *arr;
	cin >> n>>m>>k>>x;
	arr=new long long int [n * m * x];
	
	unordered_map <string, vertex> bridgesStart;
	//unordered_map <string, vertex> bridgesEnd;
	vertex v;
	for (int i=0; i<k; i++){
		cin >> start >> end;
		v.x=start/m;
		v.y=start%m;
		v.endX=end/m;
		v.endY=end%m;
		cout<<v.x<<" "<<v.y<<v.endX<<" "<<v.endY<<"\n";
		bridgesStart[to_string(v.x)+to_string(v.y)]=v;
	//	bridgesEnd[to_string(v.endX)+to_string(v.endY)]=v;
	}

	int tot=rec(n-1,m-1,x, arr,bridgesStart,n,m);
	cout <<tot<<"\n";
	return 0;
}
