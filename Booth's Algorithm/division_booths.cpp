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

pair<vector<bool>,vector<bool> > shift_left(vector<bool> A,vector<bool> Q) {
	// Arithmetic shift left operation
	// This function takes a 2 boolean vectors as input.
	// We then perform a shift left operation on the two vector.
	// The last element of A is made equal to first element of Q
	// The last element of Q is made equal to 0.
	// Return type: pair<vector<bool>,vector<bool> >
	for(int i=0;i<A.size()-1;i++)
		A[i] = A[i+1];
    A[A.size()-1]=Q[0];
    for(int i=0;i<Q.size()-1;i++)
		Q[i] = Q[i+1];
    Q[Q.size()-1]=0;
	return make_pair(A,Q);
}

void booth_restore(vector<bool> divid, vector<bool> divis, bool flag1, bool flag2) {
	// Booth's algorithm for multiplication of 2 numbers
	// This function takes 4 parameters as input. 2 boolean vectors and 2 bool variables.
	// The 2 boolean vectors represent the divident and divisor respectively.
	// The 2 boolean variables are used to represent the sign of input.
	//
	//
	//
	//
	// Return type: void
	vector<bool> rem;
	for(int i=0;i<divid.size();i++)
		rem.push_back(false);
	int sequence_counter = divid.size();
	while(sequence_counter>0)
    {
        rem=shift_left(rem,divid).first;
        divid=shift_left(rem,divid).second;
        vector<bool> rem_old;
    	for(int i=0;i<rem.size();i++)
	    	rem_old.push_back(rem[i]);
        rem=add(rem,comp(divis));
        if(rem[0]==1)
        {
            divid[divid.size()-1]=0;
            for(int i=0;i<rem_old.size();i++)
	        	rem[i]=rem_old[i];
        }
        else
        {
            divid[divid.size()-1]=1;
        }
        
        sequence_counter-=1;
    }
	if(flag1 == false) {
		for(int i=0;i<rem.size();i++)
			if(rem[i]) {
				rem = comp(rem);
				rem = add(divis,rem);
    			vector<bool> temp;
				for(int i=0;i<2;i++)
					temp.push_back(false);
				temp.push_back(true);
				divid = add(divid,temp);
    			break;
    		}
    }
    if(flag1 ^ flag2)
    	divid = comp(divid);
	cout<<"Binary equivalent of quotient ";
	for(bool x: divid)
		cout<<x;
	cout<<endl;
	cout<<"Binary equivalent of remainder ";
	for(bool x: rem)
		cout<<x;
	cout<<endl;
	cout<<"quotient "<<num(divid)<<endl;
	cout<<"remainder "<<num(rem)<<endl;
}

int main(){
	// Procedural code for basic I/O requirements of the program
	vector<bool> a,b;
	long long A, B;
	cin>>A>>B;
	if(B==0)
	{
	    cout<<"Invalid operation";
	}
	else{
	    bool f1 = true, f2 = true;
	if(A<0) {
		A = -A;
		f1 = false;
	}
	if(B<0) {
		B = -B;
		f2 = false;
	}
	a = cov_bin(A);
	b = cov_bin(B);
	if(a.size()>b.size())
		b = append(b,a.size());
	if(b.size()>a.size())
		a = append(a,b.size());
	booth_restore(a,b,f1,f2);
	return 0;
	}
	
}
