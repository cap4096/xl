#include "gtypes.hh"

namespace dbg {
    std::string dump( int v ) { return std::to_string( v ); }
    std::string dump( long v ) { return std::to_string( v ); }
    std::string dump( long long v ) { return std::to_string( v ); }
    std::string dump( unsigned v ) { return std::to_string( v ); }
    std::string dump( unsigned long v ) { return std::to_string( v ); }
    std::string dump( unsigned long long v ) { return std::to_string( v ); }
    std::string dump( float v ) { return std::to_string( v ); }
    std::string dump( double v ) { return std::to_string( v ); }
    std::string dump( long double v ) { return std::to_string( v ); }
    std::string dump( const std::string& v ) { return "\""+v+"\""; }
}