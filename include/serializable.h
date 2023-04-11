#include<iostream>
#include <string>
/*
    The Serializable is a base class that acts like the Java Object class.
    The purpose of this class is to allow serialization and deserialization from
    string to C++ class when needed. 
*/
class Serializable{
    private:
        /*
            The name of the serializable class
        */
        std::string object_name;
        std::string serializeId;
    public:
        Serializable(const std::string &name): object_name(name){
            // CREATE A SERIALIZED ID EITHER WITH NUMBERS AS STRINGS OR UUID
        }
        virtual std::string class_name()const{return object_name;}
        virtual void print(){
            std::cout << "This is the "<< object_name << " class" << std::endl;
        }
    
};