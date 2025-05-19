#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <ctime>

const std::string NAME[] = {
    "Терри", "Джон", "Джордж", "Айзек", "Стивен",
    "Джоан", "Филип", "Роджер", "Нил", "Аркадий",
    "Борис", "Сергей", "Мария", "Анджей", "Олег"};

const std::string SURNAME[] = {
    "Пратчетт", "Толкин", "Мартин", "Азимов", "Кинг",
    "Роулинг", "Дик", "Желязны", "Гейман", "Стругацкий",
    "Акунин", "Лукьяненко", "Семёнова", "Сапковский", "Громов"};

const std::string GENRE[] = {
    "Фэнтези", "Научная фантастика", "Ужасы", "Детектив", "Киберпанк",
    "Пост-апокалипсис", "Мистика", "Стимпанк", "Историческое", "Попаданцы"};

const std::string BOOK_P1[] = {
    "Цвет", "Властелин", "Загадка", "Тайна", "Сон",
    "Знак", "Город", "Дом", "Код", "Путь",
    "Игра", "Сад", "Клич", "Герой", "Лист",
    "Остров", "Зов", "Дар", "Песнь", "Круг"};

const std::string BOOK_P2[] = {
    "Волшебства", "Колец", "Дыры", "Времени", "Дракона",
    "Четырех", "Теней", "Тьмы", "Дао", "Ветра",
    "Престолов", "Камней", "Тишины", "Вечности", "Звезд",
    "Памяти", "Крови", "Смерти", "Льда", "Пламени"};

int randGenerate(int end)
{
    return rand() % end;
}

std::string generateBook()
{
    float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    std::string outputString;
    if (x < .3)
    {
        outputString = BOOK_P1[randGenerate(sizeof(BOOK_P1) / sizeof(std::string))] + " и " + BOOK_P2[randGenerate(sizeof(BOOK_P2) / sizeof(std::string))];
    }
    else
    {
        outputString = BOOK_P1[randGenerate(sizeof(BOOK_P1) / sizeof(std::string))] + " " + BOOK_P2[randGenerate(sizeof(BOOK_P2) / sizeof(std::string))];
    }
    return outputString;
}

std::string generateAuthor()
{
    std::string outputString = NAME[randGenerate(sizeof(NAME) / sizeof(std::string))] + " " + SURNAME[randGenerate(sizeof(SURNAME) / sizeof(std::string))];

    return outputString;
}

std::string generateGenre()
{
    std::string outputString = GENRE[randGenerate(sizeof(GENRE) / sizeof(std::string))];

    return outputString;
}

class Book
{
public:
    std::string name;
    std::string author;
    std::string genre;
    int EPUB;
    int quantity;

    Book(std::string name, std::string author, std::string genre, int EPUB, int quantity)
    {
        this->name = name;
        this->author = author;
        this->genre = genre;
        this->EPUB = EPUB;
        this->quantity = quantity;
    };

    void print()
    {
        std::cout << "'" << name << "' (" << genre << "), автор: " << author
                  << ", в наличии: " << quantity << " шт." << ", EPUB: " << EPUB << "\n";
    };
};

class Library
{
private:
    std::vector<Book> books;

public:
    void add(Book book)
    {
        for (Book &el : books)
        {
            if (el.name == book.name && el.author == book.author)
            {
                el.quantity += book.quantity;
                return;
            }
        }
        this->books.push_back(book);
    }

    std::vector<Book> searchByTitle(std::string name)
    {
        std::vector<Book> result;
        for (auto el : books)
        {
            if (el.name.find(name) != std::string::npos)
            {
                result.push_back(el);
            }
        }
        return result;
    }

    std::vector<Book> searchByAuthor(std::string author)
    {
        std::vector<Book> result;
        for (auto el : books)
        {
            if (el.author.find(author) != std::string::npos)
            {
                result.push_back(el);
            }
        }
        return result;
    }

    bool takeBook(std::string name, std::string author, int num = 1)
    {
        for (auto &el : books)
        {
            if (el.name == name && el.author == author)
            {
                if (el.quantity >= num)
                {
                    el.quantity -= num;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        std::cout << "Книга не найдена!\n";
        return false;
    }

    void returnBook(std::string title, std::string author, int num = 1)
    {
        for (auto &el : books)
        {
            if (el.name == title && el.author == author)
            {
                el.quantity += num;
                return;
            }
        }
        books.push_back(Book(title, author, "Неизвестно", 0, num));
    }

    void showAll()
    {
        for (auto el : books)
        {
            el.print();
        }
    }
};

int main()
{
    srand(time(NULL));
    Library library;
    for (int i = 0; i < 15; i++)
    {
        library.add(Book(generateBook(), generateAuthor(), generateGenre(), randGenerate(1000000), randGenerate(20)));
    }

    library.add(Book("Гарри Потер и пересдачала Бавренова", "Джоан Роулинг", "Хоррор", randGenerate(1000000), randGenerate(20)));
    library.add(Book("Гарри Потер и тайная жанчика", "Джоан Роулинг", "Детектив", randGenerate(1000000), randGenerate(20)));

    std::cout << "Поиск по названию 'Гарри Потер':\n";
    std::vector<Book> books = library.searchByTitle("Гарри Потер");
    for (auto book : books) {
        book.print();
    }

    std::cout << "\nПоиск по автору 'Роулинг':\n";
    books = library.searchByAuthor("Роулинг");
    for (auto book : books) {
        book.print();
    }

    return 0;
}