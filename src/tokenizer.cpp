#include <string>
#include <vector>
#include <algorithm>

namespace
{
    using cptr = std::string::const_iterator;

    struct MatchRange {
        cptr first;
        cptr last;

        MatchRange(const std::string& s) :
            first(s.cbegin()), last(s.cend())  {}

        MatchRange(const MatchRange& mr) :
            first(mr.first), last(mr.last) {}

        bool advance() {
            if(first!=last) {
                ++first;
            }

            return first!=last;
        }

    };

    struct CharRange {
        char first;
        char last;

        CharRange(char f, char l) : first(f), last(l) {}

        bool match(char c) {
            return c>=first && c<=last;
        }
    };

    using Sequence = std::vector<std::vector<CharRange>>;

    const Sequence tm_float {
        {
            { '0', '9' },
        },
        {
            { '.', '.' }
        },
        {
            { '0', '9' },
        },
        {
            { 'f', 'f' }
        }
    };

    const Sequence tm_id {
        {
            { 'a', 'z' },
            { 'A', 'Z' },
            { '_', '_' }
        },
        {
            { 'a', 'z' },
            { 'A', 'Z' },
            { '0', '9' },
            { '_', '_' }
        }
    };


    bool seqMatch(const Sequence& seq, const MatchRange& r2, std::string& out){
        for(cptr c = r2.first; c!=r2.last; ++c){

        }

        return false;
    }



    bool match(const MatchRange& r1, const MatchRange& r2, std::string& out){
        if(std::distance(r1.first, r1.last) <= std::distance(r2.first, r2.last)) {
            return std::equal(r1.first, r1.last, r2.first);
        }
        return false;
    }

    bool id_match()

    bool pmatch()


    bool is_str_match(const std::string& s, MatchRange& mr, std::string& out){
        MatchRange mrs(s);
        MatchRange r(mr);



    }

    bool is_char_match(char mc, const MatchRange& mr, std::string& ms){

    }

    bool is_cmatch(char mc, char c, std::string& ms){
        if(mc == c) {
            ms.push_back(c);
            return true;
        }

        return false;
    }

    bool is_rmatch(char a, char b, char c, std::string& ms){
        if(c>=a && c<=c) {
            ms.push_back(c);

            return true;
        }

        return false;
    }

    //
    // Matches: 1234
    //
    bool is_int_match(const std::string::const_iterator in, std::string& out){
        out.clear();

    }

    //
    // Matches: 100.25f
    // Matches: 2f
    //
    bool is_fmatch(std::string::const_it, std::string& out){
        out.clear();


    }

    bool id_match(const std::string& in, std::string& out){
        bool first = true;
        for(auto c : in){
            if(!(
                is_rmatch('a', 'z', c, out) ||
                is_rmatch('A', 'z', c, out) ||
                is_cmatch('_', c, out)      ||
                (!first  && is_rmatch('0','9', c, out)))){
                    break;
                }

            first = false;
        }

        return out.size()>0;
    }
}
