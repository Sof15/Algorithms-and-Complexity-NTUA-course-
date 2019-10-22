#include <iostream>
#include <stack>

#include <cstdlib>
using namespace std;

/* create e structure that contains the maximum value 
of every subset and its population*/

struct set{
    long long int SetPopulation;
    long long int maxValue;
};

stack <set> myStack;

long long int  *h, *sum;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(static_cast<ostream*>(0));
    long long int n,min,total=0;
    cin >> n;
	h= new long long int [n];
	sum=new long long int [n];
    //read input of n elements 
    for(long int i=0; i<n; i++)
    {
        
        cin >>h[i];
        sum[i]=0;
    }
    //start traversing the array
    //from the left side
    //cout << myStack.empty();
    for(long int i=0; i<n; i++)
    {
        
        if(!myStack.empty()){ 
            if ((myStack.top().maxValue)<=h[i])
            {
                set s;
                s.SetPopulation=0;
                while(!myStack.empty() && (myStack.top().maxValue)<=h[i])
                {
                    s.maxValue=h[i];
                    s.SetPopulation+=(myStack.top().SetPopulation);
                    total-=myStack.top().SetPopulation*myStack.top().maxValue;
                    myStack.pop();
                }
                s.SetPopulation+=1;
                myStack.push(s);
                total+=s.SetPopulation*s.maxValue;
            }
            else
            {
                set mySet;
                mySet.maxValue=h[i];
                total+=h[i];
                mySet.SetPopulation=1;
                myStack.push(mySet);
            }
        }
        else if (myStack.empty() )
        {
            total+=h[i];
            set mySet;
            mySet.maxValue=h[i];
            mySet.SetPopulation=1;
            myStack.push(mySet);
        }
        sum[i]+=total;
        //cout<<sum[i];
        //showstack(myStack);
    }
    total=0;
    
    while(!myStack.empty())
        {
            myStack.pop();
        }
    for(long int i=n-1; i>-1; i--)
    {

        if(!myStack.empty()){ 
            if ((myStack.top().maxValue)<=h[i])
            {
                set s;
                s.SetPopulation=0;
                while(!myStack.empty() && (myStack.top().maxValue)<=h[i])
                {
                    s.maxValue=h[i];
                    s.SetPopulation+=(myStack.top().SetPopulation);
                    total-=myStack.top().SetPopulation*myStack.top().maxValue;
                    myStack.pop();
                }
                s.SetPopulation+=1;
                myStack.push(s);
                total+=s.SetPopulation*s.maxValue;
            }
            else
            {
                set mySet;
                mySet.maxValue=h[i];
                total+=h[i];
                mySet.SetPopulation=1;
                myStack.push(mySet);
            }
        }
        else if (myStack.empty() )
        {
            total+=h[i];
            set mySet;
            mySet.maxValue=h[i];
            mySet.SetPopulation=1;
            myStack.push(mySet);
        }
        sum[i]+=total;
    }
    min=sum[0]-h[0];
    for(long long int i=1; i<n; i++)
    {
        sum[i]-=h[i];
        if(sum[i]<min){min=sum[i];}
    }
    cout<<min<<"\n";
	return 0;
}