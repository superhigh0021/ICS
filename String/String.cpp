#include"String.h"
#include<cstring>

String::String(const char* data=0){
    if(data){
        this->m_data = new char[strlen(data)+1];
        strcpy(this->m_data,data);
    }else{
        this->m_data = new char[1];
        *this->m_data='\0';
    }
}

String::String(const String& str){
    this->m_data = new char[strlen(str.m_data)+1];
    strcpy(this->m_data,str.m_data);
}

String& String::operator=(const String& str){
    if(this == &str)
        return *this;
    delete[] this->m_data;
    this->m_data = new char[strlen(str.m_data)+1];
    strcpy(this->m_data,str.m_data);
    return *this;
}