#ifndef __STRING__
#define __STRING__

class String{
public:
    String(const char* data);
    
    String(const String& str);

    String& operator=(const String& str);

    ~String()=default;
private:
    char *m_data;
};

#endif