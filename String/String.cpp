#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include <cassert>
#include <vector>
using namespace std;

String::String(char const* str):length(strlen(str)),p_str(new char[length+1])
{
    strcpy(p_str, str);
}
String::String(String const& str):length(str.length),p_str(new char[length+1])
{
    strcpy(p_str, str.p_str);
}
String::String(const int len, const char ch):length(len),p_str(new char[length+1])
{
    for (int i = 0; i < length; i++)
        p_str[i] = ch;
    p_str[length] = '\0';
}

ostream& operator<<(ostream& os, String const& str)
{
    if (str.p_str != nullptr)
        os << str.p_str;
    return os;
}

istream& operator>>(istream& is, String &str)
{
    char temp[100];
    if (is >> temp)
    {
        delete[]str.p_str;
        str.length = strlen(temp);
        str.p_str = new char[str.length + 1];
        strcpy(str.p_str, temp);
    }
    return is;
}

String operator+(String const& lhs, String const& rhs)
{
    /*String ret;
    ret.length=lhs.length+rhs.length;
    ret.p_str=new char[ret.length+1];
    strcpy(ret.p_str,lhs.p_str);
    strcat(ret.p_str,rhs.p_str);
    return ret;*/
    String sum=lhs;
    sum+=rhs;
    return sum;
  }

inline bool operator==(String const &lhs,String const &rhs)
{
    return strcmp(lhs.p_str,rhs.p_str)==0?true:false;
}

inline bool operator!=(String const &lhs,String const &rhs)
{
    return !(lhs == rhs);
}

inline bool operator>(String const &lhs,String const &rhs)
{
    return strcmp(lhs.p_str,rhs.p_str)<=0?true:false;
}

inline bool operator<(String const &lhs,String const &rhs)
{
    return strcmp(rhs.p_str,lhs.p_str)>0?true:false;
}

inline bool operator>=(String const &lhs,String const &rhs)
{
    return strcmp(rhs.p_str,lhs.p_str)>=0?true:false;
}

inline bool operator<=(String const &lhs,String const &rhs)
{
    return strcmp(rhs.p_str,lhs.p_str)<=0?true:false;
}

char& String::operator[](const int index)
{
    if(index<0||index>=length)
      throw out_of_range("不存在该下标！");
    return p_str[index];
}

char const& String::operator[](const int index)const
{
    if(index<0||index>=length)
      throw out_of_range("不存在该下标！");
    return p_str[index];
}

String String::operator=(const String& rhs)
{
    if(this!=&rhs)
    {
      if(length<rhs.length)
      {
        delete[] p_str;
        p_str=new char[rhs.length+1];
      }
        length=rhs.length;
        strcpy(p_str,rhs.p_str);
    }
    return *this;
}

String String::operator+=(const String& rhs)
{
    if(!rhs.p_str)
    {
      return *this;
    }
    if (this == &rhs)
    {
        String copy(*this);
        return *this += copy;
    }
    length += rhs.length;
    char* p_old=p_str;
    p_str=new char[length+1];
    strcpy(p_str,p_old);
    strcat(p_str,rhs.p_str);
    delete[]p_old;
    return *this;
}

String String::subString(int pos,int n)
{
    if((pos+n)>length)
      throw out_of_range("超出范围！");
    String ret;
    ret.length=n;
    ret.p_str=new char[n+1];
    for(int i=0;i<n;i++)
    {
      ret.p_str[i]=p_str[pos+i];
    }
    ret.p_str[n]='\0';
    return ret;
}

//在第pos个字符后面插入str
String& String::insert(int pos,String const& str)
{
    if(pos<0||pos>=length)  //pos是第几个字符
      throw out_of_range("超出范围！");
    char* p_old=p_str;
    length+=str.length;
    p_str=new char[length+1];
    int i;
    for(i=0;i<pos;i++)
    {
      *(p_str+i)=*(p_old+i);
    }
    for(i=pos;i<str.length+pos;i++)
    {
      *(p_str+i)=str.p_str[i-pos];
    }
    for(i=str.length+pos;i<length;i++)
    {
      *(p_str+i)=p_old[i-str.length];
    }
    *(p_str+length)='\0';
    return *this;
}

//将str的内容从位置pos起的n个字符作为原字串的新内容赋给原字串
String& String::assign(String const& str, int pos, int len)
{
      assert(pos > 0 && pos <length);
      assert(pos + len < str.length);
      if (pos + len > length)
      {
          char *p_old = p_str;
          length = pos + len;
          p_str = new char[length+1];
          for (int i = 0; i < pos; i++)
          {
              *(p_str+i) = *(p_old+i);
          }
          delete[]p_old;
      }
      for (int i = pos; i < pos+len; i++)
      {
          *(p_str + i) = str.p_str[i];
      }
      *(p_str + pos+len) = '\0';
      return *this;
}

String& String::append(String const& str)
{
      *this += str;
      return *this;
}

//PS:是删除第pos个字符后面len个字符
String& String::erase(int pos,int len)
{
      if((pos+len)>length)
      {
        throw out_of_range("超出范围！");
      }
      char* p_old=p_str;
      length-=len;
      p_str=new char[length+1];
      for(int i=0;i<pos;i++)
      {
        p_str[i]=p_old[i];
      }
      for(int i=pos;i<length;i++)
      {
         p_str[i]=p_old[i+len];
      }
      p_str[length]='\0';
      return *this;
}

int String::find(String const &T)
{
      //KMP
      assert(T.p_str != nullptr);
      int i=0,j=0;
      int nextval[T.length];//gcc
      //int nextval[100];//vs
      get_nextval(T, nextval);
      //for (int i = 0; i < T.length; i++) { cout << nextval[i] << "|"; }
      while(i<length&&j<T.length)
      {
        if(j==-1||p_str[i]==T[j])
        {
          i++;
          j++;
        }
        else
        {
          j=nextval[j];
        }
      }
      if(j==T.length)
        return i-j;
      else
        return -1;
}

void String::get_nextval(String T,int* nextval)
{
     int i=0,j=-1;
     nextval[0]=-1;
     while(i<T.length-1)
     {
       if(j==-1||T[i]==T[j])
       {
         i++;j++;
         if(T[i]!=T[j])  //当前字符与前缀字符不同,照旧
           nextval[i]=j;
         else
           nextval[i]=nextval[j];
           //若相同，则将前缀位置给当前字符
       }
       else
       {
         j=nextval[j];
       }
     }
}
