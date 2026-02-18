#include <cmath>
#include <iostream>

/*
 * Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.
 *
 * Example 1:
 *
 * Input: n = 5
 * Output: true
 * Explanation: The binary representation of 5 is: 101
 *  
 * Example 2:
 *
 * Input: n = 7
 * Output: false
 * Explanation: The binary representation of 7 is: 111.
 * 
 * Example 3:
 *
 * Input: n = 11
 * Output: false
 * Explanation: The binary representation of 11 is: 1011.
 *
 * Constraints:
 *    1 <= n <= 231 - 1
 *
 * Link: https://leetcode.com/problems/binary-number-with-alternating-bits?envType=daily-question&envId=2026-02-18
 */

int main(void) {

	int n = 100;
	int l = log2(n);
	std::cout << l << std::endl;
	l++;
	
	int prev = (n >> l)&1;
	std::cout << "prev: " << prev << std::endl;

	for (int i = l -1; i >= 0; i--) {
		int bit = (n>>i)&1;
		std::cout << "bit: " << bit << std::endl;
		if (prev == bit) {
			std::cout << "false" << std::endl;;
			break;
		}
		prev = bit;
	}
	std::cout << "true" << std::endl;;

	return 0;
}
