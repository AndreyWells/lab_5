#include <iostream>
#include "Patterns.h"
#include <cstdlib>
#include <ctime>



using namespace std;

// Абстрактный класс для входа с устройства
class LoggingStrategy
{
public:
// Инкапсуляция enum class в абстрактный класс, для того, чтобы он работал только в унаследованных классах
    enum class DeviceEnum : int
    {
        Undefined,
        Laptop,
        Smartphone,
        TV,
        Tablet
        };
    virtual ~LoggingStrategy() {};
    virtual void Login() =0;
};

class LaptopLoggingStrategy : public LoggingStrategy
{
public:
    void Login() override {cout <<"Laptop booting with hard drive..." << endl;}

};

class SmartphoneLoggingStrategy : public LoggingStrategy
{
public:
    void Login() override {cout <<"Smartphone booting with memory disk..." << endl;}

};

class TvLoggingStrategy : public LoggingStrategy
{
public:
    void Login() override {cout <<"TV booting with CD disk..." << endl;}

};

class TabletLoggingStrategy : public LoggingStrategy
{
public:
    void Login() override {cout <<"Tablet booting with memory disk..." << endl;}

};
// Фабричная функция для способа входа
LoggingStrategy *CreateLoggingStrategy(LoggingStrategy::DeviceEnum device)
{
    LoggingStrategy * newDevice = nullptr;
    if (device == LoggingStrategy::DeviceEnum::Laptop)
    {
        newDevice = new LaptopLoggingStrategy();
    }
    else if (device == LoggingStrategy::DeviceEnum::Smartphone)
    {
        newDevice = new SmartphoneLoggingStrategy();
    }
    else if (device == LoggingStrategy::DeviceEnum::TV)
    {
        newDevice = new TvLoggingStrategy();
    }
    else if (device == LoggingStrategy::DeviceEnum::Tablet)
    {
        newDevice = new TabletLoggingStrategy();
    }
    return newDevice;

}


class DistribKit
{
    public:
        // Инкапсуляция enum class в абстрактный класс, для того, чтобы он работал только в унаследованных классах
        enum class Username : int
        {
            Root,
            DebianUser,
            KaliUser,
            CentosUser
        };

        enum class OsType : int
        {
            Undefined=0,
            Debian=1,
            Kali=2,
            Centos=3
        };

         // Конструктом с параметром
        DistribKit(Username user):StatusIsActive(static_cast<bool>(rand()%2)), StableVer(0.0), User(user),LoginMethod(nullptr) {}

        // Деструктор
        virtual ~DistribKit() {if(LoginMethod !=nullptr) delete LoginMethod;}

        // Геттеры
        virtual double GetStableVer() {return StableVer;}

        Username GetUser() {return User;}

        bool GetStatus() {return StatusIsActive;}

        void SetLoginMethod(LoggingStrategy *method) {LoginMethod = method;}

        void Connect()
        {
            // Вывод названия ОС
            PrintType();

            cout <<"| |";
            // Проверка статуса ОС
            StatusCheck();

            cout <<"| |";
            // Место входа в ОС
            EntryPoint();

            cout <<"| |";
            // Подключиться с устройства
            ConnectFromDevice();

            cout << endl;


        }
        protected:

            bool StatusIsActive;

        private:
            double StableVer;
            Username User;
            LoggingStrategy *LoginMethod;
            void ConnectFromDevice()
        {
            if(LoginMethod == nullptr)
            {
                cout << "Any device doesn't launched..." << endl;
                return;
            }
            else
            {
             LoginMethod->Login();
            }

        };

        void StatusCheck()
        {
            if (GetStatus())
            {
            cout << "Connecting to ACTIVE os" << endl;
            }
            else
            {
            cout <<"Connecting to UNACTIVE os" << endl;
            }
        };

        virtual void PrintType() = 0;

        virtual void EntryPoint() = 0;


};
class Debian : public DistribKit
{
public:
    Debian() : DistribKit(Username::DebianUser)
    {
            // Определим метод входа по умолчанию
    SetLoginMethod(CreateLoggingStrategy(LoggingStrategy::DeviceEnum::Laptop));
    }

    ~Debian() {}

    void PrintType() override {cout << "Debian" << endl;}

    void EntryPoint() override {cout << "Connection from home " << endl;}

    double GetStableVer() override {return StableVer;}

private:

    double StableVer = 12.4;
};

class Kali : public DistribKit
{
public:

    Kali() : DistribKit(Username::KaliUser)
    {
        // Определим метод входа по умолчани
        SetLoginMethod(CreateLoggingStrategy(LoggingStrategy::DeviceEnum::Smartphone));
    }

    ~Kali() {}

     void PrintType() override {cout << "Kali" << endl;}

    void EntryPoint() override {cout << "Connection from office " << endl;}

    double GetStableVer() override {return StableVer;}

private:

    double StableVer = 2023.3;
};
class Centos : public DistribKit
{
public:

    Centos() : DistribKit(Username::CentosUser)
     {
         // Определим метод входа по умолчани
         SetLoginMethod(CreateLoggingStrategy(LoggingStrategy::DeviceEnum::TV));
     }

    ~Centos() {}

     void PrintType() override {cout << "Centos" << endl;}

    void EntryPoint() override {cout << "Connection from country house " << endl;}

    double GetStableVer() override {return StableVer;}

private:

