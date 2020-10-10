//не работает дописывать не буду та еще х****
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

//проверка на подходящее символы
bool check_char(char str) {
	if (str != '(' && str != ')')
		if (str != '*' && str != 'v' && str != 'V')
			if (str != 'a' && str != 'b' && str != 'b')
				return false;
	
	return true;
}

//проверка на скобки
bool check_bracks_char(char str) {
	if (str != '(' && str != ')')
		return false;
	return true;
}

//проверка на "или" или "звездочка клини"
bool check_action_char(char str) {
	if (str != '*' && str != 'v' && str != 'V')
		return false;
	return true;
}

//добвать рацион. языка (сейчас только упрощение скобок)
//рационализация языка
string rationalization_language(string languageStr) {
	int num_brack{};
	bool even_brack_open{ false }, even_brack_close{ false }, union_in_brack {false};
	if (languageStr[0] == 'v' || languageStr[0] == 'V')
		return "0";
	for (int i{}; i < languageStr.length(); ++i) {																	//проверка корректного ввода 
		if (!check_char(languageStr[i]))
			return "0";
		if (languageStr[i] == '(') {
			++num_brack;
			if (even_brack_open) even_brack_open = false;
			else even_brack_open = true;
		}
		if (i + 1 < languageStr.length() && languageStr[i + 1] == ')') {
			--num_brack;
			if (even_brack_open) even_brack_open = false;
			else even_brack_open = true;
			if (languageStr[num_brack] == '(' && languageStr[languageStr.length() - 1] == ')') {					//сокращение скобок в начале и в конце "(*)"
				languageStr.erase(num_brack, 1);
				languageStr.erase(languageStr.length() - 1, 2);
				--i;
				--num_brack;
			}
			if (i + 2 < languageStr.length() && languageStr[i + 2] != '*') {//полсле скобки ")" не идет "*" 		//сокращение лишних скобок
				if (!union_in_brack) {//внутри скобок нет "v" или "V"									
					languageStr.erase(i+1, 1);
					for (int k{i}; k >= 0; --k) {
						if (languageStr[k] == '(') {
							languageStr.erase(k, 1);
							break;
						}
					}
					--i;
				}
			}
			union_in_brack = false;
		}
		if (languageStr[i] == 'v' || languageStr[i] == 'V') {//внутри скобок "v" или "V"
			union_in_brack = true;
		}
		if (i > 0 && (check_action_char(languageStr[i - 1]) == true && check_action_char(languageStr[i]) == true)) {//подряд "**" или "vv"
			cout << "Not corret: * or v" << endl;
			return "0";
		}
		if ((languageStr.length() < i + 2) && languageStr[i + 1] == '(' && languageStr[i + 2] == ')') {				//пустые скобки "()"
			languageStr.erase(i + 1, 2);
		}
	}
	if (num_brack != 0) {
		cout << "Not corret: '(' or ')'" << endl;
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
	cout << "Доступные символы: e a b ( ) v V *" << endl << "Введите язык: ";
	cin >> languageStr;
	languageStr = rationalization_language(languageStr);
	if (languageStr == "0") {
		cout << "NOT CORRECT INPUT!!!" << endl;
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