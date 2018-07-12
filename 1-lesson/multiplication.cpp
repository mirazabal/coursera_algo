#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
//#include "catch.hpp"

////////////////// my version ///////////////////////////////////////////////////////////////////
inline 
uint64_t get_carry(uint64_t a)
{
	return a/10;
}

inline
uint64_t get_remainder(uint64_t a)
{
	return a%10;
}

std::pair<uint64_t,uint64_t> multiply2_with_carry(uint64_t m0, uint64_t m1, uint64_t c)
{
	uint64_t ret = m0 * m1;
	ret += c;
	return std::make_pair(get_remainder(ret), get_carry(ret));
}

uint64_t sum_columms_vals( std::vector<std::vector<uint64_t>> const& v, int64_t index_vec)
{
		uint64_t val{0};

		for(auto it = std::begin(v); it != std::end(v); ++it){
			if(index_vec >= 0 && index_vec < it->size() )		val += (*it)[index_vec];
			--index_vec;
		}
	return val;
}

std::vector<uint64_t> sum_multiply_vec(std::vector<std::vector<uint64_t>> const& v)
{
	std::vector<uint64_t> retVec;
	int64_t iteration = v[0].size()*2;
	uint64_t carry{0};
	while(iteration > 0){

		int64_t index_vec = v[0].size()*2  - iteration;					
		uint64_t val = sum_columms_vals(v, index_vec);
		val += carry;

		carry = get_carry(val);
		if(val != 0)	retVec.emplace_back( get_remainder(val) );
		--iteration;
	}

	if(carry != 0) retVec.emplace_back(carry);
		
	return retVec;
}

std::vector<std::vector<uint64_t>> multiply_digit_with_vector(std::vector<uint64_t> const& v1, std::vector<uint64_t> const& v2)
{
	std::vector<std::vector<uint64_t>> vecMiddle;
	for(auto it = std::rbegin(v1); it != std::rend(v1); ++it){
		uint64_t carry{0};
		std::vector<uint64_t> tempVec;
		for(auto it2 = std::rbegin(v2); it2 != std::rend(v2); ++it2){
			auto ret = multiply2_with_carry(*it, *it2, carry);
			carry = ret.second;
			tempVec.emplace_back(ret.first);
		}
		if(carry != 0) tempVec.emplace_back(carry);
		vecMiddle.emplace_back(tempVec);
	}
	return vecMiddle;
}

std::vector<uint64_t> multiplication(std::vector<uint64_t> const& v1, std::vector<uint64_t> const& v2)
{
	auto vecMiddle = multiply_digit_with_vector(v1,v2);
	return sum_multiply_vec(vecMiddle);
}
////////////////// my version ///////////////////////////////////////////////////////////////////


///////////////// https://www.geeksforgeeks.org/multiply-large-numbers-represented-as-strings/
std::string multiply_geeks(std::string num1, std::string num2)
{
    int n1 = num1.size();
    int n2 = num2.size();
    if (n1 == 0 || n2 == 0)
       return "0";
 
    // will keep the result number in vector
    // in reverse order
    std::vector<int> result(n1 + n2, 0);
 
    // Below two indexes are used to find positions
    // in result. 
    int i_n1 = 0; 
    int i_n2 = 0; 
 
    // Go from right to left in num1
    for (int i=n1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';
 
        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0; 
         
        // Go from right to left in num2             
        for (int j=n2-1; j>=0; j--)
        {
            // Take current digit of second number
            int n2 = num2[j] - '0';
 
            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position. 
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
 
            // Carry for next iteration
            carry = sum/10;
 
            // Store result
            result[i_n1 + i_n2] = sum % 10;
 
            i_n2++;
        }
 
        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
 
        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }
 
    // ignore '0's from the right
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
       i--;
 
    // If all were '0's - means either both or
    // one of num1 or num2 were '0'
    if (i == -1)
       return "0";
 
    // generate the result string
    std::string s = "";
    while (i >= 0)
        s += std::to_string(result[i--]);
 
    return s;
}


/*
TEST_CASE( "Big numbers multiplication are computed", "[factorial]" ) {
	std::vector<uint64_t> v1 = {9,2};
	std::vector<uint64_t> v2 = {2,7};
	std::vector<uint64_t> result = {4,8,4,2};
	REQUIRE( multiplication(v1,v2)  ==  result);

	std::vector<uint64_t> v12 = {9,2,9,0,1};
	std::vector<uint64_t> v22 = {2,7,3,6,2};

	std::vector<uint64_t> result2 = {2,6,1,7,5,9,1,4,5,2};
	REQUIRE( multiplication(v12,v22)  ==  result2);

	std::vector<uint64_t> v13 = {3,4,9,2,9,0,1};
	std::vector<uint64_t> v23 = {2,7,3,6,2,3,4};

	std::vector<uint64_t> result3 = {4,3,8,4,7,4,4,9,3,7,5,5,9};
	REQUIRE( multiplication(v13,v23)  ==  result3);

}
*/

int main()
{
	std::vector<uint64_t> v1 = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8,4,1,9,7,1,6,9,3,9,9,3,7,5,1,0,5,8,2,0,9,7,4,9,4,4,5,9,2};
	std::vector<uint64_t> v2 = {2,7,1,8,2,8,1,8,2,8,4,5,9,0,4,5,2,3,5,3,6,0,2,8,7,4,7,1,3,5,2,6,6,2,4,9,7,7,5,7,2,4,7,0,9,3,6,9,9,9,5,9,5,7,4,9,6,6,9,6,7,6,2,7};
	
	auto val = multiplication(v1,v2);
	for(auto it = std::rbegin(val); it != std::rend(val); ++it )
		std::cout << *it;
	std::cout << " " << std::endl; 

	std::string num1 = {"3141592653589793238462643383279502884197169399375105820974944592"};
	std::string num2 = {"2718281828459045235360287471352662497757247093699959574966967627" };

	std::cout << multiply_geeks( num1, num2) << '\n';

	return 0;
}

