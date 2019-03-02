#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
class BigInteger
{
private:
  std::vector<int> b_digit;
  bool isPositive = true;

public:
  BigInteger();
  BigInteger(const std::string &big_number);
  BigInteger(std::vector<int> &digit);
  const std::vector<int> &getNumber() const;
  int getDigitSize() const;
  int getDigit(int digit) const;
  void checkOverflow();
  BigInteger &operator=(const BigInteger &num);
  friend BigInteger &operator+=(BigInteger &num1, const BigInteger &num2);
  friend std::ostream &operator<<(std::ostream &out, const BigInteger &big_integer);
  friend BigInteger operator+(const BigInteger &num1, const BigInteger &num2);
  friend BigInteger operator-(const BigInteger &num1, const BigInteger &num2);
  friend BigInteger operator*(const BigInteger &num1, const BigInteger &num2);
  friend BigInteger operator/(const BigInteger &num1, const BigInteger &num2);
  friend bool operator<(const BigInteger &num1, const BigInteger &num2);
  friend bool operator<(int num1, const BigInteger &num2);
};
#endif