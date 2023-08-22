// Apriorit Poland Summer 2023 Internship Program
// Modern and Effective C++
// Szymon Siąkała

#include <iostream>
#include <functional>
#include <vector>
#include "Linked List.h"

class Test
{
private:
    int value = 0;
public:
    Test() = default;

	Test(int value) : value(value) {}

	int get_value() const
    {
        return value;
    }
};

void print_list(Linked_List<int>& list)
{
	for (int i = 0; i < list.size(); ++i)
	{
		std::cout << list[i]->data << " ";
	}
	std::cout << std::endl;
}

void print_list(Linked_List<Test>& test_list)
{
    for (int i = 0; i < test_list.size(); ++i)
    {
        std::cout << test_list[i]->data.get_value() << " ";
    }
    std::cout << std::endl;
}

int main()
{
    try
    {
        Linked_List<int> list = { 1, 42, 3, 7, 8, 59, 5 };
        std::cout << "List after creation:" << std::endl;
        print_list(list);

        std::cout << "Size of list: " << list.size() << std::endl;

        list.push_front(99);
        std::cout << "List after pushing front 99:" << std::endl;
        print_list(list);

        std::cout << "Element at index 0: " << list[0]->data << std::endl;

        list.remove(3);
        std::cout << "Size of list after removing element at index 3: " << list.size() << std::endl;

        std::cout << "Original list:" << std::endl;
        print_list(list);

        auto tail = list.split_when([](const int& value) { return value == 42; });

        std::cout << "Original list after split:" << std::endl;
        print_list(list);

        std::cout << "Tail list:" << std::endl;
        print_list(tail);

        list.assign({ 1, 2, 3, 4, 5 });
        std::cout << "List after assignment:" << std::endl;
        print_list(list);

        std::vector<int> values = { 6, 7, 8 };
        list.assign_range(values.begin(), values.end());

        std::cout << "List after range assignment:" << std::endl;
        print_list(list);

        std::cout << "List first element: " << list.begin()->data << std::endl;
        std::cout << "List last element: " << list.end()->data << std::endl;

        list.insert_after(list[1], 9);
        std::cout << "List after inserting 9 after 1st element:" << std::endl;
        print_list(list);

        values = { 1, 2, 3 };
        list.insert_range_after(list[1], values.begin(), values.end());
        std::cout << "List after inserting range after 1st element:" << std::endl;
        print_list(list);

        list.remove(list[1]);
        std::cout << "List after removing 1st element:" << std::endl;
        print_list(list);

        list.remove_after(list[3]);
        std::cout << "List after removing element after 3rd element:" << std::endl;
        print_list(list);

        list.pop_front();
        std::cout << "List after poping front:" << std::endl;
        print_list(list);

        values = { 9, 10, 3 };
        list.push_front_range(values.begin(), values.end());
        std::cout << "List after pushing range front:" << std::endl;
        print_list(list);

        list.reverse();
        std::cout << "List after reversing:" << std::endl;
        print_list(list);

        list.unique();
        std::cout << "List after making it unique:" << std::endl;
        print_list(list);

        list.clear();
        std::cout << "List size after clearing: " << list.size() << std::endl;

        Test test1(1);
        Test test2(2);
        Test test3(3);
        Linked_List <Test> test_list = { test1, test2 };
        test_list.push_front(test3);

        std::cout << "Test class object list:" << std::endl;
        print_list(test_list);
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    
    return 0;
}