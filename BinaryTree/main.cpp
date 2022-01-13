#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#define tab "   "

class Tree
{
protected:
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
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;
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
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int i : il)insert(i, Root);
	}
	Tree(const Tree& other) : Tree()
	{
		cout << "T_Copy_Constructor:\t" << this << endl;
		*this = other;
	}
	Tree(Tree&& other)
	{
		this->Root = other.Root;
		cout << "T_Move_Constructor:\t" << this << endl;
		other.Root = nullptr;
	}
	~Tree()
	{
		clear(Root);
		cout << "T_Destructor:\t" << this << endl;
		cout << "\n----------------------------------\n";
	}

	Tree& operator=(const Tree& other)
	{
		if (this != &other)
		{
			this->clear();
			Element* Root = other.Root;
			Copy(Root);
		}
		cout << "T_Copy_Assignment:\t" << this << endl;
		return *this;
	}
	Tree& operator=(Tree&& other)
	{
		this->Root = other.Root;
		other.Root = nullptr;
		cout << "T_Move_Assignment:\t" << this << endl;
		return *this;
	}
	void Copy(Element* Root)
	{
		if (Root != nullptr)
		{
			this->insert(Root->Data);
			Copy(Root->pLeft);
			Copy(Root->pRight);
		}
	}

	

	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
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
	int depth()const
	{
		return depth(this->Root);
	}
	void print()const
	{
		print(this->Root);
		cout << endl;
	}
	void print(int depth)const
	{
		print(this->Root, depth);
		cout << endl;
	}
	void tree_print()
	{
		tree_print(0);
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
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf()) //Если элемент является листком, его можно удалять
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);//Заменяем значение удаляемого 
												   //элемента макс. значением в
												   //левой ветке
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
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
		//return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
		//return Root ? count(Root->pLeft) + count(Root->pRight) + 1 : 0;
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		return Root ? sum(Root->pLeft) + sum(Root->pRight) + Root->Data : 0;
	}
	double avg(Element* Root)const
	{
		return double(sum(Root)) / count(Root);
	}
	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			depth(Root->pLeft) + 1 : depth(Root->pRight) + 1;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	void print(Element* Root, int depth)const
	{
		if (Root == nullptr || depth == -1)return;
		if (depth == 1 && Root->pLeft == nullptr)cout << "  " << tab;
		print(Root->pLeft, depth - 1);
		cout << tab;

		if (depth == 0)cout << Root->Data /*<< tab*/;

		if (depth == 1 && Root->pRight == nullptr)cout << "  " << tab;
		print(Root->pRight, depth - 1);
		cout << tab;
	}



	void clear(Element*& Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}

	void tree_print(int depth)
	{
		if (depth==this->depth())return;
		for (int i = 0; i < (this->depth() - depth)*2; i++)cout << tab;
		print(depth);
		for (int i = 0; i < (this->depth() - depth)*2; i++)cout << tab;
		cout << endl;
		tree_print(depth + 1);
	}
};

class UniqueTree : public Tree
{
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
		else if(Data>Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK
//#define COPY_MOVE
void main()
{
	setlocale(LC_ALL, "Rus");

#ifdef BASE_CHECK
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


	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << u_tree.count() << endl;
	cout << "Сумма элементов в дереве: " << u_tree.sum() << endl;
	cout << "Среднее значение элементов в дереве: " << u_tree.avg() << endl;

	tree.clear();
	u_tree.clear();
	tree.print();
	u_tree.print();
#endif // BASE_CHECK

	Tree tree = { 50, 25, 75, 16, 32, 64, 80, 8, 18, 48, 77, 85 };
	tree.print();
	int value;
	/*cout << "Введите удаляемое значение: "; cin >> value;
	tree.erase(value);
	tree.print();
	tree.print();*/

#ifdef COPY_MOVE
	Tree tree1;
	for (int i = 0; i < 10; i++)
	{
		tree1.insert(rand() % 100);
	}
	tree1.print();
	Tree tree2 = tree1;
	tree2.print();
	Tree tree3;
	tree3 = tree2;
	tree3.print();
#endif // COPY_MOVE

	cout << "Глубина дерева: " << tree.depth() << endl;
	//tree.print(3);
	tree.tree_print();
}