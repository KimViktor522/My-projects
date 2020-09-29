#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

//проверка на подходящее символы
bool check_char(char str, int num) {
	if (num == 3) {
		if (str != '(' && str != ')')
			if (str != '*' && str != 'v' && str != 'V')
				if (str != 'a' && str != 'b')
					return false;
	}
	else
		return true;
	if (num == 2) {
		if (str != '(' && str != ')')
			return false;
	}
	else
		return true;
	if (num == 1) {
		if (str != '*' && str != 'v' && str != 'V')
			return false;
	}
	else
		return true;
	if (num == 0) {
		if (str != ')')
			return false;
	}
	else
		return true;
	if (num == 9) {
		if (str != '(')
			return false;
	}
	else
		return true;
}

//рационализация языка
string rationalization_language(string languageStr) {
	int num_brac{};
	if (languageStr[0] == 'v' || languageStr[0] == 'V')
		return "0";
	for (int i{}; i < languageStr.length(); ++i) {//проверка корректного ввода 
		if (!check_char(languageStr[i], 3))
			return "0";
		if (i > 0 && (check_char(languageStr[i - 1], 1) == check_char(languageStr[i], 1))) {
			cout << "Not corret: * or v";
			return "0";
		}
		if (check_char(languageStr[i - 1], 9)) ++num_brac;
		if (check_char(languageStr[i - 1], 0)) --num_brac;
	}
	if (num_brac != 0) {
		cout << "Not corret: '(' or ')'";
		return "0";
	}
	cout << "Рационализированный язык: " << languageStr << endl;
	return languageStr;
}

template<typename T>
class Node {
public:
	T value{};
	int numIncoming{ 0 };
	int numOutcoming{ 0 };
	int intСomponent{ 0 };//к какой компаненте относится точка
	Node<T>* next_a;
	Node<T>* next_b;
};

template<typename T>
class Graph {
	int graphSize{ 0 };//длина
	Node<T>* first{ nullptr };
public:
	~Graph() {
		clear();
	}
	//поиск определенного числа 
	Node<T>* Search_elem(T data) {
		Node<T>* current{ first };
		if (current == nullptr) return nullptr;
		while (current != nullptr) {
			if (current->value == data) return current;
			current = current->next;
		}
		return nullptr;
	}
	//добавляет элемент в начало 
	Node<T>* push(T data) {
		if (Search_elem(data) != nullptr) return nullptr;
		if (first == nullptr) {
			Node<T>* current = new Node<T>;
			current->value = data;
			current->numIncoming = 0;
			current->numOutcoming = 0;
			current->next = nullptr;
			first = current;
			++graphSize;
			return current;
		}
		else {
			Node<T>* current = new Node<T>;
			current->value = data;
			current->numIncoming = 0;
			current->numOutcoming = 0;
			current->next = nullptr;
			Node<T>* currentOld{ first };
			while (currentOld->next != nullptr)	currentOld = currentOld->next;
			currentOld->next = current;
			++graphSize;
			return current;
		}
	}
	//поиск того элемента который еще не проверялся
	Node<T>* search_Free_Element() {
		Node<T>* current{ first };
		for (int i{ 0 }; i < graphSize; ++i) {
			if (current->intСomponent == 0) return current;
			else current = current->next;
		}
		return nullptr;
	}
	//количество элементов
	int look_graphSize() {
		return graphSize;
	}
	//полностью очищает графа
	void clear() {
		if (!graphSize) {
			first = nullptr;
			return;
		}
		Node<T>* current{ first };
		Node<T>* currentDel{ nullptr };
		while (current->next != nullptr) {
			currentDel = current->next;
			delete current;
			current = currentDel;
		}
		first = nullptr;
		graphSize = 0;
	}
	//выводит граф
	void print() {
		if (!graphSize) return;
		Node<T>* current{ first };
		while (current != nullptr) {
			cout << current->value << "  ";
			current = current->next;
		}
		cout << endl;
	}
};

int main() {
	system("chcp 65001"); system("cls");
	string languageStr;
	cout << "Введите язык: ";
	cin >> languageStr;
	languageStr = rationalization_language(languageStr);
	if (languageStr == "0") {
		cout << "NOT CORRECT INPUT!!!";
	}


	/*ifstream inputFail;	inputFail.open("input.txt");
	ofstream outputFail; outputFail.open("output.txt");
	if (!inputFail.is_open() || !outputFail.is_open()) {
		cerr << "Error opening file!" << endl;
	}
	else {
		Graph<int> graph;
		string str{}, tranferStrToInt{};
		int tops{}/*вершины*, ribs{}/*ребра*;
		bool check{};
		getline(inputFail, str);
		for (int i{}; i < (int)str.length(); ++i) {			//запись количества вершин графа и количества ребер
			if ((i == (int)str.length()) || (str[i] != ' ')) {
				tranferStrToInt.clear();
				while (str[i] != ' ' && i != str.length()) {
					tranferStrToInt += str[i];
					++i;
				}
				if (!check) tops = stoi(tranferStrToInt);
				else ribs = stoi(tranferStrToInt);
				check = true;
			}
		}
		for (int i{ 1 }; i <= tops; ++i) graph.push(i);		//добавление точек
		int num1{}, num2{};
		for (int p{ 0 }; p < ribs; ++p) {
			getline(inputFail, str);
			check = false;
			for (int i{}; i < (int)str.length(); ++i) {
				if ((i == (int)str.length()) || (str[i] != ' ')) {
					tranferStrToInt.clear();
					while ((i != (int)str.length()) && (str[i] != ' ')) {
						tranferStrToInt += str[i];
						++i;
					}
					if (!check) num1 = stoi(tranferStrToInt);
					else num2 = stoi(tranferStrToInt);
					check = true;
				}
			}
			graph.add_Child(num1, num2);//создает двойные связи (неориентированный граф)
			graph.add_Child(num2, num1);
		}
		graph.print();
		graph.search_For_Connectivity_Components_rec(graph.search_Free_Element());
		//вывод в файл
		outputFail << graph.look_Num_Connectivity_Components() << endl;
		for (int i{ 0 }; i < graph.look_graphSize(); ++i) outputFail << graph.num_Subgraph(i) << " ";
		//вывод в консоль
		cout << graph.look_Num_Connectivity_Components() << endl;
		for (int i{ 0 }; i < graph.look_graphSize(); ++i) cout << graph.num_Subgraph(i) << " ";
		cout << endl;

	}
	inputFail.close();
	outputFail.close();*/
	system("pause");
	return 0;
}