    double StableVer = 12.4;
};
// Фабричная функция
DistribKit * CreateOS(DistribKit::OsType type)
{
    DistribKit* newOS = nullptr;

    if (type == DistribKit::OsType::Centos)
    {
        newOS = new Centos();
    }
    else if (type == DistribKit::OsType::Debian)
    {
        newOS = new Debian();
    }
    else if (type == DistribKit::OsType::Kali)
    {
        newOS = new Kali();
    }
    return newOS;
}
    // Декоратор по username

    class UserDecorator : public IteratorDecorator<DistribKit*>
    {
    public:
        UserDecorator(Iterator<DistribKit*> *it, DistribKit::Username user): IteratorDecorator<DistribKit*>(it), TargetUser(user) {}

        void FirstEl() override
        {
            It->FirstEl();

            while (!It->IsDone() && It->GetCurrentElement()->GetUser() != TargetUser)
            {
                It->NextEl();
            }
        }
        void NextEl() override
        {
            do
            {
                It->NextEl();
            } while(!It->IsDone() && It->GetCurrentElement()->GetUser() != TargetUser);
        }
    private:

        DistribKit::Username TargetUser;
    };

    // Декоратор для активных ОС

    class ActiveOsDecorator : public IteratorDecorator<DistribKit*>
    {
    public:

        ActiveOsDecorator(Iterator<DistribKit*>* it,bool status ) : IteratorDecorator<DistribKit*>(it), TargetStatus(status) {}

        void FirstEl() override
        {
            It->FirstEl();

            while(!It->IsDone() && It->GetCurrentElement()->GetStatus() != TargetStatus)
            {
                It->NextEl();
            }
        }
        void NextEl() override
        {
            do {
                It->NextEl();
            } while(!It->IsDone() && It->GetCurrentElement()->GetStatus() != TargetStatus);
        }

     private:

        bool TargetStatus;
    };
    // Декоратор стабильной версии
class StableVerDecorator : public IteratorDecorator<DistribKit*>
{
private:

    double TargetStableVer; // Целевая версия, по которой фильтруются элементы

public:

    StableVerDecorator(Iterator<DistribKit*>*it, double ver) : IteratorDecorator<DistribKit*>(it), TargetStableVer(ver) {}

    void FirstEl() override
    {
        It->FirstEl();
        // Пропускаем элементы, пока не дойдем до конца или не найдем подходящий
        while(!It->IsDone() && It->GetCurrentElement()->GetStableVer() != TargetStableVer)
        {
            It->NextEl(); // Переход к следующему элементу
        };
    }
    void NextEl() override
    {
        do {
            It->NextEl(); // Переход к след. элементу
    // Пропускаем элементы, пока не дойдем до конца или не найдем подходящий
        } while (!It->IsDone() && It->GetCurrentElement()->GetStableVer() != TargetStableVer);
    }
};
void ConnectEmAll(Iterator<DistribKit*> *it)

{   // Выставляем итератор на 1 место, пока не дойдет до конца, переходим к след.элементу
    for(it->FirstEl(); !it->IsDone(); it->NextEl())
    {   // Передаем currentOS текущий элемент
        DistribKit* currentOS = it->GetCurrentElement();
        // Подключаем текущий элемент
        currentOS->Connect();
    }
}
main()
{
    // Случайный seed от времени
    srand(time(0));

    setlocale(LC_ALL,"Russian");

    size_t N = 0;

    wcout << L"Введите количество OS:" << endl;

    cin >> N;

    StackClass<DistribKit*> OsStack;
    // Заполняем стек
    for(size_t i=0;i<N;i++)
    {
        int os_num = rand()%3+1; // Рандомное число от 1 до 3
        // Явно приводим рандомное число к типу OsType
        DistribKit::OsType os_type = static_cast<DistribKit::OsType>(os_num);
        // Вызываем фабричную функцию для этого числа
        DistribKit *newOS = CreateOS(os_type);
        // Добавляем ОС в стэк
        OsStack.Push(newOS);
    }
    wcout << L"Размер стека OS:" << OsStack.GetSize() << endl;
    cout << endl;

    wcout << L"Подключиться только от лица DebianUser" << endl;
    // Создает декорированный итератор, который фильтрует только пользователей DebianUser
    Iterator<DistribKit*> *debIt = new UserDecorator(OsStack.GetIterator(),DistribKit::Username::DebianUser);
    // Вызывает функцию подключения для отфилтрованных пользователей
    ConnectEmAll(debIt);

    delete debIt;

    cout << endl;

    wcout << L"Подключиться только к активным ОС" << endl;

    Iterator<DistribKit*>* activIt = new ActiveOsDecorator(OsStack.GetIterator(),true);

    ConnectEmAll(activIt);

    delete activIt;

    cout<<endl;

    wcout << L"Подключиться только к ОС со стабильной версией 12.4" << endl;

    Iterator<DistribKit*>* stabIt = new StableVerDecorator(OsStack.GetIterator(),12.4);

    ConnectEmAll(stabIt);

    delete stabIt;

    // Связанный список ОС для адаптера
    VectorClass<DistribKit*> OsVector;

    for(size_t i=0;i<N;i++)
    {
        int os_num = rand()%3+1;

        DistribKit::OsType os_type = static_cast<DistribKit::OsType>(os_num);

        DistribKit* newOS = CreateOS(os_type);

        OsVector.Push(newOS);
    }

    // Демонстрация работы адаптера

    wcout << endl << L"Подключение ко всем активным ОС от лица DebianUser" << endl;

    // Сохраняем в указателе адптированный итератор, возвращающий указатели на абстрактный класс
    Iterator<DistribKit*> *adaptedIt = new ConstIterAdapter<VectorClass<DistribKit*>, DistribKit*>(&OsVector);

    Iterator<DistribKit*> *adaptedDebIt = new ActiveOsDecorator(new UserDecorator(adaptedIt, DistribKit::Username::DebianUser),true);

    ConnectEmAll(adaptedDebIt);

    delete adaptedDebIt;

}






