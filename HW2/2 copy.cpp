#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

//Ŭ���� Bag ���ø�
template <typename T>
class Bag {
public:
    Bag(int bagCapacity = 3);
    ~Bag();
    
    int Size();
    bool IsEmpty();
    T Element();
    
    void Push(const T&);
    void Pop();

private:
    T array[3];
    int capacity;
    int top;
};

//������
template <typename T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity) {
    if (capacity < 1) throw "Capacity must be > 0";
    array = new T& [capacity];
    top = -1;
}

//�Ҹ���
template <typename T>
Bag<T>::~Bag(){
    delete[] array;
}

//������ Size()
template <typename T>
int Bag<T>::Size() {
    return top + 1;
}

//�����? IsEmpty
template <typename T>
bool Bag<T>::IsEmpty() {
    return Size() == 0;
}

//���� ���� ���� Element
template <typename T>
T Bag<T>::Element() {
    if (IsEmpty()) throw "Bag is empty";
    srand(time(NULL));
    int randomIndex = rand() % (top + 1);
    return array[randomIndex];
}

//�迭�� ���� �ֱ� Push
template <typename T>
void Bag<T>::Push(const T& x) {
    if (capacity == top + 1)
    {
        T* oldArray = array;
        capacity *= 2;
        array = new T[capacity];
        for (int i = 0; i <= top; i++)
            array[i] = oldArray[i];
        delete[] oldArray;
    }
    array[++top] = x;
}

//���� ���� ���� Pop
template <typename T>
void Bag<T>::Pop() {
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    srand(time(NULL));
    int deletePos = rand() % (top + 1);
    copy(array + deletePos + 1, array + top + 1, array + deletePos);
    top--;
}


//ĳ���� Ŭ���� ����
class Character{
protected:
    char * name = NULL;
    int level;
    int str;
    int dex;
    int intelligence;
    int op;
    int dp;
    int hp;
    int mp;

public:
    Character(char * name, int myLevel, int myStr, int myDex, int myIntelligence, int myOp, int myDp, int myHP, int myMp)
    : level(myLevel), str(myStr), dex(myDex), intelligence(myIntelligence), op(myOp), dp(myDp), hp(myHP), mp(myMp){
        const int lenName = strlen(name) + 1;
        this->name = new char[lenName];
        strcpy(this->name, name);
    }
    virtual void move() const { }
    virtual void showInfo() const { }
    virtual void attack() const { }
    virtual ~Character(){
        delete name;
    }
};

//������ Ŭ����
class Warrior : public Character{
    private:
        char * weapon;

    public:
        Warrior(char * name, char * weapon) : Character(name, 1, 100, 50, 20, 5, 3, 80, 20) {
            const int lenWeapon = strlen(weapon) + 1;
            this->weapon = new char[lenWeapon];
            strcpy(this->weapon, weapon);
        }

        virtual void move() const {
        cout << "�̵��߽��ϴ�." << endl;
        }

        virtual void showInfo() const {
            cout << "ĳ���� �̸�: " << name << endl;
            cout << "���� �̸�: " << weapon << endl;
            cout << "����: " << level << endl;
            cout << "��: " << str << endl;
            cout << "��ø: " << dex << endl;
            cout << "����: " << intelligence << endl;
            cout << "���ݷ�: " << op << endl;
            cout << "����: " << dp << endl;
            cout << "ü��: " << hp << endl;
            cout << "���ŷ�: " << mp << endl;
        }

        virtual void attack() const {
            cout << weapon << "Į�� �񷶽��ϴ�." << endl;
        }

        virtual ~Warrior() {
            delete weapon;
        }
};

//��ó Ŭ����
class Archer : public Character{
    private:
        char * weapon;

    public:
        Archer(char * name, char * weapon) : Character(name, 1, 50, 100, 20, 5, 3, 50, 50) {
            const int lenWeapon = strlen(weapon) + 1;
            this->weapon = new char[lenWeapon];
            strcpy(this->weapon, weapon);
        }

