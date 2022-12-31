#ifndef LAB_4_PARSER_H
#define LAB_4_PARSER_H


#include <istream>
#include <limits>
#include <tuple>
#include <sstream>
#include <vector>

template<class... Args>
class CSVParser {
private:
    std::istream &istream;

    std::vector<std::string> ParseString(std::string string);

    template<class T>
    T ConvertTupleItem(const std::string &string);

public:
    CSVParser(std::istream &istream, size_t skip = 0);

    std::tuple<Args...> GetNextTuple();

    class CSVParserIterator {
    private:
        using value_type = std::tuple<Args...>;
        CSVParser<Args...> &csvParser;
        value_type nextTuple;

        bool isEoF;

    public:
        enum Type {
            BEGIN, END
        };

        CSVParserIterator(CSVParser<Args...> &parser, Type type) : csvParser(parser), isEoF(type == END) {}

        value_type operator*() {
            if (isEoF) {
                return value_type();
            }
            if (nextTuple == value_type()) {
                isEoF = csvParser.istream.eof();
                nextTuple = csvParser.GetNextTuple();
            }
            return nextTuple;
        }

        CSVParserIterator &operator++() {
            nextTuple = csvParser.GetNextTuple();

            if (nextTuple == value_type()) {
                isEoF = csvParser.istream.eof();
            }
            return *this;
        }

        friend bool operator==(CSVParserIterator &a, CSVParserIterator &b) {
            return !(a != b);
        }

        friend bool operator!=(CSVParserIterator &a, CSVParserIterator &b) {
            return (&(a.csvParser) != &(b.csvParser)) || (*a != *b) || (a.isEoF != b.isEoF);
        }

    };

    CSVParserIterator begin() { return CSVParserIterator(*this, CSVParserIterator::BEGIN); }

    CSVParserIterator end() { return CSVParserIterator(*this, CSVParserIterator::END); }
};

template<class... Args>
CSVParser<Args...>::CSVParser(std::istream &istream, size_t skip)  : istream(istream) {
    istream.exceptions(std::istream::badbit);

    std::string skippedLine;
    for (size_t i = 0; i < skip; ++i) {
        std::getline(istream, skippedLine);
    }
}

template<class... Args>
std::tuple<Args...> CSVParser<Args...>::GetNextTuple() {
    std::string nextLine;

    std::getline(istream, nextLine);

    if (nextLine.empty() && istream.eof()) {
        return std::tuple<Args...>();
    }

    std::vector<std::string> strings = ParseString(nextLine);

    auto GetLastElement = [&strings]() -> std::string {
        std::string last = strings.back();
        strings.pop_back();
        return last;
    };

    if (strings.size() != sizeof...(Args)) {
        throw std::invalid_argument("Input error: the number of elements in the row does not match the tuple size");
    }
    return std::tuple<Args...>(ConvertTupleItem<Args>(GetLastElement())...);

//    return std::tuple<int, double, std::string>(ConvertTupleItem<int>(GetLastElement()),
//                                                ConvertTupleItem<double>(GetLastElement()),
//                                                ConvertTupleItem<std::string>(GetLastElement()));
}

template<class... Args>
std::vector<std::string> CSVParser<Args...>::ParseString(std::string string) {
    std::vector<std::string> result;
    size_t pos;
    char delimiter = ',';
    std::string token;
    while ((pos = string.find(delimiter)) != std::string::npos) {
        token = string.substr(0, pos);
        result.push_back(token);
        string.erase(0, pos + 1);
    }

    result.push_back(string);

    return result;
}

template<class... Args>
template<class T>
T CSVParser<Args...>::ConvertTupleItem(const std::string &string) {
    std::stringstream stringstream;

    stringstream << string;

    T result;

    stringstream >> result;

    return result;
}

#endif //LAB_4_PARSER_H
