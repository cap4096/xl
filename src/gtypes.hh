#ifndef E147569C_4133_EFA5_646B_F9BB54FFE3F1
#define E147569C_4133_EFA5_646B_F9BB54FFE3F1

#include<memory>
#include<string>
#include<vector>
#include<map>

struct LineResult;
struct Line;
struct File;
struct FileLocation;
struct ErrorMessage;
struct FileStore;

namespace dbg {
    std::string dump( int v );
    std::string dump( long v );
    std::string dump( long long v );
    std::string dump( unsigned v );
    std::string dump( unsigned long v );
    std::string dump( unsigned long long v );
    std::string dump( float v );
    std::string dump( double v );
    std::string dump( long double v );
    std::string dump( const std::string& v );

    std::string dump(const LineResult& lr);
    std::string dump(const Line& line);
    std::string dump(const FileLocation& loc);
    std::string dump(const File& file);
    std::string dump(std::shared_ptr<File> file);
    std::string dump(const ErrorMessage& m);

    template<typename T>
    std::string dump(const std::vector<T>& v)
    {
        bool remove = false;
        std::string out = "[";

        for(auto i: v){
            out += dump(i) + ", ";
            remove = true;
        }

        if(remove){
            out = out.substr(0, out.size() - 2);
        }

        out+="]";

        return out;
    }

    template<typename K, typename V>
    std::string dump(const std::map<K,V>& m)
    {
        bool remove = false;
        std::string out = "{";

        for(auto item: m){
            out +=  dump(item.first) +": "+ dump(item.second) + ", ";
            remove = true;
        }

        if(remove){
            out = out.substr(0, out.size() - 2);
        }

        out+="}";

        return out;
    }
}

#endif /* E147569C_4133_EFA5_646B_F9BB54FFE3F1 */