        virtual void move() const {
            cout << "�̵��߽��ϴ�." << endl;
        }

        virtual void showInfo() const {
            cout << "ĳ���� �̸�: " << name << endl;
            cout << "���� �̸�: " << weapon << endl;
            cout << "����: " << level << endl;
            cout << "��: " << str << endl;
            cout << "��ø: " << dex << endl;
            cout << "����: " << intelligence << endl;
            cout << "���ݷ�: " << op << endl;
            cout << "����: " << dp << endl;
            cout << "ü��: " << hp << endl;
            cout << "���ŷ�: " << mp << endl;
        }

        virtual void attack() const {
            cout << weapon << "ȭ��� �����ϴ�." << endl;
        }

        virtual ~Archer() {
            delete weapon;
        }
};

//�Ҽ��� Ŭ����
class Sorcerer : public Character{
    private:
        char * weapon;

    public:
        Sorcerer(char * name, char * weapon) : Character(name, 1, 20, 50, 100, 5, 3, 20, 80) {
            const int lenWeapon = strlen(weapon) + 1;
            this->weapon = new char[lenWeapon];
            strcpy(this->weapon, weapon);
        }

        virtual void move() const {
        cout << "�̵��߽��ϴ�." << endl;
    }

        virtual void showInfo() const {
            cout << "ĳ���� �̸�: " << name << endl;
            cout << "���� �̸�: " << weapon << endl;
            cout << "����: " << level << endl;
            cout << "��: " << str << endl;
            cout << "��ø: " << dex << endl;
            cout << "����: " << intelligence << endl;
            cout << "���ݷ�: " << op << endl;
            cout << "����: " << dp << endl;
            cout << "ü��: " << hp << endl;
            cout << "���ŷ�: " << mp << endl;
        }

        virtual void attack() const {
            cout << weapon << "������ �ɾ����ϴ�." << endl;
        }

        virtual ~Sorcerer() {
            delete weapon;
        }
};

int main(void)
{
    Bag<Character*> bag;

    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;

    Warrior * leonard = new Warrior("��������", "�츣");
    Archer * weet = new Archer("��Ʈ", "����");
    Sorcerer * ocon = new Sorcerer("����", "��Ŭ");
    bag.Push(leonard);
    bag.Push(weet);
    bag.Push(ocon);

    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;
    cout << "Element: " << bag.Element() << endl;

    Warrior * walter = new Warrior("����", "����");
    Warrior * wooganda = new Warrior("�찣��", "������");
    Archer * legolas = new Archer("�����", "����");
    Archer * lucas = new Archer("��ī��", "��");
    Sorcerer * dexter = new Sorcerer("������", "�����");
    Sorcerer * myrr = new Sorcerer("�̸�", "Ʈ����");
    bag.Push(walter);
    bag.Push(wooganda);
    bag.Push(legolas);
    bag.Push(lucas);
    bag.Push(dexter);
    bag.Push(myrr);

    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;
    cout << "Element: " << bag.Element() << endl;

    bag.Pop();
    bag.Pop();
    
    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;
    cout << "Element: " << bag.Element() << endl;

    /*
    const int a = 3;
    const int b = 4;
    const int c = 1;
    bag.Push(a);
    bag.Push(b);
    bag.Push(c);

    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;
    cout << "Element: " << bag.Element() << endl;

    const int d = 9;
    const int e = 15;
    const int f = 7;
    const int g = 5;
    const int h = 20;
    const int i = 30;
    bag.Push(d);
    bag.Push(e);
    bag.Push(f);
    bag.Push(g);
    bag.Push(h);
    bag.Push(i);

    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;
    cout << "Element: " << bag.Element() << endl;

    bag.Pop();
    bag.Pop();

    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;
    cout << "Element: " << bag.Element() << endl;
    */

    return 0;
}
