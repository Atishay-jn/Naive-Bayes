//░░░░░░░░░░▄
//░░░░░░░░▄▐░▄▄█████▄▄
//░░░░░░▄█████████████▄▀▄▄░▄▄▄
//░░░░░█████████████████▄██████
//░░░░████▐█████▌████████▌█████▌
//░░░████▌█████▌█░████████▐▀██▀
//░▄█████░█████▌░█░▀██████▌█▄▄▀▄
//░▌███▌█░▐███▌▌░░▄▄░▌█▌███▐███░▀
//▐░▐██░░▄▄▐▀█░░░▐▄█▀▌█▐███▐█
//░░███░▌▄█▌░░▀░░▀██░░▀██████▌
//░░░▀█▌▀██▀░▄░░░░░░░░░███▐███
//░░░░██▌░░░░░░░░░░░░░▐███████▌
//░░░░███░░░░░▀█▀░░░░░▐██▐███▀▌
//░░░░▌█▌█▄░░░░░░░░░▄▄████▀░▀
//░░░░░░█▀██▄▄▄░▄▄▀▀▒█▀█░▀
//░░░░░░░░░▀░▀█▀▌▒▒▒░▐▄▄
//░░░░░░░░▄▄▀▀▄░░░░░░▄▀░▀▀▄▄
//░░░░░░▄▀░▄▀▄░▌░░░▄▀░░░░░░▄▀▀▄
//░░░░░▐▒▄▀▄▀░▌▀▄▄▀░░░░░░▄▀▒▒▒▐
//░░░░▐▒▒▌▀▄░░░░░▌░░░░▄▄▀▒▐▒▒▒▒▌
//░░░▐▒▒▐░▌░▀▄░░▄▀▀▄▀▀▒▌▒▐▒▒▒▒▐▐
//░░░▌▄▀░░░▄▀░█▀▒▒▒▒▀▄▒▌▐▒▒▒▒▒▌▌
//░░▄▀▒▐░▄▀░░░▌▒▐▒▐▒▒▒▌▀▒▒▒▒▒▐▒▌
#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;

vector<bool> comp(vector<bool> v) {
	// 2's Complement
	// This function takes a boolean vector as input and does a bitwise not.
	// It then does logical addition of one in the array to achive 2's complement.
	// Return type: vector<bool>
	for(int i=0;i<v.size();i++)
		v[i] = !v[i];
	bool check = true;
	bool sum;
	int i = v.size()-1;
	while(check and i>=0) {
		sum = check ^ v[i];
		check = check & v[i];
		v[i] = sum;
		i--;
	}
	return v;
}

vector<bool> bin(long long n) {
	// Decimal to Binary conversion for positive numbers
	// This function takes a number in decimal notation as input. positive only.
	// It converts the input into its equivalent binary. 
	// Array reversal is done as numbers are pushed in opposite order from the formula being used.
	// Return type: vector<bool>
	vector<bool> temp;
	while(n>0) {
		if(n%2)
			temp.push_back(true);
		else
			temp.push_back(false);
		n /= 2;
	}
	vector<bool> ch;
	ch.push_back(false);
	for(int i=temp.size()-1;i>=0;i--)
		ch.push_back(temp[i]);
	return ch;
}

vector<bool> nbin(long long n) {
	// Decimal to Binary conversion for negative numbers
	// This function takes a negative decimal number as input and gives 2's complement as output.
	// The function itself just calls bin() and comp() to achieve this.
	// Return type: vector<bool>
	vector<bool> temp = bin(-n);
	temp = comp(temp);
	return temp;
}

vector<bool> cov_bin(long long n) {
	// Decimal to Binary conversion for all integers
	// This function is used to segregate between positive and negative numbers.
	// This helps us decide between binary and 2's complement representation.
	// Return type: vector<bool>
	if(n>0)
		return bin(n);
	else
		return nbin(n);
}

