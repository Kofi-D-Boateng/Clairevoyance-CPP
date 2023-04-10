#include<iostream>
/*
    The Serializable is a base class that acts like the Java Object class.
    The purpose of this class is to allow serialization and deserialization from
    string to C++ class when needed. 
*/
class Serializable{
    public:
        virtual void print(){
            std::cout << "This is the base object class" << std::endl;
        }
};