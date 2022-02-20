#include<iostream>
using namespace std;
template<class T>
class Collection
{
private:
int p1_p2p,p2_p2p,p_data;
T *data,**p2p,**cp2p;
public:

Collection()  //default constructor
{
data=new T[10];
p2p=new T*[10];
p_data=p1_p2p=p2_p2p=0;
p2p[0]=data;
}

void add(T i)  //add function
{
data[p_data]=i;
p_data++;
if(p_data==10)
{
  //expand data array
p_data=0;
newArray();
}

}

void newArray() //expanding array
{
data=new T[10];
p1_p2p++;
p2_p2p++;
if(p1_p2p==10)
{
p1_p2p==0;
newP2P();
}
p2p[p2_p2p]=data;
}

void newP2P()  //expanding p2p array
{
cp2p=new T*[p2_p2p];
int i;
for(i=0; i<p2_p2p; i++)
{
cp2p[i]=p2p[i];
}
delete []p2p;
p2p=new T*[p2_p2p+10];
for(i=0; i<p2_p2p; i++)
{
p2p[i]=cp2p[i];
}
delete []cp2p;
}

T operator[](int j) //geting jth element of arrray
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
return p2_p2p*10+p_data;
}

void numberOfPointers()
{
cout<<"number of p2p array declared (in each p2p) : "<<p2_p2p+1<<endl;
cout<<"last p2p pointer elemets "<<p_data<<endl;
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
Collection <char> c1,c2;

c1.add('a');
c1.add('b');

for(int j=0; j<c1.getSize(); j++)
{
cout<<c1[j]<<endl;
}
c2.add('c');
c2=c1;
c2.add('d');

c1.add('e');
cout<<"size :"<<c2.getSize()<<endl;
cout<<"List of databers c2"<<endl;
for(int j=0; j<c2.getSize(); j++)
{
cout<<c2[j]<<endl;
}


cout<<"c1 : "<<c1.getSize()<<endl;
for(int j=0; j<c1.getSize(); j++)
{
cout<<c1[j]<<endl;
}

cout<<"Program ends"<<endl;
return 0;
}