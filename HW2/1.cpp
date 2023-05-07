#include <iostream>
#include <cstring>
using namespace std;

//클래스 Bag 템플릿
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

//생성자
template <class T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity) {
    if (capacity < 1) throw "Capacity must be > 0";
    array = new T*[capacity];
    top = -1;
}

//소멸자
template <class T>
Bag<T>::~Bag()
{
    delete[] array;
}

//사이즈 Size()
template <class T>
int Bag<T>::Size() const {
    return top + 1;
}

//비었니? IsEmpty
template <class T>
bool Bag<T>::IsEmpty() const {
    return Size() == 0;
}

//랜덤 원소 리턴 Element
template <class T>
T& Bag<T>::Element() const {
    if (IsEmpty()) throw "Bag is empty";
    int randomIndex = rand() % (top + 1);
    return array[randomIndex];
}

//배열에 원소 넣기 Push
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

//랜덤 원소 삭제 Pop
template <class T>
void Bag<T>::Pop() {
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    int deletePos = rand() % (top + 1);
    copy(array + deletePos + 1, array + top + 1, array + deletePos);
    array[top--].~T();
}


//캐릭터 클래스 정의
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
    cout << "이동했습니다." << endl;
}

void Character::showInfo() const {
    cout << "캐릭터 이름: " << *name << endl;
    cout << "무기 이름: " << *weapon << endl;
    cout << "레벨: " << level << endl;
    cout << "힘: " << strength << endl;
    cout << "민첩: " << agility << endl;
    cout << "지능: " << intelligence << endl;
    cout << "공격력: " << attackPower << endl;
    cout << "방어력: " << defensePower << endl;
    cout << "체력: " << health << endl;
    cout << "정신력: " << spirit << endl;
}

//전사
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
        cout << *weapon << "칼로 찔렀습니다." << endl;
    }
};

//궁수
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
        cout << *weapon << "화살을 쐈습니다." << endl;
    }
};

//마법사
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
        cout << *weapon << "마법을 걸었습니다." << endl;
    }
};

//main
int main(void)
{
    Bag<Character*> bag;
    bag.Size();
    bag.IsEmpty();
    //Push() 3번 수행
    Warrior * lowWarrior = new Warrior("하급전사", "녹슨 칼");
    Archer * lowArcher = new Archer("하급궁수", "나무화살");
    Sorcerer * lowSorcerer = new Sorcerer("하급마법사", "중독");
    bag.Push(lowWarrior);
    bag.Push(lowArcher);
    bag.Push(lowSorcerer);
    bag.Size();
    bag.IsEmpty();
    Character* hero = bag.Element();

    hero->showInfo();
    hero->move();
    //hero.attack();
    //Push() 6번 수행
    Warrior * middleWarrior = new Warrior("중급전사", "날카로운 칼");
    Warrior * highWarrior = new Warrior("상급전사", "전설의 칼");
    Archer * middleArcher = new Archer("중급궁수", "예리한 화살");
    Archer * highArcher = new Archer("상급궁수", "전설의 화살");
    Sorcerer * middleSorcerer = new Sorcerer("중급마법사", "화상");
    Sorcerer * highSorcerer = new Sorcerer("상급마법사", "정신지배");
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
    //Pop() 2번 수행
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