vector<bool> append(vector<bool> t, int k) {
	// Adds appropriate padding
	// This function is used to add appropriate padding at the start of the vector.
	// Positive numbers are padded with zero and negative numbers with 1.
	// Return type: vector<bool>
	std::vector<bool> v;
	for(int i=0;i<k-t.size();i++)
		v.push_back(t[0]);
	for(int i=0;i<t.size();i++)
		v.push_back(t[i]);
	return v;
}

long long num(vector<bool> v) {
	// Binary to Decimal conversion
	// This function is used to convert binary/2's complement representation back to decimal.
	// flag variable is used to remember if number is in binary or 2's complement.
	// 2's complement is taken if the number is in 2's complement to get the binary representation.
	// The corresponding decimal is multiplied by -1 if flag is true.
	// Return type: long long
	bool flag = v[0];
	if(v[0])
		v = comp(v);
	long long temp = 0;
	for(int i=0;i<v.size();i++) {
		temp*=2;
		if(v[i])
			temp++;
	}
	if(flag)
		return -temp;
	return temp;
}

vector<bool> add(vector<bool> a, vector<bool> b) {
	// Adding 2 numbers
	// This function takes 2 boolean vectors as inputs.
	// It first ensures that the size of the 2 vectors are the same. We assume no overflow.
	// Bitwise addition is then performed using the idea of a full-adder circuit.
	// Last overflow bit is ignored because the numbers are being represented in 2's complement.
	// Return type: vector<bool>
	vector<bool> answer;
	int k = a.size();
	if(k<b.size())
		k = b.size();
	b = append(b,k);
	a = append(a,k);
	for(int i=0;i<a.size();i++)
		answer.push_back(false);
	bool carry = false;
	bool sum;
	int i = b.size()-1;
	while(i>=0) {
		sum = carry ^ a[i] ^ b[i];
		if(sum)
			carry = carry & a[i] & b[i];
		else
			carry = carry | a[i] | b[i];
		answer[i] = sum;
		i--;
	}
	return answer;
}

vector<bool> shift_right(vector<bool> v, bool flag) {
	// Arithmetic shift right operation
	// This function takes a boolean vector and flag variable as input.
	// We then perform a shift right operation on the entire vector.
	// The first element is made equal to the flag variable.
	// Return type: vector<bool>
	for(int i=v.size()-1;i>0;i--)
		v[i] = v[i-1];
	v[0] = flag;
	return v;
}

void booth(vector<bool> a, vector<bool> q) {
	// Booth's algorithm for multiplication of 2 numbers
	// This function taken in 2 boolean vectors as inputs and applies Booth algorithm to multiply them.
	// An answer vector<bool> is created of appropriate size and initialized to 0.
	// Sequence counter is initialized.
	// In each interation a check is made followed by arithmetic shift right operation.
	// For the final output, Q is appended to answer and last bit of Q(n+1) is ignored.
	// Required output is displayed.
	// Return type: void
	vector<bool> answer;
	for(int i=0;i<a.size();i++)
		answer.push_back(false);
	int sequence_counter = q.size();
	q.push_back(false);
	while(sequence_counter>0) {
		if(q[q.size() - 2] == 0 and q[q.size() - 1] == 1) {
			answer = add(answer,a);
		}
		if(q[q.size() - 2] == 1 and q[q.size() - 1] == 0) {
			answer = add(answer,comp(a));
		}
		q = shift_right(q,answer[answer.size()-1]);
		answer = shift_right(answer,answer[0]);
		sequence_counter--;
	}
	for(int i=0;i<q.size()-1;i++)
		answer.push_back(q[i]);
	cout<<"Binary equivalent: ";
	for(bool x: answer)
		cout<<x;
	cout<<endl;
	cout<<"Answer: "<<num(answer)<<endl;
}

int main(){
	// Procedural code for basic I/O requirements of the program
	vector<bool> a,b;
	long long A, B;
	cin>>A>>B;
	a = cov_bin(A);
	b = cov_bin(B);
	if(a.size()>b.size())
		b = append(b,a.size());
	if(b.size()>a.size())
		a = append(a,b.size());
	booth(a,b);
	return 0;
}