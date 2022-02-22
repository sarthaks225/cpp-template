#include<iostream>
#define bool int
#define true 1
#define True 1
#define false 0
#define False 0


using namespace std;
class List
{
public:
virtual void add(int,bool *succ)=0;
virtual int get(int index, bool *) const=0;
virtual int getSize()=0;

virtual void insertAt(int index,int data,bool *)=0;
virtual int removeAt(int index,bool *)=0;
virtual void update(int index,int data,bool *)=0;

virtual void removeAll()=0;
virtual void clear()=0;
};

class Array:public List
{
private: 
int **pointer;
int size,capacity;
void createRow();

public:
  //constructor....
Array();
Array(int buffer);
Array(const Array &v);
  //Methods
void add(int ,bool *);
int get(int index, bool *) const;
int getSize();

void insertAt(int index,int data,bool *);
int removeAt(int index,bool *);
void update(int index,int data,bool *);

void removeAll();
void clear();


void check()   //checking
{
cout<<"size "<<this->getSize()<<endl<<"Capacity "<<this->capacity<<endl;
}

};





Array::Array() //default constructor
{
this->pointer=new int*[10];
this->pointer[0]=new int[10];
this->size=0;
this->capacity=10;
}

//Construtors
Array::Array(int bufferSize)
{
if(bufferSize<=0)
{
this->pointer=new int*[10];
this->pointer[0]=new int[10];
this->size=0;
this->capacity=10;
return;
}
int row;
row=bufferSize/10;
if(bufferSize%10!=0) row++;
this->pointer=new int*[row+(10-row%10)];
for(int i=0; i<row; i++) this->pointer[i]=new int[10];
this->size=0;
this->capacity=row*10;
}
Array::Array(const Array &v)
{
cout<<"1111 copy constructor invoked"<<endl;
bool succ;
if(v.size==0)
{
this->pointer=new int*[10];
this->pointer[0]=new int[10];
this->capacity=10;
}
else
{
int row;
row=v.size/10;
if(v.size%10!=0) row++;
this->pointer=new int*[row+(10-row%10)];
for(int i=0; i<row; i++) this->pointer[i]=new int[10];
this->capacity=row*10;
}
this->size=0;
for(int i=0; i<v.size; i++)
{
this->add((v.get(i,&succ)),&succ);
}

}

//Methods

void Array::createRow()
{
if(this->size%100==0)
{
int **copyPointer;
int row=this->size/10;
copyPointer=new int*[row];
if(copyPointer==NULL) return;
for(int i=0; i<row; i++ ) copyPointer[i]=this->pointer[i];
delete []this->pointer;
this->pointer=new int*[row+10];
if(this->pointer==NULL) return;
for(int i=0; i<row; i++) this->pointer[i]=copyPointer[i];
delete []copyPointer;
}
if(this->size%10==0) 
{
this->pointer[size/10]=new int[10];
this->capacity=capacity+10;
}

}


void Array::add(int data,bool *succ)
{
if(succ) *succ=false;
int size;
size=this->size;
this->pointer[size/10][size%10]=data;
this->size++;
if(this->size==this->capacity) createRow();

if(succ) *succ=true;
}
int Array::get(int index, bool *succ) const
{
if(succ) *succ=false;
if(size<=index || index<0) return 0;
return this->pointer[index/10][index%10];
}
int Array::getSize()
{
return this->size;
}

void Array::insertAt(int index,int data,bool *succ)
{}
int Array::removeAt(int index,bool *succ)
{}
void Array::update(int index,int data,bool *succ)
{}

void Array:: removeAll()
{}
void Array::clear()
{}


int main()
{
bool succ;
Array a1(300);
a1.check();
cout<<"a1 size  "<<a1.getSize()<<endl;
cout<<"adding data to a1"<<endl;
for(int i=0; i<251; i++)
{
a1.add(i,&succ);
}
cout<<"a1 size  "<<a1.getSize()<<endl;
cout<<"data of a1"<<endl;
for(int i=0; i<a1.getSize(); i++)
{
cout<<a1.get(i,&succ)<<" ";
}
cout<<endl;
a1.check();

Array a2(a1);

a2.check();
cout<<"a2 size  "<<a2.getSize()<<endl;

cout<<"data of a2"<<endl;
for(int i=0; i<a2.getSize(); i++)
{
cout<<a2.get(i,&succ)<<" ";
}
cout<<endl;


cout<<"Program ends"<<endl;
cout<<".....";
return 0;
}