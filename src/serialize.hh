#include<string>
#include<vector>
#include<map>

namespace {
    std::string to_string( int v ) { return std::to_string( v ); }
    std::string to_string( long v ) { return std::to_string( v ); }
    std::string to_string( long long v ) { return std::to_string( v ); }
    std::string to_string( unsigned v ) { return std::to_string( v ); }
    std::string to_string( unsigned long v ) { return std::to_string( v ); }
    std::string to_string( unsigned long long v ) { return std::to_string( v ); }
    std::string to_string( float v ) { return std::to_string( v ); }
    std::string to_string( double v ) { return std::to_string( v ); }
    std::string to_string( long double v ) { return std::to_string( v ); }
    std::string to_string( const std::string& v ) { return "\""+v+"\""; }
}

 

template<typename T>
std::string to_string(const std::vector<T>& v)
{
    bool remove = false;
    std::string out = "[";
    
    for(auto i: v){
        out += to_string(i) + ", ";
        remove = true;
    }

    if(remove){
        out = out.substr(0, out.size() - 2);
    }

    out+="]";

    return out;
}

template<typename K, typename V>
std::string to_string(const std::map<K,V>& m)
{
    bool remove = false;
    std::string out = "{";

    for(auto item: m){
        out +=  to_string(item.first) +": "+ to_string(item.second) + ", ";
        remove = true;
    }

    if(remove){
        out = out.substr(0, out.size() - 2);
    }

    out+="}";

    return out;
}
