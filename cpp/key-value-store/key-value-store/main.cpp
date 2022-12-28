#include <thread>
#include <iostream>
#include "KeyValueStore.h"

using string = std::string;
using attributelist = std::vector<std::pair<std::string, AttributeValue>>;

void printEntry(KeyValueStore<string> &store, string key)
{
    try
    {
        string entry = store.get(key).toString();
        std::cout << key << ": { " << entry << " }" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void addEntry(KeyValueStore<string> &store, string key, attributelist list)
{
    try
    {
        store.put(key, list);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void removeEntry(KeyValueStore<string> &store, string key)
{
    try
    {
        store.remove(key);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void printStringVector(std::vector<string> &str_list)
{
    bool first = true;
    for (string s : str_list)
    {
        if (first)
        {
            std::cout << s;
            first = false;
        }
        else
        {
            std::cout << ", " << s;
        }
    }
}

void search(KeyValueStore<string> &store, string attr, AttributeValue attr_val)
{
    auto list = store.search(attr, attr_val);
    std::cout << "Keys with attr=" << attr << " and attr_val=" << attr_val.toString() << " : ";
    printStringVector(list);
    std::cout << std::endl;
}

void printKeys(KeyValueStore<string> &store)
{
    auto list = store.getKeys();
    std::cout << "Key list : ";
    printStringVector(list);
    std::cout << std::endl;
}

int main()
{
    KeyValueStore<string> key_val_store;

    std::thread t1([&key_val_store]()
                   {
        addEntry(key_val_store, "key1", {{"attr1", {"val1"}}, {"attr2", {4}}, {"attr3", {true}}, {"attr4", {0.6234}}});
        addEntry(key_val_store, "key2", {{"attr1", {"val2"}}, {"attr2", {6}}}); });

    std::thread t2([&key_val_store]()
                   {
        addEntry(key_val_store, "key2", {{"attr1", {4}}, {"attr2", {6}}, {"attr3", {false}}});
        addEntry(key_val_store, "key2", {{"attr1", {"val3"}}, {"attr2", {7}}, {"attr3", {false}}, {"attr4", {0.314}}});
        addEntry(key_val_store, "key3", {{"attr2", {10}}, {"attr3", {true}}, {"attr5", {"val5"}}}); });

    t1.join();
    t2.join();

    printEntry(key_val_store, "key1");
    printEntry(key_val_store, "key2");
    printEntry(key_val_store, "key3");

    printKeys(key_val_store);
    search(key_val_store, "attr3", {true});

    removeEntry(key_val_store, "key3");
    printEntry(key_val_store, "key3");

    printKeys(key_val_store);
    search(key_val_store, "attr3", {true});
}