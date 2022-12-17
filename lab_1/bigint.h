#ifndef LAB_1_BIGINT_H
#define LAB_1_BIGINT_H

#include <string>
#include <stdexcept>

namespace {
    const char *EMPTY_STRING_EXCEPTION_MESSAGE = "Cannot build <BigInt> with empty string";
    const char *NOT_NUMBER_EXCEPTION_MESSAGE = "Cannot build <BigInt> with string which is not a number";
    const char *RANGE_ERROR_EXCEPTION_MESSAGE = "Cannot be casted to <int>";
    const char *NOT_BINARY_STRING_EXCEPTION_MESSAGE = "String does not represent binary number";
    const char *DIV_BY_ZERO_EXCEPTION_MESSAGE = "Division by zero";
}

/**
 * @class BigInt.
 *
 * @brief Represents an arbitrarily large signed integer.
 *        The BigInt type is a type that represents an arbitrarily large integer whose value,
 *        in theory, has no upper or lower bounds.
 *        The BigInt type supports arithmetic operations on arbitrary precision integers in a manner
 *        that is broadly consistent with the conventional operations on primitive fixed length integers.
 *
 * @author Nadya Kotelnikova.
 *
 * @version 1.2.1 - After Google Tests.
 */
class BigInt {
private:
    /**
     * @brief Number representation as a string.
     */
    std::string number;

    /**
     * @brief Saves a sign of a number.
     */
    bool isNegative;

    friend BigInt ConversionToDecimalSystem(const BigInt &);

    friend BigInt ConversionToBinarySystem(const BigInt &);

public:
    /**
     * @brief Builds the new BigInt object from default value 0.
     */
    BigInt();

    /**
     * @brief Builds the new BigInt object from int value.
     *
     * @param Signed decimal number of int type.
     */
    BigInt(int);

    /**
     * @brief Translates the decimal string representation of a BigInt into a BigInt.
     *
     * @param The decimal string representation of an arbitrary precision number.
     *
     * @throw invalid_argument exception - if param string is empty or or does not describe a number.
     */
    BigInt(const std::string &);

    /**
     * @brief Builds a new BigInt object based on the BigInt object passed.
     *        The corresponding field values of the passed object
     *        are copied into the fields of the object being built.
     *
     * @param The existed BigInt object.
     */
    BigInt(const BigInt &);

    /**
     * @brief Destructs object and clears field values.
     */
    ~BigInt();

    /**
     * @brief Copies field values param object into the same fields of this objects.
     *        If param object is this, just returns this.
     *
     * @param The existed BigInt object.
     *
     * @return Updated this object.
     */
    BigInt &operator=(const BigInt &);

    /**
     * @brief Defines prefix increment operator.
     *        Updates this object without creating new.
     *
     * @return This.
     */
    BigInt &operator++();

    /**
     * @brief Defines postfix increment operator.
     *        Creates new BigInt object based on this and applies increment operator to it.
     *
     * @param This.
     *
     * @return New BigInt incremented object.
     */
    const BigInt operator++(int);

    /**
     * @brief Defines prefix decrement operator.
     *        Updates this object without creating new.
     *
     * @return This.
     */
    BigInt &operator--();

    /**
     * @brief Defines postfix decrement operator.
     *        Creates new BigInt object based on this and applies decrement operator to it.
     *
     * @param This.
     *
     * @return New BigInt decremented object.
     */
    const BigInt operator--(int);

    /**
     * @brief Look at definition of overloaded operator+, left operand for addition operation is this object.
     *
     * @param Right operand for addition operation.
     *
     * @return Updated this object.
     */
    BigInt &operator+=(const BigInt &);

    /**
     * @brief Look at definition of overloaded operator*, left operand for multiplication operation is this object.
     *
     * @param Right operand for multiplication operation.
     *
     * @return Updated this object.
     */
    BigInt &operator*=(const BigInt &);

    /**
     * @brief Look at definition of overloaded operator-, left operand for subtraction operation is this object.
     *
     * @param Right operand for subtraction operation.
     *
     * @return Updated this object.
     */
    BigInt &operator-=(const BigInt &);

    /**
     * @brief Look at definition of overloaded operator-, left operand for dividing operation is this object.
     *
     * @param Right operand for dividing operation.
     *
     * @return Updated this object.
     */
    BigInt &operator/=(const BigInt &);

    /**
     * @brief Look at definition of overloaded operator^, left operand for bitwise "XOR" operation is this object.
     *
     * @param Right operand for bitwise "XOR" operation.
     *
     * @return Updated this object.
     */
    BigInt &operator^=(const BigInt &);

    /**
     * @brief Look at definition of overloaded operator&, left operand for bitwise "AND" operation is this object.
     *
     * @param Right operand for bitwise "AND" operation.
     *
     * @return Updated this object.
     */
    BigInt &operator&=(const BigInt &);

    /**
     * @brief Look at definition of overloaded operator^, left operand for bitwise "OR" operation is this object.
     *
     * @param Right operand for bitwise "OR" operation.
     *
     * @return Updated this object.
     */
    BigInt &operator|=(const BigInt &);

    /**
     * @brief Look at definition of overloaded operator%, left operand for modulo division operation is this object.
     *
     * @param Right operand for modulo division operation.
     *
     * @return Updated this object.
     */
    BigInt &operator%=(const BigInt &);

