#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;

struct line{
	long long int order;
	long long int slope;
	long long int horizIntersect;
	long double prevInter;
};

stack <line> StackA,StackB;
line particle;
void printStack(stack <line> s){
	stack <line> r;
	while(!s.empty()){
		cout<<s.top().order<<"\n";
		r.push(s.top());
		s.pop();
	}
	while(!r.empty()){
		s.push(r.top());
		r.pop();
	}
}
stack <line> fillStack(long long int i,long  long int t, long long int u){
	if(StackA.empty()){
			particle.order=i+1;
			particle.slope=u;
			particle.horizIntersect=-1*t*u;
			particle.prevInter=0.0;
			StackA.push(particle);
		}
		else if (StackA.top().order==1){
			particle.prevInter=((-1*t*u-StackA.top().horizIntersect)/(StackA.top().slope-u));
		//	cout<<" "<<particle.prevInter<<" "<<StackA.top().slope<<" "<<u<<" "<<StackA.top().horizIntersect<<" "<<t;
			particle.order=i+1;
			particle.slope=u;
			particle.horizIntersect=-t*u;
			StackA.push(particle);
		}		
		else{
			//cout<<StackA.top().slope<<" "<<u;
			//printStack(StackA);
			if(!(StackA.top().slope>=u)){
				
				if(StackA.top().prevInter<((-1*t*u-StackA.top().horizIntersect)/(StackA.top().slope-u))){
					//cout << "foo";
					particle.order=i+1;
					particle.slope=u;
					particle.horizIntersect=-t*u;
					particle.prevInter=(StackA.top().slope-u)/(StackA.top().horizIntersect+t*u);
					StackA.push(particle);
				}
				else{
					
					while(StackA.top().order>1 && StackA.top().prevInter>((-1*t*u-StackA.top().horizIntersect)/(StackA.top().slope-u)))
					{
						
						StackA.pop();
						particle.order=i+1;
						particle.slope=u;
						particle.horizIntersect=-t*u;
						particle.prevInter=(StackA.top().slope-u)/(StackA.top().horizIntersect+t*u);
						StackA.push(particle);
					}
				}
			}
		}
	return StackA;
}
int main(){
	long long int k;
	long int n;
	long long int l;
	long long int u,t;
	//prevInter holds the previous time that 2 lines intersect
	cin >> n >>l>>k;
	//find for each section which particle from A is first O(n)
	for (long long int i=0; i<n; i++){
		cin>>t>>u;
		StackA=fillStack(i,t,u);
	}
	//find for each section which particle from B is first O(n)
	for (long long int i=0; i<n; i++){
		cin>>t>>u;
		StackB=fillStack(i,t,u);
	}
	printStack(StackA);
	printStack(StackB);
	return 0;
}