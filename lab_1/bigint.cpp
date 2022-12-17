#include "bigint.h"
#include <algorithm>
#include <vector>
#include <limits>

char ToChar(int d);

int ToDigit(char c);

std::string BinaryNumberInversion(std::string a);

size_t GetExpectedLength(size_t binaryStringLength);

BigInt::BigInt() {
    number = "0";
    isNegative = false;
}

BigInt::BigInt(const int n) {
    isNegative = (n < 0);
    number = isNegative ? std::to_string(n).substr(1) : std::to_string(n);
}

BigInt::BigInt(const std::string &n) {
    if (n.empty()) {
        throw std::invalid_argument(EMPTY_STRING_EXCEPTION_MESSAGE);
    }

    if (n[0] != '-' && !std::isdigit(n[0])) {
        throw std::invalid_argument(NOT_NUMBER_EXCEPTION_MESSAGE);
    }

    isNegative = (n[0] == '-');
    bool isLeadingZero = true;
    int leadingZeroCount = 0;

    auto it = n.cbegin() + isNegative;
    for (; it < n.cend(); it++) {
        if (!std::isdigit(*it)) {
            throw std::invalid_argument(NOT_NUMBER_EXCEPTION_MESSAGE);
        }

        isLeadingZero = isLeadingZero && *it == '0';
        if (isLeadingZero) {
            leadingZeroCount++;
        }
    }

    if (leadingZeroCount == (n.length() - isNegative)) {
        leadingZeroCount--;
    }
    std::move(n.cbegin() + leadingZeroCount + isNegative, n.cend(), std::inserter(number, number.begin()));
    isNegative &= !(number == "0");
}

BigInt::BigInt(const BigInt &n) {
    number = n.number;
    isNegative = n.isNegative;
}

BigInt::~BigInt() {
    number.clear();
}

BigInt &BigInt::operator=(const BigInt &n) {
    if (this != &n) {
        number = n.number;
        isNegative = n.isNegative;
    }
    return *this;
}

bool BigInt::operator==(const BigInt &n) const {
    return number == n.number && isNegative == n.isNegative;
}

bool BigInt::operator!=(const BigInt &n) const {
    return !(*this == n);
}

bool BigInt::operator<(const BigInt &n) const {
    if (isNegative && !n.isNegative) {
        return true;
    }
    if (!isNegative && n.isNegative) {
        return false;
    }
    if (number.length() < n.number.length()) {
        return !isNegative;
    }
    if (number.length() > n.number.length()) {
        return isNegative;
    }
    bool less = false;
    for (int i = 0; i < number.length(); ++i) {
        if (number[i] != n.number[i]) {
            less = (number[i] < n.number[i]);
            break;
        }
    }
    return less ^ isNegative;
}

bool BigInt::operator>=(const BigInt &n) const {
    return !(*this < n);
}

bool BigInt::operator>(const BigInt &n) const {
    return !(*this < n) && (*this != n);
}

bool BigInt::operator<=(const BigInt &n) const {
    return !(*this > n);
}

BigInt::operator std::string() const {
    if (isNegative) {
        std::string result = "-";
        result += number;
        return result;
    }
    return number;
}

size_t BigInt::size() const {
    return number.size() + sizeof(bool);
}

BigInt operator+(const BigInt &a, const BigInt &b) {
    bool isSignMatched = !(a.isNegative ^ b.isNegative);

    if (!isSignMatched) {
        return a - (-b);
    }

    std::string result;
    int digitOverflow = 0;
    auto aIt = a.number.crbegin();
    auto bIt = b.number.crbegin();
    for (; aIt < a.number.crend() && bIt < b.number.crend(); aIt++, bIt++) {
        int aDigit = ToDigit(*aIt);
        int bDigit = ToDigit(*bIt);
        int resultDigit = aDigit + bDigit + digitOverflow;
        result.push_back(ToChar((resultDigit) % 10));
        digitOverflow = ((resultDigit) < 10) ? 0 : 1;
    }
    auto restIt = (aIt == a.number.crend()) ? bIt : aIt;
    auto restEnd = (aIt == a.number.crend()) ? b.number.crend() : a.number.crend();
    for (; restIt < restEnd; restIt++) {
        int restDigit = ToDigit(*restIt);
        result.push_back(ToChar((restDigit + digitOverflow) % 10));
        digitOverflow = (restDigit < 10) ? 0 : 1;
    }
    if (digitOverflow) {
        result.push_back('1');
    }
    std::reverse(result.begin(), result.end());
    BigInt c(result);
    c.isNegative = a.isNegative;
    return c;
}

