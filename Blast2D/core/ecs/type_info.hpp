#ifndef BLAST2D_TYPE_INFO_HPP
#define BLAST2D_TYPE_INFO_HPP


#include <string>
#include <iostream>
#include <vector>

namespace Blast2D{
    using Index = std::size_t;

    template<typename Type>
    struct TypeInfo {

        static Index index(Index index) {
            static const Index constIndex = index;
            return constIndex;
        }

        static Index resource(Index resource) {
            static const Index constResource = resource;
            return constResource;
        }

        static Index index() {
            return index(0);
        }
    };
}



#endif
