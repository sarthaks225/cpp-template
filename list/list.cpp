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
virtual int get(int index, bool *)const=0;
virtual int getSize()const=0;

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
int size,capacity,faltu;
int flagVariable; //for operator + function
void createRow();

public:
  //constructor....
Array();
Array(int buffer);
Array(const List &other);
Array(const Array &v);
virtual ~Array(); //Destructor
  //Methods
void add(int ,bool *);
int get(int index, bool *) const;
int getSize() const;

void insertAt(int index,int data,bool *);
int removeAt(int index,bool *);
void update(int index,int data,bool *);

void removeAll();
void clear();

// operator function
Array & operator=(const Array &other);
void operator+=(const Array &other);
int & operator[](int index);
Array operator+(const Array &other);

void check()   //checking
{
cout<<"size "<<this->getSize()<<endl<<"Capacity "<<this->capacity<<endl;
}


// function to copy data of another class object
void operator=(const List &other);
Array operator+(const List &other);
void operator+=(const List &other);

};

//Construtors
Array::Array() //default constructor
{
this->flagVariable=0; //for operator + function
this->pointer=new int*[10];
this->pointer[0]=new int[10];
this->size=0;
this->capacity=10;
}

Array::Array(int bufferSize)
{
this->flagVariable=0; //for operator + function
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

Array::Array(const List &other)
{
this->flagVariable=0; //for operator + function
this->pointer=new int*[10];
this->pointer[0]=new int[10];
this->size=0;
this->capacity=10;
bool succ;
for(int i=0; i<other.getSize(); i++)
{
this->add(other.get(i,&succ),&succ);
if(succ==false) break;
}

}


Array::Array(const Array &v)
{
this->flagVariable=0; //for operator + function
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

Array:: ~Array() //Destructor
{
if(this->flagVariable==0) //flagVariable is used for issues related to a=b+c statement
{
int i,row;
row=this->capacity/10;
for(i=0; i<row; i++)
{
delete []this->pointer[i];
}
delete []this->pointer;
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
int Array::getSize() const
{
return this->size;
}

void Array::insertAt(int index,int data,bool *succ)
{
if(succ) *succ=false;
if(index<0 || index>size) return;
if(index==size)
{
this->add(data,succ);
}
else
{
int i;
this->add(this->get(size-1,succ),succ);
if(*succ==false) return;
int updateAtIndex=this->size-2;
for(i=updateAtIndex; i>index; i--)
{
this->update(i,this->get(i-1,succ),succ);
}
this->update(i,data,succ);
}

}

int Array::removeAt(int index,bool *succ)
{
int data;
if(succ) *succ=false;
if(index<0 || index>=this->size)
{
return 0;
}
data=this->pointer[index/10][index%10];
if(index==this->size-1)
{
size--;
}
else
{
for(int i=index; i<size-1; i++)
{
this->update(i,this->get(i+1,succ),succ);
}
size--;
}
if(succ) *succ=true;
return data;
}

void Array::update(int index,int data,bool *succ)
{
if(succ) *succ=false;
if(index<0 || index>=size) return;
this->pointer[index/10][index%10]=data;
if(succ) *succ=true;
}

void Array:: removeAll()
{
this->size=0;
}
void Array::clear()
{
this->size=0;
}

// operator function
Array & Array::operator=(const Array &other)
{

if(this->flagVariable==0) //if operator + function executed flagVariable==1
{
this->size=0;
bool succ;
for(int i=0; i<other.size; i++) 
{
this->add(other.get(i,&succ),&succ);
if(succ==false) break;
}
}
else
{
for(int i=0; i<this->size; i++)
{
delete []this->pointer[i/10];
}
delete []this->pointer;
this->size=other.size;
this->capacity=other.capacity;
this->pointer=other.pointer;
}

return *this;
}

Array Array::operator+(const Array &other)
{
Array k;
k.flagVariable=1;
k=*this;
k+=other;
return k;
}

void Array::operator+=(const Array &other)
{
bool succ;
for(int i=0; i<other.size; i++)
{
this->add(other.get(i,&succ),&succ);
if(succ==false) break;
}

}

int & Array::operator[](int index)
{
if(index>=this->size || index<0) return faltu=0;
return this->pointer[index/10][index%10];
}


// function to copy data of another class object

void Array::operator=(const List &other)
{
this->size=0;
bool succ;
for(int i=0; i<other.getSize(); i++) 
{
this->add(other.get(i,&succ),&succ);
if(succ==false) break;
}
}

Array Array::operator+(const List &other)
{
Array k;
k=*this;
k+=other;
return k;
}

void Array::operator+=(const List &other)
{
bool succ;
for(int i=0; i<other.getSize(); i++)
{
this->add(other.get(i,&succ),&succ);
if(succ==false) break;
}

}


class ForwardList;

int mainArray()
{
bool succ;
Array a1;
a1.check();
cout<<"adding data to a1"<<endl;
for(int i=0; i<19; i++)
{
a1.add(i,&succ);
}
a1.check();
cout<<"data of a1"<<endl;
for(int i=0; i<a1.getSize(); i++)
{
cout<<a1.get(i,&succ)<<" ";
}
cout<<endl<<endl;

/*
cout<<"creating a forwardList "<<endl;


cout<<"size of list1: "<<list1.getSize()<<endl;
for(int i=0; i<13; i++)
{
list1.add(i+40,&succ);
}


cout<<"size of list1: "<<list1.getSize()<<endl;
cout<<"data of list1 is : "<<endl;
for(int i=0; i<13; i++)
{
list1.get(i,&succ);
}

*/


cout<<"Program ends"<<endl;
cout<<".....";
return 0;
}


//..... forwardList .....

class ForwardList:public List
{
private:

class Node
{
public:
int data;
Node *next;
};

Node *start,*end;
int size;
int faltu;
int flagVariable; //flagVariable used for operator+ function
public:
// .... constructor ....
ForwardList();
ForwardList(int );
ForwardList(const List &other);
ForwardList(const ForwardList &other);
// .. destructor ...
~ForwardList();

// .... Methods ...
void add(int,bool *succ);
int get(int index, bool *)const;
int getSize()const;

void insertAt(int index,int data,bool *);
int removeAt(int index,bool *);
void update(int index,int data,bool *);

void removeAll();
void clear();

// ... operator functions
int & operator[](int index);
void operator+=(const ForwardList &other);
void operator=(const ForwardList &other);
ForwardList operator+(const ForwardList &other);


// function to copy data of another class object
void operator=(const List &other);
ForwardList operator+(const List &other);
void operator+=(const List &other);

};

// ... constructor ...
ForwardList::ForwardList()
{
this->flagVariable=0;
this->start=this->end=NULL;
this->size=0;
}

ForwardList::ForwardList(int buffer)
{
this->flagVariable=0;   //flagVariable used for operator+ function
this->start=this->end=NULL;
this->size=0;
}

ForwardList::ForwardList(const List &other)
{
this->flagVariable=0;
this->start=this->end=NULL;
this->size=0;
bool succ;
for(int i=0; i<other.getSize(); i++)
{
this->add(other.get(i,&succ),&succ);
if(succ==false) break;
}

}

ForwardList::ForwardList(const ForwardList &other)
{
bool succ;
this->start=this->end=NULL;
this->size=0;
this->flagVariable=0;   //flagVariable used for operator+ function
for(int i=0; i<other.size; i++)
{
this->add(other.get(i,&succ),&succ);
if(succ==false) break;
}
}

// .. destructor ...
ForwardList::~ForwardList()
{
if(this->flagVariable==0) this->removeAll(); // flagVariable used for operator+ function
}

// ..... Methods .....
void ForwardList::add(int data,bool *succ)
{
if(succ) *succ=false;
Node *node;
node=new Node;
if(node==NULL) return;
node->data=data;
node->next=NULL;
if(this->start==NULL)
{                       //Adding first element
this->start=this->end=node;
}
else
{
this->end->next=node;
this->end=node;
}
this->size++;
if(succ) *succ=true;
}
int ForwardList::get(int index, bool *succ) const
{
if(succ) *succ=false;
if(index<0 || index>=this->size) return 0;
Node *t;
t=this->start;
for(int i=0; i<index; i++) t=t->next;
if(succ)  *succ=true;
return t->data;
}
int ForwardList::getSize() const
{
return this->size;
}

void ForwardList::insertAt(int index,int data,bool *succ)
{
if(succ) *succ=false;
if(index<0 || index>this->size) return;
if(index==this->size)
{              // insertion at index=size or size=0
this->add(data,succ);
return;
}

Node *t;
t=new Node;
if(t==NULL) return;
t->data=data;
t->next=NULL;
if(index==0)
{             //insertion when index=0 and size!=0
t->next=this->start;
this->start=t;
}
else
{
Node *e,*f;             //insertion between 0 to size-1
f=this->start;
for(int i=0; i<index; i++)
{
e=f;
f=f->next;
}

e->next=t;
t->next=f;
}

this->size++;
if(succ) *succ=true;
return;
}

int ForwardList::removeAt(int index,bool *succ)
{
if(succ) *succ=false;
if(index<0 || index>=this->size) return 0;
int data;
Node *e,*f;
e=this->start;
if(index==0)
{
data=e->data;   // removing node when index=0
this->start=e->next;
delete e;
if(this->start==NULL) this->end=NULL; //if there is only one node in list
}
else 
{

for(int i=0; i<index; i++)
{
f=e;
e=e->next;
}
data=e->data;
if(index==this->size-1)
{
delete e;  //removing last node of list
f->next=NULL;
this->end=f;
}
else
{
f->next=e->next; //removing a node which lies between first and last node of list
delete e;
}

}

this->size--;
if(succ) *succ=true;
return data;
}
void ForwardList::update(int index,int data,bool *succ)
{
if(succ) *succ=false;
if(index<0 || index>=this->size) return;
Node *e;
e=this->start;
for(int i=0; i<index; i++) e=e->next;
e->data=data;
if(succ) *succ=true;
}

void ForwardList::removeAll()
{
this->clear();
}
void ForwardList::clear()
{
if(this->size==0) return;
Node *t;

while(this->start!=NULL)
{
t=this->start;
this->start=t->next;
delete t; 
}
this->size=0;
this->end=NULL;
}


// ... operator function
int &ForwardList::operator[](int index)
{
if(index<0 || index>=this->size) return faltu=0;
Node *t;
t=this->start;
for(int i=0; i<index; i++)
{
t=t->next;
}
return t->data;
}

void ForwardList::operator+=(const ForwardList &other)
{
bool succ;
for(int i=0; i<other.size; i++)
{
this->add(other.get(i,&succ),&succ);
if(succ==false) break;
}
}

void ForwardList::operator=(const ForwardList &other)
{
if(this->size!=0) this->removeAll();
bool succ;
if(flagVariable==0)  //flagVariable used for operator+ function
{
for(int i=0; i<other.size; i++)
{
this->add(other.get(i,&succ),&succ);
if(succ==false) break;
}
}
else
{
this->start=other.start;
this->end=other.end;
this->size=other.size;
}

}

ForwardList ForwardList::operator+(const ForwardList &other)
{
ForwardList k;
k.flagVariable=0;
k=*this;
k+=other;
return k;
}


// function to copy data of another class object
void ForwardList::operator=(const List &other)
{
this->clear();
bool succ;
for(int i=0; i<other.getSize(); i++)
{
this->add(other.get(i,&succ),&succ);
if(succ==false) break;
}
}

ForwardList ForwardList::operator+(const List &other)
{
ForwardList k;
k=*this;
k+=other;
return k;
}
void ForwardList::operator+=(const List &other)
{
bool succ;
for(int i=0; i<other.getSize(); i++)
{
this->add(other.get(i,&succ),&succ);
if(succ==false) break;
}
}

int main()
{
bool succ;
ForwardList list1;
cout<<"list1 size "<<list1.getSize()<<endl;


for(int i=0; i<13; i++) list1.add(i*10,&succ);
cout<<"list1 size "<<list1.getSize()<<endl;
cout<<"data of list1"<<endl;
for(int i=0; i<list1.getSize(); i++) cout<<list1.get(i,&succ)<<"  ";
cout<<endl;
cout<<"list1 size "<<list1.getSize()<<endl;


cout<<"creating array a1"<<endl;
Array a1;
a1=list1;
cout<<"size of a1 : "<<a1.getSize()<<endl;
for(int i=0; i<a1.getSize(); i++) cout<<a1.get(i,&succ)<<"  ";
cout<<endl;
a1.add(10405,&succ);
cout<<"size of a1 : "<<a1.getSize()<<endl;
for(int i=0; i<a1.getSize(); i++) cout<<a1.get(i,&succ)<<"  ";
cout<<endl;


cout<<"list1 size "<<list1.getSize()<<endl;
list1.add(5645,&succ);
cout<<"size of list1: "<<list1.getSize()<<endl;
cout<<"data of list1"<<endl;
for(int i=0; i<list1.getSize(); i++) cout<<list1.get(i,&succ)<<"  ";
cout<<endl;


cout<<"size of a1 : "<<a1.getSize()<<endl;
for(int i=0; i<a1.getSize(); i++) cout<<a1.get(i,&succ)<<"  ";
cout<<endl;

Array a2;
a2=a1+list1;
cout<<"size of a2 : "<<a2.getSize()<<endl;
for(int i=0; i<a2.getSize(); i++) cout<<a2.get(i,&succ)<<"  ";
cout<<endl;
a2+=a1;
cout<<"size of a2 : "<<a2.getSize()<<endl;
for(int i=0; i<a2.getSize(); i++) cout<<a2.get(i,&succ)<<"  ";
cout<<endl;

cout<<"creating a3"<<endl;
Array a3(list1);
cout<<"size of a3 : "<<a3.getSize()<<endl;
for(int i=0; i<a3.getSize(); i++) cout<<a3.get(i,&succ)<<"  ";
cout<<endl;
a3.check();

a3+=a1;
cout<<"size of a3 : "<<a3.getSize()<<endl;
for(int i=0; i<a3.getSize(); i++) cout<<a3.get(i,&succ)<<"  ";
cout<<endl;
a3.check();

cout<<"creating list2"<<endl;
ForwardList list2(a3);

cout<<"size of list2: "<<list2.getSize()<<endl;
cout<<"data of list2"<<endl;
for(int i=0; i<list2.getSize(); i++) cout<<list2.get(i,&succ)<<"  ";
cout<<endl;

list2=a1;
cout<<"size of list2: "<<list2.getSize()<<endl;
cout<<"data of list2"<<endl;
for(int i=0; i<list2.getSize(); i++) cout<<list2.get(i,&succ)<<"  ";
cout<<endl;

list2=a1+list1;

cout<<"size of list2: "<<list2.getSize()<<endl;
cout<<"data of list2"<<endl;
for(int i=0; i<list2.getSize(); i++) cout<<list2.get(i,&succ)<<"  ";
cout<<endl;

cout<<"program ends"<<endl;
return 0;
}