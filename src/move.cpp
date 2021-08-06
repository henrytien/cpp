#include <iostream>
#include<string.h>
class String{
public:
    String()= delete;

    String(const char* s){
       std::cout << "Created!" << std::endl;
        m_size = strlen(s);
        m_Data  = new char[m_size+1];
        memcpy(m_Data,s,m_size);
    }
    String(const String& other){
        std::cout << "Copied!" << std::endl;
        m_size = other.m_size;
        m_Data  = new char[m_size+1];
        memcpy(m_Data,other.m_Data,m_size);
    }
    String(String&& other) {
        std::cout << "Moved!" << std::endl;
        m_size = other.m_size;
        m_Data  = other.m_Data;
        other.m_Data = nullptr;
        //memcpy(m_Data,other.m_Data,m_size);
    }

    ~String(){
        std::cout << "Destroyed!" << std::endl;
        delete m_Data;
    }
public:
    void print_data(){
        for(size_t i = 0; i < m_size+1; i++)
            std::cout << m_Data[i];
        std::cout << "\n";
    }

private:
    size_t m_size;
    char* m_Data;
};

class Entity{
public:
    Entity(const String& s):m_str(s){

    } 
    Entity(String&& s):m_str((String&&)s){

    } 
    ~Entity(){

    }
public:
    void print_data(){
        m_str.print_data();
    }
private:
    String m_str;
};
int main()
{

    Entity entity("Henry");
    entity.print_data();

    std::cout << "Hello world" << std::endl;
    return 0;
}

