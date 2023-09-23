// Arithmatic Expression Evaluator Project

// including the required libraries
#include<iostream>
#include<stack>
#include<algorithm>
#include<math.h>
using namespace std;


// function to give precedence of operators
int precedence(char c){
    if (c == '^'){
        return 3;
	}
    else if (c == '/' || c == '*'){
        return 2;
	}
    else if (c == '+' || c == '-'){
        return 1;
	}
    else{
        return -1;
	}
}

// Funtion to convert infix expression to postfix
string infixToPostfix(string s){
    stack<char> st;
    string result;
    for (int i = 0; i < s.length(); i++) { 
        char c = s[i]; 
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
            result += c;
    	}
        else if (c == '('){
            st.push('(');
        }
        else if (c == ')') { 
            while (st.top() != '(') { 
                result += st.top(); 
                st.pop(); 
            } 
            st.pop(); 
        } 
        else{ 
            while (!st.empty() && precedence(s[i]) <= precedence(st.top())) { 
                result += st.top();
                st.pop(); 
            }
            st.push(c);
        }
    }
    while (!st.empty()) { 
        result += st.top();
        st.pop();
    }
    return result;
}

// Funtion to evaluate postfix expression
float postfixEvaluation(string s){
	stack<float> st;
	
	for(int i = 0; i<s.length(); i++){
		if(s[i] >= '0' && s[i] <= '9'){
			st.push(s[i] - '0');
		}
		else{
			float op2 = st.top();
			st.pop();
			float op1 = st.top();
			st.pop();
			
			switch(s[i]){
				case '+':
					st.push(op1 + op2);
					break;
				case '-':
					st.push(op1 - op2);
					break;
				case '*':
					st.push(op1 * op2);
					break;
				case '/':
					st.push(op1 / op2);
					break;
				case '^':
					st.push(pow(op1, op2));
					break;
			}
		}
	}
	return st.top();
}

// Funtion for calculations
int operation(float val1, float val2, char opertr){
	if(opertr == '+'){
		return val1+val2;
	}
	else if(opertr == '-'){
		return val1-val2;
	}
	else if(opertr == '*'){
		return val1*val2;
	}
	else if(opertr == '/'){
		return val1/val2;
	}
	else{
		return pow(val1, val2);
	}
}


// Funtion to evaluate infix expression
// Here we are not making the new function
// this function will call the infixToPostfix() function and then postfixEvaluation()
// After that we will get the result
float evaluateInfix(string s){
	string postfix = infixToPostfix(s);
	return postfixEvaluation(postfix);
}

// Funtion to evaluate infix expression
// Bellow is the logic for exact infix evaluation
float infixEvaluation(string s){
	
	stack<float> stOpand;
	stack<char> stOprtr;
	
	for(int i = 0; i<s.length(); i++){
		char ch = s[i];
		
		if(ch == '('){
			stOprtr.push(ch);
		}
		else if(ch >= '0' && ch <= '9'){
			stOpand.push(ch - '0');
		}
		else if(ch == ')'){
			while(stOprtr.top() != '('){
				char optor = stOprtr.top();
				stOprtr.pop();
				
				float val2 = stOpand.top();
				stOpand.pop();
				float val1 = stOpand.top();
				stOpand.pop();
				
				float opv = operation(val1, val2, optor);
				stOpand.push(opv);
			}
			stOprtr.pop();
		}
		else if(ch == '+' || ch == '-' || ch == '*' || ch == '/'){
			while(stOprtr.size() > 0 && stOprtr.top() != '(' && precedence(ch) <= precedence(stOprtr.top())){
				char optor = stOprtr.top();
				
				float val2 = stOpand.top();
				stOpand.pop();
				float val1 = stOpand.top();
				stOpand.pop();
				
				float opv = operation(val1, val2, optor);
				stOpand.push(opv);
			}
			stOprtr.push(ch);
		}
	}
	while(stOprtr.size() != 0){
		char optor = stOprtr.top();
		stOprtr.pop();
		
		float val2 = stOpand.top();
		stOpand.pop();
		float val1 = stOpand.top();
		stOpand.pop();
		
		float opv = operation(val1, val2, optor);
		stOpand.push(opv);
	}
	return stOpand.top();
}