BigInt operator-(const BigInt &a, const BigInt &b) {
    bool isSignMatched = !(a.isNegative ^ b.isNegative);

    if (!isSignMatched) {
        return a + (-b);
    }

    if (a == b) {
        return {0};
    }

    const BigInt &minTerm = (a > b && !a.isNegative || a < b && a.isNegative) ? b : a;
    const BigInt &maxTerm = (minTerm == b) ? a : b;
    std::string result;
    int digitBorrow = 0;
    auto maxTermIt = maxTerm.number.rbegin();
    auto minTermIt = minTerm.number.rbegin();
    for (; minTermIt < minTerm.number.rend(); maxTermIt++, minTermIt++) {
        int maxTermDigit = ToDigit(*maxTermIt);
        int minTermDigit = ToDigit(*minTermIt);
        int resultDigit = maxTermDigit - minTermDigit;
        result.push_back(ToChar((resultDigit - digitBorrow + 10) % 10));
        digitBorrow = (resultDigit - digitBorrow < 0);
    }
    auto restIt = maxTermIt;
    auto restEnd = maxTerm.number.rend();
    for (; restIt < restEnd; restIt++) {
        int restDigit = ToDigit(*restIt);
        result.push_back(ToChar((restDigit - digitBorrow + 10) % 10));
        digitBorrow = (restDigit - digitBorrow < 0);
    }

    std::reverse(result.begin(), result.end());
    BigInt c(result);
    c.isNegative = (a == minTerm) ? !a.isNegative : a.isNegative;
    return c;
}

std::ostream &operator<<(std::ostream &o, const BigInt &i) {
    o << ((i.isNegative) ? "-" : "") + i.number;
    return o;
}

BigInt::operator int() const {
    int intMax = std::numeric_limits<int>::max();
    int intMin = std::numeric_limits<int>::min();
    BigInt maxBorder = BigInt(intMax);
    BigInt minBorder = BigInt(intMin);

    if (*this < minBorder || *this > maxBorder) {
        throw std::range_error(RANGE_ERROR_EXCEPTION_MESSAGE);
    }

    int accumulator = 0;
    for (auto ch: this->number) {
        accumulator = accumulator * 10 + ToDigit(ch);
    }
    accumulator *= this->isNegative ? -1 : 1;

    return accumulator;
}

BigInt BigInt::operator+() const {
    // To make operator+ useful
    const char *kitty =       "         ／＞　  フ \n"
                              "　　　　　| 　_　 _|\n"
                              "　 　　　／`ミ _x 彡\n"
                              "　　 　 /　　　 　 |\n"
                              "　　　 /　 ヽ　　 ﾉ\n"
                              "　／￣|　　 |　|　|\n"
                              "　| (￣ヽ＿_ヽ_)_)\n"
                              "　＼二つ          \n";
    printf(kitty);
    return {*this};
}

BigInt BigInt::operator-() const {
    BigInt n = BigInt(*this);
    n.isNegative = !isNegative;
    return n;
}

BigInt operator*(const BigInt &a, const BigInt &b) {
    auto aNumber = a.number;
    auto bNumber = b.number;
    std::reverse(aNumber.begin(), aNumber.end());
    std::reverse(bNumber.begin(), bNumber.end());

    std::vector<int> mults(aNumber.length() + bNumber.length());
    for (int i = 0; i < aNumber.length(); i++) {
        for (int j = 0; j < bNumber.length(); j++) {
            mults[i + j] += ToDigit(aNumber[i]) * ToDigit(bNumber[j]);
        }
    }

    std::string multResult;
    for (int i = 0; i < mults.size(); i++) {
        int digitRest = mults[i] % 10;
        int digitOverflow = mults[i] / 10;
        if (i + 1 < mults.size()) {
            mults[i + 1] += digitOverflow;
        }
        multResult.push_back(ToChar(digitRest));
    }

    std::reverse(multResult.begin(), multResult.end());

    while (multResult.length() > 1 && multResult[0] == '0') {
        multResult = multResult.substr(1);
    }

    BigInt result(multResult);
    if ((a.isNegative && !b.isNegative) || (!a.isNegative && b.isNegative)) {
        result.isNegative = true;
    }

    return result;
}

