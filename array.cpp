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


Collection & operator=(const Collection &v) //operator = function(copying array)
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

void removeFromTop()
{

if(p2_p2p==0 && p_data==0) return;
if(p2_p2p==0)
{
cout<<"removing : "<<p2p[p2_p2p][p_data-1];
p_data--;
}
else
{
if(p_data==0)
{
cout<<"22222 removing"<<(p2p[p2_p2p-1][9]);
delete [] p2p[p2_p2p--];
if(p1_p2p>0) p1_p2p--;
p_data=9;
}
else
{
p_data--;
}

}




cout<<"***succ"<<endl;
}
};



class Bulb
{
char wattage;
public:
void setWattage(char wattage)
{
this->wattage=wattage;
}
char getWattage()
{
return wattage;
}

Bulb(char wattage)
{
this->wattage=wattage;
}

};

typedef struct model_
{
char model;
}Car;


int main()
{
Collection <char> c1,c2;

for(int i=0; i<10; i++)
{
c1.add(i+'a');
}

cout<<"c1 : elements "<<c1.getSize()<<endl;
for(int i=0; i<c1.getSize(); i++)
{
cout<<c1[i]<<endl;
}

while(c1.getSize()!=0)
{
c1.removeFromTop();
cout<<"removed  c1 size : "<<c1.getSize()<<endl;
for(int i=0; i<c1.getSize(); i++)
{
cout<<c1[i]<<"  ";
}
cout<<endl;
}
cout<<"Program ends"<<endl;
return 0;
}