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
            std::cout << k << ": " << store.get(k) << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

int main()
{
    KeyValueStoreFactory<string, string> key_value_factory;
    auto key_val_store = key_value_factory.getDefaultStore(3);

    std::thread t1([&key_val_store](){
        addKey(key_val_store, "key1", "val1");
        addKey(key_val_store, "key2", "val2");
        addKey(key_val_store, "key3", "val3");
    });

    std::thread t2([&key_val_store](){
        addKey(key_val_store, "key2", "val22");
        addKey(key_val_store, "key3", "val33");
        removeKey(key_val_store, "key1");   // evict key1 from store
    });

    t1.join();
    t2.join();

    printKeyValues(key_val_store, {"key1", "key2", "key3"});

    addKey(key_val_store, "key4", "val4");  // this should evict key1 from policy
    addKey(key_val_store, "key5", "val5");  // this should evict key2 from policy and store 

    printKeyValues(key_val_store, {"key2", "key3", "key4", "key5"});
}