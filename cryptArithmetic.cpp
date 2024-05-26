#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool solveCryptarithmeticHelper(const string &s1, const string &s2, const string &s3,
                                vector<char> &charList, int index,
                                unordered_map<char, int> &charToDigit,
                                unordered_set<int> &usedDigits);

int convertToNumber(const string &s, const unordered_map<char, int> &charToDigit);

bool solveCryptarithmetic(const string &s1, const string &s2, const string &s3)
{
    unordered_set<char> charSet;
    for (char c : s1)
        charSet.insert(c);
    for (char c : s2)
        charSet.insert(c);
    for (char c : s3)
        charSet.insert(c);

    if (charSet.size() > 10)
    {
        return false;
    }

    vector<char> charList(charSet.begin(), charSet.end());
    unordered_map<char, int> charToDigit;
    unordered_set<int> usedDigits;

    if (solveCryptarithmeticHelper(s1, s2, s3, charList, 0, charToDigit, usedDigits))
    {
        // Print the character to digit mapping
        for (const auto &entry : charToDigit)
        {
            cout << entry.first << "=" << entry.second << endl;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool solveCryptarithmeticHelper(const string &s1, const string &s2, const string &s3,
                                vector<char> &charList, int index,
                                unordered_map<char, int> &charToDigit,
                                unordered_set<int> &usedDigits)
{

    if (index == charList.size())
    {
        int num1 = convertToNumber(s1, charToDigit);
        int num2 = convertToNumber(s2, charToDigit);
        int num3 = convertToNumber(s3, charToDigit);

        return num1 + num2 == num3;
    }

    char currentChar = charList[index];
    for (int digit = 0; digit <= 9; digit++)
    {
        // Check if the digit is already used or if it violates the leading zero constraint
        if (usedDigits.count(digit) == 0 &&
            !(digit == 0 && (currentChar == s1[0] || currentChar == s2[0] || currentChar == s3[0])))
        {

            charToDigit[currentChar] = digit;
            usedDigits.insert(digit);

            if (solveCryptarithmeticHelper(s1, s2, s3, charList, index + 1, charToDigit, usedDigits))
            {
                return true;
            }

            charToDigit.erase(currentChar);
            usedDigits.erase(digit);
        }
    }
    return false;
}

int convertToNumber(const string &s, const unordered_map<char, int> &charToDigit)
{
    int number = 0;
    for (char c : s)
    {
        number = number * 10 + charToDigit.at(c);
    }
    return number;
}

int main()
{
    string s1, s2, s3;

    cout << "Enter the first word (s1): ";
    cin >> s1;

    cout << "Enter the second word (s2): ";
    cin >> s2;

    cout << "Enter the third word (s3): ";
    cin >> s3;

    if (solveCryptarithmetic(s1, s2, s3))
    {
        cout << "Solution found!" << endl;
    }
    else
    {
        cout << "No solution exists." << endl;
    }
    return 0;
}
