#include<iostream>
#include<string.h>
using namespace std;
class TMString
{
private:
int size;
char *ptr;
public:

//constructor
TMString();
TMString(const char *ptr);
TMString(const TMString &other);
virtual ~TMString();

// operator functions
TMString & operator=(const char *);
TMString & operator=(const TMString &);
int operator<(const TMString &);
int operator<=(const TMString &);
int operator>(const TMString &);
int operator>=(const TMString &);
int operator==(const TMString &);
int operator!=(const TMString &);
void operator+=(const char *);
void operator+=(const TMString &);
TMString operator+(const TMString &);
friend ostream & operator<<(ostream &oo,TMString &string);
};

// constructor

TMString::TMString()
{
this->ptr=NULL;
this->size=0;
}
TMString::TMString(const char *string)
{
int i;
i=strlen(string);
if(i!=0)
{
this->ptr=new char[i];
strcpy(this->ptr,string);
}
else this->ptr=NULL;
this->size=i;
}

TMString::TMString(const TMString &other)
{
if(this->size!=0)
{
delete [] this->ptr;
this->ptr=NULL;
this->size=0;
}
if(other.size!=0)
{
this->ptr=new char[other.size];
strcpy(this->ptr,other.ptr);
this->size=other.size;
}
}
TMString::~TMString()
{
delete []this->ptr;
}

// operator function

TMString& TMString::operator=(const char *string)
{
if(this->size!=0)
{
delete []this->ptr;
this->size=0;
}

if(string==NULL) return *this;
this->size=strlen(string);
this->ptr=new char[this->size];
strcpy(this->ptr,string);
return *this;
}

TMString & TMString::operator=(const TMString &other)
{
if(this->size!=0)
{
delete []this->ptr;
this->size=0;
}

if(other.ptr==NULL) return *this;
this->size=other.size;
this->ptr=new char[this->size];
strcpy(this->ptr,other.ptr);
return *this;
}

int TMString::operator<(const TMString &other)
{
if(this->size==0 && other.size==0) return 0;
if(this->size==0) return 1;
if(other.size==0) return 0;
return strcmp(this->ptr,other.ptr)<0;
}
int TMString::operator<=(const TMString &other)
{
if(this->size==0 && other.size==0) return 1;
if(this->size==0) return 1;
if(other.size==0) return 0;
return strcmp(this->ptr,other.ptr)<=0;
}
int TMString::operator>(const TMString &other)
{
if(this->size==0 && other.size==0) return 0;
if(this->size==0) return 0;
if(other.size==0) return 1;
return strcmp(this->ptr,other.ptr)>0;
}
int TMString::operator>=(const TMString &other)
{
if(this->size==0 && other.size==0) return 1;
if(this->size==0) return 0;
if(other.size==0) return 1;
return strcmp(this->ptr,other.ptr)>=0;
}
int TMString::operator==(const TMString &other)
{
if(this->size==0 && other.size==0) return 1;
if(this->size==0) return 0;
if(other.size==0) return 0;
return strcmp(this->ptr,other.ptr)==0;
}
int TMString::operator!=(const TMString &other)
{
if(this->size==0 && other.size==0) return 0;
if(this->size==0) return 1;
if(other.size==0) return 1;
return strcmp(this->ptr,other.ptr)!=0;
}

void TMString::operator+=(const char *string)
{
if(string==NULL) return;

if(this->size==0)
{
this->size=strlen(string);
this->ptr=new char[this->size];
strcpy(this->ptr,string);
}
else
{
char *ptr;
this->size=this->size+strlen(string);
ptr=new char[this->size];
strcpy(ptr,this->ptr);
delete [] this->ptr;
strcat(ptr,string);
if(this->ptr!=NULL) delete [] this->ptr;
this->ptr=ptr;
}


}

void TMString::operator+=(const TMString &other)
{
if(this->size==0 && other.size==0) return;
if(other.size==0) return;
if(this->size==0)
{
this->size=other.size;
this->ptr=new char[this->size];
strcpy(this->ptr,other.ptr);
}
else
{
char *ptr;
this->size=this->size+other.size;
ptr=new char[this->size];
strcpy(ptr,this->ptr);
strcat(ptr,other.ptr);
delete []this->ptr;
this->ptr=ptr;
}

}
TMString TMString::operator+(const TMString &other)
{
TMString k;
k=*this;
k+=other;
return k;
}

// done
ostream & operator<<(ostream &oo,TMString &string)
{
if(string.size!=0)
{
oo<<string.ptr;
}
return oo;
}

int main()
{
TMString string1("");

cout<<"string1:"<<string1<<endl;
TMString string2;

cout<<"string2: "<<string2<<endl;
string2+="lives in manawar";
cout<<"string2: "<<string2<<endl;

TMString c;
c="sydneyd";
cout<<"c: "<<c<<endl;
c=string1+string2;

cout<<"c: "<<c<<endl;

cout<<"program ends"<<endl;
return 0;
}
