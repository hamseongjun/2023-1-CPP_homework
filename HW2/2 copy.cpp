#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

//클래스 Bag 템플릿
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

//생성자
template <typename T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity) {
    if (capacity < 1) throw "Capacity must be > 0";
    array = new T& [capacity];
    top = -1;
}

//소멸자
template <typename T>
Bag<T>::~Bag(){
    delete[] array;
}

//사이즈 Size()
template <typename T>
int Bag<T>::Size() {
    return top + 1;
}

//비었니? IsEmpty
template <typename T>
bool Bag<T>::IsEmpty() {
    return Size() == 0;
}

//랜덤 원소 리턴 Element
template <typename T>
T Bag<T>::Element() {
    if (IsEmpty()) throw "Bag is empty";
    srand(time(NULL));
    int randomIndex = rand() % (top + 1);
    return array[randomIndex];
}

//배열에 원소 넣기 Push
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

//랜덤 원소 삭제 Pop
template <typename T>
void Bag<T>::Pop() {
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    srand(time(NULL));
    int deletePos = rand() % (top + 1);
    copy(array + deletePos + 1, array + top + 1, array + deletePos);
    top--;
}


//캐릭터 클래스 정의
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

//워리어 클래스
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
        cout << "이동했습니다." << endl;
        }

        virtual void showInfo() const {
            cout << "캐릭터 이름: " << name << endl;
            cout << "무기 이름: " << weapon << endl;
            cout << "레벨: " << level << endl;
            cout << "힘: " << str << endl;
            cout << "민첩: " << dex << endl;
            cout << "지능: " << intelligence << endl;
            cout << "공격력: " << op << endl;
            cout << "방어력: " << dp << endl;
            cout << "체력: " << hp << endl;
            cout << "정신력: " << mp << endl;
        }

        virtual void attack() const {
            cout << weapon << "칼로 찔렀습니다." << endl;
        }

        virtual ~Warrior() {
            delete weapon;
        }
};

//아처 클래스
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
            cout << "이동했습니다." << endl;
        }

        virtual void showInfo() const {
            cout << "캐릭터 이름: " << name << endl;
            cout << "무기 이름: " << weapon << endl;
            cout << "레벨: " << level << endl;
            cout << "힘: " << str << endl;
            cout << "민첩: " << dex << endl;
            cout << "지능: " << intelligence << endl;
            cout << "공격력: " << op << endl;
            cout << "방어력: " << dp << endl;
            cout << "체력: " << hp << endl;
            cout << "정신력: " << mp << endl;
        }

        virtual void attack() const {
            cout << weapon << "화살로 쐈습니다." << endl;
        }

        virtual ~Archer() {
            delete weapon;
        }
};

//소서러 클래스
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
        cout << "이동했습니다." << endl;
    }

        virtual void showInfo() const {
            cout << "캐릭터 이름: " << name << endl;
            cout << "무기 이름: " << weapon << endl;
            cout << "레벨: " << level << endl;
            cout << "힘: " << str << endl;
            cout << "민첩: " << dex << endl;
            cout << "지능: " << intelligence << endl;
            cout << "공격력: " << op << endl;
            cout << "방어력: " << dp << endl;
            cout << "체력: " << hp << endl;
            cout << "정신력: " << mp << endl;
        }

        virtual void attack() const {
            cout << weapon << "마법을 걸었습니다." << endl;
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

    Warrior * leonard = new Warrior("레오나드", "우르");
    Archer * weet = new Archer("위트", "보우");
    Sorcerer * ocon = new Sorcerer("오콘", "써클");
    bag.Push(leonard);
    bag.Push(weet);
    bag.Push(ocon);

    cout << "Size: " << bag.Size() << endl;
    cout << "IsEmpty: " << bag.IsEmpty() << endl;
    cout << "Element: " << bag.Element() << endl;

    Warrior * walter = new Warrior("월터", "비브라늄");
    Warrior * wooganda = new Warrior("우간다", "셀리스");
    Archer * legolas = new Archer("레골라스", "위프");
    Archer * lucas = new Archer("루카스", "신");
    Sorcerer * dexter = new Sorcerer("덱스터", "아토믹");
    Sorcerer * myrr = new Sorcerer("미르", "트렌스");
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
