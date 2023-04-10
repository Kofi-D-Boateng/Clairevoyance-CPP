
#include <string>
#include "include/serializable.h"

class DataProcessor{
    public:
        void serialize(Serializable &serializable, std::string &output);
        void deserialize(std::string &input, Serializable &serializable);
};