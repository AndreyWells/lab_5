#ifndef PATTERNS_H_INCLUDED
#define PATTERNS_H_INCLUDED
const size_t MaxSize = 200;
// Абстрактный класс итератора
template<typename T>

class Iterator
{
public:
    virtual ~Iterator() {}
    virtual void FirstEl() = 0;
    virtual void NextEl() = 0;
    virtual bool IsDone() const = 0;
    virtual T GetCurrentElement() const = 0;

protected:
    Iterator() {}
};
// Абстрактный класс контейнера
template<typename T>

class Container
{
public:
    virtual ~Container() {}
    virtual bool IsEmpty() const = 0;
    virtual size_t GetSize() const =0;
    virtual Iterator<T> *GetIterator() = 0;
    virtual T GetElementByIndex(size_t index) const = 0;
    virtual T Pop() = 0;
    virtual void Push(T newObj) = 0;
};
// Итератор для стэка
template<typename T>

class StackIterator : public Iterator<T>
{
public:
    StackIterator(const T* con, size_t size): Pos(0), Size(size), StackCon(con) {}

    void FirstEl() override { Pos=0;}

    void NextEl() override { ++Pos;}

    bool IsDone() const override {return (Pos>=Size);}

    T GetCurrentElement() const override {return StackCon[Pos];}

private:
    size_t Pos;
    size_t Size;
    const T* StackCon;
};
// Шаблонный класс Стэк
template<typename T>

class StackClass : public Container<T>
{
public:
    StackClass(): EndElem(0) {}

    bool IsEmpty() const override {return (EndElem==0);}

    size_t GetSize() const override {return EndElem;}

    T GetElementByIndex(size_t index) const override{return Mass[index];}

    T Pop() override {return Mass[--EndElem];}

    void Push(T newObj) override {Mass[EndElem++]=newObj;}

    Iterator<T> *GetIterator() override {return new StackIterator<T>(Mass,EndElem);}
private:
    T Mass[MaxSize];
    size_t EndElem;
};

// Итератор для вектора

template <typename T>
class VectorIterator : public Iterator<T>
{
public:
    VectorIterator(T* con, size_t size):Pos(0),Size(size), VecCon(con) {}

    void FirstEl() override {Pos=0;}

    void NextEl() override {Pos++;}

    bool IsDone() const override {return (Pos>=Size);}

    T GetCurrentElement() const {return VecCon[Pos];}

private:
    size_t Pos;
    size_t Size;
    T* VecCon;
};

// Шаблонный класс Вектор

template<typename T>

class VectorClass : public Container<T>
{
public:
       VectorClass(): Data(0),Capacity(0),EndElem(0) {}

       ~VectorClass()
       {
           delete[] Data;
       }
    // Превращаем щаблонныцй класс Вектор в полноценный STL контейнер
    // Добавляем определение типа итераторов
        typedef const T* const_iter;
    // Добавляем определение методов для работы с конст. итератором
        const_iter begin() const {return Data;}

        const_iter end() const {return Data+EndElem;}

       bool IsEmpty() const override {return (EndElem==0);}

       size_t GetSize() const override {return EndElem;}

       T GetElementByIndex(size_t index) const override {return Data[index];}

       T Pop() override {return Data[--EndElem];}

       size_t GetCapacity() const {return Capacity;}
           // Изменение вместимости вектора
    void Reserve(size_t newCapacity) {
        if (newCapacity > Capacity) {
            // Выделяет память для нового массива с новой вместимостью
            T* newData = new T[newCapacity];
            // Копирует элементы из старого массива в новый
            for (size_t i = 0; i < EndElem; ++i)
            {
                newData[i] = Data[i];
            }
            delete[] Data;
            // Обновление указателя нового массива
            Data = newData;
            // Обновление значения вместимости
            Capacity = newCapacity;
        }
    }

   // Добавление элемента в конец вектора
    void Push(T newObj) override{
        if (EndElem >= Capacity) {
            // Увеличиваем вместимость, если необходимо
            size_t newCapacity = 0;
            // Если вектор пуст, то меняем значение на 1
            if (Capacity == 0)
            {
                newCapacity = 1;
            }
            else // Если не пуст, то удваиваем текущее значение
            {
                newCapacity = Capacity*2;
            }
            Reserve(newCapacity);
        }
        Data[EndElem++] = newObj;
    }
    Iterator<T>* GetIterator() override {return new VectorIterator<T>(Data,EndElem);}

private:
    T* Data;
    size_t Capacity;
    size_t EndElem;
};

// Декоратор для итератора
template<typename T>

class IteratorDecorator : public Iterator<T>
{
public:
    IteratorDecorator(Iterator<T>*it) : It(it) {}

    virtual ~IteratorDecorator() {delete It;}

    virtual void FirstEl()  {It->FirstEl();}

    virtual void NextEl()  {It->NextEl();}

    virtual bool IsDone() const  {return It->IsDone();}

    virtual T GetCurrentElement() const  {return It->GetCurrentElement();}

protected:
    Iterator<T> *It;
};

// Адаптер для контейнерных классов
template<typename ConType, typename DataType> // Принимает тип контейнера и тип данных элементов

class ConstIterAdapter: public Iterator<DataType>
{
public:
    ConstIterAdapter(ConType* con): Container(con)
    {
        It = Container->begin();
    }
    virtual ~ConstIterAdapter() {}

    virtual void FirstEl() {It = Container->begin();}

    virtual void NextEl() {It++;}

    virtual bool IsDone() const {return (It == Container->end());}

    virtual DataType GetCurrentElement() const {return *It;} // Разыменовываем итератор

protected:

    ConType *Container; // Указатель на контейнер по кот. проходит итератор
    typename ConType::const_iter It; // Константный итератор этого контейнера
};


#endif // PATTERNS_H_INCLUDED
