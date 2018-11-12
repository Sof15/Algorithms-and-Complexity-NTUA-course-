#include <iostream>

using namespace std;

struct line{
	long long int order;
	long long int slope;
	long long int horizIntersect;
	long double prevInter;
};
struct input{
	long long int t;
	long long int u;
	short int relevant;
};

line particle;
long long int top;
//function for finding the "first" lines and intersections
void fillStack(line *s, long long int slo, long long int horIn){
		
		if(s[0].order==0){		
			particle.prevInter=0.0;
			s[0]=particle;
			top=0;
		}
		else if (s[top].order==1){
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
					while(s[top].order>1 && s[top].prevInter>((-abs(horIn)+abs(s[top].horizIntersect))/(long double)(abs(s[top].slope)-abs(slo))))
					{
						s[top].order=0;
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
int main(){
	short int flag, count,flag1,flag2;
	long long int k,n,l,ptrA,ptrB,orderA=0,orderB=0,k1,j,ind1,ind2;
	long double x1,x2,t;
	//prevInter holds the previous time that 2 lines intersect
	cin >> n >>l>>k1;
	input *inA= new input [n];
	input *inB= new input [n];
	line *stackA = new line [n];
	line *stackB = new line [n];
	for (long long int i=0; i<n; i++){
		cin>>inA[i].t>>inA[i].u;
		inA[i].relevant=1;
	}
	for (long long int i=0; i<n; i++){
			cin>>inB[i].t>>inB[i].u;
			inB[i].relevant=1;
	}
	for (long long int j1=0; j1<k1; j1++){
		flag=0; 

		//find for each section which particle from A is first O(n)
		for (long long int i=0; i<n; i++){
			stackA[i].order=0;
			stackB[i].order=0;
			if(inA[i].relevant){
				particle.order=i+1;
				particle.slope=inA[i].u;
				particle.horizIntersect=inA[i].t*inA[i].u;
				fillStack(stackA,particle.slope,particle.horizIntersect);
			}
		}
		long long int i;
		ptrA=0;long long int endptrA=top;
		//find for each section which particle from B is first O(n)
		for (long long int i=0; i<n; i++){
			if(inB[i].relevant){
				particle.order=i+1;
				particle.slope=-inB[i].u;
				particle.horizIntersect=-l-inB[i].t*inB[i].u;
				fillStack(stackB,particle.slope,particle.horizIntersect);
			}
		}
		ptrB=top;
		long long int endptrB=top;

		i=0 ; 
        long long int k=0;
		long double *time = new long double [endptrB+endptrA+2];

        i=0;
        j=0;
        // merge the 2 arrays to 1 (asc)
		while(stackA[i].order!=0 && stackB[j].order!=0){
			
			if(stackA[i].prevInter<stackB[j].prevInter){
				time[k]=stackA[i].prevInter;
				k++;
				i++;
			}
			else if(stackA[i].prevInter>stackB[j].prevInter){
				time[k]=stackB[j].prevInter;
				k++;
				j++;
			}
            else{
                time[k]=stackB[j].prevInter;
                k++;
                i++;
                j++;
            }
		}
		if (stackA[i].order==0){
			while(stackB[j].order!=0){
				time[k]=stackB[j].prevInter;
				k++;
				j++;
			}
		}
		else
		{
			while(stackA[i].order!=0){
				time[k]=stackA[i].prevInter;
				k++;
				i++;
			}
		}
        i = 0; j = 0;
		//find the first conflict
		for (int lol=0; lol<k; lol++)
		{
			t = time[lol];

            flag1 = 0;
            flag2 = 0;
            if (stackA[i+1].order!=0 && stackA[i+1].prevInter<=t){
                flag1 = 1;
                i++;
            }
            if (stackB[j+1].order!=0 && stackB[j+1].prevInter<=t){
                flag2 = 1;
                j++;
            }
           	ind1 = stackA[i].order -1;
           	ind2 = stackB[j].order -1;

            x1 = inA[ind1].u * (t - inA[ind1].t);
            x2 = l-1.0*inB[ind2].u * (t - inB[ind2].t);

            if (x1>x2) 
                break;
            flag1 = 0;
            flag2 = 0;
            
		}
			if (flag1 && !flag2){
				ind1 = stackA[i-1].order-1;
				ind2 = stackB[j].order -1;
			}
			else if (flag2 && !flag1){
				ind1 = stackA[i].order - 1;
				ind2 = stackB[j-1].order - 1;
			}
			else {
				ind1 = stackA[i].order-1;
				ind2 = stackB[j].order -1;
			}
			cout<<ind1+1<<" "<<ind2+1<<"\n";
			inA[ind1].u=0;
			inB[ind2].u=0;
	}
	return 0;
}
