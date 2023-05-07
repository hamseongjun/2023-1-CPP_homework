#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

//????? Bag ???©ª?
template <typename T>
class Bag {
public:
    Bag(int bagCapacity = 3);
    ~Bag();
    
    int Size() const;
    bool IsEmpty() const;
    T& Element() const;
    
    void Push(const T&);
    void Pop();

private:
    T *array;
    int capacity;
    int top;
};

//??????
template <typename T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity) {
    if (capacity < 1) throw "Capacity must be > 0";
    array = new T[capacity];
    top = -1;
}

//?????
template <typename T>
Bag<T>::~Bag(){ delete[] array; }

//?????? Size()
template <typename T>
int Bag<T>::Size() const { return top + 1; }

//?????? IsEmpty
template <typename T>
bool Bag<T>::IsEmpty() const { return Size() == 0; }

//???? ???? ???? Element
template <typename T>
T& Bag<T>::Element() const {
    if (IsEmpty()) throw "Bag is empty";
    srand(time(NULL));
    int randomIndex = rand() % (top + 1);
    return array[randomIndex];
}

//?ò÷?? ???? ??? Push
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

//???? ???? ???? Pop
template <typename T>
void Bag<T>::Pop() {
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    srand(time(NULL));
    int deletePos = rand() % (top + 1);
    copy(array + deletePos + 1, array + top + 1, array + deletePos);
    array[top--].~T();
}

//©¦???? ????? ????
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
    Character(const char * name, int myLevel, int myStr, int myDex, int myIntelligence, int myOp, int myDp, int myHP, int myMp)
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

//?????? ?????
class Warrior : public Character{
    private:
        char * weapon = NULL;

    public:
        Warrior(const char * name, const char * weapon) : Character(name, 1, 100, 50, 20, 5, 3, 80, 20) {
            const int lenWeapon = strlen(weapon) + 1;
            this->weapon = new char[lenWeapon];
            strcpy(this->weapon, weapon);
        }

        virtual void move() const {
        cout << "?????????." << endl;
        }

        virtual void showInfo() const {
            cout << "©¦???? ???: " << name << endl;
            cout << "???? ???: " << weapon << endl;
            cout << "????: " << level << endl;
            cout << "??: " << str << endl;
            cout << "??©ª: " << dex << endl;
            cout << "????: " << intelligence << endl;
            cout << "?????: " << op << endl;
            cout << "????: " << dp << endl;
            cout << "???: " << hp << endl;
            cout << "?????: " << mp << endl;
        }

        virtual void attack() const {
            cout << weapon << "??? ??????." << endl;
        }

        virtual ~Warrior() {
            delete weapon;
        }
};

//??? ?????
class Archer : public Character{
    private:
        char * weapon = NULL;

    public:
        Archer(const char * name, const char * weapon) : Character(name, 1, 50, 100, 20, 5, 3, 50, 50) {
            const int lenWeapon = strlen(weapon) + 1;
            this->weapon = new char[lenWeapon];
            strcpy(this->weapon, weapon);
        }

        virtual void move() const {
            cout << "?????????." << endl;
        }

        virtual void showInfo() const {
            cout << "©¦???? ???: " << name << endl;
            cout << "???? ???: " << weapon << endl;
            cout << "????: " << level << endl;
            cout << "??: " << str << endl;
            cout << "??©ª: " << dex << endl;
            cout << "????: " << intelligence << endl;
            cout << "?????: " << op << endl;
            cout << "????: " << dp << endl;
            cout << "???: " << hp << endl;
            cout << "?????: " << mp << endl;
        }

        virtual void attack() const {
            cout << weapon << "????? ???????." << endl;
        }

        virtual ~Archer() {
            delete weapon;
        }
};

//????? ?????
class Sorcerer : public Character{
    private:
        char * weapon = NULL;

    public:
        Sorcerer(const char * name, const char * weapon) : Character(name, 1, 20, 50, 100, 5, 3, 20, 80) {
            const int lenWeapon = strlen(weapon) + 1;
            this->weapon = new char[lenWeapon];
            strcpy(this->weapon, weapon);
        }

        virtual void move() const {
        cout << "?????????." << endl;
    }

        virtual void showInfo() const {
            cout << "©¦???? ???: " << name << endl;
            cout << "???? ???: " << weapon << endl;
            cout << "????: " << level << endl;
            cout << "??: " << str << endl;
            cout << "??©ª: " << dex << endl;
            cout << "????: " << intelligence << endl;
            cout << "?????: " << op << endl;
            cout << "????: " << dp << endl;
            cout << "???: " << hp << endl;
            cout << "?????: " << mp << endl;
        }

        virtual void attack() const {
            cout << weapon << "?????? ????????." << endl;
        }

        virtual ~Sorcerer() {
            delete weapon;
        }
};

int main(void)
{
    Bag<Character*>* bag = new Bag<Character*>();
    Character * element = NULL;

    cout << "**?? Bag ????**" << endl;
    cout << "Size: " << bag->Size() << endl;
    cout << "IsEmpty: " << bag->IsEmpty() << endl << endl;

    Warrior * leonard = new Warrior("????????", "?®š");
    Archer * weet = new Archer("???", "????");
    Sorcerer * ocon = new Sorcerer("????", "???");
    bag->Push(leonard);
    bag->Push(weet);
    bag->Push(ocon);

    cout << "**3?? Push() ????**" << endl;
    cout << "Size: " << bag->Size() << endl;
    cout << "IsEmpty: " << bag->IsEmpty() << endl << endl;
    element = bag->Element();
    element->showInfo();
    element->move();
    element->attack();

    Warrior * walter = new Warrior("????", "????");
    Warrior * wooganda = new Warrior("?©Ÿ??", "??????");
    Archer * legolas = new Archer("?????", "????");
    Archer * lucas = new Archer("?????", "??");
    Sorcerer * dexter = new Sorcerer("??????", "?????");
    Sorcerer * myrr = new Sorcerer("???", "?????");
    bag->Push(walter);
    bag->Push(wooganda);
    bag->Push(legolas);
    bag->Push(lucas);
    bag->Push(dexter);
    bag->Push(myrr);

    cout << endl << "**6?? Push() ????**" << endl;
    cout << "Size: " << bag->Size() << endl;
    cout << "IsEmpty: " << bag->IsEmpty() << endl << endl;
    element = bag->Element();
    element->showInfo();
    element->move();
    element->attack();

    bag->Pop();
    bag->Pop();
    
    cout << endl << "**2?? Pop() ????**" << endl;
    cout << "Size: " << bag->Size() << endl;
    cout << "IsEmpty: " << bag->IsEmpty() << endl << endl;
    element = bag->Element();
    element->showInfo();
    element->move();
    element->attack();

    return 0;
}
