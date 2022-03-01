#include<iostream>
#include<time.h>
#include<string.h>
using namespace std;

class TMDate
{
private:
int dayOfMonth,month,year;
int dayNumber;

public:
//..... constructor
TMDate();
TMDate(const char *);
TMDate(const TMDate &other);


//..... functions
void isValidDate(const char *,int *isValid,int *d,int *m,int *y);
void toDayNumber();
void fromDayNumber();
int isLeapYear(int );
void date();
int getDayOfMonth();
int getMonth();
int getYear();
// done
int getDayOfWeeak();
void getMonthString(char *);
void getMonthShortString(char *);
void getDayOfWeekString(char *);
void getDayOfWeekShortString(char *);
int isLeapYear();

//..... operator function

void operator+=(int );
void operator-=(int );
int operator>(const TMDate &);
int operator<(const TMDate &);
int operator>=(const TMDate &);
int operator<=(const TMDate &);
int operator==(const TMDate &);
int operator!=(const TMDate &);
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
TMDate::TMDate(const char *dateString)
{
int isValid,d,m,y;
isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else 
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
this->dayNumber=0;
}

}

TMDate::TMDate(const TMDate &other)
{
this->dayNumber=other.dayNumber;
this->dayOfMonth=other.dayOfMonth;
this->month=other.month;
this->year=other.year;
}


// done

//... functions

void TMDate::isValidDate(const char *x,int *isValid,int *d,int *m,int *y)
{
*isValid=0,*d=0,*m=0,*y=0;
if(x==NULL || strlen(x)<8 || strlen(x)>10) return;
char seprator,c;
int i,date=0,month=0,year=0;
int sepIndex1;
i=0;
while(1)
{
c=x[i];
i++;
if(c>='0' && c<='9') date=date*10+c-'0';
else if((i==2 || i==3) && (c=='/' || c=='-'))
{
sepIndex1=i-1;
seprator=c;
break;
}
else return;
}
while(1)
{
c=x[i];
i++;
if(c>='0' && c<='9') month=month*10+c-'0';
else if((i-1==sepIndex1+2 || i-1==sepIndex1+3) && seprator==c)
{
break;
}
else return;
}
int count=0;
while(1)
{
c=x[i];
i++;
if(c>='0' && c<='9')
{
year=year*10+c-'0';
count++;
}
else if(c=='\0') break;
else return;
}
if(count!=4 || year<1901) return;
if(month>12 || month<=0) return;
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(year)) mth[1]=29;
if(mth[month-1]<date || date<=0 ) return;
*d=date;
*m=month;
*y=year;
*isValid=1;
}

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
if(daysInYear>=x) break;
x-=daysInYear;
y++;
}

if(isLeapYear(y)) mth[1]=29;

m=0;
while(1)
{
if(mth[m]>=x) break;
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
cout<<getDayOfMonth()<<"/"<<getMonth()<<"/"<<getYear()<<endl;
}

// done
int TMDate::getDayOfWeeak()
{
}
void TMDate::getMonthString(char *monthString)
{
if(this->dayNumber==0)
{
monthString='\0';
return;
}
int m;
m=this->month;
if(m==1) strcpy(monthString,"January");
else if(m==2) strcpy(monthString,"February");
else if(m==3) strcpy(monthString,"March");
else if(m==4) strcpy(monthString,"April");
else if(m==5) strcpy(monthString,"May");
else if(m==6) strcpy(monthString,"June");
else if(m==7) strcpy(monthString,"July");
else if(m==8) strcpy(monthString,"August");
else if(m==9) strcpy(monthString,"September");
else if(m==10) strcpy(monthString,"October");
else if(m==11) strcpy(monthString,"November");
else strcpy(monthString,"December");
}
void TMDate::getMonthShortString(char *monthShortString)
{
if(this->dayNumber==0)
{
monthShortString='\0';
return;
}
int m;
m=this->month;
if(m==1) strcpy(monthShortString,"Jan");
else if(m==2) strcpy(monthShortString,"Feb");
else if(m==3) strcpy(monthShortString,"Mar");
else if(m==4) strcpy(monthShortString,"Apr");
else if(m==5) strcpy(monthShortString,"May");
else if(m==6) strcpy(monthShortString,"Jun");
else if(m==7) strcpy(monthShortString,"Jul");
else if(m==8) strcpy(monthShortString,"Aug");
else if(m==9) strcpy(monthShortString,"Sep");
else if(m==10) strcpy(monthShortString,"Oct");
else if(m==11) strcpy(monthShortString,"Nov");
else strcpy(monthShortString,"Dec");
}
void TMDate::getDayOfWeekString(char *dayOfWeekString)
{

}
void TMDate::getDayOfWeekShortString(char *dayOfWeekShortString)
{

}

int TMDate::isLeapYear()
{
if(this->dayNumber==0) return 0;
int i;
i=this->year;
if(i%400==0) return 1;
else if(i%100==0) return 0;
else if(i%4==0) return 1;
else return 0;
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

int TMDate::operator>(const TMDate &other)
{
if(this->dayNumber>other.dayNumber) return 1;
else return 0;
}
int TMDate::operator<(const TMDate &other)
{
if(this->dayNumber<other.dayNumber) return 1;
else return 0;
}
int TMDate::operator>=(const TMDate &other)
{
if(this->dayNumber>=other.dayNumber) return 1;
else return 0;
}
int TMDate::operator<=(const TMDate &other)
{
if(this->dayNumber<=other.dayNumber) return 1;
else return 0;
}
int TMDate::operator==(const TMDate &other)
{
if(this->dayNumber==other.dayNumber) return 1;
else return 0;
}
int TMDate::operator!=(const TMDate &other)
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


ostream & operator<<(ostream &cout,TMDate &tmDate)
{
tmDate.date();
return cout;
}

int main()
{
TMDate date1("2/12/2002");
cout<<date1;
//date1.toDayNumber();

cout<<"....."<<endl;
date1+=5;
cout<<"date 1: "<<date1;
char m[16];
date1.getMonthString(m);
cout<<m<<endl;
date1.getMonthShortString(m);
cout<<m<<endl;

date1="12/12/1901";
cout<<date1;
cout<<"...... test"<<endl;
date1+=19;


cout<<date1;
date1+=1;
cout<<date1<<endl;
date1.getMonthString(m);
cout<<m<<endl;
date1.getMonthShortString(m);
cout<<m<<endl;



cout<<"..... program ends"<<endl;
return 0;
}