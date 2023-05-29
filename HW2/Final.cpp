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

//생성자
template <typename T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity) {
    if (capacity < 1) throw "Capacity must be > 0";
    array = new T[capacity];
    top = -1;
}

//소멸자
template <typename T>
Bag<T>::~Bag(){ delete[] array; }

//사이즈 Size()
template <typename T>
int Bag<T>::Size() const { return top + 1; }

//비었니? IsEmpty
template <typename T>
bool Bag<T>::IsEmpty() const { return Size() == 0; }

//랜덤 원소 리턴 Element
template <typename T>
T& Bag<T>::Element() const {
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
    array[top--].~T();
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

//워리어 클래스
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
            cout << weapon << "으로 찔렀습니다." << endl;
        }

        virtual ~Warrior() {
            delete weapon;
        }
};

//아처 클래스
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
            cout << weapon << "을 쐈습니다." << endl;
        }

        virtual ~Archer() {
            delete weapon;
        }
};

//소서러 클래스
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
            cout << weapon << " 마법을 사용했습니다." << endl;
        }

        virtual ~Sorcerer() {
            delete weapon;
        }
};

int main(void)
{
    Bag<Character*>* bag = new Bag<Character*>();
    Character * element = NULL;

    cout << "**빈 Bag 생성**" << endl;
    cout << "Size: " << bag->Size() << endl;
    cout << "IsEmpty: " << bag->IsEmpty() << endl << endl;

    Warrior * leonhart = new Warrior("레온하트", "용사의 전투검");
    Archer * silvia = new Archer("실비아", "신성한 화살");
    Sorcerer * alice = new Sorcerer("엘리스", "파이어볼");
    bag->Push(leonhart);
    bag->Push(silvia);
    bag->Push(alice);

    cout << "**3번 Push() 이후**" << endl;
    cout << "Size: " << bag->Size() << endl;
    cout << "IsEmpty: " << bag->IsEmpty() << endl << endl;
    element = bag->Element();
    element->showInfo();
    element->move();
    element->attack();

    Warrior * morpheus = new Warrior("모르페우스", "어둠의 심판검");
    Warrior * cassius = new Warrior("카시우스", "피로 물든 전투검");
    Archer * ariel = new Archer("아리엘", "번개 화살");
    Archer * daniel = new Archer("다니엘", "회오리 화살");
    Sorcerer * iris = new Sorcerer("아이리스", "라이트닝 볼트");
    Sorcerer * marie = new Sorcerer("마리", "아이스 애로우");
    bag->Push(morpheus);
    bag->Push(cassius);
    bag->Push(ariel);
    bag->Push(daniel);
    bag->Push(iris);
    bag->Push(marie);

    cout << endl << "**6번 Push() 이후**" << endl;
    cout << "Size: " << bag->Size() << endl;
    cout << "IsEmpty: " << bag->IsEmpty() << endl << endl;
    element = bag->Element();
    element->showInfo();
    element->move();
    element->attack();

    bag->Pop();
    bag->Pop();
    
    cout << endl << "**2번 Pop() 이후**" << endl;
    cout << "Size: " << bag->Size() << endl;
    cout << "IsEmpty: " << bag->IsEmpty() << endl << endl;
    element = bag->Element();
    element->showInfo();
    element->move();
    element->attack();

    return 0;
}