    /**
     * @brief Implements unary plus operation which builds a new Bigint object
     *        and fills that fields values by fields values of this object.
     *
     * @return New BigInt object built from this.
     */
    BigInt operator+() const;

    /**
     * @brief Implements unary plus operation which builds a new Bigint object
     *        and fills that fields values by fields values of this object but reverses the sign field value.
     *
     * @return New BigInt object built from this with reversed sign.
     */
    BigInt operator-() const;

    /**
     * @brief Compares this BigInt with the specified object for equality.
     *
     * @param Object to which this BigInt is to be compared.
     *
     * @return True - if and only if the specified object has the same corresponding field values as this BigInt.
     */
    bool operator==(const BigInt &) const;

    /**
    * @brief Compares this BigInt with the specified object for non-equality.
    *
    * @param Object to which this BigInt is to be compared.
    *
    * @return False - if and only if the specified object has the same corresponding field values as this BigInt.
    */
    bool operator!=(const BigInt &) const;

    /**
    * @brief Compares this BigInt with the specified object for a strict weak ordering.
    *
    * @param Object to which this BigInt is to be compared.
    *
    * @return True - if and only if this object represents a smaller number than the specified object.
    */
    bool operator<(const BigInt &) const;

    /**
    * @brief Compares this BigInt with the specified object for a higher weak ordering.
    *
    * @param Object to which this BigInt is to be compared.
    *
    * @return True - if and only if this object represents a greater number than the specified object.
    */
    bool operator>(const BigInt &) const;

    /**
    * @brief Compares this BigInt with the specified object for a not higher weak ordering.
    *
    * @param Object to which this BigInt is to be compared.
    *
    * @return True - if and only if this object represents a not greater number than the specified object.
    */
    bool operator<=(const BigInt &) const;

    /**
    * @brief Compares this BigInt with the specified object for a not strict weak ordering.
    *
    * @param Object to which this BigInt is to be compared.
    *
    * @return True - if and only if this object represents a not smaller number than the specified object.
    */
    bool operator>=(const BigInt &) const;

    /**
     * @brief Defines the operator for converting the BigInt type to the int type.
     *        The conversion operation create new object without changing the object being converted.
     *
     * @return Int representation of this object.
     *
     * @throw range_error exception - if the numeric value of this BigInt is out of bounds for an int type.
     */
    explicit operator int() const;

    /**
     * @brief Casts this BigInt object into the decimal signed string representation.
     *
     * @return Decimal signed string representation of this.
     */
    explicit operator std::string() const;

    /**
     * @brief Specifies the amount of memory, in bytes, that this BigInt occupies.
     *
     * @return The number of bytes occupied by this object.
     */
    size_t size() const;

    /**
     * @brief Implements the operation of addition two BigInt numbers.
     *
     * @param Two BigInt operands.
     *
     * @return Result of addition two BigInt objects.
     */
    friend BigInt operator+(const BigInt &, const BigInt &);

    /**
     * @brief Implements the operation of subtraction two BigInt numbers.
     *
     * @param Two BigInt operands.
     *
     * @return Result of subtraction two BigInt objects.
     */
    friend BigInt operator-(const BigInt &, const BigInt &);

    /**
     * @brief Implements the operation of multiplication two BigInt numbers.
     *
     * @param Two BigInt operands.
     *
     * @return Result of multiplication two BigInt objects.
     */
    friend BigInt operator*(const BigInt &, const BigInt &);

    /**
     * @brief Implements the operation of dividing two BigInt numbers.
     *
     * @param The first param is BigInt dividend and the second param is BigInt divisor.
     *
     * @return The result of dividing two BigInt objects.
     */
    friend BigInt operator/(const BigInt &, const BigInt &);

    /**
     * @brief Implements the operation of modulo division of two BigInt numbers.
     *
     * @param The first param is BigInt dividend and the second param is BigInt modulo.
     *
     * @return Result of modulo division two BigInt objects.
     */
    friend BigInt operator%(const BigInt &, const BigInt &);

    /**
     * @brief Implements a "bitwise AND" of two objects.
     *        This method returns a negative BigInt if and only if input objects are both negative.
     *
     * @param Two BigInt terms.
     *
     * @return New BigInt object which is result of bitwise AND operation.
     */
    friend BigInt operator&(const BigInt &, const BigInt &);

    /**
     * @brief Implements a "bitwise OR" of two objects.
     *        This method returns a negative BigInt if and only if at least one of the input objects is negative.
     *
     * @param Two BigInt terms.
     *
     * @return New BigInt object which is result of bitwise OR operation.
     */
    friend BigInt operator|(const BigInt &, const BigInt &);

    /**
     * @brief Implements a "bitwise NOT" over this object.
     *        This method returns a negative value if and only if this BigInt is non-negative.
     *
     * @return This.
     */
    BigInt operator~() const;

    /**
     * @brief Implements a "bitwise XOR" of two objects.
     *        This method returns a negative BigInt if and only if input objects have different signs.
     *
     * @param Two BigInt terms.
     *
     * @return New BigInt object which is result of bitwise XOR operation.
     */
    friend BigInt operator^(const BigInt &, const BigInt &);

    /**
     * @brief Formats the output of a BigInt object to the output stream in pretty viewing.
     *
     * @param The first - reference to a non-const output stream object,
     *        the second - reference to an object class constant that should be printed in a stream.
     *
     * @return Updated output stream object.
     */
    friend std::ostream &operator<<(std::ostream &o, const BigInt &i);
};

#endif //LAB_1_BIGINT_H
