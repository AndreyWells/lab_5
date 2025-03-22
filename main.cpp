#include <iostream>
#include "Patterns.h"

//Создать фабричный метод для создания объектов вашего семейства.
//Создать два контейнера с различным устройством для хранения объектов вашего семейства. Внутри контейнеров могут быть: статический или динамический массив, вектор (vector) или список (list). В последнем случае произвольный доступ к элементам невозможен, обход реализуется при помощи итератора begin() - end(). Контейнеры должны иметь различный интерфейс.
//Создать итераторы для обхода созданных вами контейнеров.
//Наполнить контейнеры случайными объектами.
//Продемонстрировать взаимозаменяемость контейнеров с точки зрения их последовательного обхода при помощи итераторов (над каждым объектом надо выполнить одно и то же действие).
using namespace std;
class DistribKit {
    // Семейство LINUX
    string Family;

    // Год выпуска
    int Year;

    // Область применения
    string Appoinment;

    // Стабильная версия
    double StableVer;

protected:
    bool StatusIsActive;
public:
    DistribKit(string family, int year, string appoinment, double stablever): Family(family),Year(year), Appoinment(appoinment), StableVer(stablever), StatusIsActive(false)
    {
        cout << "Starting VBox..." <<endl;
    }
    virtual ~DistribKit()
    {
    cout << "Reboot system..." << endl;
    }
// Геттеры для атрибутов
    string GetFamily() const {return Family;}

    int GetYear() const {return Year;}

    string GetAppoinment() const {return Appoinment;}

    double GetStableVer() const {return StableVer;}

    virtual void LoginAsRoot() = 0;

    virtual void OpeningBash() = 0;

    virtual void ChangePassword() = 0;
};

class Centos : public DistribKit
{
public:
    Centos(string family, int year, string appoinment, double stablever): DistribKit(family, year, appoinment, stablever)
    {
    StatusIsActive = false;
    cout << "Logging in Centos..." << endl;
    }
    ~Centos()
    {
         cout << "Exit Centos..." << endl;
    }
    void LoginAsRoot() override
    {
    cout << "Write in tty3 \"su\"" << endl;
    cout << "Password: ???" << endl;
    cout << "Write in tty3 \"centos\"" << endl;
    cout << "You're logging as root!!" << endl;
    }
    void OpeningBash()
    {
     cout << "Ctrl + Alt + F3.." << endl;
     cout << "You are in tty3 " << endl;
    };
    void ChangePassword()
    {
    cout << "Push \"e\"" << endl;
    cout << "Find \"linuxefi\" string" << endl;
    cout << "Change argument \"ro\" to \"rw\"" << endl;
    cout << "Delete argument \"rhgb\""  << endl;
    cout << "Add \"rd.break enforcing=0\" at the end of the string"  << endl;
    cout << "Push \"Ctrl + x\""  << endl;
    cout << "Write \"chroot\" in tty3"  << endl;
    cout << "Write \"passwd root\" in tty3"  << endl;
    cout << "Type your new password"  << endl;
    cout << "Your password successfully changed!!"  << endl;
    };
};

/*void Centos::LoginAsRoot()
{
    cout << "Write in bash \"su\"" << endl;
    cout << "Password: ???" << endl;
    cout << "Write in bash \"centos\"" << endl;
    cout << "You're logging as root" << endl;
}

void Centos::OpeningBash()
{
    cout << "Push F2..." << endl;
}

void Centos::CheckShadow()
{
    cout << "Write  sudo cat /etc/shadow..." << endl;
}
*/
class Debian : public DistribKit
{
public:
    Debian(string family, int year, string appoinment, double stablever): DistribKit(family, year, appoinment, stablever)
    {
    StatusIsActive = true;
    cout << "Logging in Debian..." << endl;
    }
    ~Debian()
    {
         cout << "Exit Debian..." << endl;
    }
    void LoginAsRoot()
    {
    cout << "Write in bash \"su\"" << endl;
    cout << "Password: ???" << endl;
    cout << "Write in bash \"debian\"" << endl;
    cout << "You're logging as root!!" << endl;
    };
    void OpeningBash()
    {
     cout << "Push F2..." << endl;
    };
     void ChangePassword()
    {
    cout << "Push \"e\"" << endl;
    cout << "Find \"Linux\" string" << endl;
    cout << "Add \"init=/bin/bash\" at the end of the string" << endl;
    cout << "Push \"Ctrl + x\""  << endl;
    cout << "Write \"mount -o remount /\""  << endl;
    cout << "Write \"passwd\""  << endl;
    cout << "Type your new password"  << endl;
    cout << "Your password successfully changed!!"  << endl;
    };
};

class Kali : public DistribKit
{
public:
    Kali(string family, int year, string appoinment, double stablever): DistribKit(family, year, appoinment, stablever)
    {
    StatusIsActive = true;
    cout << "Logging in Kali..." << endl;
    }
    ~Kali()
    {
         cout << "Exit Kali..." << endl;
    }
    void LoginAsRoot()
    {
    cout << "Write in bash \"su\"" << endl;
    cout << "Password: ???" << endl;
    cout << "Write in bash \"kali\"" << endl;
    cout << "You're logging as root!!" << endl;
    };
    void OpeningBash()
    {
     cout << "Alt + F1..." << endl;
    };
     void ChangePassword()
    {
    cout << "Choose \"Advanced options for KALI GNU/Linux\" in the boot menu" << endl;
    cout << "Find \"Recovery mode\" point" << endl;
    cout << "Find \"linuxefi\" string" << endl;
    cout << "Change argument \"ro\" to \"rw\"" << endl;
    cout << "Add \"init=/bin/bash\" at the end of the string" << endl;
    cout << "Push \"F10\""  << endl;
    cout << "Write \"passwd\""  << endl;
    cout << "Type your new password"  << endl;
    cout << "Your password successfully changed!!"  << endl;
    };
};
// Реализация фабричного метода
enum class OsType: int // Перечисление с областью видимости, базового типа int
{
    Centos = 1,
    Debian = 2,
    Kali = 3,

