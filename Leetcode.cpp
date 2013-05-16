/*
 * Leetcode.cpp
 *	Solutions to questions from leetcode 
 * 	Created on: May 11, 2013
 *      Author: Vincent Yun
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// #1 Two Sum *
// return the index of the target in the array of numbers
// index is 1-based; bool value indicates whether start from left
int findIndex(vector<int>& numbers, int target, bool fromLeft) {
	if (fromLeft) {
		for (size_t i=0; i<numbers.size(); ++i) {
			if (numbers[i] == target)
				return i+1; 
		}
	} else {
		for (size_t i=numbers.size()-1; i>=0; --i) {
			if (numbers[i] == target)
				return i+1; 
		}
	}
	return -1; 
}
// find two numbers that sum up to target, return their 1-based indexes 
// index1 should be < index2
// method: sort + running pointers
// passed test in 16 milli secs
vector<int> twoSum(vector<int> &numbers, int target) {
	vector<int> numCopy(numbers);
	sort(numCopy.begin(), numCopy.end()); 
	int left = 0;
	int right = numCopy.size()-1;
	int sum; 
	while (left < right) {
		sum = numCopy[left] + numCopy[right]; 
		if (sum == target) break; 
		else if (sum < target) left++; 
		else right--;
	}
	vector<int> ret(2); 
	ret[0] = findIndex(numbers, numCopy[left], true); 
	ret[1] = findIndex(numbers, numCopy[right], false);
	if (ret[0] > ret[1])
		swap(ret[0], ret[1]);
	return ret;
}

// #2 Median of Two Sorted Arrays (also in article) ***
// find the median of two sorted array in O(log(m+n))

// #3 Longest substring without repeating characters *
// passed large test in 80 milli secs
// running pointers method
// Note how to manage the running pointers
int lengthOfLongestSubstring(string s) {
	vector<int> charCount(256, 0); 
	int maxLen = 0; 
	// head of longest substring without repeadting char
	int head = 0; 
	// current char
	int curr = 0;
	while (curr < s.length()) {
		if (charCount[s[curr]]) {
			// curr - head is the length of the longest substring 
			//		without repeadting char ending at current char
			maxLen = max(maxLen, curr-head);
			// shift head and curr to the right position
			while (s[curr] != s[head]) {
				charCount[s[head]] = 0;
				head++;
			}
			head++; 
			curr++;
		} else {
			charCount[s[curr]] = 1; 
			curr++;
		}
	}
	// do not forget the last round
	maxLen = max(maxLen, curr-head);
	return maxLen;
}

// #4 Add two numbers

// #5 Add longest palindromic substring


// #6 ZigZag conversion *
// A naive version that exceeded time limit on leetcode
// Following method is based on the observation of pattern
string convert(string s, int nRows) {
	if (nRows <=1) return s; 
	string ret;
	// one zig is a repeating unit 
	int zigSize = 2*nRows - 2;
	int c;
	for (int i=0; i<nRows; ++i) {
		// for the first and last lines, add every zigSize-th char into string
		if (i == 0 || i == nRows-1) {
			for (c = i; c < s.length(); ) {
				ret.push_back(s[c]);
				c = c + zigSize;
			}
		} else { // for the rest lines, add two chars for each zig
			for (c = i; c < s.length(); ) {
				ret.push_back(s[c]);
				int secId = c+zigSize-2*i;
				if (secId< s.length()) { // note this check
					ret.push_back(s[secId]);
				}
				c = c + zigSize;
			}
		}
	} // since push s[c] is executed for every i, we can actually merge those two branches
	return ret;
}

// #7 Reverse integer
// a simple variant of atoi
// it may overflow?
int reverse(int x) {
	// for non-negative integer only
	assert(x >= 0); 
	int y = ((x < 0) ? -1 * x : x);
	int ret = 0;
	while (y > 0) {
		ret = ret*10 + (y % 10); 
		y = y/10; 
	}
	return ((x < 0) ? -1 * ret: ret);
}

// #8 atoi *
// The function first discards as many whitespace characters as necessary 
//	until the first non-whitespace character is found. Then, starting from 
//	this character, takes an optional initial plus or minus sign followed 
//	by as many numerical digits as possible, and interprets them as a numerical value.
// The string can contain additional characters after those that form the integral number, 
//	which are ignored and have no effect on the behavior of this function.
// If the first sequence of non-whitespace characters in str is not a valid 
//	integral number, or if no such sequence exists because either str is empty 
//	or it contains only whitespace characters, no conversion is performed.
// If no valid conversion could be performed, a zero value is returned. 
//	If the correct value is out of the range of representable values, 
//	INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
int atoi(const char *str) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	if (!str) return NULL; 
	const char* p = str; 
	// skip heading blanks
	while (*p == ' ') 
		p++;

	// check symbol
	bool isNeg = false;
	if (*p == '-') {
		isNeg = true; 
		p++;
	} else if (*p == '+') {
		p++;
	}

	int ret = 0; 
	int heading = true; 
	while (*p != '\0') {
		if (*p > '0' && *p <= '9') {
			// deal with overflow
			int y = *p - '0';  
			if (!isNeg && ret > (INT_MAX - y)/10 || isNeg && ret > -1 * ((INT_MIN + y)/10)) {
				return (isNeg ? INT_MIN : INT_MAX);
			} else {
				ret = ret*10 + y;
				p++;
				if (heading)    
					heading = false;
			}
		} else if (*p == '0' && heading) {
			p++;
		} else if (*p == '0' && !heading) {
			// deal with overflow
			if (!isNeg && ret > INT_MAX/10 || isNeg && ret > -1 * (INT_MIN/10)) {
				return (isNeg ? INT_MIN : INT_MAX);
			} else {
				ret = ret*10; 
				p++;                    
			}
		} else {
			break; 
		}
	}
	return (isNeg ? -1*ret : ret);
}

// #9 Palindrome integer
// Determine whether an integer is a palindrome. Do this without extra space.
// (the requirement about "no extra space" does not mean that you can not defined primitive variables
bool isPalindrome(int x) {
	// define negative as non-palindrome
	if (x < 0) return false;                   
	int div = 1; 
	// find the first digit (this is really ugly, but ...)
	while (x/div >= 10)
		div *= 10; 
	int l, r;
	while (x > 0) {
		l = x/div; 
		r = x%10; 
		if (l != r) return false;
		else {
			x = (x % div) / 10;
			div /= 100;
		}
	}
	return true;
}

// Regular expression match (hard)**
// recursive method
// There is a dynamic programming method from CaiMuNiao
bool isMatch(const char *s, const char *p) { // '.' and '*' can only occur in latter
	if (*p == '\0') return *s == '\0'; 
	// '*' is critical for recursion
	if (*(p+1) != '*') { // without '*', compare one by one
		if (*s == *p || *p == '.' && *s != '\0') 
			return isMatch(s+1, p+1); 
		return false;   
	} else {
		// with '*', move forward on string s as far as possible
		while (*s == *p || *p == '.' && *s != '\0') {
			if (isMatch(s, p+2))
				return true;
			s++; 
		}
		// *p and *(p+1) = '*' have been consumed, move forward by two steps 
		return isMatch(s, p+2);
	}
}

// #14 longest common prefix
string longestCommonPrefix(vector<string> &strs) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	if (strs.empty()) return ""; 
	string ret;
	int m = strs.size(); 
	int n = strs[0].size(); 
	for (int i=0; i<n; ++i) {
		for (int j=1; j<m; ++j) {
			if (strs[j][i] != strs[0][i]) {
				return ret;
			}
		}
		ret.push_back(strs[0][i]);
	}
	return ret;
}

// 3sum *
// Naive method requires O(n^3), which may exceed time limit
vector<vector<int> > threeSum(vector<int> &num) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	int nSize = num.size(); 
	// here threeSum returns numbers (not indices), so sort does not increse complexity
	sort(num.begin(), num.end()); 
	vector<vector<int> > ret; 
	for (int i=0; i<nSize;) {
		int j, k; 
		for (j=i+1, k=nSize-1; j<k; ) {
			int sum = num[i]+num[j]+num[k]; 
			if (sum == 0) {
				vector<int> iVec; 
				iVec.push_back(num[i]);
				iVec.push_back(num[j]);
				iVec.push_back(num[k]);
				ret.push_back(iVec);
				// skip over duplicates, necessary
				while (j<k && num[j] == num[j+1])
					j++; 
				while (k>j && num[k] == num[k-1])
					k--;
				j++; 
				k--;
			} else if (sum < 0) {
				//skip over duplicates, but does not impact the correctness
				while (j<k && num[j] == num[j+1])
					j++;
				j++; 
			} else {
				//skip over duplicates, but does not impact the correctnes
				while (k>j && num[k] == num[k-1])
					k--;
				k--;
			}
		}
		//skip over duplicates, necessary
		while (i+1<nSize && num[i+1] == num[i]) 
			i++;
		i++;
	}
	return ret; 
}

// #16 3Sum closest*
// incorrect solution, passed almost every testing case
int threeSumClosest(vector<int> &num, int target) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	int ret; 
	sort(num.begin(), num.end()); 
	int minDiff = INT_MAX; 
	int nSize = num.size(); 
	for (int i=0; i<nSize; ) {
		int j, k;
		for (j=i+1, k=nSize-1; j<k; ) {
			int sum = num[i] + num[j] + num[k]; 
			int diff = abs(sum-target); 
			if (diff < minDiff) {
				minDiff = diff; 
				ret = sum; 
				while (j+1<k && num[j] == num[j+1])
					j++;
				while (k-1>j && num[k] == num[k-1])
					k--;
			}
			// this is NOT correct
			int sum1 = num[i] + num[j+1] + num[k];
			int sum2 = num[i] + num[j] + num[k-1];
			if (abs(sum1-target) < abs(sum2-target))
				j++; 
			else 
				k--;  
		}
		while (i+1<nSize && num[i+1] == num[i])
			i++; 
		i++; 
	}
	return ret; 
}

// This is correct, note how to deal with pointers 
int threeSumClosest(vector<int> &num, int target) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function

	//sort is necessary
	sort(num.begin(), num.end());
	int n = num.size(); 
	int minDiff = INT_MAX;
	int clos; 
	int sum; 
	for (int i=0; i<n-2; ++i) {
		int j = i+1; 
		int k = n-1; 
		while (j<k) {
			sum = num[i] + num[j] + num[k]; 
			int diff = abs(sum - target); 
			if (diff<minDiff) {
				minDiff = diff;
				clos = sum; 
			}
			// note how j and k are updated
			if (sum < target) 
				j++; 
			else 
				k--;
		}
	}
	return clos; 
}

// #17 4Sum *
// add one more loop for 3sum
// complexity O(n^3), better solution?
vector<vector<int> > fourSum(vector<int> &num, int target) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	sort(num.begin(), num.end());
	vector<vector<int> > ret; 
	int n = num.size(); 
	for (int i=0; i<n-3; ) {
		for (int j=i+1; j<n-2; ) {
			int l = j+1; 
			int r = n-1;  
			while (l<r) {
				int sum = num[i] + num[j] + num[l] + num[r]; 
				if (sum == target) {
					vector<int> iVec(4); 
					iVec[0] = num[i]; 
					iVec[1] = num[j]; 
					iVec[2] = num[l]; 
					iVec[3] = num[r];
					ret.push_back(iVec);
					while (l+1<r && num[l+1] == num[l]) 
						l++; 
					l++;
					while (r-1>l && num[r-1] == num[r])
						r--;
					r--;
				} else if (sum < target)
					l++; 
				else 
					r--; 
			}
			while (j+1 < n-2 && num[j+1] == num[j])
				j++;
			j++; 
		}
		while (i+1 < n-3 && num[i+1] == num[i])
			i++;
		i++; 
	}
	return ret;  
}

// #18 letter combinations of a phone number *
// A generic question about generating combinations of Descartes multiplications of multiple sets
// Use tail recursive and static array
void comb(string& digits, vector<string>& ret, string str, int pos) {
	const static string digArr[] = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"}; 
	if (str.size() == digits.size()) 
		ret.push_back(str); 
	int curr = digits[pos] - '0'; 
	for (int i=0; i<digArr[curr].size(); ++i) {
		string tmp; 
		tmp = str + digArr[curr][i]; 
		comb(digits, ret, tmp, pos+1);
	}
}

vector<string> letterCombinations(string digits) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	vector<string> ret; 
	comb(digits, ret, "", 0); 
	return ret; 
}

// #19 Remove Nth node from end of list
// simple sliding windows method
// note the use of dummy head node
ListNode *removeNthFromEnd(ListNode *head, int n) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	ListNode dummy(-1); 
	dummy.next = head; 
	ListNode* l = &dummy; 
	ListNode* r = &dummy; 
	while (n--) 
		r = r->next; 
	while (r->next) {
		l = l->next; 
		r = r->next; 
	}
	if (l->next == r) {
		l->next = NULL; 
		delete r;
	} else {
		ListNode* curr = l->next; 
		l->next = l->next->next; 
		delete curr;            
	} 
	return dummy.next; 
}

// #20 Valid parentheses
// clear logic
bool isValid(string s) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	string stack; 
	for (size_t i=0; i<s.size(); ++i) {
		if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
			stack += s[i];
		} else if (s[i] == ')'){
			if (stack.size() > 0 && stack.back() == '(') {
				stack.erase(stack.end()-1);
			} else 
				return false;
		} else if (s[i] == ']') {
			if (stack.size() > 0 && stack.back() == '[') {
				stack.erase(stack.end()-1);
			} else 
				return false;
		} else if (s[i] == '}') {
			if (stack.size() > 0 && stack.back() == '{') {
				stack.erase(stack.end()-1);
			} else 
				return false;
		}
	}
	if (stack.size() == 0)
		return true; 
	else 
		return false;
}

// #21 Generate Parentheses
// imagine a binary tree, expand its every legal node
// use tail recursion
void generate(vector<string> &pairs, string str, int lc, int rc, int n) {
	if (lc == n && rc == n) {
		pairs.push_back(str); 
		return;
	} else if (lc == n && rc < n) {
		generate(pairs, str+')', lc, rc+1, n);
	} else if (lc > rc) {
		generate(pairs, str+'(', lc+1, rc, n);
		generate(pairs, str+')', lc, rc+1, n);
	} else if (lc == rc) {
		generate(pairs, str+'(', lc+1, rc, n);
	} 
}
vector<string> generateParenthesis(int n) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	vector<string> ret; 
	generate(ret, "", 0, 0, n);
	return ret;
}


// #22 Merge k sorted lists
// recursively use "merge two sorted lists"

// #23 Swap nodes in pairs
// repeatedly remove the middle node and insert it after the right node with the help of the left pointer
// use dummy head, note boundary condition
ListNode *swapPairs(ListNode *head) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	if (head == NULL || head->next == NULL) return head;
	ListNode dummy(-1); 
	dummy.next = head; 
	ListNode* l = &dummy;
	ListNode* m = head;
	ListNode* r = head->next;
	while (r) {
		// remove the middle node
		l->next = r;
		m->next = r->next;
		r->next = m;
		l = r; 
		if (m->next != NULL && m->next->next != NULL) {
			l =m; 
			r = m->next->next; 
			m = l->next;
		} else {
			break; 
		}
	}
	return dummy.next;
}

// #24 Reverse nodes in K groups *
// process groups recursively and reverse each group iteratively
ListNode *reverseKGroup(ListNode *head, int k) {
	// boundary condition
	if (head == NULL) return head; 
	// shift the currently processing window to right postions
	ListNode* l = head; 
	ListNode* r = l;
	int i; 
	for (i=0; i<k-1; ++i) {
		if (r->next)
			r = r->next;
		else 
			break;
	}
	// this sublist is not long enough, directly return its head 
	if (i<k-1) 
		return head; 
	else {
		// iteratively reverse the current k nodes,
		ListNode* remListHead = r->next; 
		ListNode *prev = NULL; 
		ListNode *curr = head; 
		for (i =0; i<k; ++i) {
			ListNode *next = curr->next; 
			curr->next = prev;
			prev = curr; 
			curr = next; 
		} 
		// recursively link to the remaining sublist
		// now head is tail, prev is head
		head->next = reverseKGroup(remListHead, k);
		return prev;            
	}
}

// #25 Remove duplicates from sorted array
int removeDuplicates(int A[], int n) {
	// the position of the current number
	int curr=0; 
	// the position to insert the next number
	int pos=0; 
	while (curr<n) {
		A[pos] = A[curr];
		pos++; 
		while (curr+1<n && A[curr+1] == A[curr]) 
			curr++; 
		curr++;
	}
	return pos; 
}

// #26 Remove elements
int removeElement(int A[], int n, int elem) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	int curr = 0; 
	int pos = 0; 
	while (curr<n) {
		if (A[curr] != elem) {
			A[pos] = A[curr]; 
			pos++;
		}
		curr++;
	}
	return pos; 
}

// #27 strStr()
// http://leetcode.com/2010/10/implement-strstr-to-find-substring-in.html
// brute force, cannot pass large test set
// note if needle is empty string, return the entire haystack
// note that to check whether char pointed by p is null, use *p rather than p
char *strStr(char *haystack, char *needle) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	if (haystack == NULL || needle == NULL) return NULL;
	if (!*needle) return haystack; 
	char *p = haystack; 
	while (*p) {
		char *haySubStr_p = p; 
		char *neeStr_p= needle; 
		while (*haySubStr_p && *neeStr_p && *haySubStr_p == *neeStr_p) {
			haySubStr_p++; 
			neeStr_p++; 
		}
		if (!*neeStr_p)
			return p;            
		p++; 
	}
	return NULL; 
}

// track the string length and return NULL when needle is longer than remaining haystack
// use chasing pointer to implement this
// passed large test set in 20 milli secs
// we should check M - N + 1 before returning NULL, where M = haystack.size and N = needle.size
// check how this is implemented in this code (use probe_p pointer)
char *strStr(char *haystack, char *needle) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	if (haystack == NULL || needle == NULL) return NULL;
	if (!*needle) return haystack; 
	char *p = haystack; 
	char *neeStr_p= needle;
	char *probe_p = haystack; 
	while (*++neeStr_p) 
		probe_p++; 
	while (*probe_p) {
		char *haySubStr_p = p; 
		neeStr_p = needle; 
		while (*haySubStr_p && *neeStr_p && *haySubStr_p == *neeStr_p) {
			haySubStr_p++; 
			neeStr_p++; 
		}
		if (!*neeStr_p)
			return p;            
		p++; 
		probe_p++; 
	}
	return NULL; 
}

// #28 Divide two integers **
// This question explores both numerical representation and detailes of numbers
// Representation: given dividend = a and divisor = b, a = b*2^(n1) + b*2^(n2) + ..., 
//	and thus a = (2^(n1)+2^(n2)+...)b. 
// Example: 15 = 1111, 7 = 111, 1111 = 111<<1 + 1 (remainder), where opertion <<1 equals 2^1
//	so 15/7 = 2. 
int divide(int dividend, int divisor) {
	// throw exception for divisor = 0
	// overflow_error is included in <stdexcept>
    if (divisor == 0)
        throw std::overflow_error("Divided by zero exception!");
    // check whether two integers have different symbol (+/-)
	bool neg = false;
    if (dividend < 0) neg = !neg;
    if (divisor < 0) neg = !neg;
	// convert to long long to aviod nasty issue relevant to overflow
    long long a = (long long)dividend;
	// abstract value should be calculated after type conversion because 
	//	abs(INT_MIN) = INT_MIN, (INT_MIN = -2147483648);
    a = abs(a); 
    long long b = (long long)divisor;
    b = abs(b);

	// increase c to the first position such that b*2^c >= a
	// c must be int, not unsigned to avoid infinite loop
    int c = 0;
    while (b<<c < a) {
        c++;
    }
	// check every bit and add the return value
    int ret = 0;
    while (c>=0) {
        if (b<<c <=a) {
			// note 1<<c (i.e., 2^c), not b<<c
            ret += (1<<c);
            a -= b<<c;
        }
        c--;
    }
	// return value with correct symbol
    return (neg? -1*ret : ret);
}

// #29 Substring with concatenation of all words
// Solution: iterate on S; at each position, chop the next N substrings of length K, 
//				and check whether they match with strings in L
// It is easy to do it reversely, that is, records the indices of strings in L, and 
//	checks whether those indices satisfy the requirement. But then it becomes very 
//	tedious, especially for issues such as duplciate strings in L. 
// Complexity = O(M*N); Leetcode large set 1.6 secs
vector<int> findSubstring(string S, vector<string> &L) {
	// records the frequencies of words in L
	map<string, int> words; 
	// records the frequencies of words in the current round
	map<string, int> curWords; 
	int M = S.size(); 
	int N = L.size();
	int K = L[0].size(); 
	vector<int> ret; 
	// deal with empty set
	if (N == 0) return ret; 
	for (int i=0; i<N; ++i)
		++words[L.at(i)]; 
	// check at every position in the string S
	// note use <= only if N*K cannot be zero (we assume K=/=0)
	for (int i=0; i<=M-N*K; ++i) {
		int j; 
		// reset the current word set
		curWords.clear(); 
		// chop and check every substring
		// two breaks guarantee that finally two maps are exactly the same 
		for (j=0; j<N; ++j) {
			string str = S.substr(i+j*K, K); 
			if (words.find(str) == words.end())
				break; 
			++curWords[str]; 
			if (curWords[str] > words[str])
				break;
		}
		if (j == N) 
			ret.push_back(i);
	}
	return ret; 
}

// #30 Implement next permutation, which rearranges numbers into the 
//		lexicographically next greater permutation of numbers.*
// This solution search A backward for the last position i where 
//	the tailing substring after i is non-increasing. It then swap A[i] with 
//	the first position j in the tailing substring that is greater than A[i] (linear). 
//	Finally, it sort the tailing substrint.
// Note the boundy conditions. 

void nextPermutation(vector<int> &num) {
	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	int nSize = num.size(); 
	if (nSize<2) return; 
	int i = nSize-1; 
	while (i-1>=0 && num[i-1]>=num[i])
		--i; 
	if (i==0) {// A has no next permutation
		sort(num.begin(), num.end());
	} else {
		--i; // the last pos where the tailing substring afterward is non-increasing
		int j=i+1; 
		// find the first position j in the tailing substring that is greater than A[i]
		while (j<nSize && num[j]>num[i])
			++j;
		swap(num[i], num[j-1]); 
		sort(num.begin()+i+1, num.end());
	}
}

// #31 Longest valid pairs of parentheses *

// Solution 1, scan forward and backward
// Scan backward to avoid the case that the longest exists in the last block, 
//	which was not complete. e.g., ((), scanning only forward returns 0. 
// Note how the conditions are arranged so that all possibilites are included
int longestValidParentheses(string s) {
	int left = 0; 
	int curLen = 0; 
	int ret = 0; 
	for (size_t i=0; i<(int)s.size(); ++i) {
		if (s[i] == '(') {
			left++;
		} else {
			left--; 
			curLen += 2; 
		}
		// update ret at left = right, but not necessarily reset
		if (left == 0) {
			ret = (curLen>=ret ? curLen : ret); 
		}
		// This cannot be start of valid parentheses, reset 
		if (left < 0) {
			left = 0; 
			curLen = 0; 
		}
	}
	left = 0; 
	curLen = 0; 
	for (int i=s.size()-1; i>=0; --i) {
		if (s[i] == ')') {
			left++;
		} else {
			left--; 
			curLen += 2; 
		}
		// update ret at left = right, but not necessarily reset
		if (left == 0) {
			ret = (curLen>=ret ? curLen : ret); 
		}
		// This cannot be start of valid parentheses, reset 
		if (left < 0) {
			left = 0; 
			curLen = 0; 
		}
	}
	return ret; 
}
// a simple but non-trivial solution use stack (implemented with vector here)
// the stack stores the address/iterator rather than char
// the benefit is that it is very easy to compute the max length, because
//	(1) for case like ()() or )()(), it counts all () pairs
//	(2) it pushes all unmatched ) to the bottom of the stack, e.g., ))()))
int longestValidParentheses(string s) {
	int nMax = 0;
	vector<string::iterator> stk; 
	for (string::iterator it=s.begin(); it!=s.end(); ++it) {
		if (*it == '(')
			stk.push_back(it);
		else {
			if (!stk.empty() && *stk.back() == '(') {
				stk.erase(stk.end()-1); 
				nMax = max(it - (stk.empty()? (s.begin()-1):stk.back()), nMax); 
			} else {
				stk.push_back(it);
			}
		}
	}
	return nMax;
}

int main() {

}


