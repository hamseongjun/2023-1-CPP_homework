#include <iostream>
#include <cstring>
using namespace std;

//Ŭ���� Bag ���ø�
template <class T>
class Bag {
public:
    Bag(int bagCapacity = 3);
    ~Bag();
    
    int Size() const;
    bool IsEmpty() const;
    T& Element() const;
    
    void Push(const T);
    void Pop();

private:
    T *array;
    int capacity;
    int top;
};

//������
template <class T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity) {
    if (capacity < 1) throw "Capacity must be > 0";
    array = new T*[capacity];
    top = -1;
}

//�Ҹ���
template <class T>
Bag<T>::~Bag()
{
    delete[] array;
}

//������ Size()
template <class T>
int Bag<T>::Size() const {
    return top + 1;
}

//�����? IsEmpty
template <class T>
bool Bag<T>::IsEmpty() const {
    return Size() == 0;
}

//���� ���� ���� Element
template <class T>
T& Bag<T>::Element() const {
    if (IsEmpty()) throw "Bag is empty";
    int randomIndex = rand() % (top + 1);
    return array[randomIndex];
}

//�迭�� ���� �ֱ� Push
template <class T>
void Bag<T>::Push(const T x) {
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
template <class T>
void Bag<T>::Pop() {
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    int deletePos = rand() % (top + 1);
    copy(array + deletePos + 1, array + top + 1, array + deletePos);
    array[top--].~T();
}


//ĳ���� Ŭ���� ����
class Character {
public:
    Character(const char* name, const int level, const int strength,const int agility, const int intelligence, const int attackPower, const int defensePower,const int health, const int spirit);
    virtual ~Character();
    void move() const;
    void showInfo() const;

protected:
    char* name;
    int level;
    int strength;
    int agility;
    int intelligence;
    int attackPower;
    int defensePower;
    int health;
    int spirit;
    char* weapon;
};

Character::Character(const char* namconst int lenName = strlen(name) + 1;
        this->name = new char[lenName];
        strcpy(this->name, name);e, const int level, const int strength,
const int agility, const int intelligence, const int attackPower, const int defensePower,
const int health, const int spirit) 
: level(level), strength(strength), agility(agility), intelligence(intelligence), 
    attackPower(attackPower), defensePower(defensePower), health(health), spirit(spirit) 
    { 
        
    }

Character::~Character() {
    delete name;
}

void Character::move() const {
    cout << "�̵��߽��ϴ�." << endl;
}

void Character::showInfo() const {
    cout << "ĳ���� �̸�: " << *name << endl;
    cout << "���� �̸�: " << *weapon << endl;
    cout << "����: " << level << endl;
    cout << "��: " << strength << endl;
    cout << "��ø: " << agility << endl;
    cout << "����: " << intelligence << endl;
    cout << "���ݷ�: " << attackPower << endl;
    cout << "����: " << defensePower << endl;
    cout << "ü��: " << health << endl;
    cout << "���ŷ�: " << spirit << endl;
}

//����
class Warrior : public Character {
private:
    char* weapon;

public:
    Warrior(const char * name, const char * weapon)
        : Character(name, 1, 100, 50, 20, 5, 3, 80, 20) {
            const int lenWeapon = strlen(weapon) + 1;
            this->weapon = new char[lenWeapon];
            strcpy(this->weapon, weapon);
        }

    virtual ~Warrior() {
        delete weapon;
    }

    virtual void attack() {
        cout << *weapon << "Į�� �񷶽��ϴ�." << endl;
    }
};

//�ü�
class Archer : public Character {
private:
    char * weapon;

public:
    Archer(const char * name, const char * weapon)
        : Character(name, 1, 50, 100, 20, 5, 3, 50, 50) {
            const int lenWeapon = strlen(weapon) + 1;
            this->weapon = new char[lenWeapon];
            strcpy(this->weapon, weapon);
    }

    ~Archer() {
        delete weapon;
    }

    virtual void attack() {
        cout << *weapon << "ȭ���� �����ϴ�." << endl;
    }
};

//������
class Sorcerer : public Character {
private:
    char* weapon;

public:
    Sorcerer(const char * name, const char * weapon)
        : Character(name, 1, 20, 50, 100, 5, 3, 20, 80) {
            const int lenWeapon = strlen(weapon) + 1;
            this->weapon = new char[lenWeapon];
            strcpy(this->weapon, weapon);
    }

    ~Sorcerer() {
        delete weapon;
    }

    virtual void attack() {
        cout << *weapon << "������ �ɾ����ϴ�." << endl;
    }
};

//main
int main(void)
{
    Bag<Character*> bag;
    bag.Size();
    bag.IsEmpty();
    //Push() 3�� ����
    Warrior * lowWarrior = new Warrior("�ϱ�����", "�콼 Į");
    Archer * lowArcher = new Archer("�ϱޱü�", "����ȭ��");
    Sorcerer * lowSorcerer = new Sorcerer("�ϱ޸�����", "�ߵ�");
    bag.Push(lowWarrior);
    bag.Push(lowArcher);
    bag.Push(lowSorcerer);
    bag.Size();
    bag.IsEmpty();
    Character* hero = bag.Element();

    hero->showInfo();
    hero->move();
    //hero.attack();
    //Push() 6�� ����
    Warrior * middleWarrior = new Warrior("�߱�����", "��ī�ο� Į");
    Warrior * highWarrior = new Warrior("�������", "������ Į");
    Archer * middleArcher = new Archer("�߱ޱü�", "������ ȭ��");
    Archer * highArcher = new Archer("��ޱü�", "������ ȭ��");
    Sorcerer * middleSorcerer = new Sorcerer("�߱޸�����", "ȭ��");
    Sorcerer * highSorcerer = new Sorcerer("��޸�����", "��������");
    bag.Push(middleWarrior);
    bag.Push(highWarrior);
    bag.Push(middleArcher);
    bag.Push(highArcher);
    bag.Push(middleSorcerer);
    bag.Push(highSorcerer);

    bag.Size();
    bag.IsEmpty();
    hero = bag.Element();
    
    hero->showInfo();
    hero->move();
    //hero.attack();
    //Pop() 2�� ����
    bag.Pop();
    bag.Pop();
    bag.Size();
    bag.IsEmpty();
    hero = bag.Element();
    
    hero->showInfo();
    hero->move();
    //hero.attack();
    return 0;
}