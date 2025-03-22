#ifndef PATTERNS_H_INCLUDED
#define PATTERNS_H_INCLUDED
const size_t MaxSize = 200; // Определяем максимальный размер стека, делаем его беззнаковым

// Шаблонный класс "Стек"

template <typename T> // Класс будет работать с любым типом данных, в кач-ве параметра Т(int,doyble,string...)
class StackClass
{
T Mass[MaxSize]; // Массив, который хранит элементы стека

size_t ElBefEnd; // Cоздаем переменную, которая хранит индекс элемента, следующего за верхним элементом стека

public:
    // Конструктор, инициализируем переменную нулем
    StackClass(): ElBefEnd(0) {}

    // Проверка стека на пустоту
    bool IsEmpty() const {return (ElBefEnd == 0);}

    // Определение размера стека
    size_t StackSize() const {return ElBefEnd;}

    // Поместить в стек новый элемент
    void Push(T newObj) {Mass[ElBefEnd++] = newObj;} // Элемент помещается в массив на позицию ElBefEnd,присваивает значение, после чего ElBefEnd увеличивается на 1

    // Извлекает последний элемент из массива
    T Pop() {return Mass[--ElBefEnd];}

    // Возвращает элемент стека по указанному индексу
    T GetElByInd(size_t index) const {return Mass[index];}
};
// Абстрактный класс для итератора
template<typename T> // Класс будет работать с любым типом данных, в кач-ве параметра Т(int,doyble,string...)

class Iterator
{
protected:

    Iterator() {} // Объявили конструктор

public:

    virtual ~Iterator() {} // Объявили деструктор

    virtual void FirstEl() = 0; // Спозиционироваться на первый элемент контейнера

    virtual void NextEl() = 0;  // Перейти к следующему элементу контейнера

    virtual bool IsDone() const = 0;  // Проверить, достигнут ли конец

    virtual T GetCurrentEl() const = 0; // Получить текущий элемент контейнера
};

// Итератор для обхода стека
template<typename T> // Класс будет работать с любым типом данных, в кач-ве параметра Т(int,doyble,string...)

class IteratorForStack: public Iterator<T> // Наследование от абстрактного класса
{
    const StackClass<T> *StackCon; // Указатель на контейнер, по которому будет итерироваться итератор; итератор не изменяет контейнер
    size_t Pos; // Текущая позиция итератора
public:
    // Конструктор инициализирующий позицию и контейнер
     IteratorForStack(StackClass<T> *container): StackCon(container), Pos(0) {}

    void FirstEl() override { Pos = 0; } //Cпозиционироваться на первый элемент контейнера

    void NextEl() override { Pos++; }// Перейти к следующему элементу контейнера

    bool IsDone() const override { return (Pos >= StackCon->StackSize()); }// Проверить, достигнут ли конец

    T GetCurrentEl() const override { return StackCon->GetElByInd(Pos); }// Получить текущий элемент контейнера
};

// Шаблонный класс "vector"

template <typename T> // Класс будет работать с любым типом данных, в кач-ве параметра Т(int,doyble,string...)
class VectorClass
{
T* data; // Массив, который хранит элементы вектора

size_t capacity; // Вместимость вектора(макс. кол-во элементов, которое может хранить вектор без перераспред. памяти)

size_t VecSize; // Текущий размер вектора

public:
    // Конструктор, инициализируем переменные нулем
    VectorClass(): data(0),capacity(0),VecSize(0) {}

    // Деструктор
    ~VectorClass() {delete[] data;}

    // Проверка вектора на пустоту
    bool IsEmpty() const {return (VecSize == 0);}

    // Определение размера вектора
    size_t VectorSize() const {return VecSize;}

    // Определение вместимости вектора
    size_t VectorCapacity() const {return capacity;}

    // Удаление последнего элемента
    T PopBack() {return --VecSize;}

    // Доступ к элементу по индексу
    T operator[](size_t index) const {return data[index];}

        // Изменение вместимости вектора
    void Reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            // Выделяет память для нового массива с новой вместимостью
            T* newData = new T[newCapacity];
            // Копирует элементы из старого массива в новый
            for (size_t i = 0; i < VecSize; ++i)
            {
                newData[i] = data[i];
            }
            delete[] data;
            // Обновление указателя нового массива
            data = newData;
            // Обновление значения вместимости
            capacity = newCapacity;
        }
    }

   // Добавление элемента в конец вектора
    void PushBack(const T& value) {
        if (VecSize >= capacity) {
            // Увеличиваем вместимость, если необходимо
            size_t newCapacity = 0;
            // Если вектор пуст, то меняем значение на 1
            if (capacity == 0)
            {
                newCapacity = 1;
            }
            else // Если не пуст, то удваиваем текущее значение
            {
                newCapacity = capacity*2;
            }
            Reserve(newCapacity);
        }
        data[VecSize++] = value;
    }

    // Очистка вектора
    void Clear() {VecSize=0;}
};

// Итератор для вектора
template<typename T> // Класс будет работать с любым типом данных, в кач-ве параметра Т(int,doyble,string...)

class IteratorForVector: public Iterator<T> // Наследование от абстрактного класса
{
    const VectorClass<T> *VecCon; // Указатель на контейнер, по которому будет итерироваться итератор; итератор не изменяет контейнер
    size_t CurrPos; // Текущая позиция итератора
public:
    // Конструктор инициализирующий позицию и контейнер
     IteratorForVector(VectorClass<T> *vec): VecCon(vec), CurrPos(0) {}

    void FirstEl() override { CurrPos = 0; } //Cпозиционироваться на первый элемент контейнера

    void NextEl() override { CurrPos++; }// Перейти к следующему элементу контейнера

    bool IsDone() const override { return (CurrPos >= VecCon->VectorSize()); }// Проверить, достигнут ли конец

    T GetCurrentEl() const override { return (*VecCon)[CurrPos]; }// Получить текущий элемент контейнера
};


#endif // PATTERNS_H_INCLUDED
