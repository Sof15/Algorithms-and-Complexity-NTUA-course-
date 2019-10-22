#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
struct vertex
{
	long long int  endX, endY;
}v;

unordered_map <string, vertex> bridgesStart;
long long int *arr;

long long int rec(int i, int j, int h, int n, int m, int x)
{
	
	//cout<<i<<" "<<j<<" "<<arr[((i*m+j)*(x+1)+h)]<<"\n";

	long long int sum=0;

	if((i>n-1 || i<0)|| (j>m-1 || j<0) || h<0){return 0;}
	else if(i==0 && j==0){return 1;}
	else if(arr[(i*m+j)*(x+1)+h]>-1){return arr[(i*m+j)*(x+1)+h]%1000000103;}
	else if(bridgesStart.find(to_string(i)+" "+to_string(j))!=bridgesStart.end()){
		//if it's the start of a passage 
		sum += rec(bridgesStart.find(to_string(i)+" "+to_string(j))->second.endX,bridgesStart.find(to_string(i)+" "+to_string(j))->second.endY, h-1, n,m,x)%1000000103;
		sum=sum%1000000103;
	}
	else{
		//cout<<i<<" "<<j<<"\n";
		sum+=rec(i-1,j, h, n,m,x)%1000000103;
		sum=sum%1000000103;
		sum+=rec(i,j-1,h,n,m,x)%1000000103;
		sum=sum%1000000103;
	}

	arr[(i*m+j)*(x+1)+h]=sum;

	return sum;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(static_cast<ostream*>(0));
	int n,m,k,x;
	long long int start, end;
	
	cin >> n>>m>>k>>x;
	arr=new long long int [n * m * (x+1)];
	
	
	for ( int i=0; i<k; i++){
		cin >> start >> end;
		v.endX=end/m;
		v.endY=end%m;
		
		bridgesStart[to_string(start/m)+" "+to_string(start%m)]=v;

	}

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			for(int k=0; k<x+1; k++){
				arr[(i*m+j)*(x+1)+k]=-1;
			}
		}
	}

	long long int tot=rec(n-1,m-1,x, n,m,x)%1000000103;
	cout <<tot<<"\n";
	return 0;
}
