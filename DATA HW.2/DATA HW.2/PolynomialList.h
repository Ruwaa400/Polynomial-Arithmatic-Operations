#pragma once
#include<iostream>
#include<string>
using namespace std;
class Node {
public:
	double coef;
	int exp;
	Node *next;
	Node(double coefValue = 0.0, int expValue = 0, Node* nextNode = NULL) {
		coef = coefValue;
		exp = expValue;
		next = nextNode;
	}
};

class PolynomialList {
private:
	Node*head = NULL;
public:
	PolynomialList();
	PolynomialList(string str_poly);
	~PolynomialList();
	friend string* get_terms(string s);
	Node* creat_node(string);
	Node* add_node(Node* n);
	void delete_poly(Node*& h);
	Node* remove_zeros(Node *head);
	friend PolynomialList operator +(PolynomialList a, PolynomialList b);
	friend PolynomialList operator -(PolynomialList a, PolynomialList b);
	friend PolynomialList operator *(PolynomialList a, PolynomialList b);
	friend ostream& operator<<(ostream& out, PolynomialList b);
	friend istream& operator>>(istream& in, PolynomialList &b);
};