#include <iostream>
#include <algorithm>
//#include <cstdlib>
using namespace std;

long long int  *h,*hNeg;
long long int *arr;
long int *lengths;
//function that calculates an array with longest increasing
//sequence of each length

long int binSearch(long long int *a, long int start, long int end, long long int key)
{
	if(end>start){
		long long int middle=start+(end-start)/2;
		if(a[middle]==key){return middle;}
		if(a[middle]<key)
		{
			return binSearch(a,middle+1,end,key);
		}
		else
		{
			return binSearch(a,start,middle-1,key);
		}
	}
	return start;
}

long int*  lis (long long int *a, long int size )
{
	//lengths is an array that stores the 
	//longest incr subsequence until the element i 
	lengths=new long int [size];
	arr=new long long int [size];
	long int j=0, maximum;
	long long int temp;
	arr[0]=a[0];
	lengths[0]=1;
	maximum=1;
	for(long int i=1; i<size; i++)
	{
		if( a[i] < arr[0] ) {
		  arr[0] = a[i]; 
		  lengths[i] = maximum;
		}
		else if(a[i]>arr[j])
		{
			j++;
			arr[j]=a[i]; 
			if(j<maximum){lengths[i]=maximum;} //------>if (j-1<maximum-1)
			else{maximum=j+1; lengths[i]=maximum;}
		}
		else 
		{
			temp=binSearch(arr,0,j,a[i]);
			if(arr[temp]<a[i]){
				temp++;	
			}

			arr[temp]=a[i];
			if(temp<maximum){lengths[i]=maximum;}
			else{maximum=temp+1; lengths[i]=maximum;}
		}
	}
	return lengths;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(static_cast<ostream*>(0));
	
    long int n,i,j,max;
    cin >> n;
    h=new long long int [n];
    hNeg=new long long int [n];
    for(i=0; i<n; i++)
    {
		cin>>h[i];
	}
    
    for(i=0; i<n; i++)
    {
		hNeg[n-1-i]=-h[i];
		
	}	
	// function call for the array traversing from left to right
	long int *left=lis(h,n);
	// same for right to left
	long int *right=lis(hNeg,n);
	i=0;j=n-2;
	max=left[i]+right[j];
	for(i=1; i<n-1; i++)
	{
		j--;
		if(left[i]+right[j]>max){max=left[i]+right[j];}
	}
	if(left[n-1]>max){max=left[n-1];}
	cout<<max<<"\n";
	return 0;
}
