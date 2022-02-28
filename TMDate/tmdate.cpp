#include<iostream>
#include<time.h>

using namespace std;

class TMDate
{
private:
int dayOfMonth,month,year;
int dayNumber;

public:
//..... constructor
TMDate();

//..... functions
void toDayNumber();
void fromDayNumber();
int isLeapYear(int );
void date();
int getDayOfMonth();
int getMonth();
int getYear();

//..... operator function

void operator+=(int );
void operator-=(int );
int operator>(TMDate &);
int operator<(TMDate &);
int operator==(TMDate &);
int operator!=(TMDate &);
TMDate operator+(const TMDate &);
TMDate operator-(const TMDate &);
void operator=(const TMDate &);
};

//.... constructor
TMDate::TMDate()
{
time_t x;
time(&x);
struct tm *now;
now=localtime(&x);
dayOfMonth=now->tm_mday;
month=now->tm_mon+1;
year=now->tm_year+1900;
this->toDayNumber();
}
//... functions

void TMDate::toDayNumber()
{
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int x=0;
int y;
for(y=1901; y<this->year; y++)
{
if(isLeapYear(y)) x+=366;
else x+=365;
}
if(isLeapYear(y)) mth[1]=29;
for(int m=0; m<this->month-1; m++)
{
x+=mth[m];
}
x+=this->dayOfMonth;
this->dayNumber=x;
}

void TMDate::fromDayNumber()
{
if(this->dayNumber==0)
{
this->dayOfMonth=this->month=this->year=0;
return;
}

int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int x=this->dayNumber;
int d,m,y;
y=1901;
int daysInYear;
while(1)
{
if(isLeapYear(y)) daysInYear=366;
else daysInYear=365;
if(daysInYear>x) break;
x-=daysInYear;
y++;
}

m=0;
while(1)
{
if(mth[m]>x) break;
x-=mth[m];
m++;
}
m++;
d=x;
this->dayOfMonth=d;
this->month=m;
this->year=y;
}


int TMDate::isLeapYear(int year)
{
if(year%400==0) return 1;
else if(year%100==0) return 0;
else if(year%4==0) return 1;
else return 0;
}


int TMDate::getDayOfMonth()
{
return dayOfMonth;
}
int TMDate::getMonth()
{
return month;
}
int TMDate::getYear()
{
return year;
}
void TMDate::date()
{
cout<<getDayOfMonth()<<" "<<getMonth()<<" "<<getYear()<<endl;
}


//..... operator function

void TMDate::operator+=(int days)
{
if(days<=0) if(-days>this->dayNumber) days=this->dayNumber;

this->dayNumber+=days;
this->fromDayNumber();
}
void TMDate::operator-=(int days)
{
if(days>dayNumber) days=this->dayNumber;
this->dayNumber-=days;
this->fromDayNumber();
}

int TMDate::operator>(TMDate &other)
{
if(this->dayNumber>other.dayNumber) return 1;
else return 0;
}
int TMDate::operator<(TMDate &other)
{
if(this->dayNumber<other.dayNumber) return 1;
else return 0;
}
int TMDate::operator==(TMDate &other)
{
if(this->dayNumber==other.dayNumber) return 1;
else return 0;
}
int TMDate::operator!=(TMDate &other)
{
if(this->dayNumber==other.dayNumber) return 0;
else return 1;
}

TMDate TMDate::operator+(const TMDate &other)
{
TMDate k;
k.dayNumber=this->dayNumber+other.dayNumber;
k.fromDayNumber();
return k;
}
TMDate TMDate::operator-(const TMDate &other)
{
int z;
TMDate k;
z=this->dayNumber-other.dayNumber;
if(z<0) k.dayNumber=0;
else k.dayNumber=z;
k.fromDayNumber();
return k;
}
void TMDate::operator=(const TMDate &other)
{
this->dayNumber=other.dayNumber;
this->dayOfMonth=other.dayOfMonth;
this->month=other.month;
this->year=other.year;
}

// done

ostream & operator<<(ostream &cout,TMDate &tmDate)
{
tmDate.date();
return cout;
}

int main()
{
TMDate date1;
cout<<date1;
date1.toDayNumber();

cout<<"....."<<endl;
date1+=5;
cout<<"date 1: "<<date1;

cout<<"creating date2"<<endl;
TMDate date2;
if(date1>date2) cout<<"111 date1>date2"<<endl;
else cout<<"2222 date1<date2"<<endl;
if(date1<date2) cout<<"3333 date1<date2"<<endl;
else cout<<"4444 date1>date2"<<endl;
if(date1==date2) cout<<"55555 date1==dat2"<<endl;
else cout<<"6666 date1!=date2"<<endl;
cout<<"date1 "<<date1<<endl;
cout<<"date2 "<<date2<<endl;


cout<<endl<<endl<<"......"<<endl;
TMDate date3;
date3=date1-date2;
cout<<"date3 "<<date3<<endl;


date3=date3+date1;
cout<<"date3 "<<date3<<endl;

cout<<"..... program ends"<<endl;
return 0;
}