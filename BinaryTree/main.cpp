#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "E_Constructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "E_Destructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root; //Корень дерева
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "T_Construcotr:\t" << this << endl;
	}
	~Tree()
	{
		cout << "T_Destructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	int minValue()const
	{
		return minValue(this->Root);
	}
	int maxValue()const
	{
		return maxValue(this->Root);
	}
	int count()const
	{
		return count(this->Root);
	}
	int sum()const
	{
		return sum(this->Root);
	}
	double avg()const
	{
		return avg(this->Root);
	}
	void print()const
	{
		print(this->Root);
		cout << endl;
	}
	void clear()
	{
		clear(this->Root);
	}

private:
	void insert(int Data, Element* Root)
	{
		//Root - корень поддерева
		//this->Root - корень всего дерева
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);//Если есть место
			    //для добавления элемента, добавляем элемент прямо сюда.
			else insert(Data, Root->pLeft);// в противном же случае идем налево и ищем 
			    //место куда добавить добавить элемент. 
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	int minValue(Element* Root)const
	{
		if (Root->pLeft == nullptr)return Root->Data;
		return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		//if (Root->pRight == nullptr)return Root->Data;
		//return maxValue(Root->pRight);
		//return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		return count(Root->pLeft) + count(Root->pRight) + 1;*/
		return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		return Root ? sum(Root->pLeft) + sum(Root->pRight) + Root->Data : 0;
	}
	double avg(Element* Root)const
	{
		return double(sum(Root)) / count(Root);
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
};

void main()
{
	setlocale(LC_ALL, "Rus");
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << "Сумма элементов в дереве: " << tree.sum() << endl;
	cout << "Среднее значение элементов в дереве: " << tree.avg() << endl;
	tree.clear();
	tree.print();
}