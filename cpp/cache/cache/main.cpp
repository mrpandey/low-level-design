#include <thread>
#include <iostream>
#include <vector>
#include "KeyValueStoreFactory.h"

using string = std::string;

void addKey(KeyValueStore<string, string> &store, string key, string val)
{
    try
    {
        store.put(key, val);
    }
    catch (std::exception &e)
    {
        std::cout << "Error while adding key=" << key << ": " << e.what() << std::endl;
    }
}

void removeKey(KeyValueStore<string, string> &store, string key)
{
    try
    {
        store.remove(key);
    }
    catch (std::exception &e)
    {
        std::cout << "Error while removing key=" << key << ": " << e.what() << std::endl;
    }
}

void printKeyValues(KeyValueStore<string, string> &store, std::vector<string> keys)
{
    for (string k : keys)
    {
        try
        {
            string val = store.get(k);
            std::cout << k << ": " << val << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << "Error while printing key " << k << ": " << e.what() << std::endl;
        }
    }
}

int main()
{
    KeyValueStoreFactory<string, string> key_value_factory;
    
    auto lru_store = key_value_factory.getDefaultStore(3);

    std::thread t1([&lru_store](){
        addKey(lru_store, "key1", "val1");
        addKey(lru_store, "key2", "val2");
        addKey(lru_store, "key3", "val3");
    });

    std::thread t2([&lru_store](){
        addKey(lru_store, "key2", "val22");
        addKey(lru_store, "key3", "val33");
        removeKey(lru_store, "key1");
    });

    t1.join();
    t2.join();

    printKeyValues(lru_store, {"key1", "key2", "key3"});

    addKey(lru_store, "key4", "val4");
    addKey(lru_store, "key5", "val5");  // this should evict key2 from policy and store 

    printKeyValues(lru_store, {"key2", "key3", "key4", "key5"});


    auto lfu_store = key_value_factory.getLFUStore(2);

    addKey(lfu_store, "lk1", "lval1");
    addKey(lfu_store, "lk2", "lval2");

    addKey(lfu_store, "lk2", "lval3");
    addKey(lfu_store, "lk1", "lval4");

    addKey(lfu_store, "lk3", "lval5");  // lk2 should be evicted
    printKeyValues(lfu_store, {"lk1", "lk2"});
}