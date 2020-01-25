#include "PolynomialList.h"
#include<string>
#include<sstream>
string* get_terms(string s);
PolynomialList::PolynomialList() { head = NULL; }
PolynomialList::PolynomialList(string str_poly){
	string *term;
	term = get_terms(str_poly);
	for (int i = 0; term[i] != "\0"; i++) {
		Node* n = creat_node(term[i]);
		head = add_node(n);
	}
	head = remove_zeros(head);
}
PolynomialList::~PolynomialList() {}
Node * PolynomialList::creat_node(string s){
	Node*n = new Node;
	if (s.find('x') == -1) {
		n->coef = stof(s);
		n->exp = 0;
		n->next = NULL;
	}
	else {
		if (s.find('x') == 0) n->coef = 1;
		else
			if (s.find('x') == 1 && (s[0] == '-')) {
				n->coef = (s[0] == '-') ? -1 : 1;
			}
			else n->coef = stof(s.substr(0, s.find('x')));
		s = s.substr(s.find('x') + 1);
		n->exp = (s[0] == '^') ? stoi(s.substr(1)) : 1;
		n->next = NULL;
	}
	return n;
}
Node * PolynomialList::add_node(Node * n){
	if (head == NULL) {
		head = n;
		return head;
	}
	Node* p1, *p2;
	if (head->exp < n->exp) {
		n->next = head;
		head = n;
		return head;
	}
	else if (n->exp == head->exp) {
		head->coef += n->coef;
		return head;
	}
	p1 = head;
	p2 = head->next;
	while (p2 != NULL) {
		if (n->exp > p2->exp) {
			n->next = p2;
			p1->next = n;
			return head;
		}
		else if (n->exp == p2->exp) {
			p2->coef += n->coef;
			return head;
		}
		p1 = p2;
		p2 = p2->next;
	}
	p1->next = n;
	return head;
}
void PolynomialList::delete_poly(Node * &h){
	Node* p;
	while (h != NULL) {
		p = h;
		h = h->next;
		delete p;
	}
}
Node * PolynomialList::remove_zeros(Node * head){
	Node* p1, *p2;
	while ((head != NULL) && (head->coef == 0)) {
		p1 = head;
		head = head->next;
		delete p1;
	}
	if (head == NULL) {    //if all coef. = 0 >>> create one zero node
		Node*n = new Node(0, 0, NULL);
		head = add_node(n);
		return head;
	}
	p1 = head;
	p2 = head;
	while (p2 != NULL) {
		if (p2->coef == 0) {
			p1->next = p2->next;
			delete p2;
			p2 = p1->next;
		}
		else {
			p1 = p2;
			p2 = p2->next;
		}
	}
	return head;
}
string* get_terms(string s){
	string tmp = s;
	string *test = new string[20];
	int term = 0;
	while (tmp != "\0"){
		if (tmp[0] == '-') {    //first coef is -ve
			test[term] += "-";
			tmp = tmp.substr(1);
		}
		if ((tmp.find('+') == -1) && (tmp.find('-') == -1)) {  //case:one term
			test[term] += tmp;
			tmp = "\0";
			term++;
		}
		else if (tmp.find('-') == -1) {  //case: all +ve terms
			test[term] += tmp.substr(0, tmp.find('+'));
			tmp = tmp.substr(tmp.find('+') + 1);
			term++;
		}
		else if (tmp.find('+') == -1) {  //case: all -ve terms
			test[term] += tmp.substr(0, tmp.find('-'));
			tmp = tmp.substr(tmp.find('-'));
			term++;
		}
		else if (tmp.find('+') < tmp.find('-')) {   //+ve & -ve >> +ve first
			test[term] += tmp.substr(0, tmp.find('+'));
			tmp = tmp.substr(tmp.find('+') + 1);
			term++;
		}
		else if (tmp.find('-') < tmp.find('+')) {    //+ve & -ve >> -ve first
			test[term] += tmp.substr(0, tmp.find('-'));
			tmp = tmp.substr(tmp.find('-'));
			term++;
		}
	}
	return test;
}
PolynomialList operator+(PolynomialList a, PolynomialList b){
	PolynomialList sum;
	Node*p1 = a.head;
	Node*p2 = b.head;
	Node*p3;
	if (a.head == NULL && b.head == NULL) return sum;
	while (p1 != NULL && p2 != NULL) {
		if (p1->exp > p2->exp) {
			sum.head = sum.add_node(p3 = new Node(p1->coef, p1->exp));
			p1 = p1->next;
		}
		else if (p2->exp > p1->exp) {
			sum.head = sum.add_node(p3 = new Node(p2->coef, p2->exp));
			p2 = p2->next;
		}
		else {
			sum.head = sum.add_node(p3 = new Node((p1->coef + p2->coef), p1->exp));
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	if (p1 == NULL)
		while (p2 != NULL) {
			sum.head = sum.add_node(p3 = new Node(p2->coef, p2->exp));
			p2 = p2->next;
		}
	if (p2 == NULL)
		while (p1 != NULL) {
			sum.head = sum.add_node(p3 = new Node(p1->coef, p1->exp));
			p1 = p1->next;
		}
	sum.head = sum.remove_zeros(sum.head);
	return sum;
}
PolynomialList operator-(PolynomialList a, PolynomialList b){ //a-b
	PolynomialList subt;
	Node*p1 = a.head;
	Node*p2 = b.head;
	Node*p3;
	if (a.head == NULL && b.head == NULL) return subt;
	while (p1 != NULL && p2 != NULL) {
		if (p1->exp > p2->exp) {
			subt.head = subt.add_node(p3 = new Node(p1->coef, p1->exp));
			p1 = p1->next;
		}
		else if (p2->exp > p1->exp) {
			subt.head = subt.add_node(p3 = new Node((p2->coef)*-1, p2->exp));
			p2 = p2->next;
		}
		else {
			subt.head = subt.add_node(p3 = new Node((p1->coef - p2->coef), p1->exp));
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	if (p1 == NULL)
		while (p2 != NULL) {
			subt.head = subt.add_node(p3 = new Node((p2->coef)*-1, p2->exp));
			p2 = p2->next;
		}
	if (p2 == NULL)
		while (p1 != NULL) {
			subt.head = subt.add_node(p3 = new Node(p1->coef, p1->exp));
			p1 = p1->next;
		}
	subt.head = subt.remove_zeros(subt.head);
	return subt;
}
PolynomialList operator*(PolynomialList a, PolynomialList b){
	PolynomialList product;
	Node*n = new Node(0);
	product.head = product.add_node(n);
	Node *p1, *p2;
	p1 = a.head;
	p2 = b.head;
	if (p1 == NULL || p2 == NULL) return product;
	while (p1 != NULL) {
		p2 = b.head;
		while (p2 != NULL) {
			Node*n = new Node((p1->coef*p2->coef), (p1->exp + p2->exp));
			product.head = product.add_node(n);
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	product.head = product.remove_zeros(product.head);
	return product;
}
ostream & operator<<(ostream & out, PolynomialList List){
	Node*p;
	p = List.head;
	if (p == NULL) {
		out << "There is no polynomial!!\n";
		return out;
	}
	int first_term = 1;
	while (p != NULL) {
		if (p->coef < 0)
			if (p->exp != 0) {
				if (p->exp == 1) { first_term = 0; (p->coef == -1) ? out << "-x" : out << p->coef << "x"; }
				else { first_term = 0; (p->coef == -1) ? out << "-x^" << p->exp : out << p->coef << "x^" << p->exp; }
			}
			else { first_term = 0; (p->coef == -1) ? out << "-1" : out << p->coef; }
		else
			if (p->coef == 0) {
				out << '0';
				return out;
			}
			else if (p->exp != 0) {
				if (p->exp == 1)
					if (p->coef == 1)
						if (first_term) { out << "x";   first_term = 0; }
						else out << "+x";
					else
						if (first_term) { out << p->coef << "x";   first_term = 0; }
						else out << "+" << p->coef << "x";
				else if (p->coef == 1)
					if (first_term) { out << "x^" << p->exp;   first_term = 0; }
					else out << "+x^" << p->exp;
				else
					if (first_term) { out << p->coef << "x^" << p->exp; first_term = 0; }
					else out << '+' << p->coef << "x^" << p->exp;
			}
			else {    (p->coef == 1) ? out << "+1" : out << '+' << p->coef;   }
		p = p->next;
	}
	return out;
}
istream & operator>>(istream & in, PolynomialList & b){
	string s;
	in >> s;
	string *term;
	b.delete_poly(b.head);
	if (b.head == NULL) {
		term = get_terms(s);
		for (int i = 0; term[i] != "\0"; i++) {
			Node* n = b.creat_node(term[i]);
			b.head = b.add_node(n);
		}
	}
	b.head = b.remove_zeros(b.head);
	return in;
}