BigInt operator/(const BigInt &a, const BigInt &b) {
    if (b == 0) {
        throw std::invalid_argument(DIV_BY_ZERO_EXCEPTION_MESSAGE);
    }

    BigInt aAbs(a);
    aAbs.isNegative = false;
    BigInt bAbs(b);
    bAbs.isNegative = false;
    if (aAbs < bAbs) {
        return {0};
    }

    BigInt divisionResult;
    divisionResult.number.clear();
    divisionResult.isNegative = a.isNegative ^ b.isNegative;
    bool isDivisionFinished = false;
    int index = 0;
    BigInt currentDividend(ToDigit(aAbs.number[index]));

    while (index < aAbs.number.length()) {
        while (currentDividend < bAbs) {
            if (index + 1 == aAbs.number.length()) {
                isDivisionFinished = true;
                break;
            }

            ++index;
            auto nextDigit = ToDigit(aAbs.number[index]);
            currentDividend *= 10;
            currentDividend += nextDigit;

            if (currentDividend < bAbs) {
                divisionResult *= 10;
            }
        }

        if (isDivisionFinished && currentDividend < bAbs) {
            return divisionResult;
        }

        BigInt rest = currentDividend;
        int subtractionNumber = 0;
        while (rest >= bAbs) {
            rest -= bAbs;
            ++subtractionNumber;
        }

        divisionResult.number.push_back(ToChar(subtractionNumber));
        currentDividend = rest;
    }

    return divisionResult;
}

BigInt operator%(const BigInt &a, const BigInt &b) {
    BigInt result = a - a / b * b;

    return result;
}

std::string ExtendBinaryString(std::string a, size_t expectedLen, char addition) {
    if (a.length() >= expectedLen) {
        return a;
    }

    auto lenNum = a.length();
    for (int i = 0; i < expectedLen - lenNum; ++i) {
        a = addition + a;
    }

    return a;
}

BigInt ConversionToDecimalSystem(const BigInt &a) {
    BigInt result(0);

    BigInt powerOfTwo = 1;
    auto begin = a.number.rbegin();
    auto end = a.number.rend();
    for (; begin < end; begin++) {
        result += ((a.isNegative) ? -1 : 1) * ToDigit(*begin) * powerOfTwo;
        powerOfTwo *= 2;
    }

    return result;
}

BigInt operator&(const BigInt &a, const BigInt &b) {
    BigInt aBinary = ConversionToBinarySystem(a);
    BigInt bBinary = ConversionToBinarySystem(b);

    size_t maxLen = std::max(aBinary.number.length(), bBinary.number.length());
    size_t expectedLen = GetExpectedLength(maxLen);

    aBinary.number = ExtendBinaryString(aBinary.number, expectedLen, '0');
    bBinary.number = ExtendBinaryString(bBinary.number, expectedLen, '0');

    std::string resultBinaryString;

    for (int i = 0; i < expectedLen; ++i) {
        resultBinaryString.push_back(ToChar(ToDigit(aBinary.number[i]) & (ToDigit(bBinary.number[i]))));
    }

    BigInt binaryResult = BigInt();
    binaryResult.isNegative = a.isNegative & b.isNegative;
    binaryResult.number = resultBinaryString;

    BigInt result = ConversionToDecimalSystem(binaryResult);
    return result;
}

BigInt operator|(const BigInt &a, const BigInt &b) {
    BigInt aBinary = ConversionToBinarySystem(a);
    BigInt bBinary = ConversionToBinarySystem(b);

    size_t maxLen = std::max(aBinary.number.length(), bBinary.number.length());
    size_t expectedLen = GetExpectedLength(maxLen);

    aBinary.number = ExtendBinaryString(aBinary.number, expectedLen, '0');
    bBinary.number = ExtendBinaryString(bBinary.number, expectedLen, '0');

    std::string resultBinaryString;

    for (int i = 0; i < expectedLen; ++i) {
        resultBinaryString.push_back(ToChar(ToDigit(aBinary.number[i]) | (ToDigit(bBinary.number[i]))));
    }

    BigInt binaryResult = BigInt();
    binaryResult.isNegative = a.isNegative | b.isNegative;
    binaryResult.number = resultBinaryString;

    BigInt result = ConversionToDecimalSystem(binaryResult);
    return result;
}

