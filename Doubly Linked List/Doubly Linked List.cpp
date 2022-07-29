#include <iostream>
#include <string>

using namespace std;


class Category {

	private:

		string groupName;
		string album;
		int yearOfIssue;
		string studioName;

	public:

		string get_groupName() {
			return this->groupName;
		}

		void set_groupName(string groupName) {
			this->groupName = groupName;
		}

		string get_album() {
			return this->album;
		}

		void set_album(string album) {
			this->album = album;
		}

		int get_yearOfIssue() {
			return this->yearOfIssue;
		}

		void set_yearOfIssue(int yearOfIssue) {
			this->yearOfIssue = yearOfIssue;
		}

		string get_studioName() {
			return this->studioName;
		}

		void set_studioName(string studioName) {
			this->studioName = studioName;
		}

		friend ostream& operator<<(ostream& out, const Category& category)
		{
			out << "Название группы:" + category.groupName << "\n" << "Название альбома:" + category.album <<  "\n"  << "Год выпуска:" << " " << category.yearOfIssue << "\n" << "Название студии:" + category.studioName << endl;
			return out;
		}

		friend istream& operator>>(istream& in, Category& category)
		{
			cout << "Введите группу:";
			in >> category.groupName;
			cout << "Введите название альбома:";
			in >> category.album;
			cout << "Введите год издания:";
			in >> category.yearOfIssue;
			cout << "Введите название студии:";
			in >> category.studioName;
			cout << endl;
			return in;
		}

};


struct Node {
	Category category;
	Node* Next, * Prev;
};


class List {
	Node* Head, * Tail;
	Node* Array;
	int p = 10;
	int counter = 0;

	public:

	List() :Head(NULL), Tail(NULL) {
		Array = new Node[p];
	};

	~List() {

		while (Head) {                       //Пока по адресу на начало списка что-то ест
			Tail = Head->Next;             //Резервная копия адреса следующего звена списка
			delete Head;                   //Очистка памяти от первого звена
			Head = Tail;					//Смена адреса начала на адрес следующего элемента
		}
	}

	void ShowAll() {
		//ВЫВОДИМ СПИСОК С КОНЦА
		//Node* temp = Tail;                   //Временный указатель на адрес последнего элемента

		//while (temp != NULL)               //Пока не встретится пустое значение
		//{
		//	cout << temp->category << " ";        //Выводить значение на экран
		//	temp = temp->Prev;             //Указываем, что нужен адрес предыдущего элемента
		//}
		//cout << "\n";

		//ВЫВОДИМ СПИСОК С НАЧАЛА
		cout << "\n";
		Node* temp = Head;
	                       //Временно указываем на адрес первого элемента
		while (temp != NULL)              //Пока не встретим пустое значение
		{
			cout << temp->category;//Выводим каждое считанное значение на экран
			cout << endl;
			temp = temp->Next;             //Смена адреса на адрес следующего элемента
		}
		cout << "\n";
	};

	void Add(Category category) {
		Node* temp = new Node;               //Выделение памяти под новый элемент структуры
		temp->Next = NULL;                   //Указываем, что изначально по следующему адресу пусто
		temp->category = category;                         //Записываем значение в структуру

		if (Head != NULL)                    //Если список не пуст
		{
			temp->Prev = Tail;               //Указываем адрес на предыдущий элемент в соотв. поле
			Tail->Next = temp;               //Указываем адрес следующего за хвостом элемента
			Tail = temp;                     //Меняем адрес хвоста
		}
		else								//Если список пустой
		{
			temp->Prev = NULL;               //Предыдущий элемент указывает в пустоту
			Head = Tail = temp;              //Голова = Хвост = тот элемент, что сейчас добавили
		}
	};

	List* DeleteFirst() {
		Node* temp;
		temp = Head;
		Head= Head->Next;
		Head->Prev = NULL;
		free(temp);   // освобождение памяти текущего корня
		return(this); // новый корень списка
	}

	List* DeleteLast() {
		Node* temp;
		temp = Tail;
		Tail = Tail->Prev;
		Tail->Next = NULL;
		free(temp);
		return (this);
	}

