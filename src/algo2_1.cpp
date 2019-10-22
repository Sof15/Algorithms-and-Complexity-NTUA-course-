#include <iostream>

using namespace std;

long long int *maximum;
int *h;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(static_cast<ostream*>(0));
	
	short int a;
	int b,c,i,j,n,k,maxPos;
    long long int temp,dishX,temp2;
    cin >> n;
    cin >> a>>b>>c;
    h= new int [n];
    maximum= new long long int [n];
    // store at aux array values for dp
    // to calvulate each line it should only check the line above
    //---->O(n^2)
   
    long long int ** aux = new long long int *[n];
	for(i = 0; i < n; i++)
		aux[i] = new long long int  [n];
    
	for (i=0; i<n; i++)
	{
		cin >> h[i];
	}
	dishX = a*h[0]*h[0]+b*h[0]+c;
	aux[0][0] = h[0];
	maximum[0]=dishX;
	k=0;
	for (i=1; i<n; i++)
	{
		maximum[i]=-2000000000000000000;
		for(j=k; j<i; j++) //to k apotimatai sthn arxi tou for
		{
			temp=aux[i-1][j]+h[i];
			temp2=h[i];
			if(j==0){dishX =a*(temp)*(temp)+b*(temp)+c;}
			else{dishX =maximum[j-1]+a*(temp)*(temp)+b*(temp)+c;}
			
			aux[i][j] = temp;
			if (dishX>maximum[i]){maximum[i]=dishX; maxPos=j;}
		}
		dishX = maximum[i-1]+a*(temp2)*(temp2)+b*(temp2)+c;
		aux[i][j] = temp2;
		if (dishX>maximum[i]){maximum[i]=dishX; maxPos=j;}
		k=maxPos;
	}

	cout<<maximum[n-1]<<"\n";
	return 0;
}