// Funtion to evaluate prefix expression
// this function is same as the postfixEvaluate function
// but here we are traversing the string in reverse order
float prefixEvaluation(string s){
	stack<float> st;
	for(int i = s.length()-1; i>=0; i--){
		if(s[i] >= '0' && s[i] <= '9'){
			st.push(s[i] - '0');
		}
		else{
			float op1 = st.top();
			st.pop();
			float op2 = st.top();
			st.pop();
			
			switch(s[i]){
				case '+':
					st.push(op1+op2);
					break;
				case '-':
					st.push(op1-op2);
					break;
				case '*':
					st.push(op1*op2);
					break;
				case '/':
					st.push(op1 / op2);
					break;
				case '^':
					st.push(pow(op1, op2));
					break;
			}
		}
		
	}
	return st.top();
}

// Funtion to convert infix expression to prefix expression
string infixToPrefix(string s){
	reverse(s.begin(), s.end());
	
	stack<char> st;
    string result;
    for (int i = 0; i < s.length(); i++) { 
        char c = s[i]; 
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
            result += c;
    	}
        else if (c == ')'){
            st.push(')');
        }
        else if (c == '(') {
            while (!st.empty() && st.top() != ')') { 
                result += st.top(); 
                st.pop();
            }
            if(!st.empty()){
            	st.pop(); 
            }
        } 
        else{ 
            while (!st.empty() && precedence(st.top()) >= precedence(c)) { 
                result += st.top();
                st.pop(); 
            }
            st.push(c); 
        }
    }
    while (!st.empty()) { 
        result += st.top(); 
        st.pop();
    }
    reverse(result.begin(), result.end());
    return result;
}

int main(){
	
	// infinite loop
	while(1){
		cout<<endl;
		for(int i = 0; i<170; i++){
			cout<<"*";
		}
		cout<<endl;
		cout<<"Choose from bellow : \n"<<endl;
		cout<<"1. Evaluate infix Expression \n\n2. Evaluate Postfix Expression \n"<<endl;
		cout<<"3. Evaluate prefix Expression\n"<<endl;
		cout<<"4. Convert Infix to Postfix \n\n5. Convert Infix to Prefix\n\n6. Calculate roots of quadratic equation.\n"<<endl;
		cout<<"7. Enter 0 to exit\n"<<endl;
		int choose;
		cin>>choose;
		string postfix, prefix;
		string infix;
		string str;
		float a,b,c,Discriminant,root1,root2,realPart,imaginaryPart, sqDet;
		
		// switch case for multiple cases
		switch(choose){
			
			// case of Evaluate infix Expression
			case 1:
				cout<<"Enter Infix expression : ";
				cin>>infix;
				cout<<"Here is the answer : "<<evaluateInfix(infix)<<endl;
				break;
				
			// case of Evaluate Postfix Expression
			case 2:
				cout<<"Enter Postfix expression : ";
				cin>>postfix;
				cout<<"Here is the answer : "<<postfixEvaluation(postfix)<<endl;
				break;
				
			// case of Evaluate prefix Expression
			case 3:
				cout<<"Enter prefix expression : ";
				cin>>prefix;
				cout<<"Here is the answer : "<<prefixEvaluation(prefix)<<endl;
				break;
				
			// case of Convert Infix to Postfix
			case 4:
				cout<<"Enter Infix expression : ";
				cin>>infix;
				cout<<"Here is the result form : "<<infixToPostfix(infix)<<endl;
				break;
				
			// case of Convert Infix to Prefix
			case 5:
				cout<<"Enter Infix expression : ";
				cin>>infix;
				cout<<"Here is the result form : "<<infixToPrefix(infix)<<endl;
				break;
				
			// case of Calculate roots of quadratic equation
			case 6:
				cout<<"Enter coefficients of quadratic equation one by one : ";
				cin>>a>>b>>c;
				Discriminant = (b*b)-(4*a*c);
				cout<<"Your Discriminant is : "<<Discriminant<<endl;
				if(Discriminant > 0){
					sqDet = sqrt(Discriminant);
					root1 = (-1*b + sqDet)/(2*a);
					root2 = (-1*b - sqDet)/(2*a);
					cout<<"root1 = "<<root1<<endl<<"root2 = "<<root2<<endl;
				}
				else if(Discriminant == 0){
					root1 = root2 = -1*b/2*a;
				}
				else{
					cout<<"The equation is having imaginary roots : "<<endl;
					realPart = -b/2*a;
					imaginaryPart = sqrt(-Discriminant)/2*a;
					cout<<"root1 = "<<realPart<<"+"<<imaginaryPart<<"i"<<endl<<"root2 = "<<realPart<<"-"<<imaginaryPart<<"i"<<endl;
				}
				break;
			case 7:
				return 0;
				
			// to break the loop
			default:
				cout<<"Enter valid number"<<endl;
		}
	}
}