    Undefined = 0 // Значение по умолчанию
};
// Фабричная функция
DistribKit* CreateOS(OsType type)
{
    DistribKit* newOS = nullptr; // Инициализируем указатель на абстрактный класс
    if (type == OsType::Centos)
    {
        newOS = new Centos("RHEL-based",2007, "Server",7.9);
    }
    else if (type == OsType::Debian)
    {
        newOS = new Debian("Debian-based",1993,"Everyday use",12.9);
    }
    else if (type == OsType::Kali)
    {
        newOS = new Kali("Debian-based",2013,"Security audit",2024.4);
    }
    return newOS; // Возвращаем указатель на созданный объект
}
// Функция, позволяющая "залогинить" любые ос из любого контейнера
void LoginEmAll(Iterator<DistribKit*> *it)
{
    // Цикл позволяет обойти все элементы контейнера
    // Устанавливаем итератор на первый элемент, пока итератор не дошел до конца контейнера, переводим его на след.элемент)
    for(it->FirstEl(); !it->IsDone(); it->NextEl())
    {   // Возвращаем текущий элемент контейнера
        DistribKit *currentOS = it->GetCurrentEl();
        // Текущим элементом контейнера вызываем функцию Login
        currentOS->LoginAsRoot();
    }
}
int main()
{
    setlocale(LC_ALL,"Russian");

    wcout << L"Какую операционную систему создать (1 - Centos, 2 - Debian, 3 - Kali)?" << endl;

    OsType type = OsType::Undefined; // Инициализация OsType

    int i;

    cin >> i;

    type = static_cast<OsType>(i); // Перевод числа к типу OsType

    // Создание ОС при помощи фабричного метода
    DistribKit *newOS = CreateOS(type);

    newOS->ChangePassword();

    delete newOS;

    // Использование контейнеров и итераторов для их обхода
    size_t N = 0;

    wcout << L"Введите количество OS: " << endl;

    cin >> N;

    StackClass<DistribKit*> OsStack;
    // Цикл для заполнения стека
    for(size_t i=0;i<N;i++)
    {   // Рандомное число от 1 до 3
        int os_num = rand()%3+1;
        // Перевод числа к типу OsType
        OsType os_type = static_cast<OsType>(os_num);
        // Создание ОС при помощи фабричного метода
        DistribKit *newOS = CreateOS(os_type);
        // Добавляем ОС в стек
        OsStack.Push(newOS);
    }
    wcout << L"Размер стека OS: " << OsStack.StackSize() << endl;

    Iterator<DistribKit*> *it2 = new IteratorForStack<DistribKit*>(&OsStack);
    LoginEmAll(it2);
    // Очищаем память
    delete it2;

    cout << endl;
    cout << endl;

     VectorClass<DistribKit*> OsVector;
     // Цикл для заполнения стека
    for(size_t i=0;i<N;i++)
    { // Рандомное число от 1 до 3
        int os_num = rand()%3+1;
        // Перевод числа к типу OsType
        OsType os_type = static_cast<OsType>(os_num);
        // Создание ОС при помощи фабричного метода
        DistribKit *newOS = CreateOS(os_type);
        // Добавляем ОС в вектор
        OsVector.PushBack(newOS);
    }
    wcout << L"Размер вектора OS: " << OsVector.VectorSize() << endl;

    Iterator<DistribKit*> *it3 = new IteratorForVector<DistribKit*>(&OsVector);

    LoginEmAll(it3);

    delete it3;

   /*  // Пример полиморфизма
    DistribKit* Debian12 = new Debian("Debian-based",1993,"Everyday use",12.9);
    cout << "Family: " << Debian12->GetFamily() << endl;
    cout << "Year of issue: " << Debian12->GetYear() << endl;
    cout << "Typically used for: " << Debian12->GetAppoinment()<< endl;
    cout << "The most stable version: " << Debian12->GetStableVer()<<endl;
    Debian12->ChangePassword();
    Debian12->OpeningBash();
    Debian12->LoginAsRoot();
    delete Debian12;

    cout << " " << endl;

    DistribKit* Centos7 = new Centos("RHEL-based",2007, "Server",7.9);
    cout << "Family: " << Centos7->GetFamily() << endl;
    cout << "Year of issue: " << Centos7->GetYear() << endl;
    cout << "Typically used for: " << Centos7->GetAppoinment()<< endl;
    cout << "The most stable version: " << Centos7->GetStableVer()<<endl;
    Centos7->ChangePassword();
    Centos7->OpeningBash();
    Centos7->LoginAsRoot();
    delete Centos7;


    cout << " " << endl;

    DistribKit* KaliLinux = new Kali("Debian-based",2013,"Security audit",2024.4);
    cout << "Family: " << KaliLinux->GetFamily() << endl;
    cout << "Year of issue: " << KaliLinux->GetYear() << endl;
    cout << "Typically used for: " << KaliLinux->GetAppoinment()<< endl;
    cout << "The most stable version: " << KaliLinux->GetStableVer()<<endl;
    KaliLinux->ChangePassword();
    KaliLinux->OpeningBash();
    KaliLinux->LoginAsRoot();
    delete KaliLinux;

*/
}