BigInt BigInt::operator~() const {
    BigInt result = ConversionToBinarySystem(*this);

    size_t expectedLen = GetExpectedLength(result.number.length());

    result.number = ExtendBinaryString(result.number, expectedLen, '0');
    result.number = BinaryNumberInversion(result.number);
    result = ConversionToDecimalSystem(result);
    result.isNegative = !isNegative;

    return result;
}

size_t GetExpectedLength(size_t binaryStringLength) {
    size_t expectedLen = binaryStringLength / 8 * 8 + ((binaryStringLength % 8) ? 8 : 0);
    return expectedLen;
}

BigInt operator^(const BigInt &a, const BigInt &b) {
    BigInt aBinary = ConversionToBinarySystem(a);
    BigInt bBinary = ConversionToBinarySystem(b);

    size_t maxLen = std::max(aBinary.number.length(), bBinary.number.length());
    size_t expectedLen = GetExpectedLength(maxLen);

    aBinary.number = ExtendBinaryString(aBinary.number, expectedLen, '0');
    bBinary.number = ExtendBinaryString(bBinary.number, expectedLen, '0');

    std::string resultBinaryString;

    for (int i = 0; i < expectedLen; ++i) {
        resultBinaryString.push_back(ToChar(ToDigit(aBinary.number[i]) ^ (ToDigit(bBinary.number[i]))));
    }

    BigInt binaryResult = BigInt();
    binaryResult.isNegative = a.isNegative ^ b.isNegative;
    binaryResult.number = resultBinaryString;

    BigInt result = ConversionToDecimalSystem(binaryResult);
    return result;
}

BigInt &BigInt::operator+=(const BigInt &n) {
    return *this = *this + n;
}

BigInt &BigInt::operator*=(const BigInt &n) {
    return *this = *this * n;
}

BigInt &BigInt::operator-=(const BigInt &n) {
    return *this = *this - n;
}

BigInt &BigInt::operator/=(const BigInt &n) {
    return *this = *this / n;
}

BigInt &BigInt::operator^=(const BigInt &n) {
    return *this = *this ^ n;
}

BigInt &BigInt::operator%=(const BigInt &n) {
    return *this = *this % n;
}

BigInt &BigInt::operator&=(const BigInt &n) {
    return *this = *this & n;
}

BigInt &BigInt::operator|=(const BigInt &n) {
    return *this = *this | n;
}

BigInt &BigInt::operator++() {
    return *this = *this + BigInt(1);
}

const BigInt BigInt::operator++(int) {
    auto previousState = *this;
    *this += 1;
    return previousState;
}

BigInt &BigInt::operator--() {
    return *this = *this - BigInt(1);
}

const BigInt BigInt::operator--(int) {
    auto previousState = *this;
    *this -= 1;
    return previousState;
}

char ToChar(const int d) {
    return d + '0';
}

int ToDigit(const char c) {
    return c - '0';
}

BigInt ConversionToBinarySystem(const BigInt &a) {
    BigInt two = 2;
    BigInt aCopy = a;
    aCopy.isNegative = false;

    std::string binaryNumber;
    while (aCopy >= two) {
        BigInt rest = aCopy % two;
        binaryNumber.push_back(ToChar((int) rest));
        aCopy /= two;
    }

    binaryNumber.push_back(ToChar((int) aCopy));
    std::reverse(binaryNumber.begin(), binaryNumber.end());

    BigInt result = BigInt(binaryNumber);
    result.isNegative = a.isNegative;
    return result;
}

std::string BinaryNumberInversion(std::string a) {
    auto lambda = [](char &a) {
        switch (a) {
            case '1':
                return a = '0';
            case '0':
                return a = '1';
            default:
                throw std::invalid_argument(NOT_BINARY_STRING_EXCEPTION_MESSAGE);
        }
    };

    std::for_each(a.begin(), a.end(), lambda);

    return a;
}
