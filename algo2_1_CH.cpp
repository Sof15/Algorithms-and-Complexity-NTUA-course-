#include <iostream>

using namespace std;

struct line{
	long long int slope;
	long long int horizIntersect;
	long double prevInter;
};

long long int binSearch(line *a,long long int start,long long int end, long long int key)
{
	if(end>start){
		long long int middle=start+(end-start)/2;
		if(a[middle].prevInter==key){return middle;}
		if(a[middle].prevInter<key)
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

line particle;
long long int top=-1;

void fillStack(line *s, long long int slo, long long int horIn){
		
		if(top==-1){		
			particle.prevInter=0.0;
			s[0]=particle;
			top=0;
		}
		else if (top==0){
			if(!(abs(s[top].slope)>=abs(slo))){
				particle.prevInter=((-abs(horIn)+abs(s[top].horizIntersect))/(long double)(abs(s[top].slope)-abs(slo)));
				s[top+1]=particle;
				top++;
			}
		}		
		else{
			if(!(abs(s[top].slope)>=abs(slo))){
				
				if(s[top].prevInter<((-abs(horIn)+abs(s[top].horizIntersect))/(long double)(abs(s[top].slope)-abs(slo)))){
					particle.prevInter=((-abs(horIn)+abs(s[top].horizIntersect))/(long double)(abs(s[top].slope)-abs(slo)));
					s[top+1]=particle;
					top++;
				}
				else{
					while(top>1 && s[top].prevInter>((-abs(horIn)+abs(s[top].horizIntersect))/(long double)(abs(s[top].slope)-abs(slo))))
					{
						
						top--;		
					}
					particle.prevInter=((-abs(horIn)+abs(s[top].horizIntersect))/(long double)(abs(s[top].slope)-abs(slo)));
					s[top+1]=particle;
					
					top++;
				}
			}
		}
		
	return;
}

int main ()
{
	long long int n,i,joy,a,b,c,ptr,temp, temp2;
	cin >> n>>a>>b>>c;
	long long int *sum,*dynamic;
	line *s;
	s=new line [n];
	sum=new long long int [n];
	dynamic=new long long int [n];
	
	cin>>sum[0];
	//get input and calculate partial sums
	for(i=1; i<n; i++)
	{
		cin>>joy;
		sum[i]=sum[i-1]+joy;
	}
	dynamic[0]=a*sum[0]*sum[0]+b*sum[0]+c;
	ptr=0;

	for(i=0; i<n; i++)
	{
		if(i==0){dynamic[0]=a*sum[0]*sum[0]+b*sum[0]+c;}
		else {

			temp=sum[i-1];
			particle.slope=-2*a*temp;
			particle.horizIntersect=a*temp*temp-b*temp+dynamic[i-1];
			fillStack(s,particle.slope,particle.horizIntersect);
			temp2=sum[i];
			dynamic[i]=a*temp2*temp2+b*temp2+c;
			//ptr=top;
			//perhaps binary search from the last (cant exmplain what) to top
			ptr=binSearch(s,ptr,top,temp2);
			if(s[ptr].prevInter>temp2) ptr--;
			//while(s[ptr].prevInter>=temp2)
			//	ptr--;
			if(s[ptr].slope*temp2+s[ptr].horizIntersect>0){dynamic[i]+=s[ptr].slope*temp2+s[ptr].horizIntersect;}
		}

	}
	cout<<dynamic[n-1]<<"\n";
	
	return 0;
}