	List* InsertAt(Category category, int index) { //Вставить новый узел 
		Node* counter = new Node;
		Node* newNode = new Node;
		newNode->category = category;

		if (index == 1) {

			if (Head == NULL) {

				newNode->Next = NULL;
				newNode->Prev = NULL;                   
				Head = Tail = newNode;
			}
			else {

				Head->Prev = newNode;
				newNode->Next = Head;
				Head = newNode;
			}
		}
		
		else if (index == Count() + 1) {

			newNode->Next = NULL;
			newNode->Prev = Tail;
			Tail->Next = newNode;
			Tail = newNode;

		}
		else {

			counter = Head;
			int i = 0;
			Node* before = new Node;
			Node* after = new Node;
			while (counter != NULL) {

				if (i  == index - 1 ) {

					before = counter->Prev;
					after = counter->Next;
					newNode->Prev = counter->Prev;
					newNode->Next = counter;
					before->Next = newNode;
					counter->Prev = newNode;
					
					break;
				}
				i++;
				counter = counter->Next;
			}
		}

		return this;
	}

	int Count() {
		int i = 0;
		Node* counter = new Node;
		counter = Head;
		while (counter != NULL) {

			i++;
			counter = counter->Next;
		}
		return i;
	}

	List* Sort() {// Сортировка по году выпуска
		Node* left = Head;                 //Первый элемент — это пусть будет голова
		Node* right = Head->Next;          //Второй элемент — это пусть будет следующий за головой элемент

		Node* temp = new Node;              //Временное звено для хранения переставляемого всех значений переставляемого звена

		while (left->Next) {                 //Обходим по всем звеньям, за исключением крайнего правого
			while (right) {              //Обходим по всем звеньям, включая крайний правый (по всем относительно первого левого на текущий момент)
				if ((left->category.get_yearOfIssue()) < (right->category.get_yearOfIssue())) {        //Проверяем необходимость перестановки
					temp->category = left->category;              //И переставляем все внутренние элементы, за исключением указателей связи, местами
					left->category = right->category;             //Сейчас у нас имеется только x, поэтому только его
					right->category = temp->category;             //иначе бы  нужно было это проделывать для каждого несвязующего элемента
				}
				right = right->Next;                    //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
			}
			left = left->Next;                              //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
			right = left->Next;                             //Поскольку второй указатель убежал немного вперёд, обязательно возвращаем его назад, это следующий элемент относительно текущего первого
		}
		return this;
	}

	List* DeleteAll() {
		Node* tmp;

		tmp = Tail;
		while (tmp != NULL) {

			tmp = tmp->Prev;
		}
		free(tmp);
		Head = NULL;
		Tail = Head;

		return this;
	}

	void ShowByYear(int year) {
		Node* temp = Head;

		while (temp != NULL) {
			if (temp->category.get_yearOfIssue() == year) {
				cout << temp->category;        
				temp = temp->Next;
			}
		}
	}
};

	
class Handler {

	private:

		List* lst;

	public:

		Handler() {

			lst = new List();
			Menu();
		}

		void Menu() {

			int n;
			Category ctg;
			do{

				cout << "1. Добавить новую категорию" << endl;
				cout << "2. Добавить узел по номеру" << endl;
				cout << "3. Удалить последний узел" << endl;
				cout << "4. Удалить первый узел" << endl;
				cout << "5. Очистить весь список" << endl;
				cout << "6. Вывести весь список" << endl;
				cout << "7. Вывести данные по году" << endl;
				cout << "8. Сортировать список по году" << endl;
				cout << "9. Выход" << endl;
				cout << ">>";
				cin >> n;
				switch (n) {

				case 1:
					cin >> ctg;
					lst->Add(ctg);
					lst->ShowAll();
					break;
				case 2: {
					int k;
					cin >> ctg;
					cout << "Введите индекс:";
					cin >> k;
					lst = lst->InsertAt(ctg, k);
					lst->ShowAll();
				}
					break;
				case 3:
					lst = lst->DeleteLast();
					lst->ShowAll();
					break;
				case 4:
					lst = lst->DeleteFirst();
					lst->ShowAll();
					break;
				case 5:
					lst = lst->DeleteAll();
					lst->ShowAll();
					break;
				case 6:
					lst->ShowAll();
					break;
				case 7:
				{
					int k;
					cout << "Введите год:";
					cin >> k;
					lst->ShowByYear(k);
				}
					break;
				case 8:
					lst = lst->Sort();
					lst->ShowAll();
					break;
				}
			} while (n < 9);	
		}
};


int main() {

	setlocale(LC_ALL, "Russian");
	Handler* hnd = new Handler();

}
