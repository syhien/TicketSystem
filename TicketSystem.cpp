//********************
//                   *
//   C++ 11 please   *
//                   *
//********************


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

class TicketSystem
{
public:
	struct return_order
	{
		string name;
		double price;
		int year;
		int month;
		int day;
	};

	TicketSystem()
	{
		l = new node;
		l->number = -1;
		l->name = "Admin";
		l->price = -0.01;
		l->date = { 0,0,0 };
		l->next = NULL;
		inventory = 101;
		income = 0;
		srand(time(NULL));
	}

	int SellTicket(string name, double price, int year, int month, int day)//if sell successfully, return the order's number. else, return -1
	{
		if (!inventory)
			return -1;
		node* p = l;
		while (p->next)
			p = p->next;
		p->next = new node;
		p = p->next;
		p->number = abs(rand());
		p->name = name;
		p->price = price;
		p->date = { year,month,day };
		p->next = NULL;
		income += price;
		inventory--;
		return p->number;
	}

	bool GetRefund(int number)//return whether refund successfully
	{
		node* p = l;
		while (p->next and p->next->number != number)
			p = p->next;
		if (p->next == NULL)
			return 0;
		node* tmp = p->next->next;
		income -= p->next->price;
		delete p->next;
		p->next = tmp;
		inventory++;
		return 1;
	}

	void Sort()//Ascending order
	{
		for (node* i = l; i; i = i->next)
		{
			node* j = i;
			node* tmp = j;
			for (node* k = j->next; k; k = k->next)
				if (k->price < tmp->price)
					tmp = k;
			if (tmp == j)
				continue;
			swap(j->number, tmp->number);
			swap(j->name, tmp->name);
			swap(j->price, tmp->price);
			swap(j->date, tmp->date);
		}
	}

	bool FindCustomer(string name, vector<int>& result)
	{
		for (node* p = l->next; p; p = p->next)
			if (p->name == name)
				result.push_back(p->number);
		return !result.empty();
	}

	bool QueryOrder(int number, return_order& result)
	{
		for (node* p = l; p; p = p->next)
			if (p->number == number)
			{
				result = { p->name,p->price,p->date.year,p->date.month,p->date.day };
				return 1;
			}
		return 0;
	}

	int QueryInventory()
	{
		return inventory;
	}

	int QueryIncome()
	{
		return income;
	}
private:
	struct date
	{
		int year;
		int month;
		int day;
	};
	struct node
	{
		int number;
		string name;
		double price;
		struct date date;
		node* next;
	};
	node* l;
	int inventory;
	double income;
};

int main()
{	
	//example
	TicketSystem China_Eastern;
	cout << "Income:" << China_Eastern.QueryIncome() << endl;
	cout << "Inventory:" << China_Eastern.QueryInventory() << endl;

	if (!China_Eastern.SellTicket("Mamehara Issei", rand() + 0.11, 2020, 5, 30))
		cout << "ERROR" << endl;
	cout << "Income:" << China_Eastern.QueryIncome() << endl;
	cout << "Inventory:" << China_Eastern.QueryInventory() << endl;

	if (!China_Eastern.SellTicket("Hatsune Miku", rand() + 0.39, 2020, 8, 31))
		cout << "ERROR" << endl;
	cout << "Income:" << China_Eastern.QueryIncome() << endl;
	cout << "Inventory:" << China_Eastern.QueryInventory() << endl;

	if (!China_Eastern.SellTicket("Produce 101", rand() + 0.11, 2020, 5, 28))
		cout << "ERROR" << endl;
	cout << "Income:" << China_Eastern.QueryIncome() << endl;
	cout << "Inventory:" << China_Eastern.QueryInventory() << endl;

	if (!China_Eastern.SellTicket("Hatsune Miku", rand() + 0.39, 2020, 8, 31))
		cout << "ERROR" << endl;
	cout << "Income:" << China_Eastern.QueryIncome() << endl;
	cout << "Inventory:" << China_Eastern.QueryInventory() << endl;

	China_Eastern.Sort();

	vector<int> mikuorder;
	if (!China_Eastern.FindCustomer("Hatsune Miku", mikuorder))
		cout << "ERROR" << endl;
	for (auto i : mikuorder)
	{
		cout << i << " ";
		TicketSystem::return_order tmp;
		if (!China_Eastern.QueryOrder(i, tmp))
			cout << "ERROR" << endl;
		else
			cout << tmp.price << " " << tmp.name << " " << tmp.year << tmp.month << tmp.day << endl;
		China_Eastern.GetRefund(i);
		cout << "Income:" << China_Eastern.QueryIncome() << endl;
		cout << "Inventory:" << China_Eastern.QueryInventory() << endl;
	}

	return 0;
}