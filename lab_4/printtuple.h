#ifndef LAB_4_PRINTTUPLE_H
#define LAB_4_PRINTTUPLE_H

#include <tuple>

namespace hidden {
    template<std::size_t...>
    struct ParamsSequence {
    };

    template<std::size_t N, std::size_t... TSize>
    struct GeneratedSequence : GeneratedSequence<N - 1, N - 1, TSize...> {
    };

    template<std::size_t... TSize>
    struct GeneratedSequence<0, TSize...> : ParamsSequence<TSize...> {
    };

    template<class CharT, class Traits, class Tuple, std::size_t... TSize>
    void PrintTuple(std::basic_ostream<CharT, Traits> &os, Tuple const &t, ParamsSequence<TSize...>) {
        using tmp = int[];
        (void) tmp{0, (void(os << (TSize == 0 ? "" : ",") << std::get<TSize>(t)), 0)...};
    }
}

template<class CharT, class Traits, class... Args>
auto operator<<(std::basic_ostream<CharT, Traits> &os, std::tuple<Args...> const &t)
-> std::basic_ostream<CharT, Traits> & {
//    os << "(";
    hidden::PrintTuple(os, t, hidden::GeneratedSequence<sizeof...(Args)>());
//    os << ")";
    return os;
}


#endif //LAB_4_PRINTTUPLE_H
