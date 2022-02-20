#include<iostream>
using namespace std;

class Collection
{
private:
int *num,p_num;
int **p2p,**cp2p,p1_p2p,p2_p2p;
public:

Collection()  //default constructor
{
num=new int[10];
p2p=new int*[10];
p_num=p1_p2p=p2_p2p=0;
p2p[0]=num;
}

void add(int i)  //add function
{
num[p_num]=i;
p_num++;
if(p_num==10)
{
  //expand num array
p_num=0;
newArray();
}

}

void newArray() //expanding array
{
num=new int[10];
p1_p2p++;
p2_p2p++;
if(p1_p2p==10)
{
p1_p2p==0;
newP2P();
}
p2p[p2_p2p]=num;
}

void newP2P()  //expanding p2p array
{
cp2p=new int*[p2_p2p];
for(int i=0; i<p2_p2p; i++)
{
cp2p[i]=p2p[i];
}
delete []p2p;
p2p=new int*[p2_p2p+10];
for(int i=0; i<p2_p2p; i++)
{
p2p[i]=cp2p[i];
}
delete []cp2p;
}

int operator[](int j) //geting jth element of arrray
{
for(int i=0,f=0; i<=p2_p2p; i++)
{
for(int k=0; k<10; k++,f++)
{
if(f==j) return *(p2p[i]+k);
}
}
}

int getSize()
{
return p2_p2p*10+p_num;
}

void numberOfPointers()
{
cout<<"number of p2p array declared (in each p2p) : "<<p2_p2p+1<<endl;
cout<<"last p2p pointer elemets "<<p_num<<endl;
}

Collection(const Collection &v) //copy constructor
{
cout<<"copy constructer"<<endl;
}


Collection & operator=(Collection &v) //operator = function(copying array)
{
int i=0;
while(i<v.getSize())
{
this->add(v[i]);
i++;
}
return *this;
}

Collection & operator+=(Collection &v) //adding 
{
int i=0;
while(i<v.getSize())
{
this->add(v[i]);
i++;
}
return *this;
}


};

int main()
{
Collection c1,c2;

c1.add(100);
c1.add(105);

for(int j=0; j<c1.getSize(); j++)
{
cout<<c1[j]<<endl;
}
c2.add(4030);
c2=c1;
c2.add(4031);

c1.add(101);
cout<<"size :"<<c2.getSize()<<endl;
cout<<"List of numbers c2"<<endl;
for(int j=0; j<c2.getSize(); j++)
{
cout<<c2[j]<<endl;
}


cout<<"Program ends"<<endl;
return 0;
}