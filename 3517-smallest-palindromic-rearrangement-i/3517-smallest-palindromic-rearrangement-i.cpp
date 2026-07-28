#include <string>
#include <vector>

class Solution {
public:
    std::string smallestPalindrome(std::string s) {
        int n = s.length();
        std::vector<int> count(26, 0);
        
        // Count frequencies of each character
        for (char c : s) {
            count[c - 'a']++;
        }
        
        std::string first_half = "";
        char mid_char = '\0';
        
        // Build the first half greedily from 'a' to 'z'
        for (int i = 0; i < 26; ++i) {
            int freq = count[i] / 2;
            first_half.append(freq, 'a' + i);
            
            // If the character count is odd, it goes in the middle
            if (count[i] % 2 != 0) {
                mid_char = 'a' + i;
            }
        }
        
        std::string second_half = first_half;
        std::reverse(second_half.begin(), second_half.end());
        
        if (n % 2 != 0) {
            return first_half + mid_char + second_half;
        } else {
            return first_half + second_half;
        }
    }
};